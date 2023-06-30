#include <vector>
#include "EntityManager.h"


void cleanVector(std::vector<std::shared_ptr<Entity>>& vec) {


    for (int i = 0; i < vec.size();  ) {

        if (!vec[i]) {

            vec.erase(vec.begin() + i);
            i--;

        } else if (!vec[i] -> isAlive()) {

            vec.erase(vec.begin() + i);
            i--;

        }

        i++;

    }



}

EntityManager::EntityManager() {

}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag) {

    auto e = std::make_shared<Entity>(m_totalEntities++, tag);
    m_toAdd.push_back(e);
    return e;

}

EntityVector& EntityManager::getEntities() {
    
    return m_entities;

}

EntityVector& EntityManager::getEntities(const std::string& tag) {

    return m_entityMap[tag];

}

void EntityManager::update() {

    for ( auto x : m_toAdd) {

        m_entities.push_back(x);
        m_entityMap[x -> tag()].push_back(x);

    }

    m_toAdd.clear();


    cleanVector(m_entities);
    cleanVector(m_entityMap["bullet"]);
    cleanVector(m_entityMap["enemy"]);
    cleanVector(m_entityMap["specialweapon"]);
    cleanVector(m_entityMap["smallenemies"]);

}

