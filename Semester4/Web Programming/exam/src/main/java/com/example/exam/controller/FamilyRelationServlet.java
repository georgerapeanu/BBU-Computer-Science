package com.example.exam.controller;

import com.example.exam.repository.MonolithicRepository;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;

@WebServlet(name="familyRelationServlet", value="/familyRelation")
public class FamilyRelationServlet extends HttpServlet{
    MonolithicRepository repository;

    public FamilyRelationServlet() {
        super();
        repository = MonolithicRepository.getInstance();
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.getRequestDispatcher("addFamilyRelation.jsp").include(req, resp);
    }

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String username = req.getParameter("username");
        String mother = req.getParameter("mother");
        String father = req.getParameter("father");
        if(username == null) {
            req.setAttribute("error", "Username is required");
            req.getRequestDispatcher("addFamilyRelation.jsp").include(req, resp);
            return ;
        }
        if(mother == null) {
            mother = "";
        }
        if(father == null) {
            father = "";
        }
        repository.addRecord(username, mother, father);
        resp.sendRedirect("/");
    }


}
