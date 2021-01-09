#define ROW 3
#define COL 3
void IniBoard(char board[ROW][COL],int row,int col);
void PrintBoard(char board[ROW][COL], int row, int col);
void PlayerMove(char board[ROW][COL], int row, int col);
void ComputerMove(char board[ROW][COL], int row, int col);
char IsEnd(char board[ROW][COL], int row, int col);
void Menu();
void Exit();
