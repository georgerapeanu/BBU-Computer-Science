package com.example.app.repository;

import com.example.app.dto.ManufacturerProductCountDTO;
import com.example.app.dto.model.ManufacturerDTO;
import com.example.app.model.Manufacturer;
import com.example.app.model.Product;
import jakarta.persistence.EntityManager;
import jakarta.persistence.PersistenceContext;
import jakarta.persistence.Tuple;
import jakarta.persistence.TypedQuery;
import jakarta.persistence.criteria.*;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageImpl;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.stream.Collectors;

@Repository
public class ManufacturerRepositoryImpl implements IManufacturerRepository {

    @PersistenceContext
    private EntityManager em;

    /**
     * Retrieves a page of manufacturers sorted by the number of products they have.
     *
     * @param pageable the page request parameters
     * @return a page of ManufacturerProductCountDTO objects representing manufacturers and their product counts
     */
    @Override
    public Page<ManufacturerProductCountDTO> getManufacturersSortedByProductCount(Pageable pageable) {
        CriteriaBuilder cb = em.getCriteriaBuilder();
        CriteriaQuery<Object[]> cq = cb.createQuery(Object[].class);
        Root<Manufacturer> manufacturer = cq.from(Manufacturer.class);
        Join<Manufacturer, Product> manufacturerProductJoin = manufacturer.join("products", JoinType.LEFT);
        cq
                .multiselect(manufacturer, cb.count(manufacturerProductJoin))
                .groupBy(manufacturer)
                .orderBy(cb.desc(cb.count(manufacturerProductJoin)));
        TypedQuery<Object[]> typedQuery = em.createQuery(cq);

        List<ManufacturerProductCountDTO> results = typedQuery
                .setFirstResult(pageable.getPageNumber() * pageable.getPageSize())
                .setMaxResults(pageable.getPageSize())
                .getResultStream()
                .map(row -> {
                    return new ManufacturerProductCountDTO(
                            ManufacturerDTO.fromManufacturer((Manufacturer) row[0]),
                            ((Long) row[1]).intValue()
                    );
                })
                .toList();

        CriteriaQuery<Long> count_cq = cb.createQuery(Long.class);
        count_cq.select(cb.count(count_cq.from(Manufacturer.class)));;
        long total = em.createQuery(count_cq).getSingleResult();

        return new PageImpl<>(results, pageable, total);
    }

    /**
     * Retrieves a list of ManufacturerProductCountDTO objects representing the product counts for the given list of manufacturers.
     *
     * @param manufacturerDTOS the list of ManufacturerDTO objects
     * @return a list of ManufacturerProductCountDTO objects representing the product counts for the manufacturers
     */
    @Override
    public List<ManufacturerProductCountDTO> getManufacturerProductCountsFromList(List<ManufacturerDTO> manufacturerDTOS) {
        CriteriaBuilder cb = em.getCriteriaBuilder();
        CriteriaQuery<Tuple> cq = cb.createQuery(Tuple.class);
        Root<Product> product = cq.from(Product.class);
        CriteriaBuilder.In<Integer> inClause = cb.in(product.get("manufacturer").get("id"));
        for (ManufacturerDTO manufacturerDTO : manufacturerDTOS) {
            inClause.value(manufacturerDTO.getId());
        }
        cq
                .multiselect(product.get("manufacturer").get("id").alias("id"), cb.count(product.get("id")).alias("count"))
                .groupBy(product.get("manufacturer").get("id"))
                .where(inClause);

        List<Tuple> typedQueryResult = em.createQuery(cq).getResultList();

        return manufacturerDTOS.stream()
                .map(manufacturerDTO -> {
                    Integer count = typedQueryResult.stream()
                            .filter(row -> row.get("id").equals(manufacturerDTO.getId()))
                            .map(row -> (Long) row.get("count"))
                            .map(Long::intValue)
                            .findFirst()
                            .orElse(0);
                    return new ManufacturerProductCountDTO(manufacturerDTO, count);
                })
                .collect(Collectors.toList());
    }

    /**
     * Retrieves the number of manufacturers associated with the specified user handle.
     *
     * @param userHandle the user handle
     * @return the number of manufacturers
     */
    @Override
    public Integer getManufacturerCountForUserHandle(String userHandle) {
        CriteriaBuilder cb = em.getCriteriaBuilder();
        CriteriaQuery<Long> cq = cb.createQuery(Long.class);
        Root<Manufacturer> manufacturers = cq.from(Manufacturer.class);

        cq
                .select(cb.count(manufacturers))
                .where(cb.equal(manufacturers.get("user").get("handle"), userHandle));
        TypedQuery<Long> typedQuery = em.createQuery(cq);
        return typedQuery.getSingleResult().intValue();
    }
}
