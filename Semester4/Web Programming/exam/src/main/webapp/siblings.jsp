<%@ page import="com.example.exam.model.User" %>
<%@ page import="java.util.List" %>
<!DOCTYPE html>
<html>
<head>
  <title> Basic frontend login </title>
</head>
<body>
  <form method="get" action="/">
    <button type="submit">Back</button>
  </form>

  <table>
    <thead>
      <td>Id</td>
      <td>username</td>
    </thead>
    <tbody>
      <%
        List<User> siblings = (List<User>) request.getAttribute("siblings");
        if(siblings != null) {
          for(User sibling: siblings) {
      %>
      <tr>
        <td> <%= sibling.getId() %></td>
        <td> <%= sibling.getUsername() %></td>
      </tr>
      <%
          }
        }
      %>
    </tbody>
  </table>

  <div class="error">
    <%
      String error = (String) request.getAttribute("error");
      if(error != null) {
        out.print(error);
      }
    %>
  </div>
</body>
</html>