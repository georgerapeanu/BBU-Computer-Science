EXEC resetTables
DECLARE @userId INT
DECLARE @postId INT
EXEC addRowUsers 'test_user', @userId OUTPUT
EXEC addRowPosts 'test_post', @userId, @postId OUTPUT
EXEC addRowUserPostLikes @userId, @postId

SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED 
--SET TRANSACTION ISOLATION LEVEL READ COMMITTED --solution

BEGIN TRAN
	SELECT * FROM USERS
	EXEC sp_log_changes null, null, 'Dirty reads 1: after reading', null
	EXEC sp_log_locks 'Diry reads 1: First transaction initial after-read'
	WAITFOR DELAY '00:00:10'
	SELECT * FROM USERS
	EXEC sp_log_changes null, null, 'Dirty reads 1: after reading2', null
	WAITFOR DELAY '00:00:10'
	SELECT * FROM USERS
	EXEC sp_log_changes null, null, 'Dirty reads 1: after reading3', null
COMMIT TRAN


