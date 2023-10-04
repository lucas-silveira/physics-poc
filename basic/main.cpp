#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;
const sf::Vector2f GRAVITY = { 0.0f, 1000.0f };

struct ball {
    float mass;
    sf::Vector2f velocity;
    sf::CircleShape shape;
} ball;
sf::RectangleShape floorLine;

bool collision(sf::Vector2f circle, float radius, sf::Vector2f rect)
{
    float testX = circle.x;
    float testY = circle.y;

    if (circle.x < rect.x) testX = rect.x;
    else if (circle.x > rect.x+SCREEN_WIDTH) testX = rect.x+SCREEN_WIDTH;

    if (circle.y < rect.y) testY = rect.y;
    else if (circle.y > rect.y+SCREEN_HEIGHT) testY = rect.y+SCREEN_HEIGHT;

    float distX = circle.x-testX;
    float distY = circle.y-testY;
    float distance = sqrt( (distX*distX) + (distY*distY) );

    if (distance <= radius)
        return true;

    return false;
}

void applyPhysics(sf::Time elapsed)
{
    float dt = elapsed.asSeconds();
    sf::Vector2f currVelocity = ball.velocity;
    sf::Vector2f currPos = ball.shape.getPosition();

    sf::Vector2f newVelocity = {
        currVelocity.x + (GRAVITY.x/ball.mass) * dt,
        currVelocity.y + (GRAVITY.y/ball.mass) * dt,
    };
    sf::Vector2f newPos = {
        currPos.x + newVelocity.x * dt,
        currPos.y + newVelocity.y * dt,
    };

    if (collision(newPos, ball.shape.getRadius(), floorLine.getPosition()))
    {
        float cFriction = 0.9f;
        newVelocity.x = (-currVelocity.x*cFriction)/ball.mass;
        newVelocity.y = (-currVelocity.y*cFriction)/ball.mass;

        newPos.x = currPos.x + newVelocity.x * dt;
        newPos.y = currPos.y + newVelocity.y * dt;
    }

    ball.velocity = newVelocity;
    ball.shape.setPosition(newPos);
}

void init()
{
    floorLine.setSize(sf::Vector2f((float)SCREEN_WIDTH, 5.0f ));
    floorLine.setPosition(0, (float)SCREEN_HEIGHT-5.0f);

    sf::CircleShape ballShape;
    ballShape.setRadius(50.0f);
    ballShape.setOrigin(50.0f, 50.0f);
    ballShape.setPosition(400.0f, 50.0f);

    ball.mass = 1.1f;
    ball.velocity = {0.0f, 0.0f};
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

        applyPhysics(elapsed);
 
        window.clear();
        window.draw(floorLine);
        window.draw(ball.shape);
        window.display();
    }
 
    return EXIT_SUCCESS;
}