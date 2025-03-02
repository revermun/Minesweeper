#ifndef CELL_H
#define CELL_H

enum cellTypes {Empty = 0, Mine = 1};

class Cell
{
public:
    Cell(unsigned cellType);
    ~Cell();

    void reveal();
    void flag();
    bool isrevealed;
    bool isflaged;
    unsigned cellType;
};

#endif // CELL_H
