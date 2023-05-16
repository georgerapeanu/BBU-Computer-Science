BEGIN TRAN
	UPDATE POSTS SET text='test_post_updated2' WHERE id=0
	EXEC sp_log_changes 'test_post', 'test_post_updated2', 'Deadlock 2: after updating1', null
	EXEC sp_log_locks 'Deadlock 2: transaction after-update1'
	WAITFOR DELAY '00:00:10'
	UPDATE USERS SET name='test_user_updated2' WHERE id=0
	EXEC sp_log_changes 'test_user', 'test_user_updated2', 'Deadlock 2: after updating2', null
	EXEC sp_log_locks 'Deadlock 2: transaction after-update2'
COMMIT TRAN

