/*CREATE TABLE USERS (
	id INT NOT NULL,
	name VARCHAR(255) NOT NULL,
	PRIMARY KEY (id)
)


CREATE TABLE POSTS (
	id INT NOT NULL,
	userId INT NOT NULL,
	text VARCHAR(255) NOT NULL,
	PRIMARY KEY (id),
	CONSTRAINT FK_POSTS_USER_ID
		FOREIGN KEY (userId) 
		REFERENCES USERS(id)
		ON DELETE CASCADE
)

CREATE TABLE COMMENTS (
	id INT NOT NULL,
	postId INT NOT NULL,
	userId INT NOT NULL,
	text VARCHAR(255) NOT NULL,
	PRIMARY KEY (id),

	CONSTRAINT FK_COMMENTS_USER_ID
		FOREIGN KEY (userId) 
		REFERENCES USERS(id)
		ON DELETE NO ACTION,
		
	CONSTRAINT FK_COMMENTS_POST_ID
		FOREIGN KEY (postId) 
		REFERENCES POSTS(id)
		ON DELETE CASCADE
)

CREATE TABLE STORIES (
	id INT NOT NULL,
	userId INT NOT NULL,
	contentLink VARCHAR(255) NOT NULL,
	PRIMARY KEY (id),
	CONSTRAINT FK_STORIES_USER_ID
		FOREIGN KEY (userId) 
		REFERENCES USERS(id)
		ON DELETE CASCADE
)

CREATE TABLE CATEGORIES (
	name VARCHAR(255) NOT NULL,
	PRIMARY KEY (name)
)

CREATE TABLE CATEGORY_POST (
	categoryName VARCHAR(255) NOT NULL,
	postId INT NOT NULL,
	PRIMARY KEY(categoryName, postId),
		
	CONSTRAINT FK_CATEGORY_POST_NAME
		FOREIGN KEY (categoryName) 
		REFERENCES CATEGORIES(name)
		ON DELETE CASCADE,
		
	CONSTRAINT FK_CATEGORY_POST_POST_ID
		FOREIGN KEY (postId) 
		REFERENCES POSTS(id)
		ON DELETE CASCADE
)

CREATE TABLE PRIVILEDGES (
	id INT NOT NULL,
	isAdmin BIT NOT NULL,
	isModerator BIT NOT NULL,
	PRIMARY KEY (id),
		CONSTRAINT FK_PRIVILEDGES_USER_ID
		FOREIGN KEY (Id) 
		REFERENCES USERS(id)
		ON DELETE CASCADE,
)

CREATE TABLE CONNECTIONS (
	firstUserId INT NOT NULL,
	secondUserId INT NOT NULL,
	PRIMARY KEY(firstUserId, secondUserId),
	CONSTRAINT FK_CONNECTIONS_FIRST_USER_ID
		FOREIGN KEY (firstUserId) 
		REFERENCES USERS(id),
	CONSTRAINT FK_CONNECTIONS_SECOND_USER_ID
		FOREIGN KEY (secondUserId) 
		REFERENCES USERS(id)
)

CREATE TABLE USER_COMMENT_LIKES (
	userId INT NOT NULL,
	commentId INT NOT NULL,
	PRIMARY KEY(userId, commentId),
	
	CONSTRAINT FK_USER_COMMENT_LIKES_USER_ID
		FOREIGN KEY (userId) 
		REFERENCES USERS(id),
		
	CONSTRAINT FK_USER_COMMENT_LIKES_COMMENT_ID
		FOREIGN KEY (commentId) 
		REFERENCES COMMENTS(id)
)

CREATE TABLE USER_POST_LIKES (
	userId INT NOT NULL,
	postId INT NOT NULL,
	PRIMARY KEY(userId, postId),
	CONSTRAINT FK_USER_POST_LIKES_USER_ID
		FOREIGN KEY (userId) 
		REFERENCES USERS(id),
		
	CONSTRAINT FK_USER_POST_LIKES_POST_ID
		FOREIGN KEY (postId) 
		REFERENCES POSTS(id)
)



INSERT INTO USERS(USERS.id, USERS.name) VALUES (1, 'USER1');
INSERT INTO USERS(id, name) VALUES (2, 'USER2');
INSERT INTO USERS(id, name) VALUES (3, 'USER3');
INSERT INTO USERS(id, name) VALUES (4, 'USER4');
INSERT INTO USERS(id, name) VALUES (5, 'USER5');


INSERT INTO POSTS VALUES (1, 1, 'POST1');
INSERT INTO POSTS VALUES (2, 1, 'POST2');
INSERT INTO POSTS VALUES (3, 2, 'POST3');
INSERT INTO POSTS VALUES (4, 5, 'POST4');
INSERT INTO POSTS VALUES (2, 7, 'ERROR_POST2');

INSERT INTO COMMENTS VALUES (1, 1, 1, 'COMMENT1');
INSERT INTO COMMENTS VALUES (2, 1, 2, 'COMMENT2');
INSERT INTO COMMENTS VALUES (3, 2, 2, 'COMMENT3');
INSERT INTO COMMENTS VALUES (4, 2, 2, 'COMMENT4');

INSERT INTO CATEGORIES VALUES ('advertisement');
INSERT INTO CATEGORIES VALUES ('news');
INSERT INTO CATEGORIES VALUES ('normal');

INSERT INTO CATEGORY_POST VALUES ('normal', 1);
INSERT INTO CATEGORY_POST VALUES ('normal', 2);
INSERT INTO CATEGORY_POST VALUES ('news', 2);
INSERT INTO CATEGORY_POST VALUES ('advertisement', 4);
INSERT INTO CATEGORY_POST VALUES ('news', 4);

INSERT INTO CONNECTIONS VALUES (1, 2);
INSERT INTO CONNECTIONS VALUES (2, 3);
INSERT INTO CONNECTIONS VALUES (3, 4);
INSERT INTO CONNECTIONS VALUES (4, 5);

INSERT INTO PRIVILEDGES VALUES (1, 1, 1);
INSERT INTO PRIVILEDGES VALUES (2, 0, 1);
INSERT INTO PRIVILEDGES VALUES (3, 0, 1);
INSERT INTO PRIVILEDGES VALUES (4, 0, 0);
INSERT INTO PRIVILEDGES VALUES (5, 0, 0);

INSERT INTO STORIES VALUES (1, 1, 'story1');
INSERT INTO STORIES VALUES (2, 1, 'story2');
INSERT INTO STORIES VALUES (3, 2, 'none');

INSERT INTO USER_POST_LIKES VALUES(1, 1);
INSERT INTO USER_POST_LIKES VALUES(2, 1);
INSERT INTO USER_POST_LIKES VALUES(3, 1);
INSERT INTO USER_POST_LIKES VALUES(4, 1);
INSERT INTO USER_POST_LIKES VALUES(1, 2);
INSERT INTO USER_POST_LIKES VALUES(2, 2);
INSERT INTO USER_POST_LIKES VALUES(1, 3);
INSERT INTO USER_POST_LIKES VALUES(2, 3);
INSERT INTO USER_POST_LIKES VALUES(3, 3);
INSERT INTO USER_POST_LIKES VALUES(4, 2);
INSERT INTO USER_POST_LIKES VALUES(1, 4);

INSERT INTO USER_COMMENT_LIKES VALUES(1, 3);
INSERT INTO USER_COMMENT_LIKES VALUES(2, 3);
INSERT INTO USER_COMMENT_LIKES VALUES(3, 3);
INSERT INTO USER_COMMENT_LIKES VALUES(4, 2);
INSERT INTO USER_COMMENT_LIKES VALUES(1, 4);
INSERT INTO USER_COMMENT_LIKES VALUES(2, 1);



UPDATE USERS 
SET name = 'UPDATE_USER2'
WHERE id = 2 OR id =1;

UPDATE POSTS 
SET text = 'UPDATE_POST1'
WHERE id = 1 AND id = 2;

UPDATE COMMENTS
SET text = 'UPDATED_COMMENT1'
WHERE text LIKE 'COMMENT_';

DELETE 
FROM USER_COMMENT_LIKES 
WHERE userId IN (2);

DELETE
FROM USER_POST_LIKES 
WHERE userId BETWEEN 1 AND 2
*/


