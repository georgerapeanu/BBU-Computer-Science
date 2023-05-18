package com.example.lab9.controller;

import com.example.lab9.model.User;
import com.example.lab9.repository.Database;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;

@WebServlet(name="loginServlet", value="/login")
public class LoginServlet extends HttpServlet{
    Database db;
    public LoginServlet() {
        super();
        db = Database.getInstance();
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.getRequestDispatcher("login.jsp").forward(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        if(username == null || password == null) {
            req.setAttribute("error", "Username or password invalid");
            req.getRequestDispatcher("login.jsp").forward(req, resp);
            return ;
        }
        User user = db.getUserByCredentials(username, password);
        if(user == null) {
            req.setAttribute("error", "Username or password invalid");
            req.getRequestDispatcher("login.jsp").forward(req, resp);
        } else {
            resp.addCookie(new Cookie("user", user.getUsername()));
            resp.sendRedirect("/");
        }
    }
}
