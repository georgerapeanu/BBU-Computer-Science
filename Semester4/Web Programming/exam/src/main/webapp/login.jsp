<!DOCTYPE html>
<html>
<head>
  <title> Basic frontend login </title>
  <link rel="stylesheet" type="text/css" href="login.css">
</head>
<body>
<h2>Login</h2>
<form method="post" action="/login" class="login-form">
  <p>
    <label>username</label>
    <input type="text" name="username" class="username-input"/>
  </p>
  <p>
    <label>mother</label>
    <input type="text" name="mother" class="mother-input"/>
  </p>
  <p>
    <label>father</label>
    <input type="text" name="father" class="father-input"/>
  </p>
  <p>
    <button type="submit" class="login-button">Submit</button>
  </p>
</form>
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