------------------------------------------------------------------a. 2 queries with the union operation; use UNION [ALL] and OR;


/*SElECT userId, postId AS mediaId FROM USER_POST_LIKES upl 
WHERE upl.userId  = 1 OR upl.userId = 2
UNION
SElECT userId, commentId AS mediaId FROM USER_COMMENT_LIKES ucl
WHERE ucl.userId  = 1 OR ucl.userId = 2;*/

/*SElECT userId, id AS contentId FROM POSTS p  
WHERE p.userId  = 1 OR p.userId = 2
UNION ALL
SElECT userId, id AS contentId FROM COMMENTS c  
WHERE c.userId  = 1 OR c.userId = 2;*/


------------------------------------------------------------------b. 2 queries with the intersection operation; use INTERSECT and IN;


/*SELECT userId FROM POSTS p 
INTERSECT
SELECT userID FROM COMMENTS c
WHERE userId IN (2, 4);*/

/*SELECT userId FROM USER_POST_LIKES upl  
INTERSECT
SELECT userID FROM USER_COMMENT_LIKES ucl 
WHERE userId IN (2, 4);*/


------------------------------------------------------------------c. 2 queries with the difference operation; use EXCEPT and NOT IN;


/*SELECT userId FROM POSTS p 
WHERE userId NOT IN (1, 1)
EXCEPT
SELECT userID FROM COMMENTS c
WHERE userId NOT IN (1, 1);*/

