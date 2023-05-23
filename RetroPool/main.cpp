#include <SFML/Graphics.hpp>
#include <iostream>
#define GRID_SIZE 64
sf::Texture texture, items;
sf::Texture* p1, * p2;

int main()
{
    if (!texture.loadFromFile("assets/slot.png")) {
        std::cout << "texture not loading" << std::endl;
    }
    if (!items.loadFromFile("assets/items.png")) {
        std::cout << "texture not loading" << std::endl;
    }
    p1 = &texture;
    p2 = &items;
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    sf::RectangleShape grid(sf::Vector2f(GRID_SIZE, GRID_SIZE));
    grid.setTexture(p1);
    sf::Vector2f Gridsize(grid.getSize());
    sf::RectangleShape item(sf::Vector2f(GRID_SIZE, GRID_SIZE));
    item.setTexture(p2);
    sf::IntRect Itexture(0, 0, 32, 32);
    int indexL = 0;
    int indexT = 0;
    int rectnumber = 16;
    sf::Clock time;
    sf::Time t1;
    sf::FloatRect itemBound(item.getLocalBounds());
    bool mousepressed = false;
    bool itemstored = false;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos(sf::Mouse::getPosition(window));
            sf::Vector2i itemPos(item.getPosition());
            if (mousePos.x >= itemPos.x && mousePos.x <= itemPos.x + itemBound.width) {
                if (mousePos.y >= itemPos.y && mousePos.y <= itemPos.y + itemBound.height) {
                    mousepressed = true;
                    itemstored = false;
                }
            }
        }

        if (mousepressed) {
            sf::Vector2i mousePos(sf::Mouse::getPosition(window));
            item.setPosition(mousePos.x - 32.0f, mousePos.y - 32.0f);
        }

        item.setTextureRect(Itexture);
        //t1 = time.getElapsedTime();
        //std::cout << t1.asMilliseconds() << std::endl;
        if (time.getElapsedTime() >= sf::milliseconds(300)) {
            Itexture.left = 32 * indexL;
            Itexture.top = 32 * indexT;
            indexL++;
            time.restart();
        }
        if (indexL >= rectnumber) {
            indexT++;
            if (indexT >= 18) {
                rectnumber = 12;
            }
        }
        if (indexL >= rectnumber) {
            indexL = 0;
            Itexture.left = 0;
            if (indexT >= 19) {
                indexT = 0;
                rectnumber = 16;
            }
        }



        window.clear();
        float X = 64;
        float Y = 128;
        for (int i = 0; i < 3; i++) {
            for (int y = 0; y < 8; y++) {
                sf::Vector2i itemPos(item.getPosition());
                itemPos += sf::Vector2i(32, 32);
                sf::Vector2i gridPos(grid.getPosition());
                window.draw(grid);
                X += Gridsize.x;
                grid.setPosition(X, Y);
                if (itemPos.x >= X && itemPos.x <= X + Gridsize.x && !mousepressed && !itemstored) {
                    if (itemPos.y >= Y && itemPos.y <= Y + Gridsize.y && !mousepressed && !itemstored) {
                        item.setPosition(X, Y);
                        std::cout << "item stored" << " " << X << " " << Y << std::endl;
                        itemstored = true;
                    }
                }

            }
            Y += Gridsize.y;
            X = 64;
        }
        mousepressed = false;
        window.draw(item);
        window.display();
    }

    return 0;
}

// bool hello;
// game loop {
//   
//   input -> set hello to something;
//   game logic / physics -> i can move the sprite according to hello
//   rendering -> render normally