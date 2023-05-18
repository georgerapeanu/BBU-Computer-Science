package com.example.lab9.controller;

import com.example.lab9.exceptions.AppException;
import com.example.lab9.model.User;
import com.example.lab9.repository.Database;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.Date;
import java.util.Objects;

@WebServlet(name = "editServlet", value = "/edit-profile")
public class EditProfileServlet extends HttpServlet {
    Database db;
    public EditProfileServlet() {
        super();
        db = Database.getInstance();
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String username = (String) req.getAttribute("user");
        try {
            db.updateUserProfile(
                    req.getParameter("name"),
                    req.getParameter("email"),
                    req.getParameter("imageLink"),
                    Date.valueOf(req.getParameter("dateOfBirth")),
                    req.getParameter("home"),
                    username
            );
            resp.sendRedirect("/");
        } catch (AppException e) {
            req.setAttribute("error", e.toString());
            req.getRequestDispatcher("editProfile.jsp").forward(req, resp);
        }
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String username = (String) req.getAttribute("user");
        User user = db.getUserByUsername(username);
        if(user == null) {
            resp.sendRedirect("/login");
            return ;
        }
        System.out.println(user.getUserProfile().getDateOfBirth());
        req.setAttribute("userProfile", user.getUserProfile());
        req.getRequestDispatcher("editProfile.jsp").forward(req, resp);
    }
}