/*SELECT userId FROM USER_POST_LIKES upl
WHERE userId NOT IN (1, 1)
EXCEPT
SELECT userID FROM USER_COMMENT_LIKES ucl 
WHERE userId NOT IN (1, 1);*/


------------------------------------------------------------------d. 4 queries with INNER JOIN, LEFT JOIN, RIGHT JOIN, and FULL JOIN (one query per operator); one query will join at least 3 tables, while another one will join at least two many-to-many relationships;

/*SELECT u.id, SUM(like_table.likes) as total_likes
FROM USERS u 
INNER JOIN POSTS p 
ON u.id = p.userId 
INNER JOIN (
	SELECT upl.postId as id, COUNT(*) as likes 
	FROM USER_POST_LIKES upl 
	GROUP BY upl.postId) like_table 
ON like_table.id = p.id
GROUP BY u.id;*/


/*SELECT *
FROM USERS u
LEFT JOIN POSTS p 
on u.id = p.userId 
LEFT JOIN COMMENTS c 
on p.userId = c.postId 
ORDER BY p.text ASC;*/

/*SELECT c.text, u.id 
FROM COMMENTS c
RIGHT JOIN USERS u
on u.id = c.userId
ORDER BY c.text ASC;*/

/*SELECT p.id, p.[text] , c.name 
FROM POSTS p
FULL JOIN CATEGORY_POST cp  
ON cp.postId = p.id 
FULL JOIN CATEGORIES c 
on cp.categoryName = c.name;*/

------------------------------------------------------------------e. 2 queries with the IN operator and a subquery in the WHERE clause; in at least one case, the subquery must include a subquery in its own WHERE clause;
---select all user ids which have at least one like given to a post that isnt theirs

/*SELECT DISTINCT userId 
FROM USER_POST_LIKES upl 
WHERE upl.postId IN (
	SELECT TOP 1 id 
	FROM POSTS p 
	WHERE upl.postId = p.id AND p.userId <> upl.userId
);*/

---select all comments of users which have at least one like given to a post that isnt theirs

/*SELECT id FROM COMMENTS c 
WHERE c.userId IN (
	SELECT DISTINCT userId 
	FROM USER_POST_LIKES upl 
	WHERE upl.postId IN (
		SELECT TOP 1 id 
		FROM POSTS p 
		WHERE upl.postId = p.id AND p.userId <> upl.userId
	)
);*/

------------------------------------------------------------------f. 2 queries with the EXISTS operator and a subquery in the WHERE clause;
---select all user ids which have at least one like given to a post that isnt theirs

