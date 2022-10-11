package repository;

import exceptions.NegativeWeightExceptions;
import model.Entity;

import java.util.List;

public interface IRepository {

    void add(Entity entity) throws NegativeWeightExceptions;
    List<Entity> getAll();

    List<Entity> getAllWithWeightGreaterThan() ;
}
