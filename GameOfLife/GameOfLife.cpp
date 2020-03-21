//
// Created by root on 25.06.18.
//

#include <iostream>
#include <sstream>
#include "GameOfLife.h"


bool GameOfLife::fillCellMap(int count) {
    for (int i = 0 ;i<(HEIGHT/2);i++){
        for ( int j= 0;j<(WIDTH/2);j++){
            _CellMap.push_back(Cell(sf::Color::Black,sf::Vector2f(j*2,i*2),Celltype::NOTHING,sf::Vector2f(2,2)));

        }

    }
    std::cout << _CellMap.size() << std::endl;

    //_CellMap[514]._color = sf::Color::Cyan;
    //_CellMap[1]._t_cell = Celltype::PREY;
    //_CellMap[0]._t_cell = Celltype::PREY;
    //_CellMap[513]._t_cell = Celltype::PREY;
    //_CellMap[512]._t_cell = Celltype::PREY;//0-511 TopBorder
    //_CellMap[1535]._color = sf::Color::Black;//0,512,1024,1536,2048...130560 %2=0 LeftBorder yDimension is HEIGHT/2 thus 0..255
    //_CellMap[1023]._color = sf::Color::Black;//130560..131071 BottomBorder,length= WITDH/2 thus 0..511
    ////_CellMap[100025]._color = sf::Color::Black;//511,1023,1535,2047..131071 %2=1 Rightborder
    //_CellMap[511]._color = sf::Color::Black;
    //_CellMap[131071]._color = sf::Color::Black;
    ////_CellMap[130046]._color = sf::Color::Black;
    //_CellMap[130560]._color = sf::Color::Black;
    //_CellMap[100030]._color = sf::Color::Black;
    //_CellMap[2047]._color   = sf::Color::Black;
}
sf::VertexArray GameOfLife::drawAliveCells() {
   sf::Color cellColor;
   sf::VertexArray drawArray(sf::Quads,_ROWSIZE*_COLSIZE*2);
   for (int i = 0;i<aliveCells.size();i++){
       int index = aliveCells[i];
       cellColor = sf::Color::Green;
       sf::RectangleShape Rect(_CellMap[index]._cellSize);
       Rect.setPosition(_CellMap[index]._pos);
       sf::FloatRect vrect = Rect.getLocalBounds();
       sf::Vector2f topleft(vrect.left,vrect.top);
       sf::Vector2f transformedTopLeft = Rect.getTransform()*topleft;

       sf::Vector2f bottomright(vrect.height,vrect.width);
       sf::Vector2f tranformedBottomRight = Rect.getTransform()*bottomright;

       sf::Vector2f bottomleft(vrect.left,vrect.width);
       sf::Vector2f transformedBottomLeft= Rect.getTransform()*bottomleft;

       sf::Vector2f topright(vrect.height,vrect.top);
       sf::Vector2f transformedTopRight = Rect.getTransform()*topright;
       drawArray.append(sf::Vertex(transformedTopLeft,cellColor));
       drawArray.append(sf::Vertex(transformedTopRight,cellColor));
       drawArray.append(sf::Vertex(tranformedBottomRight,cellColor));
       drawArray.append(sf::Vertex(transformedBottomLeft,cellColor));


   }

    return drawArray;
}


