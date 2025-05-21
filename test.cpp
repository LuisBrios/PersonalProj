#include <iostream>
#include <cstdlib> 
#include <vector> 
#include <ctime> 
using namespace std;

const int movesX[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int movesY[] = {-1, 0, 1, -1, 1, -1, 0, 1}; 
int xMax = 0;
int yMax = 0; 
vector<vector<char>> mineBoard; 
vector<vector<char>> playerBoard; 

void promptGame() {
    cout << "Choose your difficulty" << endl;
    cout << "1 - Easy" << endl;
    cout << "2 - Medium" << endl;
    cout << "3 - Hard" << endl; 
    cout << "4 - Random" << endl; 
    cout << "Disclaimer: Random entails a MINIMUM of 5 per dimension and a MINIMUM of 10 mines." << endl;
    cout << "            Random entails a MAXIMUM of 20 per dimension and a MAXIMUM of 100 mines." << endl << endl; 
}

void boardCreate (int x, int y) {
    for (int i = 0; i < y; ++i){
        for (int j = 0; j < x; ++j){
            //replace with playerboard later.
            cout << "|_" << mineBoard[i][j] << "_|";
        } 
        cout << endl; 
    }
}

//check mines near with moves. 
int checkNearbyMines(int y, int x){
    int numMines = 0; 
    for (int i = 0; i < 8; ++i) {
        if ((movesX[i] + x > xMax) || (movesY[i] + y > yMax) || (movesX[i] + x < 0) || (movesY[i] + y < 0)){
            continue;
        } else {
            if (mineBoard[y][x] == '*'){
                ++numMines; 
            }
        }
    }
    return numMines; 
}

bool mineChecker (int x, int y) {
    int mineVal = 0; 
    if (mineBoard[y][x] == '*'){
        return true; 
    } else {
        mineVal = checkNearbyMines(x, y);
        mineBoard[y][x] = mineVal; 
        return false; 
    }
}

void mineSetter(int x, int y, int n){
    int tempX = 0, tempY = 0;
    for (int i = 0; i < n; ++i){
        tempX = (rand() % x);
        tempY = (rand() % y);
        if (mineBoard[tempY][tempX] == '*'){
            --i;
        } else {
            mineBoard[tempY][tempX] = '*';
        }
    }
    boardCreate(x, y);
}

void mineInitiation(int lvl) {
    int dimensionX = 0, dimensionY = 0, numMines = 0;
    //1 = Easy, 2 = Medium, 3 = Hard, 4 = Random Mines
    if (lvl == 1){
        dimensionX = 5, dimensionY = 5, numMines = 10; 
    } else if (lvl == 2){
        dimensionX = 8, dimensionY = 8, numMines = 20; 
    } else if (lvl == 3){
        dimensionX = 11, dimensionY = 11, numMines = 30; 
    }
    yMax = dimensionY;
    xMax = dimensionX; 
    mineBoard.resize(dimensionY, vector<char>(dimensionX, '-'));
    playerBoard.resize(dimensionY, vector<char>(dimensionX, '-'));
    mineSetter(dimensionX, dimensionY, numMines);
}

int main() {
    int lvl = 1, xSpot = 0, ySpot = 0; 
    bool detonated = false; 

    srand(time(0));

    promptGame(); 
    cin >> lvl;
    while (lvl != 1 && lvl != 2 && lvl != 3 && lvl != 4){
        cout << "Invalid choice. Try again." << endl; 
        promptGame(); 
        cin >> lvl; 
    } 
    mineInitiation(lvl);
    while (detonated == false){
        //Soon, account for invalidnumbers being selected. So basically make board coords global soon lol.
        cout << "Select a coordinate: " << endl; 
        cin >> xSpot >> ySpot; 
        detonated = mineChecker(ySpot, xSpot);
        boardCreate(xMax, yMax); 
    }
    return 0;
}
