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
    int big_food = 0;
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

            if (!dirChanged && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && dir.y == 0)
            {
                dir = { 0,-1 }; dirChanged = true;
            }

            if (!dirChanged && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && dir.y == 0)
            {
                dir = { 0, 1 }; dirChanged = true;
            }

            if (!dirChanged && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && dir.x == 0)
            {
                dir = { -1, 0 }; dirChanged = true;
            }

            if (!dirChanged && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && dir.x == 0)
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
                    if (big_food >= 5) {
                        score += 5;
                        big_food = 0;
                    }
                    else
                    {
                        score++;
                        big_food++;
                    }

                    if (speed < 30)
                    {
                        speed += 0;
                        window.setFramerateLimit(speed);
                    }
                }
                else
                    snake.pop_back();
            }
        }

        scoreText.setString("Score: " + std::to_string(score));

        window.clear(sf::Color(30, 30, 30));

        sf::RectangleShape cell(sf::Vector2f(CELL - 2, CELL - 2));

        for (int i = 0; i < (int)snake.size(); i++)
        {
            cell.setFillColor(sf::Color::Green);
            cell.setPosition(sf::Vector2f(snake[i].x * CELL, snake[i].y * CELL));
            window.draw(cell);
        }

        if (big_food < 5)
        {
            cell.setFillColor(sf::Color::Red);

        }
        else
        {
            cell.setFillColor(sf::Color::Yellow);

        }
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
            goBounds.position.x + goBounds.size.x / 2.f,goBounds.position.y + goBounds.size.y / 2.f));
            gameOverText.setPosition(sf::Vector2f(W / 2.f, H / 2.f - 50.f));

            scoreText.setCharacterSize(40);
            sf::FloatRect bounds = scoreText.getLocalBounds();
            scoreText.setOrigin(sf::Vector2f(
            bounds.position.x + bounds.size.x / 2.f, bounds.position.y + bounds.size.y / 2.f));
            scoreText.setPosition(sf::Vector2f(W / 2.0f, H / 2.0f + 50.f));

            
            sf::Text restartText(font);
            restartText.setCharacterSize(20);
            restartText.setFillColor(sf::Color::White);
            restartText.setString("Press R to Restart");
            sf::FloatRect rBounds = restartText.getLocalBounds();
            restartText.setOrigin(sf::Vector2f(
            rBounds.position.x + rBounds.size.x / 2.f, rBounds.position.y + rBounds.size.y / 2.f));
            restartText.setPosition(sf::Vector2f(W / 2.f, H / 2.f + 100.f));

            window.draw(gameOverText);
            window.draw(scoreText);
            window.draw(restartText);

            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
            {
                snake = { {5,5}, {4,5}, {3,5} };
                dir = { 1, 0 };
                score = 0;
                speed = 10;
                big_food = 0;
                alive = true;
                window.setFramerateLimit(speed);

                scoreText.setCharacterSize(20);
                scoreText.setOrigin(sf::Vector2f(0.f, 0.f));
                scoreText.setPosition(sf::Vector2f(10.f, 10.f));
            }
        }

        window.display();
    }
}