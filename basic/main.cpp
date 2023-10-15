#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;
const sf::Vector2f GRAVITY = { 0.f, 1500.f };

struct {
    float mass;
    sf::Vector2f velocity;
    sf::CircleShape shape;
} ball;

sf::Vector2f calcNormalVelocity(sf::Vector2f currVel, float mass, float dt)
{
    sf::Vector2f newVelocity = {
        currVel.x + (GRAVITY.x/mass) * dt,
        currVel.y + (GRAVITY.y/mass) * dt
    };
    return newVelocity;
}

sf::Vector2f calcFrictionVelocity(sf::Vector2f currVel, float friction, float mass)
{
    sf::Vector2f newVelocity = {
        (currVel.x*-friction)/mass,
        (currVel.y*friction)/mass
    };
    return newVelocity;
}

sf::Vector2f calcPosition(sf::Vector2f currPos, sf::Vector2f currVel, float dt)
{
    sf::Vector2f newPos = {
        currPos.x + currVel.x * dt,
        currPos.y + currVel.y * dt
    };
    return newPos;
}

void runPhysics(sf::Time elapsed)
{
    float dt = elapsed.asSeconds();
    float radius = ball.shape.getRadius();
    sf::Vector2f pos = ball.shape.getPosition();

    sf::Vector2f newVelocity = calcNormalVelocity(ball.velocity, ball.mass, dt);
    sf::Vector2f newPos = calcPosition(pos, newVelocity, dt);

    float cFriction = 0.9f;
    float topDist = newPos.y; float bottomDist = SCREEN_HEIGHT-newPos.y;
    float leftDist = newPos.x; float rightDist = SCREEN_WIDTH-newPos.x;

    if (topDist <= radius || bottomDist <= radius)
    {
        newVelocity = calcFrictionVelocity(ball.velocity, -cFriction, ball.mass);
        // Collision resolution
        if (topDist <= radius)
        {
            float penetration = radius - newPos.y;
            newPos.y += penetration;
        }
        else
        {
            float penetration = radius - std::abs(newPos.y - SCREEN_HEIGHT);
            newPos.y -= penetration;
        }
    }
    if (leftDist <= radius || rightDist <= radius)
    {
        newVelocity = calcFrictionVelocity(ball.velocity, cFriction, ball.mass);
        // Collision resolution
        if (leftDist <= radius)
        {
            float penetration = radius - newPos.x;
            newPos.x += penetration;
        }
        else
        {
            float penetration = radius - std::abs(newPos.x - SCREEN_WIDTH);
            newPos.x -= penetration;
        }
    }

    ball.velocity = newVelocity;
    ball.shape.setPosition(newPos);
}

void init()
{
    sf::CircleShape ballShape;
    ballShape.setRadius(50.f);
    ballShape.setOrigin(50.f, 50.f);
    ballShape.setPosition(400.f, 50.f);

    ball.mass = 1.f;
    ball.velocity = {0.f, 0.f};
    ball.shape = ballShape;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Basic physics");
    window.setFramerateLimit(60);

    sf::Clock clock;
    init();

    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            float x;
            if (sf::Mouse::getPosition(window).x <= (int)SCREEN_WIDTH/2) x = -100.f;
            else x = 100.f;

            ball.velocity.x += x;
            ball.velocity.y += -100.f;
        }

        runPhysics(elapsed);
 
        window.clear();
        window.draw(ball.shape);
        window.display();
    }
 
    return EXIT_SUCCESS;
}