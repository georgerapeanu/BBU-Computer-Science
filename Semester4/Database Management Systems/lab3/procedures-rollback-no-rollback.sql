CREATE OR ALTER PROCEDURE resetTables AS
	DELETE FROM USER_POST_LIKES
	DELETE FROM POSTS
	DELETE FROM USERS
GO

CREATE OR ALTER PROCEDURE rollbackNoFail AS
	BEGIN TRAN
		BEGIN TRY
			DECLARE @userId INT
			DECLARE @postId INT
			EXEC addRowUsers "test_user", @userId OUTPUT
			EXEC addRowPosts "test_post", @userId, @postId OUTPUT
			EXEC addRowUserPostLikes @userId, @postId
		END TRY
		BEGIN CATCH
			ROLLBACK TRAN
			RETURN
		END CATCH
	COMMIT TRAN
GO

CREATE OR ALTER PROCEDURE rollbackFail AS
	BEGIN TRAN
		BEGIN TRY
			DECLARE @userId INT
			DECLARE @postId INT
			EXEC addRowUsers "test_user", @userId OUTPUT
			EXEC addRowPosts null, @userId, @postId OUTPUT
			EXEC addRowUserPostLikes @userId, @posTId
		END TRY
		BEGIN CATCH
			ROLLBACK TRAN
			RETURN
		END CATCH
	COMMIT TRAN
GO

CREATE OR ALTER PROCEDURE noRollbackNoFail AS
	DECLARE @errors INT
	DECLARE @userId INT
	DECLARE @postId INT
	SET @errors = 0
	BEGIN TRY
		EXEC addRowUsers "test_user", @userId OUTPUT
	END TRY
	BEGIN CATCH
		SET @errors = @errors + 1
	END CATCH
	BEGIN TRY
		EXEC addRowPosts "test_post", @userId, @postId OUTPUT
	END TRY
	BEGIN CATCH
		SET @errors = @errors + 1
	END CATCH
		
	IF (@errors = 0)
	BEGIN
		EXEC addRowUserPostLikes @userId, @postId
	END
	
GO

CREATE OR ALTER PROCEDURE noRollbackFail AS
	DECLARE @errors INT
	DECLARE @userId INT
	DECLARE @postId INT
	SET @errors = 0
	BEGIN TRY
		EXEC addRowUsers "test_user", @userId OUTPUT
	END TRY
	BEGIN CATCH
		SET @errors = @errors + 1
	END CATCH
	BEGIN TRY
		EXEC addRowPosts null, @userId, @postId OUTPUT
	END TRY
	BEGIN CATCH
		SET @errors = @errors + 1
	END CATCH
		
	IF (@errors = 0)
	BEGIN
		EXEC addRowUserPostLikes @userId, @postId
	END
	
GO
