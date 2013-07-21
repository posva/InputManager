
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"
#include "InputManager.hpp"

void test1()
{
    std::cerr<<"Test 1 called!\n";
}

void test2()
{
    std::cerr<<"Test 2 called!\n";
}

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "cute_image.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(texture);
    
    InputManager inp;
    Action* act(new Action(&test1));
    inp.addAction(act, "test");
    //inp.addKeyToAction(act, sf::Keyboard::Key::Num1, act_keyPress);
    inp.addMouseToAction(act, sf::Mouse::Left, act_mouseDown);
    
    act = new Action(&test2);
    inp.addAction(act, "test2");
    //inp.addKeyToAction(act, sf::Keyboard::Key::A, act_keyRelease);
    //inp.addKeyToAction(act, sf::Keyboard::Key::A, act_keyPress);
    
    inp.addKeyToAction(act, sf::Keyboard::Key::B, act_keyDown);
    window.setKeyRepeatEnabled(false);


    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Espace pressed : exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            inp.update(event);
        }
        inp.updateDowns();

        // Clear screen
        window.clear();

        // Draw the sprite
        sprite.setColor(sf::Mouse::isButtonPressed(sf::Mouse::Left)?sf::Color::Red:sf::Color::White);
        window.draw(sprite);

        // Update the window
        window.display();
    }
    
    return EXIT_SUCCESS;
}
