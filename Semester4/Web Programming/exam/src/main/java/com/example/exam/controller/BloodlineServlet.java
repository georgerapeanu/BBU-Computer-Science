package com.example.exam.controller;

import com.example.exam.model.User;
import com.example.exam.repository.MonolithicRepository;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

@WebServlet(name="bloodlineServlet", value="/bloodline")
public class BloodlineServlet extends HttpServlet{
    MonolithicRepository repository;

    public BloodlineServlet() {
        super();
        repository = MonolithicRepository.getInstance();
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        User rootUser = repository.findUserByUsername((String)req.getAttribute("user"));
        List<String> father_bloodline = new ArrayList<>();
        List<String> mother_bloodline = new ArrayList<>();

        for(User currentUser = rootUser;currentUser != null;currentUser = repository.findUserByUsername(currentUser.getFamilyRelation().getFather())) {
            father_bloodline.add(currentUser.getFamilyRelation().getFather());
        }

        for(User currentUser = rootUser;currentUser != null;currentUser = repository.findUserByUsername(currentUser.getFamilyRelation().getMother())) {
            mother_bloodline.add(currentUser.getFamilyRelation().getMother());
        }

        req.setAttribute("father_bloodline", father_bloodline);
        req.setAttribute("mother_bloodline", mother_bloodline);
        req.getRequestDispatcher("bloodline.jsp").include(req, resp);
    }

}
