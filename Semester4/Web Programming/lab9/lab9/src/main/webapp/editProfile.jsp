<%@ page import="com.example.lab9.model.User" %>
<%@ page import="com.example.lab9.model.UserProfile" %><%--
  Created by IntelliJ IDEA.
  User: georgerapeanu
  Date: 17.05.2023
  Time: 18:25
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<body>
<%UserProfile userProfile = (UserProfile) request.getAttribute("userProfile");%>
<h2>Edit profile <% if(userProfile != null) out.println(userProfile.getUsername()); %></h2>
<form action="edit-profile" method="post">
  <label>
    Name:
    <input name="name" type="text" value="<% if(userProfile != null && userProfile.getName() != null) out.println(userProfile.getName()); %>"/>
  </label>
  <br/>
  <label>
    Email:
    <input name="email" type="text" value="<% if(userProfile != null && userProfile.getEmail() != null) out.println(userProfile.getEmail()); %>"/>
  </label>
  <br/>
  <label>
    Image link:
    <input name="imageLink" type="text" value="<% if(userProfile != null && userProfile.getImageLink() != null) out.println(userProfile.getImageLink()); %>"/>
  </label>
  <br/>
  <label>
    Date of birth:
    <input name="dateOfBirth" type="date" value="<% if(userProfile != null && userProfile.getDateOfBirth() != null) out.println(userProfile.getDateOfBirth()); %>"/>
  </label>
  <br/>
  <label>
    Home:
    <input name="home" type="text" value="<% if(userProfile != null && userProfile.getHome() != null) out.println(userProfile.getHome()); %>"/>
  </label>
  <br/>
  <button type="submit">Submit</button>
  <%
    String error = (String) request.getAttribute("error");
    if(error != null) {
      out.print(error);
      out.print("<br/>");
    }
  %>
</form>
</body>
</html>