/*SELECT DISTINCT userId 
FROM USER_POST_LIKES upl 
WHERE EXISTS (
	SELECT TOP 1 id 
	FROM POSTS p 
	WHERE upl.postId = p.id AND p.userId <> upl.userId
);*/

---select all user ids which have at least one like given to a comment that isnt theirs

/*SELECT DISTINCT userId 
FROM USER_COMMENT_LIKES ucl
WHERE EXISTS (
	SELECT TOP 1 id 
	FROM COMMENTS c 
	WHERE ucl.commentId = c.id AND c.userId <> ucl.userId
);*/



------------------------------------------------------------------g. 2 queries with a subquery in the FROM clause;                         

/*SELECT u.id, t.id as storyId
FROM USERS u INNER JOIN (SELECT * FROM STORIES s WHERE s.contentLink LIKE  '_one') t
ON t.userId = u.id;*/

/*SELECT u.id, SUM(like_table.likes) as total_likes
FROM USERS u 
INNER JOIN POSTS p 
ON u.id = p.userId 
INNER JOIN (
	SELECT upl.postId as id, COUNT(*) as likes 
	FROM USER_POST_LIKES upl 
	GROUP BY upl.postId) like_table 
ON like_table.id = p.id
GROUP BY u.id;*/



------------------------------------------------------------------h. 4 queries with the GROUP BY clause, 3 of which also contain the HAVING clause; 2 of the latter will also have a subquery in the HAVING clause; use the aggregation operators: COUNT, SUM, AVG, MIN, MAX;

/*SELECT upl.postId, COUNT(*)
FROM USER_POST_LIKES upl 
GROUP BY upl.postId;*/

/*SELECT upl.postId, COUNT(*) as likes 
FROM USER_POST_LIKES upl 
GROUP BY upl.postId
HAVING COUNT(*) > 2;*/

--select all posts whith positive likes and at least 2 categories
/*SELECT upl.postId, COUNT(*) as likes
FROM USER_POST_LIKES upl 
GROUP BY upl.postId
HAVING COUNT(*) > 0 AND upl.postId in (
	SELECT cp.postId
	FROM CATEGORY_POST cp 
	GROUP BY cp.postId  
	HAVING COUNT(*) > 1
);*/

-- select all stories of friends and count them for a given user
/*SELECT s.userId, COUNT(*)
FROM STORIES s
GROUP BY s.userId  
HAVING s.userId in (
	SELECT DISTINCT  c.secondUserId 
	FROM CONNECTIONS c 
	WHERE 2 = c.firstUserId 
	UNION 
	SELECT DISTINCT  c.firstUserId 
	FROM CONNECTIONS c 
	WHERE 2 = c.secondUserId 
)*/



------------------------------------------------------------------i. 4 queries using ANY and ALL to introduce a subquery in the WHERE clause (2 queries per operator); rewrite 2 of them with aggregation operators, and the other 2 with IN / [NOT] IN.

/*SELECT id
FROM USERS u
WHERE id = ANY (SELECT DISTINCT userId FROM POSTS p);
--- WHERE id IN (SELECT DISTINCT userId FROM POSTS p);
*/

/*SELECT id
FROM USERS u
WHERE id <> ALL (SELECT DISTINCT userId FROM POSTS p);
--- WHERE id NOT IN (SELECT DISTINCT userId FROM POSTS p);
*/


/*SELECT upl.postId  as likes 
FROM USER_POST_LIKES upl 
GROUP BY upl.postId
HAVING COUNT(*) >= ALL(
	SELECT COUNT(*) as likes 
	FROM USER_POST_LIKES upl2 
	GROUP BY upl2.postId
)*/
--- HAVING COUNT() >= MAX

/*SELECT upl.postId  as likes 
FROM USER_POST_LIKES upl 
GROUP BY upl.postId
HAVING COUNT(*) > ANY(
	SELECT COUNT(*) as likes 
	FROM USER_POST_LIKES upl2 
	GROUP BY upl2.postId
)*/
--- HAVING COUNT > MIN()

------------------------------------------------------------------

