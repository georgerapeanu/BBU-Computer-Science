package com.example.lab9.controller;

import com.example.lab9.model.UserProfile;
import com.example.lab9.repository.Database;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.util.List;

@WebServlet(name="rootServlet", value="")
public class RootServlet extends HttpServlet {
    Database db;
    public RootServlet() {
        db = Database.getInstance();
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        System.out.println("called");
        Integer age = null;
        try{
            age = Integer.valueOf(req.getParameter("age"));
        } catch(NumberFormatException ignored) {
            ;
        }
        List<UserProfile> userProfiles = db.getUserProfiles(
                req.getParameter("name"),
                req.getParameter("email"),
                req.getParameter("imageLink"),
                age,
                req.getParameter("home"),
                req.getParameter("username")
        );
        System.out.println(userProfiles);
        req.setAttribute("userProfiles", userProfiles);
        req.getRequestDispatcher("main.jsp").forward(req, resp);
    }
}
