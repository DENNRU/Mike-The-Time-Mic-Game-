/*
** DENNRU's Project, 2024
** scene1.cpp
** File description :
** scene1
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <chrono>
#include <thread>

void scene2(sf::RenderWindow& window);

static sf::Sound selectSound;

void displayDialogue(sf::RenderWindow& window, const std::string& dialogueString, const std::string& speaker)
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
        if (backgroundTexture.loadFromFile("file/background1.png")) {
            sf::Sprite backgroundSprite(backgroundTexture);
            window.draw(backgroundSprite);
        } else {
            std::cerr << "Error to load file/background1.png." << std::endl;
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

void playSelectSound()
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

int displayDialogueWithChoice(sf::RenderWindow& window, const std::string& dialogueString, const std::string& speaker, const std::string& choice1, const std::string& choice2)
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
        if (backgroundTexture.loadFromFile("file/background1.png")) {
            sf::Sprite backgroundSprite(backgroundTexture);
            window.draw(backgroundSprite);
        } else {
            std::cerr << "Error to load file/background1.png." << std::endl;
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
                    playSelectSound();
                    choice1Selected = true;
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    choicesClicked = true;
                    return 1; // Ret 1 for first choice
                }
            } else if (choice2Rect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                if (!choice2Selected) {
                    playSelectSound();
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

void startGame(sf::RenderWindow& window)
{
    int choice = 0;

    displayDialogue(window, "Location: Abandoned House (February 29, 2024)", "You:");
    displayDialogue(window, "You wander through the abandoned house, exploring every corner in search of something interesting.", "You:");
    displayDialogue(window, "In the corner of the room, covered in dust and cobwebs, you notice an old microphone.", "You:");
    displayDialogue(window, "Approaching it, you cautiously touch its surface, and the microphone suddenly comes to life.", "You:");
    displayDialogue(window, "Microphone: \"Hey hey! Finally, someone's here! Was it boring without me?\"", "Microphone:");
    displayDialogue(window, "You: (surprised) \"Um, who... who are you?\"", "You:");
    displayDialogue(window, "Microphone: \"Me? I'm Mike, your personal time guide! Yeah, that Mike. Michael Jackson. Just kidding, of course. But trust me, with this microphone, you can control time.\"", "Microphone:");
    displayDialogue(window, "You: (skeptically) \"Control time? That's nonsense.\"", "You:");
    displayDialogue(window, "Mike: \"Don't believe me? Well, let's give it a try! Where shall we go? Maybe back to the day you were born? Or, um, September 11th... Just kidding! Although, a bit dark humor, but nothing too scary. After all, we still have plenty of time!\"", "Mike:");

    while (choice == 0) {
        choice = displayDialogueWithChoice(window, "Where to go? - Your birth date, December 30, 2003 - September 11th (xD)", "You:", "- Your birth date, December 30, 2003", "- September 11th (xD)");
    }
    if (choice == 1) {
        choice = 0;
    } else if (choice == 2) {
        choice = 0;
    }

    displayDialogue(window, "Mike: \"Boredom... Oh! I've got it! Let's go to September 1st, 1855! Yes, exactly! A little journey into the past to tease the noses of a mad scientist and his little friend? From that movie... What's it called...? Oh yeah, exactly! Rick and Morty! Yes, that's it...\"", "Mike:");
    displayDialogue(window, "You: (hesitantly) \"Maybe we should just go to my first birthday...?\"", "You:");
    displayDialogue(window, "Mike Off (firmly): \"NO.\"", "Mike Off:");
    displayDialogue(window, "You: (hesitating) \"Um... Okay, let's go to 1855.\"", "You:");
    displayDialogue(window, "Mike: \"Great choice, buddy! Get ready! All you need to do is shout the date and place into me as clearly as possible!\"", "Mike:");
    displayDialogue(window, "Mike Off (sternly): \"And... DON'T TRY TO CHEAT.\"", "Mike Off:");

    while (choice == 0) {
        choice = displayDialogueWithChoice(window, "Shout? - December 30, 2003, Italy - September 1st, 1855, Wild West.", "You:", "- December 30, 2003, Italy", "- September 1st, 1855, Wild West.");
    }
    if (choice == 1) {
        choice = 0;

        displayDialogue(window, "Mike Off: \"...\"", "Mike Off:");
        displayDialogue(window, "Mike Off: \"I knew you had it in you...\"", "Mike Off:");
        displayDialogue(window, "Mike Off: \"You're a terrible person...\"", "Mike Off:");
        displayDialogue(window, "Mike Off: \"Or maybe I should start calling you... The Player...?\"", "Mike Off:");

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
    } else if (choice == 2) {
        choice = 0;

        displayDialogue(window, "Mike: \"LETZ ROCK!\"", "Mike:");
        displayDialogue(window, "Everything around you suddenly changes and loses its meaning; you feel as if you're being dragged deep into the past.", "You:");
        displayDialogue(window, "You try to run forward, but your legs carry you only backward...", "You:");
        displayDialogue(window, "You are transported to September 1st, 1855, in the Wild West.", "You:");

        // Go to scene 2
        scene2(window);
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
