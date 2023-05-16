SET TRANSACTION ISOLATION LEVEL SNAPSHOT

BEGIN TRAN
	UPDATE POSTS SET text='test_post_updated2' WHERE id=0
	EXEC sp_log_changes 'test_post', 'test_post_updated2', 'Update conflict 2: after updating1', null
	EXEC sp_log_locks 'Update conflict 2: transaction after-update1'
	WAITFOR DELAY '00:00:05'
COMMIT TRAN

