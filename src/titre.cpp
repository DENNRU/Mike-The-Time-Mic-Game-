/*
** DENNRU's Project, 2024
** titre.cpp
** File description :
** titre
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>

void titre(sf::RenderWindow& window)
{
    sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setFillColor(sf::Color::Black);

    // Load Font
    sf::Font font;
    if (!font.loadFromFile("file/font.otf")) {
        std::cerr << "Error to load file/font.otf." << std::endl;
        return;
    }

    // Create Text
    sf::Text developerText("Developer:\nDanilovskii Daniil (DENNRU)", font, 40);
    sf::Text designerText("Designer:\nMaxime Kovolenko (Firerit)", font, 40);
    sf::Text musicText("Music:\nEric Skiff", font, 40);

    // Color Text
    developerText.setFillColor(sf::Color::White);
    designerText.setFillColor(sf::Color::White);
    musicText.setFillColor(sf::Color::White);

    sf::FloatRect developerBounds = developerText.getLocalBounds();
    developerText.setOrigin(developerBounds.left + developerBounds.width / 2.0f, developerBounds.top + developerBounds.height / 2.0f);
    developerText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 4.0f);

    sf::FloatRect designerBounds = designerText.getLocalBounds();
    designerText.setOrigin(designerBounds.left + designerBounds.width / 2.0f, designerBounds.top + designerBounds.height / 2.0f);
    designerText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    sf::FloatRect musicBounds = musicText.getLocalBounds();
    musicText.setOrigin(musicBounds.left + musicBounds.width / 2.0f, musicBounds.top + musicBounds.height / 2.0f);
    musicText.setPosition(window.getSize().x / 2.0f, 3.0f * window.getSize().y / 4.0f);

    window.clear();
    window.draw(background);
    window.draw(developerText);
    window.draw(designerText);
    window.draw(musicText);
    window.display();

    // Wait 10 secondes
    std::this_thread::sleep_for(std::chrono::seconds(10));

    window.close();
}
