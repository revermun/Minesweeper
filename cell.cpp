#include "cell.h"

Cell::Cell(unsigned cellType)
{
    this->cellType = cellType;
    this->isflaged = 0;
    this->isrevealed = 0;
}

Cell::~Cell()
{

}

void Cell::reveal()
{
    if ((!this->isflaged) && (!this->isrevealed))
    {
        this->isrevealed = 1;
    }
    else
    {
        //pass
    }
}

void Cell::flag()
{
    if (!this->isrevealed){
        this->isflaged = !this->isflaged;
    }
}
