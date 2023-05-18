<%@ page import="com.example.lab9.model.UserProfile" %>
<%@ page import="java.util.List" %>
<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<!DOCTYPE html>
<html>
<head>
  <title>JSP - Hello World</title>
  <script src="main.js"></script>
</head>
<body>
<button class="edit_button">Edit profile</button>
<button class="logout_button">Logout</button>
<br/>
<form action="/" method="get">
  <label>
    Name:
    <input type="text" name="name"/>
  </label>
  <label>
    Email:
    <input type="text" name="email"/>
  </label>
  <label>
    Image link:
    <input type="text" name="imageLink"/>
  </label>
  <label>
    Age:
    <input type="text" name="age"/>
  </label>
  <label>
    Home:
    <input type="text" name="home"/>
  </label>

  <label>
    Username:
    <input type="text" name="username"/>
  </label>
  <button type="submit">Search</button>
</form>

<table>
  <thead>
    <td>
      Name
    </td>
    <td>
      Email
    </td>
    <td>
      Image
    </td>

    <td>
      Age
    </td>
    <td>
      Home
    </td>
    <td>
      Username
    </td>
  </thead>
  <tbody>
  <%
    List<UserProfile> userProfiles = (List<UserProfile>) request.getAttribute("userProfiles");
    if(userProfiles != null) {
      for(UserProfile userProfile: userProfiles) {
  %>
      <tr>
        <td> <%= userProfile.getName() %> </td>
        <td> <%= userProfile.getEmail() %> </td>
        <td> <img src="<%= userProfile.getImageLink() %>" width="100" height="100"/> </td>
        <td> <%= userProfile.getAge()%></td>
        <td> <%= userProfile.getHome() %> </td>
        <td> <%= userProfile.getUsername() %> </td>
      </tr>
  <%
      }
    }
  %>
  </tbody>
</table>

</body>
</html>