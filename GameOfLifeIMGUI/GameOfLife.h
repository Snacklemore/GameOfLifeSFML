//
// Created by root on 25.06.18.
//

#ifndef GAMEOFLIFE_GAMEOFLIFE_H
#define GAMEOFLIFE_GAMEOFLIFE_H


#include <vector>
#include <SFML/Graphics.hpp>
#define HEIGHT 512
#define WIDTH 1024

enum class Celltype{
    PREY = 1,
            PREDATOR = 2,
                    NOTHING = 3


};
class Cell{
    friend class GameOfLife;
private:
    sf::Color _color;
    sf::Vector2f _pos;
    Celltype _t_cell;
    sf::Vector2f _cellSize;
public:
    Cell(sf::Color color,sf::Vector2f pos, Celltype t_cell,sf::Vector2f cellsize){
        _color = color;
        _pos   = pos;
        _t_cell= t_cell;
        _cellSize = cellsize;

    }



};




class GameOfLife {
    friend class Cell;

private:
    sf::RenderWindow &_window;

public:
    sf::Text            _populationDisplay;
    sf::Text            _cycleCountDisplay;
    int                 _ROWSIZE=WIDTH/2;
    int                 _COLSIZE=HEIGHT/2;
    int                 _population;
    long int            _cycleCount;
    std::vector<int>    changeMap;
    std::vector<Cell>   _CellMap;
    bool              fillCellMap(int count);
    sf::VertexArray   drawCell();
    sf::VertexArray   drawAliveCells();
    std::vector<int>  aliveCells; // Fill this vector in genPop()!
    void updateAliveCells();//Call this in drawAliveCells()
    sf::Font font;

    GameOfLife(sf::RenderWindow &window):_window(window){
        _CellMap.reserve(_ROWSIZE*_COLSIZE);
        _population = 0;
        _cycleCount = 0; 
        font.loadFromFile("arial.ttf");
        _populationDisplay.setPosition(100,100);
        _cycleCountDisplay.setPosition(100,1000000);
    }
    sf::Vector2i getMousePos();
    bool   ChangeCell(int index,Celltype type);
    int    returnCellIndex();
    int    countNeighbours(int index);
    std::vector<Cell*> getCellNeighbours(int index);
    void   LifeCycle();
    void   genPop();
    void   displayPop();
    void   displayCycleCount();

    Cell* getTopCell        (int index);
    Cell* getBottomCell     (int index);
    Cell* getLeftCell       (int index);
    Cell* getRightCell      (int index);
    Cell* getTopLeftCell    (int index);
    Cell* getTopRightCell   (int index);
    Cell* getBottomRightCell(int index);
    Cell* getBottomLeftCell (int index);



};


#endif //GAMEOFLIFE_GAMEOFLIFE_H
