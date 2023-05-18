package com.example.lab9.controller;

import com.example.lab9.exceptions.AppException;
import com.example.lab9.model.User;
import com.example.lab9.repository.Database;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.util.Objects;

@WebServlet(name="registerServlet", value="/register")
public class RegisterServlet extends HttpServlet{
    Database db;
    public RegisterServlet() {
        super();
        db = Database.getInstance();
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.getRequestDispatcher("register.jsp").forward(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String username = req.getParameter("username");
        String password = req.getParameter("password");

        if(username == null || password == null || Objects.equals(username.strip(), "") || Objects.equals(password.strip(), "")) {
            req.setAttribute("error", "Username or password invalid");
            req.getRequestDispatcher("register.jsp").forward(req, resp);
            return ;
        }

        try {
            db.addUser(username, password);
        } catch (AppException e) {
            req.setAttribute("error", e.getMessage());
            req.getRequestDispatcher("register.jsp").forward(req, resp);
        }

        req.getRequestDispatcher("login.jsp").forward(req, resp);
    }
}
