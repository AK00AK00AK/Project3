#include <SFML/Graphics.hpp>
#include <ctime>
#include <cmath>

#define WIDTH 800
#define HEIGHT 600
#define PI 3.14159265

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "clock", sf::Style::Default);
    window.setFramerateLimit(60);

    float Rad = 250;
    sf::Vector2f Pos(WIDTH / 2, HEIGHT / 2);

    sf::CircleShape ClCirc(Rad);
    ClCirc.setFillColor(sf::Color::White);
    ClCirc.setOutlineThickness(2);
    ClCirc.setOutlineColor(sf::Color::Black);
    ClCirc.setOrigin(Rad, Rad);
    ClCirc.setPosition(Pos);

    sf::CircleShape CenterCirc(10);
    CenterCirc.setFillColor(sf::Color::Black);
    CenterCirc.setOrigin(10, 10);
    CenterCirc.setPosition(Pos);

    sf::VertexArray hPointer(sf::Lines, 2);
    hPointer[0].color= sf::Color::Black;
    hPointer[1].color = sf::Color::Black;

    sf::VertexArray mPointer(sf::Lines, 2);
    mPointer[0].color = sf::Color::Blue;
    mPointer[1].color = sf::Color::Blue;

    sf::VertexArray sPointer(sf::Lines, 2);
    sPointer[0].color = sf::Color::Red;
    sPointer[1].color= sf::Color::Red;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
            Rad += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)) {
            Rad  -= 1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            Pos.x -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            Pos.x += 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            Pos.y -= 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            Pos.y += 1;
        }

        ClCirc.setRadius(Rad);
        ClCirc.setOrigin(Rad, Rad);
        ClCirc.setPosition(Pos);
        CenterCirc.setPosition(Pos);

        std::time_t currentTime = std::time(NULL);
        std::tm* timePtr = std::localtime(&currentTime);

        float hAngle = 90 - (timePtr->tm_hour % 12 + timePtr->tm_min / 60.0) * 30;
        float mAngle = 90 - (timePtr->tm_min + timePtr->tm_sec / 60.0) * 6;
        float sAngle =  90 - timePtr->tm_sec * 6;

        hPointer[0].position = Pos;
        hPointer[1].position = sf::Vector2f(Pos.x + 0.5 * Rad * std::cos(hAngle * PI / 180),
            Pos.y - 0.5 * Rad * std::sin(hAngle * PI / 180));

        mPointer[0].position = Pos;
        mPointer[1].position = sf::Vector2f(Pos.x + 0.8 * Rad * std::cos(mAngle * PI / 180),
            Pos.y -  0.8 * Rad * std::sin(mAngle * PI / 180));

        sPointer[0].position = Pos;
        sPointer[1].position = sf::Vector2f(Pos.x + 0.9 * Rad * std::cos(sAngle * PI / 180),
            Pos.y - 0.9 * Rad * std::sin(sAngle * PI / 180));

        window.clear(sf::Color::White);
        window.draw(ClCirc);
        window.draw(CenterCirc);
        window.draw(hPointer);
        window.draw(mPointer);
        window.draw(sPointer);

        sf::VertexArray hMarks(sf::Lines, 24);
        for (int i = 0; i < 12; ++i) {
            float angle = (90 - i * 30) * PI / 180;
            float cosAngle = std::cos(angle);
            float sinAngle = std::sin(angle);

            hMarks[i * 2].position = sf::Vector2f(Pos.x + 0.92 * Rad * cosAngle,
                Pos.y - 0.92 * Rad * sinAngle);
            hMarks[i * 2  + 1].position = sf::Vector2f(Pos.x + Rad * cosAngle,
                Pos.y - Rad * sinAngle);
            hMarks[i * 2].color = sf::Color::Black;
            hMarks[i * 2 + 1].color = sf::Color::Black;
        }
        window.draw(hMarks);

        sf::VertexArray sMarks(sf::Lines, 120);
        for (int i =  0; i <  60; ++i) {
            float angle = (90 - i * 6) * PI / 180;
            float cosAngle = std::cos(angle);
            float sinAngle = std::sin(angle);

            sMarks[i * 2].position = sf::Vector2f(Pos.x + 0.97 * Rad * cosAngle,
                Pos.y - 0.97 * Rad * sinAngle);
            sMarks[i * 2 + 1].position = sf::Vector2f(Pos.x + Rad * cosAngle,
                Pos.y - Rad  * sinAngle);
            sMarks[i * 2].color = sf::Color::Black;
            sMarks[i * 2 + 1].color = sf::Color::Black;
        }
        window.draw(sMarks);

        window.display();
    }

    return 0;
}
