#ifndef MINEFIELD_H
#define MINEFIELD_H

#include "cell.h"
//#include "romanstyle.h"
#include "arabicStyle.h"

#include <vector>
#include <memory>
#include <iostream>
#include <QPainter>

enum gamestates {Ongoing = 0, Win = 1, Defeat = 2};

class MineField
{
public:
    MineField(std::vector<std::vector<bool>> mineMatrix);
    MineField();
    ~MineField();

    void reveal(int x, int y);
    void flag(int x, int y);
    void print();
    void draw(QPainter& p);
    unsigned minesNear(int x, int y);
    unsigned flagsNear(int x, int y);
    void reveal_loop(int x, int y);

    std::vector<std::vector<std::shared_ptr<Cell>>> layout;

    unsigned getMinesCount()       {return minesCount;};
    unsigned getFlagedCellsCount();
    void setRows(unsigned rows)        {this->rows = rows;};
    void setColumns(unsigned columns)  {this->columns = columns;};
    void setMinesCount(unsigned mines) {this->minesCount = mines;};
    unsigned getGamestate()     {return gamestate;};

private:
    bool isFirstTurn;
    unsigned minesCount;
    unsigned rows;
    unsigned columns;
    unsigned revealedCells;
    unsigned gamestate;
    unsigned flagedMinesCount;
};

#endif // MINEFIELD_H