/*SELECT COALESCE(comment_likes_table.id, post_likes_table.id) AS userId, (ISNULL(comment_likes_table.comment_likes, 0) + ISNULL(post_likes_table.post_likes, 0)) AS total_likes
FROM (
	SELECT ucl.userId as id, COUNT(ucl.userId) AS comment_likes
	FROM USER_COMMENT_LIKES ucl 
	GROUP BY ucl.userId 
) comment_likes_table
FULL JOIN (
	SELECT upl.userId as id, COUNT(upl.userId) AS post_likes
	FROM USER_POST_LIKES upl
	GROUP BY upl.userId 
) post_likes_table
ON comment_likes_table.id=post_likes_table.id;*/

/*SELECT COALESCE(count_comments_table.id, count_posts_table.id) AS userId, (ISNULL(count_posts_table.count_posts, 0) + ISNULL(count_comments_table.count_comments, 0)) AS total_media
FROM (
	SELECT p.userId as id, COUNT(*) as count_posts
	FROM POSTS p 
	GROUP BY p.userId
) count_posts_table
FULL JOIN (
	SELECT c.userId as id, COUNT(*) as count_comments
	FROM COMMENTS c 
	GROUP BY c.userId
) count_comments_table
ON count_posts_table.id = count_comments_table.id;*/

/*SELECT post_category_likes_table.category_name, (CONVERT(float, SUM(post_category_likes_table.likes)) / COUNT(*)) AS average_likes_per_category
FROM (
	SELECT cp.categoryName AS category_name, like_table.likes AS likes
	FROM CATEGORY_POST cp 	
	INNER JOIN (
		SELECT upl.postId AS postId, COUNT(*) AS likes
		FROM USER_POST_LIKES upl 
		GROUP BY upl.postId 
	) like_table
	ON cp.postId = like_table.postId
) post_category_likes_table
GROUP BY post_category_likes_table.category_name;*/


----------------------------------------------------- lab3

/*CREATE PROCEDURE changePriviledgesIsModeratorTinyInt AS
	ALTER TABLE PRIVILEDGES ALTER COLUMN isModerator TINYINT;
*/

/*CREATE PROCEDURE changePriviledgesIsModeratorBit AS
	ALTER TABLE PRIVILEDGES ALTER COLUMN isModerator BIT;
*/

/*
CREATE PROCEDURE addCountryToUser AS
	ALTER TABLE USERS ADD country VARCHAR(255);
	
CREATE PROCEDURE removeCountryFromUser AS
	ALTER TABLE USERS DROP COLUMN country;
*/

/*
CREATE PROCEDURE addDefaultToPriviledgesIsModerator AS
	ALTER TABLE PRIVILEDGES ADD CONSTRAINT IS_MODERATOR_DEFAULT DEFAULT(0) FOR isModerator;
*/

/*
CREATE PROCEDURE dropDefaultFromPriviledgesIsModerator AS
	ALTER TABLE PRIVILEDGES DROP CONSTRAINT IS_MODERATOR_DEFAULT; 
*/


/*	
CREATE PROCEDURE createBlacklist AS
	CREATE TABLE BLACKLIST(
		userId int NOT NULL,
		banDate date NOT NULL,
		reason VARCHAR(255) NOT NULL,
		CONSTRAINT BLACKLIST_PRIMARY_KEY PRIMARY KEY (userId, banDate) 
	);

CREATE PROCEDURE dropBlacklist AS
	DROP TABLE BLACKLIST;
*/

/*CREATE PROCEDURE addReasonToBlacklistPrimaryKeyConstraint AS
	ALTER TABLE BLACKLIST
		DROP CONSTRAINT BLACKLIST_PRIMARY_KEY
	ALTER TABLE BLACKLIST
		ADD CONSTRAINT BLACKLIST_PRIMARY_KEY PRIMARY KEY (userId, banDate, reason);

CREATE PROCEDURE removeReasonFromBlacklistPrimaryKeyConstraint AS
	ALTER TABLE BLACKLIST
		DROP CONSTRAINT BLACKLIST_PRIMARY_KEY
	ALTER TABLE BLACKLIST
		ADD CONSTRAINT BLACKLIST_PRIMARY_KEY PRIMARY KEY (userId, banDate);
	*/

