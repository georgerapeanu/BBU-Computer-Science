SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED 
--SET TRANSACTION ISOLATION LEVEL REPEATABLE READ --solution

BEGIN TRAN
	UPDATE USERS SET name='test_user_updated' WHERE name='test_user'
	EXEC sp_log_changes 'test_user', 'test_user_updated', 'Non repeatable reads 2: update', null 
	EXEC sp_log_locks 'Non repeatable reads 2: Locks after updating'  
COMMIT TRAN

