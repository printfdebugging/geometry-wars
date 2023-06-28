#pragma once

#include "Components.h"
#include <string>
#include <iostream>
#include <memory>

class Entity {
    friend class EntityManager;
    std::string m_tag = "Default";
    size_t m_id = 0;
    bool m_active = true;

    // constructor and destructor
    Entity(const size_t it, const std::string& tag);
public:
    std::shared_ptr<CTransform>     cTransform;
    std::shared_ptr<CShape>         cShape;
    std::shared_ptr<CCollision>     cCollision;
    std::shared_ptr<CInput>         cInput;
    std::shared_ptr<CScore>         cScore;
    std::shared_ptr<CLifespan>      cLifespan;

    bool isActive() const;
    const std::string& tag() const;
    const size_t id() const;
    void destroy();

};
