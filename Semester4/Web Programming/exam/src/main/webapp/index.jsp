<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<!DOCTYPE html>
<html>
<head>
    <title>JSP - Hello World</title>
</head>
<body>
<form method="get" action="/logout">
    <button type="submit">Logout</button>
</form>
<form method="get" action="/familyRelation">
    <button type="submit">Add family relation</button>
</form>
<form method="get" action="/siblings">
    <button type="submit">Siblings</button>
</form>
<form method="get" action="/bloodline">
    <button type="submit">Bloodline</button>
</form>
Succesfully logged in as <%= request.getAttribute("user") %>
</body>
</html>