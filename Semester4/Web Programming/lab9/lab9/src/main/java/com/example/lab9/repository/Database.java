package com.example.lab9.repository;

import com.example.lab9.exceptions.AppException;
import jakarta.persistence.*;
import jakarta.persistence.criteria.CriteriaBuilder;
import jakarta.persistence.criteria.CriteriaQuery;
import jakarta.persistence.criteria.Predicate;
import jakarta.persistence.criteria.Root;
import com.example.lab9.model.User;
import com.example.lab9.model.UserProfile;

import java.sql.Date;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class Database {
    private static Database instance;
    private EntityManagerFactory entityManagerFactory;
    private Database() {
        entityManagerFactory = Persistence.createEntityManagerFactory("default");
    }

    public static synchronized Database getInstance() {
        if(instance == null) {
            instance = new Database();
        }
        return instance;
    }

    public User getUserByUsername(String username) {
        EntityManager em = entityManagerFactory.createEntityManager();
        return em.find(User.class, username);
    }
    public User getUserByCredentials(String username, String password) {
        EntityManager em = entityManagerFactory.createEntityManager();
        CriteriaBuilder cb = em.getCriteriaBuilder();
        CriteriaQuery<User> cq = cb.createQuery(User.class);
        Root<User> userRoot = cq.from(User.class);
        cq
                .select(userRoot)
                .where(cb.equal(userRoot.get("username"), username), cb.equal(userRoot.get("password"), password));
        TypedQuery<User> tq = em.createQuery(cq);
        try {
            return tq.getSingleResult();
        } catch(NoResultException exception) {
            return null;
        }
    }

    public List<UserProfile> getUserProfiles(
            String name,
            String email,
            String imageLink,
            Integer age,
            String home,
            String username
    ) {
        EntityManager em = entityManagerFactory.createEntityManager();
        CriteriaBuilder cb = em.getCriteriaBuilder();
        CriteriaQuery<UserProfile> cq = cb.createQuery(UserProfile.class);
        Root<UserProfile> userProfileRoot = cq.from(UserProfile.class);
        cq.select(userProfileRoot);
        List<Predicate> conditions = new ArrayList<>();
        if(name != null) {
            conditions.add(cb.like(userProfileRoot.get("name"), "%" + name + "%"));
        }
        if(email != null) {
            conditions.add(cb.like(userProfileRoot.get("email"), "%" + email + "%"));
        }
        if(imageLink != null) {
            conditions.add(cb.like(userProfileRoot.get("imageLink"), "%" + imageLink + "%"));
        }
        if(age != null) {
            LocalDate currentDate = LocalDate.now();
            LocalDate startDate = currentDate.minusYears(age + 1);
            LocalDate endDate = currentDate.minusYears(age);
            conditions.add(cb.greaterThan(userProfileRoot.get("dateOfBirth"), startDate));
            conditions.add(cb.lessThanOrEqualTo(userProfileRoot.get("dateOfBirth"), endDate));
        }
        if(home != null) {
            conditions.add(cb.like(userProfileRoot.get("home"), "%" + home + "%"));
        }
        if(username != null) {
            conditions.add(cb.like(userProfileRoot.get("username"), "%" + username + "%"));
        }

        Optional<Predicate> condition = conditions.stream().reduce(cb::and);
        condition.ifPresent(cq::where);

        TypedQuery<UserProfile> tq = em.createQuery(cq);
        return tq.getResultList();
    }

    public void addUser(String username, String password) throws AppException {
        EntityManager em = this.entityManagerFactory.createEntityManager();
        EntityTransaction transaction = em.getTransaction();
        transaction.begin();
        if(em.find(User.class, username) != null) {
            transaction.rollback();
            throw new AppException("Username already exists");
        }
        User user = new User(username, password, null);
        UserProfile userProfile = new UserProfile();
        userProfile.setUser(user);
        userProfile.setUsername(username);
        em.persist(user);
        em.persist(userProfile);
        transaction.commit();
    }

    public void updateUserProfile(
            String name,
            String email,
            String imageLink,
            Date dateOfBirth,
            String home,
            String username
    ) throws AppException {
        EntityManager em = this.entityManagerFactory.createEntityManager();
        EntityTransaction transaction = em.getTransaction();
        transaction.begin();
        User user = em.find(User.class, username);
        if(user == null) {
            transaction.rollback();
            throw new AppException("Username not found");
        }
        UserProfile userProfile = em.find(UserProfile.class, username);
        userProfile.setName(name);
        userProfile.setEmail(email);
        userProfile.setImageLink(imageLink);
        userProfile.setDateOfBirth(dateOfBirth);
        userProfile.setHome(home);

        em.persist(userProfile);
        transaction.commit();
    }
}
