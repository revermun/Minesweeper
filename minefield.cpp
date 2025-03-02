#include "minefield.h"

#include <vector>

MineField::MineField(){

}

MineField::MineField(std::vector<std::vector<bool>> mineMatrix)
{

    for(std::vector<bool> row: mineMatrix){
        std::vector<std::shared_ptr<Cell>> rowVector;
        for (bool cellType: row){
            rowVector.push_back(std::make_shared<Cell>(cellType));
        }
        layout.push_back(rowVector);
    }
    isFirstTurn = 1;
    flagedMinesCount = 0;
    revealedCells = 0;
    gamestate = Ongoing;
}

MineField::~MineField()
{

}

void MineField::reveal_loop(int x, int y){
    std::vector<int> xOutOfBounds = {-1, int(columns)};
    std::vector<int> yOutOfBounds = {-1, int(rows)};
    for(int i = -1; i<2; i++){
        for (int j = -1; j<2; j++){
            if (x + j == xOutOfBounds[0] or x + j == xOutOfBounds[1] or y + i == yOutOfBounds[0] or y + i == yOutOfBounds[1])
            {
                //pass
            }
            else if(!layout[x+j][y+i]->isrevealed){
                reveal(x+j,y+i);
            }
        }

    }
}

void MineField::reveal(int x, int y)
{
    if (gamestate == Ongoing)
    {
        std::shared_ptr<Cell> targetCell = layout[x][y];
        if (!targetCell->isrevealed and !targetCell->isflaged) revealedCells++;
        targetCell->reveal();
        unsigned cellType = targetCell->cellType;
        if (targetCell->isflaged)
        {
            //pass
        }
        else if (isFirstTurn)
        {
            isFirstTurn = 0;
            std::vector<int> xOutOfBounds = {-1, int(columns)};
            std::vector<int> yOutOfBounds = {-1, int(rows)};
            for(int i = -1; i<2; i++){
                for (int j = -1; j<2; j++)
                {
                    if (x + j == xOutOfBounds[0] or x + j == xOutOfBounds[1] or y + i == yOutOfBounds[0] or y + i == yOutOfBounds[1])
                    {
                        //pass
                    }
                    else if(layout[x+j][y+i]->cellType == Mine)
                    {
                        int count = 0;
                        bool replaced = 0;
                        while (replaced == 0)
                        {
                            int newX = rand()%columns;
                            int newY = rand()%rows;
                            while(newY >= y-1 and newY <= y+1 and newX >= x-1 and newX <= x+1){newX = rand()%columns; newY = rand()%rows;}
                            if (count == 0){ std::cout << std::endl;}
//                            std::cout << newX << "|" << newY << ": " << layout[newX][newY]->cellType << std::endl;
                            count++;
                            if (count==100){
                                std::cout << "ploho" << std::endl;

                                for(int i = 0; i < columns; i++)
                                    {
                                        for(int j = 0; j < rows; j++)
                                        {
                                                std::cout << layout[i][j]->cellType;
                                        }
                                        std::cout << std::endl;
                                    }
                                std::cout << "\n" << x+j << "|" << y+i << std::endl;
                                break;
                            }

                            if (layout[newX][newY]->cellType == Empty)
                            {
                                layout[newX][newY]->cellType = Mine;
                                replaced = 1;
                            }
                        }
                        layout[x+j][y+i]->cellType = Empty;
                    }
                }
            }
            reveal_loop(x,y);
        }
        else if (cellType == Mine)
        {
            for(int i = 0; i < columns; i++)
            {
                for(int j = 0; j < rows; j++)
                {
                    if (layout[i][j]->cellType == Mine)
                    {
                        layout[i][j]->reveal();
                        gamestate = Defeat;
                    }
                }
            }
        }
        else if (minesNear(x,y)==flagsNear(x,y) or minesNear(x,y)==0)
        {
            std::vector<int> xOutOfBounds = {-1, int(columns)};
            std::vector<int> yOutOfBounds = {-1, int(rows)};
            reveal_loop(x,y);
        }
        if(minesCount == flagedMinesCount and revealedCells+minesCount == rows*columns)
        {
            gamestate = Win;
        }

    }
}

