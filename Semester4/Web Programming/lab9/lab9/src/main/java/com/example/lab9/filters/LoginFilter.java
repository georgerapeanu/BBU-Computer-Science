package com.example.lab9.filters;

import com.example.lab9.model.User;
import com.example.lab9.repository.Database;
import jakarta.servlet.*;
import jakarta.servlet.annotation.WebFilter;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpFilter;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.util.Arrays;
import java.util.Objects;
import java.util.Optional;

@WebFilter(urlPatterns = "/*")
public class LoginFilter extends HttpFilter {
    @Override
    protected void doFilter(HttpServletRequest req, HttpServletResponse res, FilterChain chain) throws IOException, ServletException {
        if(req.getRequestURI().equals("/login") || req.getRequestURI().equals("/register")) {
            chain.doFilter(req, res);
            return ;
        }
        if(req.getCookies() == null) {
            res.sendRedirect("/login");
            return ;
        }
        Optional<Cookie> cookie = Arrays.stream(req.getCookies()).filter(x -> Objects.equals(x.getName(), "user")).findFirst();
        if(cookie.isEmpty()){
            res.sendRedirect("/login");
            return ;
        }
        req.setAttribute("user", cookie.get().getValue());
        chain.doFilter(req, res);
    }
}
