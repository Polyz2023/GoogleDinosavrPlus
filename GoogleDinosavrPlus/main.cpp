#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class GAME
{
private:
    sf::Texture gusT;
    sf::Texture dinaT;
    sf::Texture cacT;

    sf::Sprite cacts;
    sf::Sprite gus;
    sf::Sprite dina;

    sf::Text nit;
    sf::Font nitF;

    float jumpSpeed = 0.0f;
    bool isJumping = false;
    float groundY = 600.f;
public:
    GAME() {
        gusT.loadFromFile("images/gus_v1.png");
        dinaT.loadFromFile("images/dina_v1.png");
        cacT.loadFromFile("images/cact.png");

        gus.setTexture(gusT);
        dina.setTexture(dinaT);
        cacts.setTexture(cacT);

        cacts.setScale(2.f, 2.f);
        cacts.setPosition(1500.f, 600.f);

        gus.setScale(2.f,2.f);
        gus.setPosition(250.f, groundY);
        
        nitF.loadFromFile("fonts/Roboto-Black.ttf");
        nit.setFont(nitF);
        nit.setCharacterSize(34);
        nit.setFillColor(sf::Color::Black);
    }

    sf::Sprite& getGus() {
        return gus;
    }

    sf::Sprite& getCact() {
        return cacts;
    }

    sf::Text& getNit() {
        return nit;
    }

    void Dvig() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isJumping) {
            jumpSpeed = -19.0f;
            isJumping = true;
        }

        if (isJumping) {
            gus.move(0, jumpSpeed);
            jumpSpeed += 0.5f;

            
            if (gus.getPosition().y >= groundY) {
               
                gus.setPosition(gus.getPosition().x, groundY);
                isJumping = false;
                jumpSpeed = 0.0f;
            }
        }
    }

    bool Blur(sf::Sprite one, sf::Sprite two) {
        if (one.getGlobalBounds().intersects(two.getGlobalBounds())) {
            return false;
            
        }
        else {
            return true;
        }
    }

};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1800, 800), "Google Dino Plus", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
   
    GAME obj;

    static bool play = true;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G && !play)
                play = true;
        }

        if (play) {
            obj.Dvig();

            bool go = obj.Blur(obj.getGus(), obj.getCact());
            play = go;

            window.clear(sf::Color::White);

            obj.getCact().move(-7.2f, 0);

            if (obj.getCact().getPosition().x < -200) {
                obj.getCact().setPosition(1900.f, 600.f);
            }

            window.draw(obj.getCact());
            window.draw(obj.getGus());

        }
        else {
            window.clear(sf::Color::Blue);

            obj.getNit().setString("Do you want to play again?\n Click 'G' if you want");
            obj.getNit().setPosition(window.getSize().x/2 -200, (window.getSize().y - 100 ) / 2);

            obj.getCact().setPosition(1900.f, 600.f);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
                play = true;
            }

            window.draw(obj.getNit());
        }
            
      

        window.display();
    }

    return 0;
}