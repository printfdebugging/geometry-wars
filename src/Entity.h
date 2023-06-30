#pragma once


#include "Components.h"
#include <memory>
#include <iostream>

class Entity {

    friend class EntityManager;

private:

    int                 m_id        = 0;
    std::string         m_tag       = "default";
    bool                m_isAlive   = true;


public:

    Entity(const size_t id, const std::string& tag);

    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CShape> cShape;
    std::shared_ptr<CLifespan> cLifespan;
    std::shared_ptr<CCollision> cCollision;
    std::shared_ptr<CScore> cScore;
    std::shared_ptr<CInput> cInput;


    bool isAlive() const;
    const std::string& tag() const;
    size_t id() const;
    void destroy();

};
