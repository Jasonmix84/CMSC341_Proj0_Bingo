// UMBC - CMSC 341 - Fall 2023 - Proj0
#include "bingo.h"
Bingo::Bingo(){
    m_trackCols = nullptr;
    m_trackRows = nullptr;
    m_helper = nullptr;
    m_helperSize = 0;
    m_card = nullptr;
    m_numRows = 0;
    m_numCols = 0;
    m_minBallVal = 0;
    m_maxBallVal = 0;
}

Bingo::Bingo(int rows, int columns, int min, int max){
    //cout << "overloaded constructor fires" << endl;
    if ((rows < 2 || rows > 15) || (((max - min) + 1)% CARDCOLS != 0)){
        //cout << "The row size is invalid so an empty object is made" << endl;
        //cout << "or sum of min and max is not divisible by 5 so empty object is made" << endl;
        //cout << "min value : " << min << " max value: " << max << " their range: " << ((max - min) + 1) << endl;
        m_trackCols = nullptr;
        m_trackRows = nullptr;
        m_helper = nullptr;
        m_helperSize = 0;
        m_card = nullptr;
        m_numRows = 0;
        m_numCols = 0;
        m_minBallVal = 0;
        m_maxBallVal = 0;
    }
    else if (columns != 5){
        //cout << "the number of columns is not 5 so an empty object is created" << endl;
        m_trackCols = nullptr;
        m_trackRows = nullptr;
        m_helper = nullptr;
        m_helperSize = 0;
        m_card = nullptr;
        m_numRows = 0;
        m_numCols = 0;
        m_minBallVal = 0;
        m_maxBallVal = 0;
    }
    else {
        //cout << "The else statment fires m_numcols min and max are populated" << endl;
        m_numRows = rows;
        m_numCols = columns;
        m_minBallVal = min;
        m_maxBallVal = max;
        m_trackCols = new int[columns];
        m_trackRows = new int[rows];
        m_helper = new Cell[m_maxBallVal];
        m_helperSize = m_maxBallVal;
        m_card = new Cell*[m_numRows]; 
        for (int i =0; i < m_numRows; i++){
            m_card[i] = new Cell[m_numCols];
        }
    }
}

bool Bingo::reCreateCard(int rows, int columns, int min, int max){
    //cout << "reCreateCard runs" << endl;
    //check if you can create another bingo card if you cant return 
    clear();
    Bingo(rows, columns, min, max); // hopefully this works although might not be what is needed
    if (initCard()){
        //cout << "reinitializing card if it successfully does so it function returns True" << endl;
        return true;
    }
    //cout << "something went wrong with initCard or the card was a blank object" << endl;
    return false;    
}

Bingo::~Bingo(){
    for (int i =0; i < m_numRows; i++){
            delete[] m_card[i];
        }
    delete[] m_card;
    m_card = nullptr;
}

void Bingo::clear(){
    //cout << "clear() runs" << endl;
    for (int i =0; i < m_numRows; i++){
            delete[] m_card[i];
        }
    delete[] m_card;
    delete[] m_trackCols;
    delete[] m_trackRows;
    delete[] m_helper;
    m_trackCols = nullptr;
    m_trackRows = nullptr;
    m_helper = nullptr;
    m_card = nullptr;
    m_helperSize = 0;
    m_numRows = 0;
    m_numCols = 0;
    m_minBallVal = 0;
    m_maxBallVal = 0;
}

bool Bingo::initCard(){
    //cout << "initCard() running" << endl;
    // there should be check here to see if the appropriate amount of data is allocated but i dont really get why
    if (m_helperSize == 0){// in theory if the helper size is zero then the object should be empty
        //cout << "initCard() was called on an empty object returning false" << endl;
        return false;
    }

    int storedRandNum = 0;
    int sections = ((m_maxBallVal - m_minBallVal) + 1) / CARDCOLS;
    int min = 0;
    int max = 0;
    int index = 0;
    int arrSize = (m_maxBallVal - m_minBallVal) + 1;
    int randNumArr[arrSize];  // create an int vector to pass to randNum.getShuffle()
    
    for (int col = 0; col < m_numCols; col++){
        min = m_minBallVal + (sections * col);
        max = m_minBallVal + (sections * (col + 1));
        
        Random randNum(min, max - 1, SHUFFLE);
        randNum.getShuffle(randNumArr); // fills up my vector
        for (int row = 0; row < m_numRows; row++){
           
            m_card[row][col] = Cell(row, col, randNumArr[index]);
            //cout << index << endl;
            //cout << randNumArr[index] <<endl;
            storedRandNum = m_card[row][col].getVal();
            m_helper[storedRandNum - 1] = Cell(row, col, storedRandNum);
            index++;
        }
        index = 0;
        
    }
    
    m_helperSize = m_maxBallVal;
    return true;
}

