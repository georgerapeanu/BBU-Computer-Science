<%--
  Created by IntelliJ IDEA.
  User: georgerapeanu
  Date: 17.05.2023
  Time: 19:13
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>
<h2>Register</h2>
<form action="register" method="post">
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
  <button type="submit">Register</button>
  <button type="button" onclick="window.location='/Login'">Login instead</button>
</form>
</body>
</html>
