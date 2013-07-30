#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <sstream>

class FPS : public sf::Text {
    sf::Clock myClock;
    unsigned int mySteps;

    public:
    FPS(const sf::Font& font) : sf::Text("0", font), mySteps(0)
    {}

    float step()
    {
        ++mySteps;

        float time(myClock.getElapsedTime().asSeconds());

        if (time >= 1.f)
        {
            std::ostringstream str; str.precision(4);
            str<<mySteps/time;
            setString(str.str());
            mySteps = 0;
            myClock.restart();
        }
        return time;
    }
};