vector<int> Bingo::drawBalls(){
    vector<int> ballsDrawn; // create a vector to add in the balls;

    Random randNumSet(m_minBallVal, m_maxBallVal, SHUFFLE); // create a random object type shuffle

    randNumSet.getShuffle(ballsDrawn);

    //cout << "These are the numbers that have been added into ballsDrawn which i am returning probably to play" << endl;
    for (unsigned int i = 0; i < ballsDrawn.size(); i++){
        //cout << ballsDrawn.at(i) << endl;
    }

    return ballsDrawn;
}

int Bingo::play(int numDraws, vector<int> rndBalls){
    int hits = 0;
    int count = 0;
    int rowNum = 0;
    int colNum = 0;
    int storedInt = 0;

    for (int i = 0; i < m_numCols; i++){
        m_trackCols[i] = 0;
    }

    for (int i = 0; i < m_numRows; i++){
        m_trackRows[i] = 0;
    }

    while (count != numDraws){
        for (int i = 0; i < m_numCols; i++){
            if (m_trackCols[i] == m_numRows){
                return hits;
            }
        }

        for (int i= 0; i < m_numRows; i++){
            if (m_trackRows[i] == m_numCols){
                return hits;
            }
        }
        
        for (int i = 0; i < numDraws; i++){
            storedInt = rndBalls.at(i);
            if (storedInt == m_helper[storedInt].getVal()){
                colNum = m_helper[storedInt].getCol();
                rowNum = m_helper[storedInt].getRow();
                m_card[rowNum][colNum].setVal(EMPTYCELL);
                m_helper[storedInt].setVal(EMPTYCELL);

                m_trackCols[colNum]++;
                m_trackRows[rowNum]++;
                hits++;
            }
        }
        count++;
    }
    return -1;
}

const Bingo & Bingo::operator=(const Bingo & rhs){
    //overloaded assignment operator remember from proj5 last semester

    //prevent self-assignment
    //cout << "overloaded assignment operator running " << endl;
    if (this == &rhs){
        //cout << "self assignment if statment went off" << endl;
        return *this;
    }
    //clear out data
    for (int i =0; i < m_numRows; i++){
        //cout << "for loop for clearing data going off" << endl;
        delete[] m_card[i];
        }
    
    delete[] m_card;
    delete[] m_trackCols;
    delete[] m_trackRows;
    delete[] m_helper;
    //reset member variables
    m_trackCols = nullptr;
    m_trackRows = nullptr;
    m_helper = nullptr;
    m_card = nullptr;
    m_helperSize = 0;
    m_numRows = 0;
    m_numCols = 0;
    m_minBallVal = 0;
    m_maxBallVal = 0;
    

    //copy over data
    int count = 0;
    m_numRows = rhs.m_numRows;
    m_numCols = rhs.m_numCols;
    m_minBallVal = rhs.m_minBallVal;
    m_maxBallVal = rhs.m_maxBallVal;
    m_trackCols = new int[rhs.m_numCols];
    m_trackRows = new int[rhs.m_numRows];
    m_helper = new Cell[m_maxBallVal];
    m_helperSize = m_maxBallVal;
    m_card = new Cell*[m_numRows]; 
    for (int i =0; i < m_numRows; i++){
        m_card[i] = new Cell[m_numCols];
    }
    for (int row = 0; row < rhs.m_numRows; row++){
        for (int col = 0; col < rhs.m_numCols; col++){
            
            int rhsRow = rhs.m_card[row][col].getRow();
            
            int rhsCol = rhs.m_card[row][col].getCol();
            
            int rhsData = rhs.m_card[row][col].getVal();
            
            m_card[row][col] = Cell(rhsRow, rhsCol, rhsData);
            count++;
        }
    }

    return *this;
}

// The dump function renders the card in the terminal
// This function is provided to facilitate debugging
// Using this function as a test case will not be accepted
void Bingo::dumpCard(){
    cout << "  ";
    cout << "\033[1;35m B   I   N   G   O\033[0m";    
    cout << endl;
    for (int i=1;i <= m_numRows;i++){
        if ((i < 10))
            cout << "\033[1;35m" << "0" << i << " \033[0m";
        else
            cout << "\033[1;35m" << i << " \033[0m";
        for (int j=1;j<=m_numCols;j++){
            if (m_card[i-1][j-1].getVal() == EMPTYCELL)
                cout << "\033[1;31m" << m_card[i-1][j-1].getVal() << "\033[0m" << "  ";
            else
                cout << m_card[i-1][j-1].getVal() << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

// the overloaded equality operator for the Cell object
bool operator==(const Cell & lhs, const Cell & rhs){
    return ((lhs.m_col == rhs.m_col) &&
            (lhs.m_row == rhs.m_row) &&
            (lhs.m_value == rhs.m_value));
}
