/*
** DENNRU's Project, 2024
** logo.cpp
** File description :
** logo
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

void showLogo(sf::RenderWindow& window)
{
    sf::Clock clock;
    float elapsedTime = 0.0f;

    // Wait 1.5 secondes with a black screen
    while (elapsedTime < 1.5f) {
        elapsedTime = clock.getElapsedTime().asSeconds();
        window.clear(sf::Color::Black);
        window.display();
    }

    // Load the Logo
    sf::Texture logoTexture;
    if (!logoTexture.loadFromFile("file/logoD.png")) {
        std::cerr << "Error to load file/logoD.png." << std::endl;
        return;
    }

    // Increase the Logo by 4
    sf::Sprite logoSprite(logoTexture);
    float scaleFactor = 4.00f; // Facteur d'échelle pour augmenter la taille
    logoSprite.setScale(scaleFactor, scaleFactor);

    // Center the Logo
    logoSprite.setPosition((window.getSize().x - logoSprite.getGlobalBounds().width) / 2,
                           (window.getSize().y - logoSprite.getGlobalBounds().height) / 2);

    // Load the Font
    sf::Font font;
    if (!font.loadFromFile("file/font.otf")) {
        std::cerr << "Error to load file/font.otf." << std::endl;
        return;
    }

    float logoAlpha = 0.0f;
    float textPosY = window.getSize().y;

    while (elapsedTime < 7.5f) { // Total of 7.5 secondes
        elapsedTime = clock.getElapsedTime().asSeconds();

        // The Logo appear
        if (elapsedTime < 3.5f) {
            if (logoAlpha < 255.0f) {
                logoAlpha += (255.0f / 2.0f) * (1.0f / 60.0f);
                logoSprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(logoAlpha)));
            }
        }
        // Drag the tex "DENNRU's Production!"
        else if (elapsedTime < 6.5f) {
            if (textPosY > window.getSize().y / 2 + logoSprite.getLocalBounds().height / 2 + 20) {
                textPosY -= 100.0f * (1.0f / 60.0f); // Animation du texte
            }
            else {
                // Stop the text under the Logo
                textPosY = window.getSize().y / 2 + logoSprite.getLocalBounds().height / 2 + 20;
            }
        }

        window.clear(sf::Color::Black);
        window.draw(logoSprite);

        // Draw "DENNRU's Production!"
        sf::Text text("DENNRU's Production!", font, 30);
        text.setFillColor(sf::Color::White);
        text.setPosition(window.getSize().x / 2 - text.getLocalBounds().width / 2, textPosY);
        window.draw(text);

        window.display();
    }

    // Play the Quack Sound
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("file/quack.ogg")) {
        std::cerr << "Error to load file/quack.ogg." << std::endl;
        return;
    }
    sf::Sound sound(buffer);
    sound.play();

    // Wait 2 secondes
    sf::sleep(sf::seconds(2.0f));
}