void MineField::flag(int x, int y)
{
    if (gamestate == Ongoing){
        layout[x][y]->flag();

        if (layout[x][y]->isflaged && layout[x][y]->cellType == Mine) flagedMinesCount++;
        else if (!layout[x][y]->isflaged && layout[x][y]->cellType == Mine) flagedMinesCount--;
        if(minesCount == flagedMinesCount and revealedCells+minesCount == rows*columns)
            {
                gamestate = Win;
            }
    }

}

unsigned MineField::flagsNear(int x, int y)
{
    unsigned res = 0;
    std::vector<int> xOutOfBounds = {-1, int(columns)};
    std::vector<int> yOutOfBounds = {-1, int(rows)};
    for(int i = -1; i<2; i++){
        for (int j = -1; j<2; j++){
            if (x + j == xOutOfBounds[0] or x + j == xOutOfBounds[1] or y + i == yOutOfBounds[0] or y + i == yOutOfBounds[1])
            {
                //pass
            }
            else{
                res += layout[x+j][y+i]->isflaged;
            }
        }

    }
    return res;
}


unsigned MineField::minesNear(int x, int y)
{
    unsigned res = 0;
    std::vector<int> xOutOfBounds = {-1, int(columns)};
    std::vector<int> yOutOfBounds = {-1, int(rows)};
    for(int i = -1; i<2; i++){
        for (int j = -1; j<2; j++){
            if (x + j == xOutOfBounds[0] or x + j == xOutOfBounds[1] or y + i == yOutOfBounds[0] or y + i == yOutOfBounds[1])
            {
                //pass
            }
            else{
                res += layout[x+j][y+i]->cellType;
            }
        }

    }
    return res;
}

void MineField::draw(QPainter& p)
{

    QRectF source(0.0, 0.0, 16.0, 16.0);
    QString fileName = "";
    QPixmap pixmap(CELLFILE);
    int i = 0;
    for(std::vector<std::shared_ptr<Cell>> row: layout){
        int j = 0;
        for (std::shared_ptr<Cell> cell: row){
            QRectF target(32.0*i, 32.0*j, 32.0, 32.0);
            if (cell->isflaged){
                fileName = FLAGFILE;

            }
            else if(!cell->isrevealed){
                fileName = CELLFILE;
            }
            else if(cell->cellType == Mine){
                fileName = MINEFILE;
            }
            else{
                int minesCount = minesNear(i,j);

                switch (minesCount)
                {
                    case 0: {fileName = EMPTYFILE; break;}
                    case 1: {fileName = ONEFILE;  break;}
                    case 2: {fileName = TWOFILE;   break;}
                    case 3: {fileName = THREEFILE; break;}
                    case 4: {fileName = FOURFILE;  break;}
                    case 5: {fileName = FIVEFILE;  break;}
                    case 6: {fileName = SIXFILE;   break;}
                    case 7: {fileName = SEVENFILE; break;}
                    case 8: {fileName = EIGHTFILE; break;}
                    default:{fileName = EMPTYFILE; break;}
                }
            }
            QPixmap pixmap(fileName);
            p.drawPixmap(target, pixmap, source);
            j++;
        }
        i++;
    }
}

unsigned MineField::getFlagedCellsCount()
{
    unsigned count = 0;
    for(std::vector<std::shared_ptr<Cell>> row: layout){
        std::vector<std::shared_ptr<Cell>> rowVector;
        for (std::shared_ptr<Cell> cell: row){
            if(cell->isflaged){count++;};
        }
    }
    return count;
}

void MineField::print()
{
    for(std::vector<std::shared_ptr<Cell>> row: layout){
        std::vector<std::shared_ptr<Cell>> rowVector;
        for (std::shared_ptr<Cell> cell: row){
            std::cout << cell->cellType;
        }
    }
    std::cout << layout.size();
}