sf::VertexArray GameOfLife::drawCell() {

    sf::Color cellColor;

     sf::VertexArray drawArray(sf::Quads,_ROWSIZE*_COLSIZE*2);
      for(int i =0;i<changeMap.size();i++){
          int index=changeMap[i];
      if (_CellMap[index]._t_cell == Celltype::NOTHING)
            cellColor = sf::Color::Black;
        if (_CellMap[index]._t_cell == Celltype::PREDATOR)
            cellColor = sf::Color::Red;
        if(_CellMap[index]._t_cell == Celltype::PREY){
            cellColor = sf::Color::Green;
        }

        sf::RectangleShape Rect(_CellMap[index]._cellSize); 
        Rect.setPosition(_CellMap[index]._pos);
        sf::FloatRect vrect=Rect.getLocalBounds();
        sf::Vector2f topleft(vrect.left,vrect.top);
        sf::Vector2f transformedTopLeft = Rect.getTransform()*topleft;

        sf::Vector2f bottomright(vrect.height,vrect.width);
        sf::Vector2f tranformedBottomRight = Rect.getTransform()*bottomright;

        sf::Vector2f bottomleft(vrect.left,vrect.width);
        sf::Vector2f transformedBottomLeft= Rect.getTransform()*bottomleft;

        sf::Vector2f topright(vrect.height,vrect.top);
        sf::Vector2f transformedTopRight = Rect.getTransform()*topright;
        drawArray.append(sf::Vertex(transformedTopLeft,cellColor));
        drawArray.append(sf::Vertex(transformedTopRight,cellColor));
        drawArray.append(sf::Vertex(tranformedBottomRight,cellColor));
        drawArray.append(sf::Vertex(transformedBottomLeft,cellColor));






    }

    changeMap.clear();
    return drawArray;




}
int _rOWSIZE = WIDTH/2;
int _cOLSIZE = HEIGHT/2;
//border recognition should work with any size
static inline bool isTopBorder(int index){
    if (index>=0 && index <_rOWSIZE )
        return true;
    else return false;
}
static inline bool isBottomBorder(int index){
    if (index >= ((_rOWSIZE*_cOLSIZE)-_rOWSIZE) && index < (_rOWSIZE*_cOLSIZE))
        return true;
    else return false;
}
static inline bool isLeftBorder(int index){
    if(index % _rOWSIZE == 0 )
        return true;
    else return false;
}
static inline bool isRightBorder(int index){
    if (index % _rOWSIZE == _rOWSIZE-1)
        return true;
    else return false;
}
static inline bool isTopRightCorner(int index){
    if (index == _rOWSIZE-1)
        return true;
    else return false;
}
static inline bool isTopLeftCorner(int index){
    if(index == 0)
        return true;
    else return false;
}
static inline bool isBottomRightCorner(int index){
    if(index == _rOWSIZE*_cOLSIZE-1)
        return true;
    else return false;
}
static inline bool isBottomLeftCorner(int index){
    if(index ==(_rOWSIZE*_cOLSIZE)-_rOWSIZE)
        return true;
    else return false;
}
//hardcoded border recoginition need to be reworked for torus
std::vector<Cell*> GameOfLife::getCellNeighbours(int index) {
    //std::vector<Cell*> cellArr[8] = {nullptr,nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    std::vector<Cell*> cellArr(8,nullptr) ;

    if       (isTopBorder(index)){

        if (isTopRightCorner(index)){
            cellArr[0] = getLeftCell(index);
            cellArr[1] = getBottomCell(index);
            cellArr[2] = getBottomLeftCell(index);
            //search left,bottom,bottomleft

        }
        else if (isTopLeftCorner(index)){
            cellArr[0] = getBottomCell(index);
            cellArr[1] = getBottomRightCell(index);
            cellArr[2] = getLeftCell(index);
            //search left,bottom,bottomright


        } else{//left,bottomleft,bottome,bottomright,right
            cellArr[0] = getLeftCell(index);
            cellArr[1] = getBottomLeftCell(index);
            cellArr[2] = getBottomCell(index);
            cellArr[3] = getBottomRightCell(index);
            cellArr[4] = getRightCell(index);
        }//check for border,then go deeper and check for corners eg TopBorder
                                                                                                    // has two possible Corners eg. TopLeftCorner and TopRightCorner



    } else if(isBottomBorder(index)){
        if (isBottomLeftCorner(index)){
            cellArr[0] = getRightCell(index);
            cellArr[1] = getTopRightCell(index);
            cellArr[2] = getTopCell(index);
            //search right,topright,top


        } else if (isBottomRightCorner(index)){
            cellArr[0] = getLeftCell(index);
            cellArr[1] = getTopLeftCell(index);
            cellArr[2] = getTopCell(index);
            //search left,topleft,top

        } else{
            cellArr[0] = getLeftCell(index);
            cellArr[1] = getTopLeftCell(index);
            cellArr[2] = getTopCell(index);
            cellArr[3] = getTopRightCell(index);
            cellArr[4] = getRightCell(index);
            //search left,topleft,top,topright,right

        }


    } else if(isLeftBorder  (index)){
        cellArr[0] = getTopCell(index);
        cellArr[1] = getTopRightCell(index);
        cellArr[2] = getRightCell(index);
        cellArr[3] = getBottomRightCell(index);
        cellArr[4] = getBottomCell(index);

        //search top,topright,right,bottomright,bottom
    } else if(isRightBorder (index) ){
        cellArr[0] = getTopCell(index);
        cellArr[1] = getTopLeftCell(index);
        cellArr[2] = getLeftCell(index);
        cellArr[3] = getBottomLeftCell(index);
        cellArr[4] = getBottomCell(index);
        //search top,topleft,left,bottomleft,bottom
    }else  {
        cellArr[0] = getTopLeftCell(index);
        cellArr[1] = getTopCell(index);
        cellArr[2] = getTopRightCell(index);
        cellArr[3] = getRightCell(index);
        cellArr[4] = getBottomRightCell(index);
        cellArr[5] = getBottomCell(index);
        cellArr[6] = getBottomLeftCell(index);
        cellArr[7] = getLeftCell(index);
        //search left, right,top,down topleft, topright, bottomleft,bottomright
    }
    return cellArr;
    //CELLS
    //getTopCell          =      CellIndex-rowsize;
    //getBottomCell       =      CellIndex+rowsize;
    //getLeftCell         =      CellIndex-1;
    //getRightCell        =      CellIndex+1
    //getTopLeftCell      =     (CellIndex-rowsize)-1
    //getTopRightCell     =     (CellIndex-rowsize)+1
    //getBottomRightCell  =     (CellIndex+rowsize)+1
    //getBottomeLeftCell  =     (CellIndex+rowsize)-1
            //BORDERS
            //isTopBorder         => Index >=0 a&& Index < 512
            //isBottomBorder      => Index >= 130560 && Index < 131072
            //isLeftBorder        => Index % 512 == 0
            //isRightBorder       => Index % 512 == 511
    //CORNERS(
            //isTopRightCorner    => Index = 511
            //isTopLeftCorner     => Index = 0
            //isBottomRightCorner =>  131071
            //isBottomLeftCorner  =>  130560
}
sf::Vector2i GameOfLife::getMousePos() {
    sf::Vector2i pos;
    pos = sf::Mouse::getPosition(_window);

    return pos;
}
bool GameOfLife::ChangeCell(int index,Celltype type) {

    return false;
}
bool isLeft(int x){
    return x % 2 != 1;

}
bool isTop(int y){
    return y % 2 != 1;
}
int GameOfLife::returnCellIndex() {
    std::cout << _CellMap[0]._pos.x << "::"<< _CellMap[0]._pos.y << std::endl;
    sf::Vector2i pos = getMousePos();
    std::cout << pos.x <<","<< pos.y<<std::endl;
    //CellOrigin, search for coords in CellMap
    if(isLeft(pos.x) && isTop(pos.y)){
        for (int i = 0;i<_CellMap.size();i++){
            if(_CellMap[i]._pos.x == pos.x && _CellMap[i]._pos.y == pos.y){
                return i;
            }
        }

    }
    //Not CellOrigin, BotRight=>isLeft=false and isTop=false
    if(!(isLeft(pos.x)) && !(isTop(pos.y))){
        //Shift to origin to find correct cell: x-1,y-1
        pos.x -=1;
        pos.y -=1;
        //search cell
        for (int i = 0;i<_CellMap.size();i++){
            if(_CellMap[i]._pos.x == pos.x && _CellMap[i]._pos.y == pos.y){
                return i;
            }
        }

    }
    //Not origin, TopRight=> isTop = true and isLeft = false
    if( isTop(pos.y)&& !(isLeft(pos.x))){
        //shift to origin to find correct cell: x-1
        pos.x -=1;
        //search cell
        for (int i = 0;i<_CellMap.size();i++){
            if(_CellMap[i]._pos.x == pos.x && _CellMap[i]._pos.y == pos.y){
                return i;
            }
        }
    }
    //Not origin, BotLeft=> isTop = false and isLeft= true
    if(isLeft(pos.x) && !(isTop(pos.y))){
        //shift to origin to find correct cell: y-1
        pos.y-=1;
        //search cell
        for (int i = 0;i<_CellMap.size();i++){
            if(_CellMap[i]._pos.x == pos.x && _CellMap[i]._pos.y == pos.y){
                return i;
            }
        }

    }
    std::cout << _CellMap[0]._pos.x << "::"<< _CellMap[0]._pos.y << std::endl;


    return 0;
}

