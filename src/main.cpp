
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
#include "FPS.hpp"


static InputManager* IM(NULL);

void test1()
{
    std::cerr<<"Test 1 called!\n";
}

void mouseWheel(InputManager* inp)
{
    std::cerr<<"MouseWheel moved("<<inp->getAction("mouseWheel")->check()<<"): "<<inp->getMouseWheelDelta()<<".\n";
}

void test2()
{
    std::cerr<<"Test 2 called!\n";
}

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    
    sf::Font font;
    font.loadFromFile(resourcePath()+"sansation.ttf");
    
    FPS fps(font);

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
    IM = &inp;
    Action* act(NULL);
    act = inp.getAction("test");
    act->bind(&test1);
    //inp.addKeyToAction(act, sf::Keyboard::Num1, act_keyPress);
    inp.addMouseToAction(act, sf::Mouse::Right, act_mouseWheel);
    
    act = inp.getAction("mouseWheel");
    std::cerr<<act<<" = "<<inp.getAction("mouseWheel")<<"\n";
    act->bind(&mouseWheel, &inp);
    inp.addMouseToAction(act, sf::Mouse::Middle, act_mouseWheel);
    inp.addKeyToAction(act, sf::Keyboard::A, act_keyPress);
    inp.addMouseToAction(act, sf::Mouse::Middle, act_mouseRelease);
    
    act = inp.getAction("actionCheck");
    act->bind(&mouseWheel, &inp);
    inp.addKeyToAction(act, sf::Keyboard::C, act_keyRelease);

    
    act = inp.getAction("test2");
    act->bind(&test2);
    //inp.addKeyToAction(act, sf::Keyboard::A, act_keyRelease);
    //inp.addKeyToAction(act, sf::Keyboard::A, act_keyPress);
    
    inp.addKeyToAction(act, sf::Keyboard::B, act_keyDown);
    inp.addMouseToAction(act, sf::Mouse::Left, act_mouseMove);
    window.setKeyRepeatEnabled(false);

    
    
    // Start the game loop
    fps.step();
    fps.setColor(sf::Color::Black);
    fps.setPosition(10, 10);
    while (window.isOpen())
    {
        // this must be done before the event loop
        inp.updateDowns();
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

        fps.step();
        // Clear screen
        window.clear();

        // Draw the sprite
        //sprite.setColor(sf::Mouse::isButtonPressed(sf::Mouse::Left)?sf::Color::Red:sf::Color::White);
        window.draw(sprite);
        window.draw(fps);

        // Update the window
        window.display();
    }
    
    return EXIT_SUCCESS;
}
