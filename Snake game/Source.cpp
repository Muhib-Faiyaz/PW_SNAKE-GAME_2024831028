#include <SFML/Graphics.hpp>
#include <deque>
#include <cstdlib>
#include <ctime>

const int CELL = 20;
const int W = 600;
const int H = 600;

int main()
{
    srand(time(nullptr));

    sf::RenderWindow window(sf::VideoMode({ W, H }), "Snake Game");
    int speed = 10;
    window.setFramerateLimit(speed);

    std::deque<sf::Vector2i> snake = { {5,5}, {4,5}, {3,5} };
    sf::Vector2i dir = { 1, 0 };
    sf::Vector2i food = { 10, 10 };
    bool alive = true;

    int score = 0;  

    sf::Font font;
    font.openFromFile("arial.ttf");         

    sf::Text scoreText(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(sf::Vector2f(10.f, 10.f));


    while (window.isOpen())
    {
        
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        
        if (alive)
        {
            bool dirChanged = false;  

            if (!dirChanged && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && dir.y == 0)
            {
                dir = { 0,-1 }; dirChanged = true;
            }

            if (!dirChanged && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && dir.y == 0)
            {
                dir = { 0, 1 }; dirChanged = true;
            }

            if (!dirChanged && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && dir.x == 0)
            {
                dir = { -1, 0 }; dirChanged = true;
            }

            if (!dirChanged && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && dir.x == 0)
            {
                dir = { 1, 0 }; dirChanged = true;
            }

            sf::Vector2i newHead = snake.front() + dir;

            
            if (newHead.x < 0 || newHead.x >= W / CELL ||
                newHead.y < 0 || newHead.y >= H / CELL)
            {
                newHead.x = (newHead.x + W / CELL) % (W / CELL);
                newHead.y = (newHead.y + H / CELL) % (H / CELL);
               
            }

           
            for (int i = 0; i < (int)snake.size(); i++)
                if (snake[i] == newHead) 
                    alive = false;

            if (alive)
            {
                snake.push_front(newHead);
                if (newHead == food)
                {
                    food = { rand() % (W / CELL), rand() % (H / CELL) };
                    score++;
                    if (speed < 30)
                    {
                        speed++;
                        window.setFramerateLimit(speed);
                    }
                }
                else
                    snake.pop_back();
            }
        }

        scoreText.setString("Score: " + std::to_string(score));

        window.clear(sf::Color(30, 30, 30));

        sf::RectangleShape cell(sf::Vector2f(CELL , CELL ));

        for (int i = 0; i < (int)snake.size(); i++)
        {
            cell.setFillColor(sf::Color::Green);
            cell.setPosition(sf::Vector2f(snake[i].x * CELL, snake[i].y * CELL));
            window.draw(cell);
        }

        cell.setFillColor(sf::Color::Red);
        cell.setPosition(sf::Vector2f(food.x * CELL, food.y * CELL));
        window.draw(cell);

        window.draw(scoreText);

        if (!alive)
        {
            window.clear(sf::Color(100, 0, 0));

            sf::Text gameOverText(font);
            gameOverText.setCharacterSize(60);
            gameOverText.setFillColor(sf::Color::White);
            gameOverText.setString("GAME OVER");

            sf::FloatRect goBounds = gameOverText.getLocalBounds();
            gameOverText.setOrigin(sf::Vector2f(
                goBounds.position.x + goBounds.size.x / 2.f,
                goBounds.position.y + goBounds.size.y / 2.f
            ));
            gameOverText.setPosition(sf::Vector2f(W / 2.f, H / 2.f - 50.f));


            scoreText.setCharacterSize(40);
            sf::FloatRect bounds = scoreText.getLocalBounds();        
            scoreText.setOrigin(sf::Vector2f(                         
                 bounds.position.x + bounds.size.x / 2.f,
                bounds.position.y + bounds.size.y / 2.f
            ));
            scoreText.setPosition(sf::Vector2f(W/2.0f, H/2.0f));
            window.draw(scoreText);
            window.draw(gameOverText);
        }

        window.display();
    }
}