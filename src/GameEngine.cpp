#include "GameEngine.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <fstream>

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::spawnSpecialWeapon(std::shared_ptr<Entity> entity) {


    std::shared_ptr<Entity> specialW = m_entityManager.addEntity(std::string("specialweapon"));
    specialW -> cTransform = std::make_shared<CTransform>(m_player -> cTransform -> position, Vec2(0, 0),4); // moves with the player
    specialW -> cShape = std::make_shared<CShape>(6 * m_player -> cShape-> shape.getRadius(), 32, sf::Color(100, 0, 0, 9), sf::Color(255, 0, 0, 100) , 7);
    specialW -> cLifespan = std::make_shared<CLifespan>(240);
    specialW -> cCollision = std::make_shared<CCollision>(6 * m_player ->cShape -> shape.getRadius());


}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::spawnSmallEnemies(std::shared_ptr<Entity> e) {

    int numberOfVertices = e -> cShape -> shape.getPointCount();
    // create n entities;
    float diff = (2 * M_PI) / numberOfVertices;
    float angle = 0;

    for (int i = 0; i < numberOfVertices; i++) {

        float sine = std::sin((float) angle);
        float cosine = std::cos((float) angle);

        Vec2 vel = {sine, cosine};

        std::shared_ptr<Entity> sEnemy = m_entityManager.addEntity(std::string("smallenemy"));
        sEnemy -> cTransform = std::make_shared<CTransform>(e -> cTransform -> position, vel * 4,e -> cTransform -> angle);
        sEnemy -> cShape = std::make_shared<CShape>(e -> cShape -> shape.getRadius()/2.0, numberOfVertices, e -> cShape -> shape.getFillColor(), e -> cShape -> shape.getOutlineColor(), e -> cShape -> shape.getOutlineThickness());
        sEnemy -> cCollision = std::make_shared<CCollision>(e -> cShape -> shape.getRadius());
        sEnemy -> cLifespan = std::make_shared<CLifespan>(60);
        angle += diff;

    }


    
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos) {

    std::shared_ptr<Entity> bullet = m_entityManager.addEntity(std::string("bullet"));

    float cos = (mousePos.x - entity -> cTransform -> position.x)/ mousePos.length(entity -> cTransform -> position);
    float sin = (mousePos.y - entity -> cTransform -> position.y)/ mousePos.length(entity -> cTransform -> position);

    bullet -> cTransform = std::make_shared<CTransform>(m_player -> cTransform -> position, Vec2(8*cos, 8*sin), 8);
    bullet -> cShape = std::make_shared<CShape>(12, 15, sf::Color(255, 255, 255, 255), sf::Color::Black, 2);
    bullet -> cCollision = std::make_shared<CCollision>(12);
    bullet -> cLifespan = std::make_shared<CLifespan>(70);

}




//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::run() {

    // add pause functionality here
    //      some systems should function while paused (rendering)
    //      some systems shouldn't (movement / input)


    while (m_isRunning) {

        m_entityManager.update();

        if (m_isPaused) {

            sRender();
            sUserInput(); 

        } else {

            sEnemySpawner();
            sLifespan();
            sCollision();
            sMovement();
            sUserInput(); 
            sRender();

            m_currentFrame++;

        }


    }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////
