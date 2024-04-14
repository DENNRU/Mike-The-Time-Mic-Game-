/*
** DENNRU's Project, 2024
** scene3.cpp
** File description :
** scene3
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <chrono>
#include <thread>

void titre(sf::RenderWindow& window);

static sf::Sound selectSound;

void displayDialogue3(sf::RenderWindow& window, const std::string& dialogueString, const std::string& speaker)
{
    // White dialogue rectangle
    sf::RectangleShape dialogueBox(sf::Vector2f(window.getSize().x - 40, 200));
    dialogueBox.setFillColor(sf::Color::White);
    dialogueBox.setOutlineThickness(2);
    dialogueBox.setOutlineColor(sf::Color::Black);
    dialogueBox.setPosition(20, window.getSize().y - 220);

    // Load the Font
    sf::Font font;
    if (!font.loadFromFile("file/font.otf")) {
        std::cerr << "Error to load file/font.otf." << std::endl;
        return;
    }

    // The text to show
    sf::Text dialogueText("", font, 18);
    dialogueText.setFillColor(sf::Color::Black);
    dialogueText.setPosition(dialogueBox.getPosition().x + 180, dialogueBox.getPosition().y + 10);
    dialogueText.setLineSpacing(1.5f);

    // Icons of speakers
    sf::Texture characterTexture;
    sf::Sprite characterSprite;
    if (speaker == "Microphone:" || speaker == "Mike:") {
        if (!characterTexture.loadFromFile("file/mic.png")) {
            std::cerr << "Error to load file/mic.png." << std::endl;
            return;
        }
        characterSprite.setTexture(characterTexture);
    } else if (speaker == "Mike Off:") {
        if (!characterTexture.loadFromFile("file/mic_off.png")) {
            std::cerr << "Error to load file/mic_off.png." << std::endl;
            return;
        }
        characterSprite.setTexture(characterTexture);
    } else if (speaker == "You:") {
        if (!characterTexture.loadFromFile("file/char.png")) {
            std::cerr << "Error to load file/char.png." << std::endl;
            return;
        }
        characterSprite.setTexture(characterTexture);
    }
    characterSprite.setScale(1.8f, 1.8f);
    characterSprite.setPosition(dialogueBox.getPosition().x + 10, dialogueBox.getPosition().y + 10);

    // Show the dialogue
    std::string displayedText;
    for (char letter : dialogueString) {
        displayedText += letter;
        dialogueText.setString(displayedText);

        // Check if the text don't go out the rectangle
        if (dialogueText.getGlobalBounds().width >= dialogueBox.getSize().x - 200) {
            // Find the index of the last space before overflow
            std::size_t lastSpace = displayedText.find_last_of(' ');
            if (lastSpace != std::string::npos) {
                // Cut text at last space
                displayedText = displayedText.substr(0, lastSpace) + "\n" + displayedText.substr(lastSpace + 1);
                dialogueText.setString(displayedText);
            }
        }

        window.clear();

        // Draw the background
        sf::Texture backgroundTexture;
        if (backgroundTexture.loadFromFile("file/black_jackhole.gif")) {
            sf::Sprite backgroundSprite(backgroundTexture);
            backgroundSprite.setScale(1.8f, 1.8f);
            window.draw(backgroundSprite);
        } else {
            std::cerr << "Error to load file/black_jackhole.gif." << std::endl;
        }

        // Draw dialogue Box
        window.draw(dialogueBox);

        // Draw the dialogue
        window.draw(dialogueText);

        // Draw the icon
        window.draw(characterSprite);

        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }

    // Wait the user to clickbackgroundSprite
    sf::Event clickEvent;
    bool clicked = false;
    while (window.isOpen() && !clicked) {
        while (window.pollEvent(clickEvent)) {
            if (clickEvent.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if (clickEvent.type == sf::Event::MouseButtonPressed) {
                clicked = true;
            }
        }
    }
}

void playSelectSound3()
{
    static sf::SoundBuffer selectBuffer;
    if (!selectBuffer.loadFromFile("file/select.ogg")) {
        std::cerr << "Error to load file/select.ogg." << std::endl;
        return;
    }

    selectSound.setBuffer(selectBuffer);
    selectSound.setVolume(40);
    selectSound.play();
}

int displayDialogueWithChoice3(sf::RenderWindow& window, const std::string& dialogueString, const std::string& speaker, const std::string& choice1, const std::string& choice2)
{
    sf::RectangleShape dialogueBox(sf::Vector2f(window.getSize().x - 40, 200));
    dialogueBox.setFillColor(sf::Color::White);
    dialogueBox.setOutlineThickness(2);
    dialogueBox.setOutlineColor(sf::Color::Black);
    dialogueBox.setPosition(20, window.getSize().y - 220);

    // Load the Font
    sf::Font font;
    if (!font.loadFromFile("file/font.otf")) {
        std::cerr << "Error to load file/font.otf." << std::endl;
        return -1;
    }

    // The text
    sf::Text dialogueText("", font, 18);
    dialogueText.setFillColor(sf::Color::Black);
    dialogueText.setPosition(dialogueBox.getPosition().x + 180, dialogueBox.getPosition().y + 10);
    dialogueText.setLineSpacing(1.5f);

    // The text for choices
    sf::Text choice1Text("", font, 18);
    choice1Text.setFillColor(sf::Color::White);
    choice1Text.setString(choice1);
    choice1Text.setPosition(dialogueBox.getPosition().x + 50 + 100 * 1.8f, dialogueBox.getPosition().y + 70);

    sf::Text choice2Text("", font, 18);
    choice2Text.setFillColor(sf::Color::White);
    choice2Text.setString(choice2);
    choice2Text.setPosition(dialogueBox.getPosition().x + 50 + 100 * 1.8f, dialogueBox.getPosition().y + 100);

    // Icons of the speaker
    sf::Texture characterTexture;
    sf::Sprite characterSprite;
    if (speaker == "Microphone:" || speaker == "Mike:") {
        if (!characterTexture.loadFromFile("file/mic.png")) {
            std::cerr << "Error to load file/mic.png." << std::endl;
            return -1;
        }
        characterSprite.setTexture(characterTexture);
    } else if (speaker == "Mike Off:") {
        if (!characterTexture.loadFromFile("file/mic_off.png")) {
            std::cerr << "Error to load file/mic_off.png." << std::endl;
            return -1;
        }
        characterSprite.setTexture(characterTexture);
    } else if (speaker == "You:") {
        if (!characterTexture.loadFromFile("file/char.png")) {
            std::cerr << "Error to load file/char.png." << std::endl;
            return -1;
        }
        characterSprite.setTexture(characterTexture);
    }
    characterSprite.setScale(1.8f, 1.8f);
    characterSprite.setPosition(dialogueBox.getPosition().x + 10, dialogueBox.getPosition().y + 10);

    // Choice buttons
    sf::RectangleShape choice1Rect(sf::Vector2f(choice1Text.getLocalBounds().width + 10, choice1Text.getLocalBounds().height + 10));
    choice1Rect.setFillColor(sf::Color::Black);
    choice1Rect.setPosition(dialogueBox.getPosition().x + 20 + 100 * 1.8f, dialogueBox.getPosition().y + 70); // Déplacer vers la droite

    sf::RectangleShape choice2Rect(sf::Vector2f(choice2Text.getLocalBounds().width + 10, choice2Text.getLocalBounds().height + 10));
    choice2Rect.setFillColor(sf::Color::Black);
    choice2Rect.setPosition(dialogueBox.getPosition().x + 20 + 100 * 1.8f, dialogueBox.getPosition().y + 100); // Déplacer vers la droite

    std::string displayedText;
    bool choicesClicked = false;
    bool choice1Selected = false;
    bool choice2Selected = false;
    for (char letter : dialogueString) {
        displayedText += letter;
        dialogueText.setString(displayedText);

        // Check if the text don't go out the rectangle
        if (dialogueText.getGlobalBounds().width >= dialogueBox.getSize().x - 200) {
            // Find the index of the last space before overflow
            std::size_t lastSpace = displayedText.find_last_of(' ');
            if (lastSpace != std::string::npos) {
                // Cut text at last space
                displayedText = displayedText.substr(0, lastSpace) + "\n" + displayedText.substr(lastSpace + 1);
                dialogueText.setString(displayedText);
            }
        }

        window.clear();

        // Draw the background
        sf::Texture backgroundTexture;
        if (backgroundTexture.loadFromFile("file/black_jackhole.gif")) {
            sf::Sprite backgroundSprite(backgroundTexture);
            backgroundSprite.setScale(1.8f, 1.8f);
            window.draw(backgroundSprite);
        } else {
            std::cerr << "Error file/black_jackhole.gif." << std::endl;
        }

        // Draw the dialogue box
        window.draw(dialogueBox);

        // Draw the dialogue
        window.draw(dialogueText);

        // Draw char
        window.draw(characterSprite);

        // Draw choice buttons
        window.draw(choice1Rect);
        window.draw(choice2Rect);

        // Draw text choice
        window.draw(choice1Text);
        window.draw(choice2Text);

        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(30));

        // Check if cliecked
        if (!choicesClicked) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (choice1Rect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                if (!choice1Selected) {
                    playSelectSound3();
                    choice1Selected = true;
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    choicesClicked = true;
                    return 1; // Ret 1 for first choice
                }
            } else if (choice2Rect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                if (!choice2Selected) {
                    playSelectSound3();
                    choice2Selected = true;
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    choicesClicked = true;
                    return 2; // Ret 2 for first choice
                }
            }
        }
    }

    return 0; // Ret 0 for no choice
}

void scene3(sf::RenderWindow& window)
{
    int choice = 0;

    displayDialogue3(window, "A temporal paradox arises.", "You:");
    displayDialogue3(window, "February 29, 2025 simply does not exist!", "You:");
    displayDialogue3(window, "A black hole appears, beginning to destroy everything around. You're in a panic.", "You:");
    displayDialogue3(window, "Mike: \"That's it! You've always been a weakling! Now you're paying for your helplessness!\"", "Mike Off:");
    displayDialogue3(window, "Mike: \"You're solely to blame for all this.\"", "Mike Off:");

    while (choice == 0) {
        choice = displayDialogueWithChoice3(window, "What to do? - Acknowledge guilt - Make Mike do something", "You:", "- Acknowledge guilt", "- Make Mike do something");
    }
    if (choice == 1) {
        displayDialogue3(window, "Mike: \"Easy, easy. We're in this together. But, yes, I must admit, this isn't the most ordinary situation.\"", "Mike:");
        displayDialogue3(window, "Mike: \"Often we try to control time, striving to change something in our lives. But time doesn't yield to our control. It inexorably moves forward, taking us along with it.\"", "Mike:");
        displayDialogue3(window, "Mike: \"And perhaps, that's what I need to learn to accept. We can't correct past mistakes. But we can accept them, grow from them, and move forward with the wisdom they give us.\"", "Mike:");
        displayDialogue3(window, "Mike: \"This is my choice. I'm ready to accept it. Our adventure together isn't over yet.\"", "Mike:");

        titre(window);
    } else if (choice == 2) {
        displayDialogue3(window, "Mike: \"HAHAHAHAHAHA!\"", "Mike Off:");
        displayDialogue3(window, "Mike: \"You're such a pathetic creature!\"", "Mike Off:");

        // GAME OVER.
        sf::Font font;
        if (!font.loadFromFile("file/font.otf")) {
            std::cerr << "Error to load file/font.otf." << std::endl;
            return;
        }

        sf::Text gameOverText("GAME OVER.", font, 80);
        gameOverText.setFillColor(sf::Color::White);
        gameOverText.setStyle(sf::Text::Bold);
        gameOverText.setPosition((window.getSize().x - gameOverText.getLocalBounds().width) / 2, (window.getSize().y - gameOverText.getLocalBounds().height) / 2);

        window.clear(sf::Color::Black);
        window.draw(gameOverText);
        window.display();

        // Wait 4 secondes
        sf::Clock clock;
        while (clock.getElapsedTime().asSeconds() < 4) {}

        // Quit the Game
        window.close();
    }
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
    }
}
