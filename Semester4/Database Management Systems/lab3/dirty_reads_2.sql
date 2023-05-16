SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED 
--SET TRANSACTION ISOLATION LEVEL READ COMMITTED --solution

BEGIN TRAN
	UPDATE USERS SET name='test_user_updated' WHERE name='test_user'
	EXEC sp_log_changes 'test_user', 'test_user_updated', 'Dirty reads 2: update', null 
	EXEC sp_log_locks 'Dirty reads 2: Locks after updating' 
	WAITFOR DELAY '00:00:10'
	UPDATE USERS SET name='test_user_updated2' WHERE name='test_user_updated'
	EXEC sp_log_changes 'test_user_updated', 'test_user_updated2', 'Dirty reads 2: update2', null 
	EXEC sp_log_locks 'Dirty reads 2: Locks after updating2' 
	EXEC sp_log_changes null, null, 'Dirty reads 2: commiting', null 
COMMIT TRAN