/*CREATE PROCEDURE addBlacklistForeignKeyConstaint AS
	ALTER TABLE BLACKLIST 
		ADD CONSTRAINT BLACkLIST_USERID_FOREIGN_KEY FOREIGN KEY(userId) REFERENCES USERS(id);
		
CREATE PROCEDURE removeBlacklistForeignKeyConstaint AS
	ALTER TABLE BLACKLIST 
		DROP CONSTRAINT BLACkLIST_USERID_FOREIGN_KEY;*/

/*CREATE PROCEDURE addPostsCandidateKey AS
	ALTER TABLE POSTS 
		ADD CONSTRAINT POSTS_CANDIDATE_KEY UNIQUE (userId, text);
	
CREATE PROCEDURE removePostsCandidateKey AS
	ALTER TABLE POSTS
		DROP CONSTRAINT POSTS_CANDIDATE_KEY;*/

/*
CREATE TABLE VERSION_TABLE(
	version int,
	PRIMARY KEY(version)
);

INSERT INTO VERSION_TABLE VALUES(1);
*/

/*
CREATE TABLE PROCEDURES_TABLE(
	fromVersion INT,
	toVersion INT,
	nameProc VARCHAR(255),
	PRIMARY KEY(fromVersion, toVersion)
);
	
INSERT INTO PROCEDURES_TABLE VALUES (1, 2, 'changePriviledgesIsModeratorTinyInt');
INSERT INTO PROCEDURES_TABLE VALUES (2, 1, 'changePriviledgesIsModeratorBit');
INSERT INTO PROCEDURES_TABLE VALUES (2, 3, 'addCountryToUser');
INSERT INTO PROCEDURES_TABLE VALUES (3, 2, 'removeCountryFromUser');
INSERT INTO PROCEDURES_TABLE VALUES (3, 4, 'addDefaultToPriviledgesIsModerator');
INSERT INTO PROCEDURES_TABLE VALUES (4, 3, 'dropDefaultFromPriviledgesIsModerator');
INSERT INTO PROCEDURES_TABLE VALUES (4, 5, 'createBlacklist');
INSERT INTO PROCEDURES_TABLE VALUES (5, 4, 'dropBlacklist');
INSERT INTO PROCEDURES_TABLE VALUES (5, 6, 'addReasonToBlacklistPrimaryKeyConstraint');
INSERT INTO PROCEDURES_TABLE VALUES (6, 5, 'removeReasonFromBlacklistPrimaryKeyConstraint');
INSERT INTO PROCEDURES_TABLE VALUES (6, 7, 'addBlacklistForeignKeyConstaint');
INSERT INTO PROCEDURES_TABLE VALUES (7, 6, 'removeBlacklistForeignKeyConstaint');
INSERT INTO PROCEDURES_TABLE VALUES (7, 8, 'addPostsCandidateKey');
INSERT INTO PROCEDURES_TABLE VALUES (8, 7, 'removePostsCandidateKey');
*/

/*
CREATE PROCEDURE goToVersion(@newVersion INT) AS
	DECLARE @curr int
	DECLARE @procedureName varchar(255)
	SELECT @curr=version FROM VERSION_TABLE

	IF @newVersion > (SELECT max(toVersion) FROM PROCEDURES_TABLE)
		RAISERROR ('Version does not exist', 10, 1)
	
	IF @newVersion < (SELECT min(fromVersion) FROM PROCEDURES_TABLE)
		RAISERROR ('Version does not exist', 10, 1)
	
	WHILE @curr < @newVersion BEGIN
		SELECT @procedureName=nameProc FROM PROCEDURES_TABLE WHERE @curr=fromVersion AND @curr+1=toVersion
		EXEC (@procedureName)
		SET @curr=@curr+1
		UPDATE VERSION_TABLE SET version=@curr
	END
	
	WHILE @curr > @newVersion BEGIN
		SELECT @procedureName=nameProc FROM PROCEDURES_TABLE WHERE @curr=fromVersion AND @curr-1=toVersion
		EXEC (@procedureName)
		SET @curr=@curr-1
		UPDATE VERSION_TABLE SET version=@curr
	END; 

*/

--EXEC goToVersion 1;


