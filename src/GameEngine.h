#include "Entity.h"
#include "EntityManager.h"

#include <SFML/Graphics.hpp>

struct PlayerConfig {

    int shaperadius,
    collisionradius,
    fillred,
    fillgreen,
    fillblue,
    outlinered,
    outlinegreen,
    outlineblue,
    outlinethickness,
    vertexcount;

    float speed; 

};

struct EnemyConfig {

    int shaperadius,
    collisionradius,
    outlinered,
    outlinegreen,
    outlineblue,
    outlinethickness,
    vertexmin,
    vertexmax,
    lifespan,
    spawninterval;

    float speedmin,
    speedmax;

};

struct BulletConfig {
    
    int shaperadius,
    collisionradius,
    fillred,
    fillgreen,
    fillblue,
    outlinered,
    outlinegreen,
    outlineblue,
    outlinethickness,
    vertexcount,
    lifespan;

    float speed;

};



class GameEngine {

    sf::RenderWindow    m_window;
    EntityManager       m_entityManager;
    sf::Font            m_font;
    sf::Text            m_text;
    PlayerConfig        m_playerConfig;
    EnemyConfig         m_enemyConfig;
    BulletConfig        m_bulletConfig;
    int                 m_score = 0;
    int                 m_currentFrame = 0;
    int                 m_lastEnemySpawnTime = 0;
    bool                m_isPaused = false;
    bool                m_isRunning = true;

    std::shared_ptr<Entity> m_player;

    void init(const std::string& config);
    void setPaused(bool isPaused);


    void sMovement();
    void sUserInput();
    void sLifespan();
    void sRender();
    void sEnemySpawner();
    void sCollision();

    void spawnPlayer();
    void spawnEnemy();
    void spawnSmallEnemies(std::shared_ptr<Entity> entity);
    void spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos);
    void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

public:

    GameEngine (const std::string& config);
    void run();
};
