EXEC resetTables
DECLARE @userId INT
DECLARE @postId INT
EXEC addRowUsers 'test_user', @userId OUTPUT
EXEC addRowPosts 'test_post', @userId, @postId OUTPUT
EXEC addRowUserPostLikes @userId, @postId

SET TRANSACTION ISOLATION LEVEL SNAPSHOT 

BEGIN TRAN
	UPDATE POSTS SET text='test_post_updated1' WHERE id=0
	EXEC sp_log_changes 'test_post', 'test_post_updated1', 'Update conflict 1: after updating1', null
	EXEC sp_log_locks 'Update conflict 1: transaction after-update1'
	WAITFOR DELAY '00:00:05'
COMMIT TRAN


