#pragma once

#include <SFML/Graphics.hpp>
#include "EntityManager.h"
#include "Entity.h"

class GameEngine {
    sf::RenderWindow    m_window;
    EntityManager       m_entityManager;
    sf::Font        m_font;
    sf::Text        m_text;
    // config place holders

    int m_score = 0;
    int m_currentFrame = 0;
    int m_lastEnemySpawnTime = 0;
    bool m_paused = false;
    bool m_running = true;

    std::shared_ptr<Entity> m_player;

    void init();
    void setPaused(bool paused);

    void sMovement();
    void sUserInput();
    void sLifespan();
    void sRender();
    void sEnemySpawner();
    void sCollision();

    void spawnPlayer();
    void spawnEnemy();
    void spawnSmallEnemies(std::shared_ptr<Entity> entity);
    void spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePosition);
    void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

public:
    GameEngine();
    void run();
};

