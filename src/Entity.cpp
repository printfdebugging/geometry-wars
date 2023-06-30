#include "Entity.h"

Entity::Entity(const size_t id, const std::string& tag) 
: m_id(id), m_tag(tag) {

}

bool Entity::isAlive() const {

    return m_isAlive;

}

const std::string& Entity::tag() const {

    return m_tag;

}

size_t Entity::id() const {

    return m_id;

}

void Entity::destroy() {

    m_isAlive = false;
}
