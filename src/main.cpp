/*
** DENNRU's Project, 2024
** main.cpp
** File description :
** main
*/

#include <SFML/Graphics.hpp>

void showLogo(sf::RenderWindow& window);
void createMenu(sf::RenderWindow& window);

int main()
{
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "Mike, The Time Mic!", sf::Style::Fullscreen);

    window.setFramerateLimit(60);

    // Show Logo
    showLogo(window);

    // Show Menu & Game
    createMenu(window);

    return 0;
}
