CREATE OR ALTER PROCEDURE addRowUsers (@name VARCHAR(255), @userId INT OUTPUT) AS
	DECLARE @maxId INT
	SET @maxId = 0
	SELECT TOP 1 @maxId = id + 1 FROM USERS ORDER BY id DESC 
	IF (@name IS NULL) 
	BEGIN
		RAISERROR('User name cannot be null', 24, 1)
	END
	INSERT INTO USERS (id, name) VALUES (@maxId, @name)
	SET @userId = @maxId
	EXEC sp_log_changes null, @name, 'Inserted 1 user row', NULL
GO
	
CREATE OR ALTER PROCEDURE addRowPosts (@text VARCHAR(255), @userId INT, @postId INT OUTPUT) AS
	DECLARE @maxId INT
	SET @maxId = 0
	SELECT TOP 1 @maxId = id + 1 FROM POSTS ORDER BY id DESC 
	IF (@text IS NULL) 
	BEGIN
		RAISERROR('Post text cannot be null', 24, 1)
	END
	IF NOT EXISTS (SELECT TOP 1 * FROM USERS WHERE id = @userId)
	BEGIN 
		RAISERROR ('User not found', 24, 1)
	END
	
	INSERT INTO POSTS (id, userId, text) VALUES (@maxId, @userId, @text)
	SET @postId = @maxId
	EXEC sp_log_changes null, @text, 'Inserted 1 post row', NULL
GO

CREATE OR ALTER PROCEDURE addRowUserPostLikes (@userId INT, @postId INT) AS

	IF NOT EXISTS (SELECT TOP 1 * FROM USERS WHERE id = @userId)
	BEGIN 
		RAISERROR ('User not found', 24, 1)
	END

	IF NOT EXISTS (SELECT TOP 1 * FROM POSTS WHERE id = @postId)
	BEGIN 
		RAISERROR ('Post not found', 24, 1)
	END

	INSERT INTO USER_POST_LIKES (userId, postId) VALUES (@userId, @postId)
	DECLARE @newData VARCHAR(255)
	SET @newData = @userId + ' ' + @postId
	EXEC sp_log_changes null, @newData, 'Inserted 1 user-post-lke row', NULL
GO
