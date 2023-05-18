<%--
  Created by IntelliJ IDEA.
  User: georgerapeanu
  Date: 17.05.2023
  Time: 18:25
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<body>
    <h2>Login</h2>
    <form action="login" method="post">
        <label>
            Username:
            <input name="username" type="text"/>
        </label>
        <br/>
        <label>
            Password:
            <input name="password" type="password"/>
        </label>
        <br/>
        <%
            String error = (String) request.getAttribute("error");
            if(error != null) {
                out.print(error);
                out.print("<br/>");
            }
        %>
        <button type="submit">Login</button>
        <button type="button" onclick="window.location='/register'">Register</button>
    </form>
</body>
</html>
