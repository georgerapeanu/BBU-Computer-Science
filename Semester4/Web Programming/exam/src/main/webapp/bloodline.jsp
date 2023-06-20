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
<h2>Father bloodline(displayed as such: user's father, user's grandfather, ...)</h2>
<%
  List<String> bloodline = (List<String>) request.getAttribute("father_bloodline");
  if(bloodline != null) {
%>
  <ul>
<%
    for(String user: bloodline) {
%>
<li>
  <%=user%>
</li>
<%
    }
%>
  </ul>
  <%
  }
%>
<h2>Mother bloodline(displayed as such: user's mother, user's grandmother, ...)</h2>
<%
  bloodline = (List<String>) request.getAttribute("mother_bloodline");
  if(bloodline != null) {
%>
<ul>
  <%
    for(String user: bloodline) {
  %>
  <li>
    <%=user%>
  </li>
  <%
    }
  %>
</ul>
<%
  }
%>

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