/*
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


*/

---------------LAB4

/*
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
*/

/*
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
*/

/*
CREATE PROCEDURE addToTests(@testName VARCHAR(255)) AS 
	IF @testName IN (SELECT Name FROM Tests) BEGIN
		PRINT 'Test already in tests'
		RETURN 
	END
	INSERT INTO Tests(Name) Values (@testName);
*/


/*CREATE PROCEDURE connectTableToTest(@tableName VARCHAR(255), @testName VARCHAR(255), @rows INT, @pos INT) AS
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
	*/

/*CREATE PROCEDURE connectViewToTest(@viewName VARCHAR(255), @testName VARCHAR(255)) AS
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
	*/


/*CREATE PROCEDURE runTest(@testName VARCHAR(255), @description VARCHAR(255)) AS
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
*/

--TEST 1

/*
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
*/

--EXEC runTest 'CATEGORIES_TEST', 'TEST1';

--TEST 2




/*
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
*/

--EXEC runTest 'TEST2', 'test2'; 

--TEST 3
/*
CREATE VIEW POST_CATEGORIES_COUNT_VIEW AS
	SELECT p.id, COUNT(*) AS CATEGORY_COUNT
	FROM POSTS p INNER JOIN CATEGORY_POST cp  ON p.id = cp.postId
	GROUP BY p.id;
*/

/*CREATE PROCEDURE populateTableCATEGORY_POST(@rows INT) AS
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
*/
--EXEC runTest 'TEST3', 'test3';

/*
CREATE TABLE Ta(
	aid INT NOT NULL,
	a2 INT
);

ALTER TABLE Ta ADD CONSTRAINT Ta_PRIMARY_KEY PRIMARY KEY(aid);
ALTER TABLE Ta ADD CONSTRAINT Ta_UNIQUE_a2 UNIQUE(a2);
*/

/*CREATE TABLE Tb(
	bid INT NOT NULL,
	b2 INT
);

ALTER TABLE Tb ADD CONSTRAINT Tb_PRIMARY_KEY PRIMARY KEY(bid);*/
/*
CREATE TABLE Tc(
	cid INT NOT NULL,
	aid INT NOT NULL,
	bid INT NOT NULL
);

ALTER TABLE Tc ADD CONSTRAINT TC_PRIMARY_KEY PRIMARY KEY(cid);
ALTER TABLE Tc ADD CONSTRAINT TC_FOREIGN_KEY_aid FOREIGN KEY(aid) REFERENCES Ta(aid) ON DELETE CASCADE;
ALTER TABLE Tc ADD CONSTRAINT TC_FOREIGN_KEY_bid FOREIGN KEY(bid) REFERENCES Tb(bid) ON DELETE CASCADE;
*/

/*CREATE PROCEDURE populateTableTa(@rows INT) AS
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
	*/
/*
exec populateTableTa 10000;
exec populateTableTb 10000;
exec populateTableTc 12000;
*/

--CREATE NONCLUSTERED INDEX index1 ON Ta(a2); 
-- Clustered index scan
--SELECT * FROM Ta WHERE aid >= 100;
-- Clustered index seek
--SELECT * FROM Tb WHERE bid = 100;
-- Nonclustered index scan
--SELECT * FROM Ta WHERE a2 >= 0;
-- Nonclustered index seek
--SELECT * FROM Ta WHERE a2 = 14;
-- Key lookup
--SELECT * FROM Ta WHERE aid in (1, 2, 3);

--SELECT * FROM Tb WHERE b2=0;
--CREATE NONCLUSTERED INDEX index2 on Tb(b2);
--SELECT * FROM Tb WHERE b2=0;


--DROP INDEX index1 ON Ta;
--DROP INDEX index2 ON Tb;
/*CREATE OR ALTER VIEW view1 AS 
	SELECT c.bid, SUM(a.a2) AS sumb2
	FROM Tc c INNER JOIN Tb b ON c.bid = b.bid INNER JOIN Ta a ON c.aid = a.aid
	WHERE a.a2 <= 10000 AND b.b2 <= 10000
	GROUP BY c.bid;
*/

--SELECT * FROM view1;
