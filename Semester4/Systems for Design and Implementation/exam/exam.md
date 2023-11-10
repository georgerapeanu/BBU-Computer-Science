# Examination Session - 26 June 2023

### 26.06.2023

**Theory exam (`10 minutes`)**: [Click Here](https://forms.gle/K71XUF3tPacHtfdw5)

**Practical exam (`3 hours`):**

You have to write a full stack application that groups of friends can use to choose an activity to do together and the times that they can do it at.

Recall that each functionality is worth **1 snowflake**. Your snowflakes are then converted to **points**. 

Please implement **exactly** what is asked, **nothing more** and **nothing less**. You need to present the functionalities in the order that they are listed in and each one has to be perfectly implemented for you to receive the snowflake for it. 

If something is ambiguous then you are expected to make the best decision according to what was discussed during the lectures and labs. If things are still ambiguous, then any decision will be accepted.

You should have persistence to a database for all added data, so restarting the application should keep the data. You must commit and push everything to the github repository created by accepting the assignment (link on Teams) in order for it to be considered.

1. Display the following table in plain HTML when visiting the `/` route. You do not need to color the rows, but the borders must look like they do here, as does the text:

    |         | **Time 1** | **Time 2** | **Time 3** |
    |---------|----------|----------|----------|
    | **Activity 1** |          |          |          |
    | **Activity 2** |          |          |          |
    
2. Add an `h1` tag above the table with the contents **Decide on an activity together** and a button below with the content **Create vote**.

3. When clicking on the **Create vote** button, you should be redirected to the route `/vote/<GUID>`, where `<GUID>` is a random GUID / UUID. We will call this the **Activity Voting Page**, or `AVP`. Make the `AVP` display the previous `h1` and an `h2` below it with the contents **Give this URL to your friends so that they can vote on the activities and the times that they are available**. Also display the table with all of its contents. Do not display the **Create vote** button.

4. When accessing the `AVP`, if the GUID is valid, there should be a textbox above the table that asks you to enter your name. If you enter a name that has already been entered for this GUID, an error should be displayed. If the GUID is not valid, display the message **Invalid vote ID**.

5. When accessing the `AVP`, each table cell should have an ordered list of all the names that have chosen that activity and time slot. Below the list, there should be your name together with a checkbox allowing you to choose that activity and time slot. These should only appear if you have chosen a valid name for yourself. Changing your name should update the name in the table.

6. Add a **Refresh** button below the table that refreshes the table (but not the page).

7. Save the name in `localstorage` and make it so that it is pre-populated and your choices are shown if you refresh the page. Add a **Back** button below everything else that redirects you to `/`.

8. Dockerize your application. Running the docker container should start the frontend, the backend and anything else that you need. Everything should be started with a single docker or docker-compose command. If you have done this from the start, you will receive the snowflake now.

9. Add `swagger` for your backend. If you have done this from the start, you will receive the snowflake now.

10. Make the entries in the first column of the tables on both the `/` and the `AVP` editable: the contents in the cells should be text boxes. Also, you should be able to add new rows and delete a row. Empty values should not be allowed. You should not be able to delete all rows.

11. Make the entries in the first row of the tables on both the `/` and the `AVP` editable: the contents in the cells should be text boxes. Also, you should be able to add new columns and delete a column. Empty values should not be allowed. You should not be able to delete all columns.

12. On the `AVP`, just below the table, add a paragraph that displays the text: **The winning activity is `<activity>` at `<time>`, voted on by: `<person 1>`, `<person 2>`, ...**. The winning activity and time is defined as the corresponding row and column headers for the cell with the most votes. In case there are multiple ones with the same number of votes, display any one of them. Clicking the **Refresh** button should also refresh this information. You can choose to display this entire data as a single paragraph, or have a list with a list item for each person.
    
13. Make each table cell on the `AVP` have a shade of green as the background color: the more votes, the darker the shade.
    
14. Remove the **Refresh** button. Use web sockets to update the information for all viewers in real time.
    
15. Add filtering: there should be a list of radio buttons below the table on the `AVP`, one for each name that exists for this vote. Selecting one should change the table so that it highlights in light blue only those cells corresponding to the selected name's votes. There should be a **Clear filter** button.

