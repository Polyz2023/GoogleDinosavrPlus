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

    sf::Text c;

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

        dina.setScale(3.f, 3.f);
        dina.setPosition(3300.f, 600.f);
        
        nitF.loadFromFile("fonts/Roboto-Black.ttf");
        nit.setFont(nitF);
        nit.setCharacterSize(34);
        nit.setFillColor(sf::Color::Black);

        nitF.loadFromFile("fonts/Roboto-Black.ttf");
        c.setFont(nitF);
        c.setCharacterSize(24);
        c.setFillColor(sf::Color::Black);
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

    sf::Text& getC() {
        return c;
    }

    sf::Sprite& getD() {
        return dina;
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

    sf::Image icon;
    if (!icon.loadFromFile("images/ico.png")) {
        // Обработка ошибки, если изображение не загружено
        return -1;
    }

    // Установка иконки для окна
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
   
    GAME obj;

    static int score=0;

    static bool play = true;

    static float timeSinceLastCoin=0;

    static float speed = -6.2f;
    static bool cF = true;

    static bool gh = true;

    sf::Clock cloc;

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

            
            if (obj.getCact().getPosition().x < -200) {
                obj.getCact().setPosition(1900.f, 600.f);
            }

            sf::Time elapsedCoin = cloc.restart();
            timeSinceLastCoin += elapsedCoin.asMilliseconds();

            if (timeSinceLastCoin >= 2.0f) {
                score=score+1;
                timeSinceLastCoin = 0.0f;
                obj.getC().setString("Score: "+std::to_string(score));
            }

            if (cF && (score == 1000 || score == 5000 || score == 10000 || score == 15000 || score == 20000 || score == 25000 || score == 30000 || score == 35000 || score == 40000 || score == 45000 || score == 50000 || score == 55000)) {
                speed--;
                cF = false;
                
                std::cout << speed;
            }
            else {
                cF = true;
            }

            if (score == 60000) {
                gh = false;

                obj.getD().setPosition(400.f, 600.f);
                obj.getCact().setPosition(2300.f, 600.f);
                
            }

            if (gh) obj.getCact().move(speed, 0);

            window.draw(obj.getCact());
            window.draw(obj.getGus());
            window.draw(obj.getC());
            window.draw(obj.getD());
        }

        else {
            window.clear(sf::Color::Blue);

            obj.getNit().setString("Do you want to play again?\n    Click 'G' if you want");
            obj.getNit().setPosition(window.getSize().x/2 -200, (window.getSize().y - 100 ) / 2);

            obj.getCact().setPosition(1900.f, 600.f);
            score = 0;
            speed = -6.2f;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
                play = true;
            }

            window.draw(obj.getNit());
        }
       
      

        window.display();
    }

    return 0;
}