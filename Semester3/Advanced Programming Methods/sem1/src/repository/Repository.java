package repository;

import exceptions.NegativeWeightExceptions;
import model.Entity;

import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository {

    private List<Entity> entities;

    private int size;

    public Repository() {
        entities = new ArrayList<Entity>();
    }

    @Override
    public void add(Entity entity) throws NegativeWeightExceptions {
        if (entity.getWeight() < 0) {
            throw new NegativeWeightExceptions();
        }
        entities.add(entity);
    }

    @Override
    public List<Entity> getAll() {
        return entities;
    }

    @Override
    public List<Entity> getAllWithWeightGreaterThan() {
        List<Entity> filterEntities = new ArrayList<>();

        for (Entity entity: entities) {
            if (entity.getWeight() >= 200)
                filterEntities.add(entity);
        }
        return filterEntities;
    }
}
