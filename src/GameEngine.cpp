#include "GameEngine.h"


#include <iostream>

GameEngine::GameEngine() {
    init();
}

void GameEngine::init() {
    m_window.create(sf::VideoMode(1280, 720), "My Window");
    m_window.setFramerateLimit(60);
    spawnPlayer();
}

void GameEngine::run() {
    // do take care of the pause functionality
    while (m_running) {
        m_EntityManager.update();
        sEnemySpawner();
        sMovement();
        sCollision();
        sUserInput();
        sRender();

        m_currentFrame++;
    }
}

void GameEngine::setPaused(bool paused) {
    // if pressed the p key, pause the game
}

void GameEngine::spawnPlayer() {
    auto entity = m_entityManager.addEntity("player");
    entity -> cTransform = std::make_shared<CTransform>(Vec2(200.0f, 200.0f), Vec2(1.0f, 1.0f));
    entity -> cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);
    entity -> cInput = std::make_shared<CInput>();
    m_player = entity;

    
}

void GameEngine::spawnEnemy() {
    // do the stuff here
    m_lastEnemySpawnTime = m_currentFrame;
}


void GameEngine::spawnSmallEnemies(std::shared_ptr<Entity> entity) {
    
}

void GameEngine::sMovement() {}
void GameEngine::sUserInput() {}
void GameEngine::sLifespan() {}
void GameEngine::sRender() {
    m_player.
}
void GameEngine::sEnemySpawner() {}
void GameEngine::sCollision() {}

void GameEngine::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePosition) {}
void GameEngine::spawnSpecialWeapon(std::shared_ptr<Entity> entity) {}

