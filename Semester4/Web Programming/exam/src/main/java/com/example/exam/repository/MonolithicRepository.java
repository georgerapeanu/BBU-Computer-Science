package com.example.exam.repository;

import com.example.exam.model.FamilyRelation;
import com.example.exam.model.User;
import jakarta.persistence.*;
import jakarta.persistence.criteria.*;

import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;

public class MonolithicRepository {
    private static MonolithicRepository instance;
    private EntityManagerFactory entityManagerFactory;

    private MonolithicRepository() {
        entityManagerFactory = Persistence.createEntityManagerFactory("default");
    }

    public static synchronized MonolithicRepository getInstance() {
        if(instance == null) {
            instance = new MonolithicRepository();
        }
        return instance;
    }

    public User getUserByCredentials(String username, String mother, String father) {
        User user = this.findUserByUsername(username);
        if(user.getFamilyRelation() == null) {
            return null;
        }
        if(Objects.equals(user.getFamilyRelation().getMother(), mother) || Objects.equals(user.getFamilyRelation().getFather(), father)) {
            return user;
        }
        return null;
    }

    public User findUserByUsername(String username) {
        EntityManager em = entityManagerFactory.createEntityManager();
        CriteriaBuilder cb = em.getCriteriaBuilder();
        CriteriaQuery<User> cq = cb.createQuery(User.class);
        Root<User> userRoot = cq.from(User.class);
//        Root<FamilyRelation> familyRelationRoot = cq.from(FamilyRelation.class);
//        Join<User, FamilyRelation> userFamilyRelationJoin = userRoot.join("familyRelation", JoinType.LEFT);
//        cq
//                .multiselect(userFamilyRelationJoin.get("user").get("id"), userFamilyRelationJoin.get("user").get("username"))
//                .where(cb.and(
//                        cb.equal(userRoot.get("username"), username),
//                        cb.or(
//                            cb.equal(familyRelationRoot.get("mother"), mother),
//                            cb.equal(familyRelationRoot.get("father"), father)
//                        ))
//                );
//        TypedQuery<User> tq = em.createQuery(cq);
        cq
                .select(userRoot)
                .where(cb.equal(userRoot.get("username"), username));
        TypedQuery<User> tq = em.createQuery(cq);

        try {
            User user = tq.getSingleResult();
            return user;
        } catch(NoResultException exception) {
            return null;
        }
    }

    public void addRecord(String username, String mother, String father) {
        User user = this.findUserByUsername(username);

        EntityManager em = this.entityManagerFactory.createEntityManager();
        EntityTransaction transaction = em.getTransaction();
        transaction.begin();
        FamilyRelation familyRelation = em.find(FamilyRelation.class, user.getFamilyRelation().getId());

        familyRelation.setFather(father);
        familyRelation.setMother(mother);

        em.persist(familyRelation);
        transaction.commit();
    }

    public List<User> getSiblings(String username) {
        User user = this.findUserByUsername(username);
        FamilyRelation familyRelation = user.getFamilyRelation();

        EntityManager em = entityManagerFactory.createEntityManager();
        CriteriaBuilder cb = em.getCriteriaBuilder();
        CriteriaQuery<Integer> cq = cb.createQuery(Integer.class);
        Root<FamilyRelation> familyRelationRoot = cq.from(FamilyRelation.class);

        cq.select(familyRelationRoot.get("userId"))
                .where(
                    cb.and(
                        cb.or(
                            cb.equal(familyRelationRoot.get("father"), familyRelation.getFather()),
                            cb.equal(familyRelationRoot.get("mother"), familyRelation.getMother())
                        )
                    )
                );
        TypedQuery<Integer> tq = em.createQuery(cq);

        return tq.getResultList()
                .stream()
                .filter(userId -> {
                    return user.getId() != userId;
                })
                .map(userId -> {
                    return em.find(User.class, userId);
                }).collect(Collectors.toList());
    }
}
