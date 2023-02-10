
if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_Tables

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tables

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_TestRuns

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_TestRuns

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tests

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Tests

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_Views

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)

ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Views

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[Tables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [Tables]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [TestRunTables]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [TestRunViews]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[TestRuns]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [TestRuns]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[TestTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [TestTables]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[TestViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [TestViews]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[Tests]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [Tests]

GO



if exists (select * from dbo.sysobjects where id = object_id(N'[Views]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)

drop table [Views]

GO



CREATE TABLE [Tables] (

	[TableID] [int] IDENTITY (1, 1) NOT NULL ,

	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [TestRunTables] (

	[TestRunID] [int] NOT NULL ,

	[TableID] [int] NOT NULL ,

	[StartAt] [datetime] NOT NULL ,

	[EndAt] [datetime] NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [TestRunViews] (

	[TestRunID] [int] NOT NULL ,

	[ViewID] [int] NOT NULL ,

	[StartAt] [datetime] NOT NULL ,

	[EndAt] [datetime] NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [TestRuns] (

	[TestRunID] [int] IDENTITY (1, 1) NOT NULL ,

	[Description] [nvarchar] (2000) COLLATE SQL_Latin1_General_CP1_CI_AS NULL ,

	[StartAt] [datetime] NULL ,

	[EndAt] [datetime] NULL 

) ON [PRIMARY]

GO



CREATE TABLE [TestTables] (

	[TestID] [int] NOT NULL ,

	[TableID] [int] NOT NULL ,

	[NoOfRows] [int] NOT NULL ,

	[Position] [int] NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [TestViews] (

	[TestID] [int] NOT NULL ,

	[ViewID] [int] NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [Tests] (

	[TestID] [int] IDENTITY (1, 1) NOT NULL ,

	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 

) ON [PRIMARY]

GO



CREATE TABLE [Views] (

	[ViewID] [int] IDENTITY (1, 1) NOT NULL ,

	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 

) ON [PRIMARY]

GO



ALTER TABLE [Tables] WITH NOCHECK ADD 

	CONSTRAINT [PK_Tables] PRIMARY KEY  CLUSTERED 

	(

		[TableID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestRunTables] WITH NOCHECK ADD 

	CONSTRAINT [PK_TestRunTables] PRIMARY KEY  CLUSTERED 

	(

		[TestRunID],

		[TableID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestRunViews] WITH NOCHECK ADD 

	CONSTRAINT [PK_TestRunViews] PRIMARY KEY  CLUSTERED 

	(

		[TestRunID],

		[ViewID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestRuns] WITH NOCHECK ADD 

	CONSTRAINT [PK_TestRuns] PRIMARY KEY  CLUSTERED 

	(

		[TestRunID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestTables] WITH NOCHECK ADD 

	CONSTRAINT [PK_TestTables] PRIMARY KEY  CLUSTERED 

	(

		[TestID],

		[TableID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestViews] WITH NOCHECK ADD 

	CONSTRAINT [PK_TestViews] PRIMARY KEY  CLUSTERED 

	(

		[TestID],

		[ViewID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [Tests] WITH NOCHECK ADD 

	CONSTRAINT [PK_Tests] PRIMARY KEY  CLUSTERED 

	(

		[TestID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [Views] WITH NOCHECK ADD 

	CONSTRAINT [PK_Views] PRIMARY KEY  CLUSTERED 

	(

		[ViewID]

	)  ON [PRIMARY] 

GO



ALTER TABLE [TestRunTables] ADD 

	CONSTRAINT [FK_TestRunTables_Tables] FOREIGN KEY 

	(

		[TableID]

	) REFERENCES [Tables] (

		[TableID]

	) ON DELETE CASCADE  ON UPDATE CASCADE ,

	CONSTRAINT [FK_TestRunTables_TestRuns] FOREIGN KEY 

	(

		[TestRunID]

	) REFERENCES [TestRuns] (

		[TestRunID]

	) ON DELETE CASCADE  ON UPDATE CASCADE 

GO



ALTER TABLE [TestRunViews] ADD 

	CONSTRAINT [FK_TestRunViews_TestRuns] FOREIGN KEY 

	(

		[TestRunID]

	) REFERENCES [TestRuns] (

		[TestRunID]

	) ON DELETE CASCADE  ON UPDATE CASCADE ,

	CONSTRAINT [FK_TestRunViews_Views] FOREIGN KEY 

	(

		[ViewID]

	) REFERENCES [Views] (

		[ViewID]

	) ON DELETE CASCADE  ON UPDATE CASCADE 

GO



ALTER TABLE [TestTables] ADD 

	CONSTRAINT [FK_TestTables_Tables] FOREIGN KEY 

	(

		[TableID]

	) REFERENCES [Tables] (

		[TableID]

	) ON DELETE CASCADE  ON UPDATE CASCADE ,

	CONSTRAINT [FK_TestTables_Tests] FOREIGN KEY 

	(

		[TestID]

	) REFERENCES [Tests] (

		[TestID]

	) ON DELETE CASCADE  ON UPDATE CASCADE 

GO



ALTER TABLE [TestViews] ADD 

	CONSTRAINT [FK_TestViews_Tests] FOREIGN KEY 

	(

		[TestID]

	) REFERENCES [Tests] (

		[TestID]

	),

	CONSTRAINT [FK_TestViews_Views] FOREIGN KEY 

	(

		[ViewID]

	) REFERENCES [Views] (

		[ViewID]

	)

GO




---------------LAB4


CREATE PROCEDURE addToTables (@tableName VARCHAR(255)) AS
	IF @tableName NOT IN (SELECT TABLE_NAME  FROM INFORMATION_SCHEMA.TABLES) BEGIN
		PRINT 'Table doesn''t exist'
		RETURN 
	END
	IF @tableName IN (SELECT Name FROM Tables) BEGIN
		PRINT 'Table already in Tables'
		RETURN 
	END
	INSERT INTO Tables(Name) Values (@tableName);



CREATE PROCEDURE addToViews(@viewName VARCHAR(255)) AS 
	IF @viewName NOT IN (SELECT TABLE_NAME FROM INFORMATION_SCHEMA.VIEWS) BEGIN
		PRINT 'View doesn''t exist'
		RETURN 
	END
	IF @viewName IN (SELECT Name FROM Views) BEGIN
		PRINT 'View already in views'
		RETURN 
	END
	INSERT INTO Views(Name) Values (@viewName);



CREATE PROCEDURE addToTests(@testName VARCHAR(255)) AS 
	IF @testName IN (SELECT Name FROM Tests) BEGIN
		PRINT 'Test already in tests'
		RETURN 
	END
	INSERT INTO Tests(Name) Values (@testName);



CREATE PROCEDURE connectTableToTest(@tableName VARCHAR(255), @testName VARCHAR(255), @rows INT, @pos INT) AS
	IF @tableName NOT IN (SELECT Name FROM Tables) BEGIN
		PRINT 'Table not in Tables'
		RETURN 
	END
	IF @testName NOT IN (SELECT Name FROM Tests) BEGIN
		PRINT 'Test not in tests'
		RETURN 
	END 
	DECLARE @tableId int
	DECLARE @testId int
	SET @tableId = (SELECT TableID FROM Tables WHERE Name=@tableName)
	SET @testId = (SELECT TestID FROM Tests WHERE Name=@testName)
	IF EXISTS(SELECT * FROM TestTables WHERE TestId=@testId AND TableId=@tableId) BEGIN 
		PRINT 'TestTable connection already exists'
	END
	
	INSERT INTO TestTables VALUES(@testId, @tableId, @rows, @pos);
	

CREATE PROCEDURE connectViewToTest(@viewName VARCHAR(255), @testName VARCHAR(255)) AS
	IF @viewName NOT IN (SELECT Name FROM Views) BEGIN
		PRINT 'Table not in Tables'
		RETURN 
	END
	IF @testName NOT IN (SELECT Name FROM Tests) BEGIN
		PRINT 'Test not in tests'
		RETURN 
	END 
	DECLARE @viewId int
	DECLARE @testId int
	SET @viewId = (SELECT ViewID FROM Views WHERE Name=@viewName)
	SET @testId = (SELECT TestID FROM Tests WHERE Name=@testName)
	IF EXISTS(SELECT * FROM TestViews WHERE TestId=@testId AND ViewID=@viewId) BEGIN 
		PRINT 'TestView connection already exists'
	END
	
	INSERT INTO TestViews  VALUES(@testId, @viewId);
	


CREATE PROCEDURE runTest(@testName VARCHAR(255), @description VARCHAR(255)) AS
	IF @testName NOT IN (SELECT Name FROM TESTS) BEGIN
		PRINT 'test not in Tests'
		RETURN
	END
	
	
	DECLARE @testStartTime DATETIME2
	DECLARE @testRunId INT
	DECLARE @tableId INT
	DECLARE @table VARCHAR(255)
	DECLARE @rows INT
	DECLARE @pos INT
	DECLARE @command VARCHAR(255)
	DECLARE @tableInsertStartTime DATETIME2
	DECLARE @tableInsertEndTime DATETIME2
	DECLARE @testId INT
	DECLARE @view VARCHAR(255)
	DECLARE @viewId INT
	DECLARE @viewStartTime DATETIME2
	DECLARE @viewEndTime DATETIME2
	
	SET @testId = (SELECT TestId FROM Tests T WHERE T.Name = @testName)
	
	DECLARE tableCursor CURSOR SCROLL FOR 
		SELECT T1.Name, T1.TableId, T2.NoOfRows, T2.Position
		FROM Tables T1 INNER JOIN TestTables T2 ON T1.TableID = T2.TableID
		WHERE T2.TestID = @testId
		ORDER BY T2.Position ASC
	
	DECLARE viewCursor CURSOR SCROLL FOR 
		SELECT V.Name, V.ViewId
		FROM Views V INNER JOIN TestViews TV ON V.ViewID = TV.ViewID 
		WHERE TV.TestID = @testId
	
	
	SET @testStartTime = sysdatetime()
	
	INSERT INTO TestRuns(Description, StartAt, EndAt) VALUES(@description, @testStartTime, @testStartTime)
	SET @testRunId = SCOPE_IDENTITY()
	
	OPEN tableCursor
	FETCH FIRST FROM tableCursor INTO @table, @tableId, @rows, @pos
	
	WHILE @@FETCH_STATUS = 0 BEGIN
		EXEC ('DELETE FROM ' + @table)
		FETCH tableCursor INTO @table, @tableId, @rows, @pos
	END
	
	FETCH LAST FROM tableCursor INTO @table, @tableId, @rows, @pos

	WHILE @@FETCH_STATUS = 0 BEGIN
		SET @command = 'populateTable' + @table
		IF @rows > 0 AND @command NOT IN (SELECT ROUTINE_NAME FROM INFORMATION_SCHEMA.ROUTINES) BEGIN
			PRINT @command + 'does not exist'
			RETURN
		END
		SET @tableInsertStartTime = sysdatetime()
		IF @rows > 0 BEGIN
			EXEC @command @rows
		END
		SET @tableInsertEndTime = sysdatetime()
		INSERT INTO TestRunTables VALUES(@testRunId, @tableId, @tableInsertStartTime, @tableInsertEndTime)
		FETCH PRIOR FROM tableCursor INTO @table, @tableId, @rows, @pos
	END
	CLOSE tableCursor
	DEALLOCATE tableCursor 
	
	OPEN viewCursor
	FETCH viewCursor INTO @view, @viewId
	
	WHILE @@FETCH_STATUS = 0 BEGIN
		SET @viewStartTime = sysdatetime()
		EXEC ('SELECT * FROM ' + @view)
		SET @viewEndTime = sysdatetime()
		INSERT INTO TestRunViews VALUES(@testRunID, @viewId, @viewStartTime, @viewEndTime)
		FETCH viewCursor INTO @view, @viewId	
	END
	CLOSE viewCursor 
	DEALLOCATE viewCursor
	UPDATE TestRuns 
	SET EndAt = sysdatetime()
	WHERE TestRunID = @testRunId;


--TEST 1


CREATE VIEW CATEGORIES_VIEW AS
	SELECT * FROM CATEGORIES;



CREATE PROCEDURE populateTableCategories (@rows INT) AS
	WHILE @rows > 0 BEGIN 
		INSERT INTO CATEGORIES VALUES('test_' + CONVERT(VARCHAR(255), @rows))
		SET @rows = @rows - 1
	END;

EXEC addToTables 'CATEGORIES';
EXEC addToViews 'CATEGORIES_VIEW';
EXEC addToTests 'CATEGORIES_TEST';
EXEC connectTableToTest 'CATEGORIES', 'CATEGORIES_TEST', 10000, 1;
EXEC connectViewToTest 'CATEGORIES_VIEW', 'CATEGORIES_TEST';


EXEC runTest 'CATEGORIES_TEST', 'TEST1';

--TEST 2





CREATE VIEW POST_COMMENTS_VIEW AS
	SELECT p.text AS POST_TEXT, c.text AS COMMENT_TEXT
	FROM POSTS p INNER JOIN COMMENTS c ON p.id = c.postId;

CREATE PROCEDURE populateTablePOSTS (@rows INT) AS
	DECLARE @userId INT
	SET @userId = (SELECT TOP 1 id FROM USERS)
	WHILE @rows > 0 BEGIN 
		INSERT INTO POSTS VALUES(@rows, @userId, 'test_' + CONVERT(VARCHAR(255), @rows))
		SET @rows = @rows - 1
	END;

CREATE PROCEDURE populateTableCOMMENTS (@rows INT) AS
	DECLARE @userId INT
	DECLARE @postId INT
	SET @userId = (SELECT TOP 1 id FROM USERS)
	SET @postId = (SELECT TOP 1 id FROM POSTS)
	WHILE @rows > 0 BEGIN 
		INSERT INTO COMMENTS VALUES(@rows, @postId, @userId, 'test_' + CONVERT(VARCHAR(255), @rows))
		SET @rows = @rows - 1
	END;

EXEC addToTests 'TEST2';
EXEC addToTables 'POSTS';
EXEC addToTables 'COMMENTS';
EXEC addToTables 'USER_POST_LIKES';
EXEC addToTables 'USER_COMMENT_LIKES';
EXEC addToViews 'POST_COMMENTS_VIEW' ;
EXEC connectTableToTest 'USER_COMMENT_LIKES', 'TEST2', 0, 1;
EXEC connectTableToTest 'USER_POST_LIKES', 'TEST2', 0, 2;
EXEC connectTableToTest 'COMMENTS', 'TEST2', 5000, 3;
EXEC connectTableToTest 'POSTS', 'TEST2', 2000, 4;
EXEC connectViewToTest 'POST_COMMENTS_VIEW', 'TEST2';


EXEC runTest 'TEST2', 'test2'; 

--TEST 3

CREATE VIEW POST_CATEGORIES_COUNT_VIEW AS
	SELECT p.id, COUNT(*) AS CATEGORY_COUNT
	FROM POSTS p INNER JOIN CATEGORY_POST cp  ON p.id = cp.postId
	GROUP BY p.id;


CREATE PROCEDURE populateTableCATEGORY_POST(@rows INT) AS
	IF @rows > (SELECT COUNT(*) FROM CATEGORIES) * (SELECT COUNT(*) FROM POSTS) BEGIN
		print 'Too many entities requested'	
	END
	DECLARE populateCursor CURSOR SCROLL FOR
		SELECT c.name, p.id
		FROM POSTS p CROSS JOIN CATEGORIES c
	DECLARE @postId INT
	DECLARE @categoryName VARCHAR(255)
	
	OPEN populateCursor
	WHILE @rows > 0 BEGIN 
		FETCH FROM populateCursor INTO @categoryName, @postId
		INSERT INTO CATEGORY_POST VALUES(@categoryName, @postId)
		SET @rows = @rows - 1
	END
	CLOSE populateCursor
	DEALLOCATE populateCursor;
	
EXEC addToTests 'TEST3';
EXEC addToTables 'POSTS';
EXEC addToTables 'COMMENTS';
EXEC addToTables 'USER_POST_LIKES';
EXEC addToTables 'USER_COMMENT_LIKES'; 
EXEC addToTables 'CATEGORIES';
EXEC addToTables 'CATEGORY_POST';
EXEC addToViews 'POST_CATEGORIES_COUNT_VIEW';
EXEC connectTableToTest 'USER_COMMENT_LIKES', 'TEST3', 0, 1;
EXEC connectTableToTest 'USER_POST_LIKES', 'TEST3', 0, 2;
EXEC connectTableToTest 'COMMENTS', 'TEST3', 5000, 3;
EXEC connectTableToTest 'CATEGORY_POST', 'TEST3', 2000, 4;
EXEC connectTableToTest 'POSTS', 'TEST3', 2000, 5;
EXEC connectTableToTest 'CATEGORIES', 'TEST3', 2000, 6;
EXEC connectViewToTest 'POST_CATEGORIES_COUNT_VIEW', 'TEST3';

EXEC runTest 'TEST3', 'test3';
