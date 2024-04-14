/*
** DENNRU's Project, 2024
** menu.cpp
** File description :
** menu
*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

void startGame(sf::RenderWindow& window);
void scene2(sf::RenderWindow& window);
void scene3(sf::RenderWindow& window);
void titre(sf::RenderWindow& window);

static sf::Sound selectSoundPlay;
static sf::Sound selectSoundQuit;

void drawButtonCircle(sf::RenderWindow& window, sf::Sprite& button)
{
    // Calculate the position and the rayon of circle
    sf::Vector2f center(button.getPosition().x + button.getLocalBounds().width / 2,
                        button.getPosition().y + button.getLocalBounds().height / 2);
    float radius = button.getLocalBounds().width / 2 + 5;

    // Draw the white cicle
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color::White);
    circle.setOrigin(radius, radius);
    circle.setPosition(center);
    window.draw(circle);
}

void checkButtonHover(sf::RenderWindow& window, sf::Sprite& playButton, sf::Sprite& quitButton)
{
    // Load the Font
    static sf::Font font;
    static bool fontLoaded = false;
    if (!fontLoaded) {
        if (!font.loadFromFile("file/font.otf")) {
            std::cerr << "Error to load file/font.otf." << std::endl;
            return;
        }
        fontLoaded = true;
    }

    // Load select Sound
    static sf::SoundBuffer selectBuffer;
    static bool selectBufferLoaded = false;
    if (!selectBufferLoaded) {
        if (!selectBuffer.loadFromFile("file/select.ogg")) {
            std::cerr << "Error to load file/select.ogg." << std::endl;
            return;
        }
        selectBufferLoaded = true;
    }

    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    // Check if the mouse is on Play button
    if (playButton.getGlobalBounds().contains(mousePos)) {
        sf::Text text("LET'S GO!", font, 20);
        text.setFillColor(sf::Color::White);
        text.setPosition(playButton.getPosition().x + playButton.getLocalBounds().width / 2 - text.getLocalBounds().width / 2,
                         playButton.getPosition().y - text.getLocalBounds().height - 20);
        window.draw(text);

        // Play the select Sound
        if (selectSoundPlay.getStatus() != sf::Sound::Playing) {
            selectSoundPlay.setBuffer(selectBuffer);
            selectSoundPlay.setVolume(40);
            selectSoundPlay.play();
        }
    }

    // Check if the mouse is on Quit button
    if (quitButton.getGlobalBounds().contains(mousePos)) {
        sf::Text text("OFF!", font, 20);
        text.setFillColor(sf::Color::White);
        text.setPosition(quitButton.getPosition().x + quitButton.getLocalBounds().width / 2 - text.getLocalBounds().width / 2,
                         quitButton.getPosition().y + quitButton.getLocalBounds().height + 20);
        window.draw(text);

        // Play the select Sound
        if (selectSoundQuit.getStatus() != sf::Sound::Playing) {
            selectSoundQuit.setBuffer(selectBuffer);
            selectSoundQuit.setVolume(40);
            selectSoundQuit.play();
        }
    }
}

void createMenu(sf::RenderWindow& window)
{
    // Load buttons textures
    sf::Texture playTexture, quitTexture;
    if (!playTexture.loadFromFile("file/mic.png") || !quitTexture.loadFromFile("file/mic_off.png")) {
        std::cerr << "Error to load file/mic.png or file/mic_off.png." << std::endl;
        return;
    }

    // Create button sprites
    sf::Sprite playButton(playTexture), quitButton(quitTexture);
    playButton.setPosition(window.getSize().x / 2 - playButton.getLocalBounds().width / 2, window.getSize().y / 2 - 100);
    quitButton.setPosition(window.getSize().x / 2 - quitButton.getLocalBounds().width / 2, window.getSize().y / 2 + 100);

    // Load background Music
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("file/main_ost.ogg")) {
        std::cerr << "Error to load file_main_ost.ogg." << std::endl;
        return;
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(20);
    backgroundMusic.play();

    // Load the Game Logo
    sf::Texture logoTexture;
    if (!logoTexture.loadFromFile("file/MikeTheTimeMicLOGO.png")) {
        std::cerr << "Error to load file/MikeTheTimeMicLOGO.png." << std::endl;
        return;
    }

    // Create Logo sprite
    sf::Sprite logoSprite(logoTexture);
    logoSprite.setPosition((window.getSize().x - logoSprite.getLocalBounds().width) / 2, 20);

    // Show the Menu
    bool menuOpen = true;
    while (menuOpen) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                menuOpen = false;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (playButton.getGlobalBounds().contains(mousePos)) {
                    //backgroundMusic.stop();
                    startGame(window); /////
                    menuOpen = false;
                }
                if (quitButton.getGlobalBounds().contains(mousePos)) {
                    window.close();
                    menuOpen = false;
                }
            }
        }

        window.clear(sf::Color::Black);

        window.draw(logoSprite);

        drawButtonCircle(window, playButton);
        drawButtonCircle(window, quitButton);

        window.draw(playButton);
        window.draw(quitButton);

        checkButtonHover(window, playButton, quitButton);

        window.display();
    }
}
