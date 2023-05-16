EXEC resetTables
DECLARE @userId INT
DECLARE @postId INT
EXEC addRowUsers 'test_user', @userId OUTPUT
EXEC addRowPosts 'test_post', @userId, @postId OUTPUT
EXEC addRowUserPostLikes @userId, @postId


BEGIN TRAN
	UPDATE USERS SET name='test_user_updated1' WHERE id=0
	EXEC sp_log_changes 'test_user', 'test_user_updated1', 'Deadlock 1: after updating1', null
	EXEC sp_log_locks 'Deadlock 1: transaction after-update1'
	WAITFOR DELAY '00:00:10'
	UPDATE POSTS SET text='test_post_updated1' WHERE id=0
	EXEC sp_log_changes 'test_post', 'test_post_updated1', 'Deadlock 1: after updating1', null
	EXEC sp_log_locks 'Deadlock 1: transaction after-update1'
COMMIT TRAN


