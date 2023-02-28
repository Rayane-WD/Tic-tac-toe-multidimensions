#ifndef GRID_H_
#define GRID_H_


void initializeGrid(char tab[], int size);
void displayGrid(char tab[], int edge_len, int dimension);

char getTokenByPlayer(int player);
bool isCaseFree(char tab[], int position);
int askForPosition(char tab[], int edge_len, int dimension,  int player);


bool checkHorizontalVictory2D(char tab[], int edge_len, char token);
bool checkVerticalVictory2D(char tab[], int edge_len, char token);
bool checkDiagonalVictory2D(char tab[], int edge_len, char token);


bool checkVictory2D(char tab[], int edge_len, int player);
bool checkVictory3D(char tab[], int edge_len, int player);
bool checkVictory4D(char tab[], int edge_len, int player);

bool checkVictory(char tab[], int edge_len, int player, int dimension);

#endif /* GRID_H_ */
