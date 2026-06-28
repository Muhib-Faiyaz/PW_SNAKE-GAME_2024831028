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
    window.setFramerateLimit(10);

    std::deque<sf::Vector2i> snake = { {5,5}, {4,5}, {3,5} };
    sf::Vector2i dir = { 1, 0 };
    sf::Vector2i food = { 10, 10 };
    bool alive = true;

    while (window.isOpen())
    {
        
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        
        if (alive)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && dir.y == 0) 
                dir = { 0,-1 };
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && dir.y == 0) 
                dir = { 0, 1 };
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && dir.x == 0) 
                dir = { -1, 0 };
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && dir.x == 0) 
                dir = { 1, 0 };

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
                    food = { rand() % (W / CELL), rand() % (H / CELL) };
                else
                    snake.pop_back();
            }
        }

        
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

        if (!alive)
            window.clear(sf::Color(100, 0, 0));

        window.display();
    }
}