Cell *GameOfLife::getTopCell(int index) {
    Cell* cellptr;
    cellptr = &_CellMap[index-_ROWSIZE];
    return cellptr;
}

Cell *GameOfLife::getBottomCell(int index) {
    Cell *cellptr;
    cellptr= &_CellMap[index+_ROWSIZE];
    return cellptr;
}

Cell *GameOfLife::getLeftCell(int index) {
    Cell* cellptr;
    cellptr = &_CellMap[index-1];
    return cellptr;
}

Cell *GameOfLife::getRightCell(int index) {
    Cell* cellptr;
    cellptr = &_CellMap[index+1];
    return cellptr;

}

Cell *GameOfLife::getTopLeftCell(int index) {
    Cell* cellptr;
    cellptr = &_CellMap[(index-_ROWSIZE)-1];
    return cellptr;
}

Cell *GameOfLife::getTopRightCell(int index) {
    Cell* cellptr;
    cellptr =&_CellMap[(index-_ROWSIZE)+1];
    return cellptr;
}

Cell *GameOfLife::getBottomRightCell(int index) {
    Cell* cellptr;
    cellptr=&_CellMap[(index+_ROWSIZE)+1];
    return cellptr;
}

Cell *GameOfLife::getBottomLeftCell(int index) {
    Cell* cellptr;
    cellptr=&_CellMap[(index+_ROWSIZE)-1];
    return cellptr;
}