GameEngine::GameEngine (const std::string& config) {

    init(config);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::init(const std::string& config) {

    std::ifstream fin(config);
    std::string tmp;

    while (fin >> tmp) {

        if (tmp == "Window") {

            int x, y, framelim, fullscreen;

            fin >> x >> y >> framelim >> fullscreen;
            
            m_window.create(sf::VideoMode(x, y), "Geometry Wars");
            m_window.setFramerateLimit(framelim);
            
        } else if (tmp == "Font") {

            std::string fontpath;
            int size, r, g, b;

            fin >> fontpath >> size >> r  >> g >> b;

            m_font.loadFromFile(fontpath);
            m_text.setFont(m_font);
            m_text.setFillColor(sf::Color(r, g, b));
            m_text.setCharacterSize(size);

        } else if (tmp == "Player") {

            fin >> m_playerConfig.shaperadius
                >> m_playerConfig.collisionradius
                >> m_playerConfig.speed
                >> m_playerConfig.fillred
                >> m_playerConfig.fillgreen
                >> m_playerConfig.fillblue
                >> m_playerConfig.outlinered
                >> m_playerConfig.outlinegreen
                >> m_playerConfig.outlineblue
                >> m_playerConfig.outlinethickness
                >> m_playerConfig.vertexcount;

        } else if (tmp == "enemy") {

            fin >> m_enemyConfig.shaperadius
                >> m_enemyConfig.collisionradius
                >> m_enemyConfig.speedmin
                >> m_enemyConfig.speedmax
                >> m_enemyConfig.outlinered
                >> m_enemyConfig.outlineblue
                >> m_enemyConfig.outlinegreen
                >> m_enemyConfig.outlinethickness
                >> m_enemyConfig.vertexmin
                >> m_enemyConfig.vertexmax
                >> m_enemyConfig.lifespan
                >> m_enemyConfig.spawninterval;

        } else if (tmp == "bullet") {

            fin >> m_bulletConfig.shaperadius
                >> m_bulletConfig.collisionradius
                >> m_bulletConfig.speed
                >> m_bulletConfig.fillred
                >> m_bulletConfig.fillgreen
                >> m_bulletConfig.fillblue
                >> m_bulletConfig.outlinered
                >> m_bulletConfig.outlineblue
                >> m_bulletConfig.outlinegreen
                >> m_bulletConfig.outlinethickness
                >> m_bulletConfig.vertexcount
                >> m_bulletConfig.lifespan;

        }
    }


    spawnPlayer();

}




//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::setPaused(bool isPaused) {

    m_isPaused = true;

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::sMovement() {


    for (auto e : m_entityManager.getEntities()) {

        if (e -> cTransform && e -> cShape) {

            // add velocity vector to the position vector in transform component
            e -> cTransform -> position += e -> cTransform -> velocity;
            // move the shape to that position
            e -> cShape -> shape.setPosition(e -> cTransform -> position.x, e -> cTransform -> position.y);


            // wall collision system
            int x = m_window.getSize().x;
            int y = m_window.getSize().y;

            int sx = e -> cTransform -> position.x;
            int sy = e -> cTransform -> position.y;
            int rad = e -> cShape -> shape.getRadius();

            if (sx + rad >= x || sx - rad <= 0) {

                e -> cTransform -> velocity.x *= -1;

            }

            if (sy + rad >= y || sy - rad <= 0) {

                e -> cTransform -> velocity.y *= -1;

            }

        }

    }


    // for (auto e : m_entityManager.getEntities("player")) {
    //
    //     e -> cShape -> shape.rotate(e -> cTransform -> angle); // rotation
    //     e -> cTransform -> position += e -> cTransform -> velocity;
    //     e -> cShape -> shape.setPosition(e -> cTransform -> position.x, e -> cTransform -> position.y);
    //
    // }

}





//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::sLifespan() {

    for (std::shared_ptr<Entity> x : m_entityManager.getEntities()) {

        if (x -> cLifespan) {

            x -> cLifespan -> remaining--;
            x -> cShape -> shape.setFillColor(sf::Color(x -> cShape -> shape.getFillColor().r, x -> cShape -> shape.getFillColor().g, x -> cShape -> shape.getFillColor().b, (255 * ((float) x -> cLifespan -> remaining / (float) x -> cLifespan -> total) )));
            x -> cShape -> shape.setOutlineColor(sf::Color(x -> cShape -> shape.getOutlineColor().r, x -> cShape -> shape.getOutlineColor().g, x -> cShape -> shape.getOutlineColor().b, (255 * ((float) x -> cLifespan -> remaining / (float) x -> cLifespan -> total) )));

            if (x -> cLifespan -> remaining == 0) {
                x -> destroy();
            }

        }

    }

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::sCollision() {

    for (auto b : m_entityManager.getEntities("bullet")) {

        for (auto e : m_entityManager.getEntities("enemy")) {

            if ((int) (b -> cTransform -> position.length(e -> cTransform -> position)) <= b -> cCollision -> radius + e -> cCollision -> radius) {
                // have collided
                b -> destroy();
                spawnSmallEnemies(e);
                e -> destroy();
            }

        }

    }

    for (auto e : m_entityManager.getEntities("enemy")) {

        if (e -> cTransform -> position.length(m_player -> cTransform -> position) <= e -> cCollision -> radius + m_player -> cCollision -> radius) {

            m_player -> cTransform -> position.x = m_window.getSize().x/2.0;
            m_player -> cTransform -> position.y = m_window.getSize().y/2.0;
        }

        for (auto s : m_entityManager.getEntities("specialweapon")) {

            if (s ->cTransform -> position.length(e -> cTransform -> position) <= s -> cCollision -> radius + e -> cCollision -> radius) {

                spawnSmallEnemies(e);
                e -> destroy();

            }

        }


    }


}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::sRender() {

    m_window.clear();

    // draw enemies
    for (auto e : m_entityManager.getEntities()) {

        if (e -> cTransform && e -> cShape) {

            e -> cShape -> shape.rotate(e -> cTransform -> angle); // rotation
            m_window.draw(e -> cShape -> shape);


        }

    }

    m_window.display();

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::sEnemySpawner() {

    if (m_currentFrame % 30 == 0) {

        spawnEnemy();
        m_lastEnemySpawnTime = m_currentFrame;

    }

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::spawnPlayer() {

    // this is possible only with the help of the entitymanager class
    m_player = m_entityManager.addEntity(std::string("player"));
    m_player -> cTransform = std::make_shared<CTransform>(Vec2((float) m_window.getSize().x/2, (float) m_window.getSize().y/2), Vec2(0, 0), 8);
    m_player -> cShape = std::make_shared<CShape>(30, 6, sf::Color::Black, sf::Color::Red , 3);
    m_player -> cCollision = std::make_shared<CCollision>( m_player -> cShape -> shape.getRadius());
    m_player -> cInput = std::make_shared<CInput>();


}


//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::spawnEnemy() {


    int x = m_window.getSize().x;
    int y = m_window.getSize().y;

    srand(time(0));
    int ranx = 30 + rand() % (x - 60);
    int rany = 30 + rand() % (y - 60);

    int ranvx = 2 + rand() % 2;
    int ranvy = 2 + rand() % 2;

    int r = rand() % 255;
    int g = rand() % 255;
    int b = rand() % 255;

    int s = 3 + rand() % 6;

    auto enemy = m_entityManager.addEntity(std::string("enemy"));
    enemy -> cShape = std::make_shared<CShape>(30, s, sf::Color(r, g, b), sf::Color::White, 3);
    enemy -> cTransform = std::make_shared<CTransform>(Vec2(ranx, rany), Vec2(ranvx, ranvy), 4);
    enemy -> cCollision = std::make_shared<CCollision>(30);

}






//////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameEngine::sUserInput() {

    sf::Event event;

    while (m_window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {

            m_isRunning = false;
            m_window.close();

        } else if (event.type == sf::Event::KeyPressed) {

            
            if (event.key.code == sf::Keyboard::H) {
                m_player -> cTransform -> velocity.x = -6;
            }

            if (event.key.code == sf::Keyboard::J) {
                m_player -> cTransform -> velocity.y = 6;
            }

            if (event.key.code == sf::Keyboard::K) {
                m_player -> cTransform -> velocity.y = -6;
            }

            if (event.key.code == sf::Keyboard::L) {
                m_player -> cTransform -> velocity.x = 6;

            }

        } else if (event.type == sf::Event::KeyReleased) {

            if (event.key.code == sf::Keyboard::P) {
                m_isPaused = !m_isPaused;
            }

            if (event.key.code == sf::Keyboard::B) {
                spawnSpecialWeapon(m_player);
            }

            if (event.key.code == sf::Keyboard::H) {
                m_player -> cTransform -> velocity.x = 0;
            }

            if (event.key.code == sf::Keyboard::J) {
                m_player -> cTransform -> velocity.y = 0;

            }

            if (event.key.code == sf::Keyboard::K) {
                m_player -> cTransform -> velocity.y = 0;

            }

            if (event.key.code == sf::Keyboard::L) {
                m_player -> cTransform -> velocity.x = 0;
            }
            

        } else if (event.type == sf::Event::MouseButtonPressed) {

            if (!m_isPaused) {
                spawnBullet(m_player, Vec2(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y));
            }

        }

    }


}


