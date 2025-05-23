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
vector<vector<bool>> truthBoard; 

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
            cout << "|_" << playerBoard[i][j] << "_|";
        } 
        cout << endl; 
    }
}

int checkNearbyMines(int x, int y){
    int numMines = 0; 
    for (int i = 0; i < 8; ++i) {
        if ((movesX[i] + x >= xMax) || (movesY[i] + y >= yMax) || (movesX[i] + x < 0) || (movesY[i] + y < 0)){
            continue;
        } else {
            if (mineBoard[movesY[i] + y][movesX[i] + x] == '*'){
                ++numMines; 
            }
        }
    }
    return numMines; 
}

void openZeros(int x, int y){
    int val = 0; 
    //out of bounds check
    if ((x < 0) || (x >= xMax) || (y < 0) || (y >= yMax) || (truthBoard[y][x] == true)){
        return; 
    }
    val = checkNearbyMines(x, y); 
    if (val != 0){
        playerBoard[y][x] = char(val + 48);
        truthBoard[y][x] = true; 
        return; 
    } else if (val == 0){
        playerBoard[y][x] = '0';
        truthBoard[y][x] = true; 
    } 
    //recursive for all zeros 
    openZeros(x + 1, y); 
    openZeros(x - 1, y); 
    openZeros(x, y + 1); 
    openZeros(x, y - 1); 
}

bool mineChecker (int x, int y) {
    int mineVal = 0; 
    if (mineBoard[y][x] == '*'){
        playerBoard[y][x] = '*'; 
        return true; 
    } else {
        mineVal = (checkNearbyMines(x, y) + 48); 
        playerBoard[y][x] = char(mineVal);
            if (playerBoard[y][x] == '0'){
                openZeros(x, y); 
            }
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
    //still have yet to implement lvl 4 lol 
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
    truthBoard.resize(dimensionY, vector<bool>(dimensionX, false));

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
        cout << "Select a coordinate: " << endl; 
        cin >> xSpot >> ySpot; 
        detonated = mineChecker(xSpot, ySpot);
        boardCreate(xMax, yMax); 
    }
    return 0;
}