int GameOfLife::countNeighbours(int index) {
    std::vector<Cell*> cellptr = getCellNeighbours(index);
    int cellcounter=0;
    for (int i=0;i<8;i++){
        if(cellptr[i]== nullptr)
            break;
        if (cellptr[i]->_t_cell == Celltype::PREY || cellptr[i]->_t_cell == Celltype::PREDATOR ){
            cellcounter +=1;
        }

    }
    return cellcounter;

}

void GameOfLife::LifeCycle() {

    //scan board first and save all living cells
    //iterate over living cells getting all dead cells surrounding them
    //1. life Cycle starts
    // -> rules over life cells
    // -> rules over dead cells surrounding them
    // while applying rules to life cells, save every living cell
    // while applying rules to dead cells surrounding them saving every living cell as well
    // iterate over living cells getting dead cells and start over

    std::vector<Cell> helpCellMap;
    helpCellMap.reserve(_CellMap.size());
    helpCellMap = _CellMap;
    changeMap.reserve(_CellMap.size());
    aliveCells.clear();
    int popCounter=0;


    for(int i =0;i<((HEIGHT*WIDTH)/4);i++){

        int neighbours=0;
        neighbours=countNeighbours(i);
        if(neighbours==3 && !(_CellMap[i]._t_cell == Celltype::PREY)){
            helpCellMap[i]._t_cell = Celltype::PREY;
            changeMap.push_back(i);
            aliveCells.push_back(i);
            popCounter+=1;

            continue;
        }


        if((neighbours< 2 || neighbours>3) && !(_CellMap[i]._t_cell == Celltype::NOTHING)){
            helpCellMap[i]._t_cell = Celltype::NOTHING;
            changeMap.push_back(i);
            continue;
        }

        if((_CellMap[i]._t_cell == Celltype::PREY) && neighbours == 2 )
        {
            //helpCellMap[i]._t_cell = Celltype::PREY;
            changeMap.push_back(i);
            aliveCells.push_back(i);
        }
        neighbours = 0;




    }
    _population = popCounter;
    _CellMap=helpCellMap;
    _cycleCount+=1;

}
//TODO:Function to to set population with mousehold, giving back Index of set Cell!
void GameOfLife::genPop() {
    int popC = 0;
    for(int i = 1024;i<50000;i++){



        _CellMap[i]._t_cell = Celltype::PREY;
        aliveCells.push_back(i);
        popC++;

    }
    _population = popC;

}

void GameOfLife::displayPop() {
    std::stringstream popstring;
    popstring << _population;
    sf::Text display(popstring.str(),font,32);
    _window.draw(display);

}

void GameOfLife::displayCycleCount() {
    std::stringstream cyclestring;
    cyclestring << _cycleCount;
    sf::Text display(cyclestring.str(),font,32);
    display.setPosition(900,0);
    _window.draw(display);

}

