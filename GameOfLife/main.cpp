#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <chrono>
#include <sstream>
#include "GameOfLife.h"


int main() {

    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT),"Test",sf::Style::None);
    window.setPosition(sf::Vector2i(0,0));
    GameOfLife GOL(window);
    GOL.fillCellMap(1);
    sf::VertexArray lastState;
    window.setKeyRepeatEnabled(true);
    bool keyPressed=false;

    Cell** cellptr;
    Cell* it;
    GOL.genPop();
    sf::Image image;
    if(image.loadFromFile("ytest.png"))
        return -1;
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if(event.type==sf::Event::Closed)
            {
                window.close();
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();

            }
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
                std::cout << GOL.returnCellIndex()  << std::endl;


            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::LControl){
                if (!keyPressed){
                    keyPressed = true;

                }




            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::LControl){
                if (keyPressed){
                    keyPressed = false;

                }

            }

        }

        window.clear();
        if(keyPressed){
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            GOL.LifeCycle();
            std::chrono::steady_clock::time_point end   = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            printf("Time = %lld ms\n", static_cast<long long int>(elapsed.count()));
            GOL.displayPop();
            GOL.displayCycleCount();
            sf::VertexArray drawArray= GOL.drawCell();
            lastState = drawArray;

            window.draw(drawArray);





            window.display();


        } else{
            GOL.displayCycleCount();
            GOL.displayPop();
            window.draw(GOL.drawAliveCells());
            //window.draw(image);
            window.display();
        }




    }
    return 0;
}