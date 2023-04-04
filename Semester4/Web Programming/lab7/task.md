In this lab you will have to develop a server-side web application in PHP. The web application has to manipulate a Mysql database with 1 to 3 tables and should implement the following base operations on these tables: select, insert, delete, update. Also the web application must use AJAX for getting data asynchronously from the web server and the web application should contain at least 5 web pages (client-side html or server-side php).

For the database, you can use the mysql database on www.scs.ubbcluj.ro. On this myql server you have an account, a password and a database, all identical to your username and password on the SCS network.

Please make sure that you avoid sql-injection attacks when working with the database.

Have in mind the user experience when you implement the problem:

    add different validation logic for input fields
    do not force the user to input an ID for an item if he wants to delete/edit/insert it; this should happen automatically (e.g. the user clicks an item from a list, and a page/modal prepopulated with the data for that particular item is opened, where the user can edit it)
    add confirmation when the user deletes/cancels an item
    do a bare minimum CSS that at least aligns the various input fields

Documentation can be found at:
1) http://www.cs.ubbcluj.ro/~forest/wp
2) http://www.php.net/manual/en
3) http://www.w3schools.com/php
4) http://www.w3schools.com/ajax 

Write a web application for managing log reports. The log reports are registered (added) by users to a database repository. A log report has several attributes: type, severity (i.e. debug, warning, notice, error, critical etc.), a date, a user who created the log and the log itself (message text). A user must have the posibility to view log reports added by him/her, all log reports, logs of a specific type or severity (use AJAX for this). Also a user can delete his/her own log report. Log browsing should be paged - logs are displayed on pages with maximum 4 logs on a page (you should be able to go to the previous and the next page).
