package com.example.exam.controller;

import com.example.exam.model.User;
import com.example.exam.repository.MonolithicRepository;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;

@WebServlet(name="loginServlet", value = "/login")
public class LoginServlet extends HttpServlet {
    MonolithicRepository repository;

    public LoginServlet() {
        super();
        repository = MonolithicRepository.getInstance();
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.getRequestDispatcher("login.jsp").include(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String username = req.getParameter("username");
        String mother = req.getParameter("mother");
        String father = req.getParameter("father");
        if(username == null) {
            req.setAttribute("error", "Username is required");
            req.getRequestDispatcher("login.jsp").include(req, resp);
            return ;
        }
        if(mother == null) {
            mother = "";
        }
        if(father == null) {
            father = "";
        }
        User user = repository.getUserByCredentials(username, mother, father);
        if(user == null) {
            req.setAttribute("error", "Invalid credentials");
            req.getRequestDispatcher("login.jsp").include(req, resp);
            return ;
        }
        Cookie authCookie = new Cookie("user", username);
        authCookie.setPath("/");
        resp.addCookie(authCookie);
        resp.sendRedirect("/");
    }
}
