package com.example.app.configs;

import com.example.app.interceptors.AuthInterceptor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.InterceptorRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurer;

/**
 * Configuration class for registering interceptors in the application.
 */
@Configuration
public class InterceptorsConfig implements WebMvcConfigurer {

    /**
     * Creates a new instance of the AuthInterceptor.
     *
     * @return the created AuthInterceptor instance
     */
    @Bean
    public AuthInterceptor authInterceptor() {
        return new AuthInterceptor();
    }

    /**
     * Adds the AuthInterceptor to the InterceptorRegistry with excluded path patterns.
     *
     * @param registry the InterceptorRegistry to which the AuthInterceptor should be added
     */
    @Override
    public void addInterceptors(InterceptorRegistry registry) {
        registry.addInterceptor(authInterceptor())
                .excludePathPatterns("/login")
                .excludePathPatterns("/register")
                .excludePathPatterns("/register/**");
        WebMvcConfigurer.super.addInterceptors(registry);
    }
}
