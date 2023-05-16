SET TRANSACTION ISOLATION LEVEL REPEATABLE READ 
--SET TRANSACTION ISOLATION LEVEL SERIALIZABLE --solution

BEGIN TRAN
	EXEC addRowUsers "test_user_2", null
	EXEC sp_log_changes null, 'test_user_2', 'Phatom reads 2: insert', null 
	EXEC sp_log_locks 'Non repeatable reads 2: Locks after updating'  
COMMIT TRAN

