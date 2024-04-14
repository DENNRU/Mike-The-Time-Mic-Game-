/*
** DENNRU's Project, 2024
** scene2.cpp
** File description :
** scene2
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <chrono>
#include <thread>

void scene3(sf::RenderWindow& window);

static sf::Sound selectSound;

void displayDialogue2(sf::RenderWindow& window, const std::string& dialogueString, const std::string& speaker)
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
        if (backgroundTexture.loadFromFile("file/background2.png")) {
            sf::Sprite backgroundSprite(backgroundTexture);
            window.draw(backgroundSprite);
        } else {
            std::cerr << "Error to load file/background2.png." << std::endl;
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

    // Wait the user to click
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

void playSelectSound2()
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

int displayDialogueWithChoice2(sf::RenderWindow& window, const std::string& dialogueString, const std::string& speaker, const std::string& choice1, const std::string& choice2)
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
        if (backgroundTexture.loadFromFile("file/background2.png")) {
            sf::Sprite backgroundSprite(backgroundTexture);
            window.draw(backgroundSprite);
        } else {
            std::cerr << "Error file/background2." << std::endl;
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
                    playSelectSound2();
                    choice1Selected = true;
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    choicesClicked = true;
                    return 1; // Ret 1 for first choice
                }
            } else if (choice2Rect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                if (!choice2Selected) {
                    playSelectSound2();
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

void scene2(sf::RenderWindow& window)
{
    displayDialogue2(window, "Wild West, September 1, 1855", "You:");
    displayDialogue2(window, "You and Mike find yourselves in the Wild West, in the distant past, surrounded by dusty streets and noisy saloons.", "You:");
    displayDialogue2(window, "Mike: \"Wow, the Wild West! What do you say, is this far from your usual habitat?\"", "Mike:");
    displayDialogue2(window, "You: (apprehensively) \"Yes, it's... quite unusual. Not sure I like it here.\"", "You:");
    displayDialogue2(window, "Mike: \"Why so gloomy? Come on, come on, you'll do just fine! We can find something fun or interesting here, I'm sure!\"", "Mike:");
    displayDialogue2(window, "As you continue to explore the surroundings.", "You:");
    displayDialogue2(window, "Mike Off: \"Are you always this dull? Couldn't you just relax and enjoy the adventure? Instead, you constantly bring everything down.\"", "Mike Off:");
    displayDialogue2(window, "You: (hesitantly) \"I'm just... not sure I'm in my element here. All this... it's too strange for me.\"", "You:");
    displayDialogue2(window, "Mike Off: \"Well, if you're such a coward, maybe I should find another adventure buddy. Someone who truly appreciates the opportunities I offer.\"", "Mike Off:");
    displayDialogue2(window, "At that moment, you decide that enough is enough.", "You:");
    displayDialogue2(window, "You take out the microphone and begin to speak into it the date and place:", "You:");
    displayDialogue2(window, "\"Italy, February 29, 202...\"", "You:");
    displayDialogue2(window, "Mike Off: \"Italy, February 29, 2025, and blah blah...\"", "Mike Off:");

    scene3(window);

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
