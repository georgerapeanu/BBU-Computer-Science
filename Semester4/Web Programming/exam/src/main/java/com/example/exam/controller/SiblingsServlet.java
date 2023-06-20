package com.example.exam.controller;

import com.example.exam.repository.MonolithicRepository;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;

@WebServlet(name="siblingsServlet", value="/siblings")
public class SiblingsServlet extends HttpServlet{
    MonolithicRepository repository;

    public SiblingsServlet() {
        super();
        repository = MonolithicRepository.getInstance();
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        req.setAttribute("siblings", repository.getSiblings((String)req.getAttribute("user")));
        req.getRequestDispatcher("siblings.jsp").include(req, resp);
    }

}
