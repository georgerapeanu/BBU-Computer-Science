
CREATE TABLE Ta(
	aid INT NOT NULL,
	a2 INT
);

ALTER TABLE Ta ADD CONSTRAINT Ta_PRIMARY_KEY PRIMARY KEY(aid);
ALTER TABLE Ta ADD CONSTRAINT Ta_UNIQUE_a2 UNIQUE(a2);


CREATE TABLE Tb(
	bid INT NOT NULL,
	b2 INT
);

ALTER TABLE Tb ADD CONSTRAINT Tb_PRIMARY_KEY PRIMARY KEY(bid);

CREATE TABLE Tc(
	cid INT NOT NULL,
	aid INT NOT NULL,
	bid INT NOT NULL
);

ALTER TABLE Tc ADD CONSTRAINT TC_PRIMARY_KEY PRIMARY KEY(cid);
ALTER TABLE Tc ADD CONSTRAINT TC_FOREIGN_KEY_aid FOREIGN KEY(aid) REFERENCES Ta(aid) ON DELETE CASCADE;
ALTER TABLE Tc ADD CONSTRAINT TC_FOREIGN_KEY_bid FOREIGN KEY(bid) REFERENCES Tb(bid) ON DELETE CASCADE;


CREATE PROCEDURE populateTableTa(@rows INT) AS
	while @rows > 0 BEGIN
		INSERT INTO Ta VALUES(@rows, @rows - 20000 / @rows + @rows / 4)
		SET @rows = @rows - 1
	END;
CREATE PROCEDURE populateTableTb(@rows INT) AS
	while @rows > 0 BEGIN
		INSERT INTO Tb VALUES(@rows, @rows - 60000 / @rows + @rows / 2)
		SET @rows = @rows - 1
	END;
CREATE PROCEDURE populateTableTc(@rows INT) AS
	IF @rows > (SELECT COUNT(*) FROM Ta) * (SELECT COUNT(*) FROM Tb) BEGIN
		RAISERROR ('Too many entities requested', 10, 1)
	END
	DECLARE valuesCursor CURSOR LOCAL FOR (
		SELECT a.aid, b.bid
		FROM Ta a CROSS JOIN Tb b
	)
	DECLARE @aid INT
	DECLARE @bid INT
	OPEN valuesCursor
	FETCH valuesCursor INTO @aid, @bid
	while @@FETCH_STATUS = 0 AND @rows > 0 BEGIN
		INSERT INTO Tc VALUES(@rows, @aid, @bid)
		FETCH valuesCursor INTO @aid, @bid	
		SET @rows = @rows - 1
	END
	CLOSE valuesCursor 
	DEALLOCATE valuesCursor;
	

exec populateTableTa 10000;
exec populateTableTb 10000;
exec populateTableTc 12000;


--DROP index1;
--CREATE NONCLUSTERED INDEX index1 ON Ta(a2);
--DROP INDEX index1 on Ta; 
-- Clustered index scan
--SELECT * FROM Ta WHERE aid >= 100; --36ms
-- Clustered index seek
--SELECT * FROM Tb WHERE bid = 100; --29ms
-- Nonclustered index scan
--SELECT * FROM Ta WHERE a2 >= 0; --45ms with 46ms without
-- Nonclustered index seek
--SELECT * FROM Ta WHERE a2 = 14; --40ms with 44ms without
--Key lookup
--SELECT * FROM Ta WHERE aid in (1, 2, 3); --53ms with

--DROP INDEX index2 ON Tb;
--SELECT * FROM Tb WHERE b2=0; --52ms
--CREATE NONCLUSTERED INDEX index2 on Tb(b2);
--SELECT * FROM Tb WHERE b2=0; --33ms


--DROP INDEX index1 ON Ta;
--DROP INDEX index2 ON Tb;
CREATE OR ALTER VIEW view1 AS 
	SELECT c.bid, SUM(a.a2) AS sumb2
	FROM Tc c INNER JOIN Tb b ON c.bid = b.bid INNER JOIN Ta a ON c.aid = a.aid
	WHERE a.a2 <= 10000 AND b.b2 <= 10000
	GROUP BY c.bid;


--SELECT * FROM view1; --152ms
--CREATE NONCLUSTERED INDEX index1 ON Ta(a2);
--CREATE NONCLUSTERED INDEX index2 on Tb(b2);
SELECT * FROM view1; --112ms
