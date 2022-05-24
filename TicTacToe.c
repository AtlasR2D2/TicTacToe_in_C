#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

const int numRows = 3;
const int numCols = 3;

void printGameBoard(char GameBoard_x[numRows][numCols]);
void PlayTicTacToe();
bool makeSelection(char GameBoard_x[numRows][numCols],char playerChoice);
bool checkGameOver(char GameBoard_x[numRows][numCols],char players_x[2],int Player1Ord,int Player2Ord);


int main(){
    // Game - Tic Tac Toe
    PlayTicTacToe();
    return 0;
}

void PlayTicTacToe(){
    char toke1nOptions[2]={'X','O'};
    char players[2];
    char playerChoice;
    int playerChoice_num;
    enum ActivePlayerChoices {Player1=0,Player2=1};
    int ActivePlayer = Player1;

    printf("--- Welcome to PlayTicTacToe ---\n");

    bool validChoice = false;

    while (!validChoice){
        printf("Player 1 choose your token (X, O): ");
        scanf(" %c",&playerChoice);
        switch (playerChoice) {
            case 'o':
            case 'O':
            {
                players[Player1]='O';
                players[Player2]='X';
                validChoice = true;
                break;
            }
            case 'x':
            case 'X':
            {
                players[Player1]='X';
                players[Player2]='O';
                validChoice = true;
                break;
            }
            default:
                printf("Invalid choice. Choose a valid token (X,O).\n");
        }
    }
    
    // TicTacToe Board
    char GameBoard_Choices[numRows][numCols];
    int k=0;
    for (int i=0;i<numRows;++i){
        for (int j=0;j<numCols;++j){
            GameBoard_Choices[i][j]=++k + '0';
        }
    }
    char GameBoard[numRows][numCols];
    for (int i=0;i<numRows;++i){
        for (int j=0;j<numCols;++j){
            GameBoard[i][j]='-';
        }
    }

    bool GameOver=false;
    
    
    while (!GameOver){
        if (ActivePlayer == Player1) {
            printf("Player 1, your turn.\n");
        }
        else {
            printf("Player 2, it's your turn.\n");
        }
        printf("Game Board Available Choices\n");
        printGameBoard(GameBoard_Choices);
        printf("Game Board\n");
        printGameBoard(GameBoard);

        validChoice = false;

        while (!validChoice){
            printf("--- Select a choice: ");
            scanf(" %c",&playerChoice);
            validChoice = makeSelection(GameBoard_Choices,playerChoice);
            if (!validChoice){
                printf("Invalid choice. Select Again.\n");
            }
            else {
                // Convert number in char to int form and normalise to 0 base
                playerChoice_num = playerChoice - '0' - 1;
            }
        }
        // Mark move on Game Board
        GameBoard_Choices[playerChoice_num / numRows][playerChoice_num % numCols] = '-';
        GameBoard[playerChoice_num / numRows][playerChoice_num % numCols] = players[ActivePlayer];
        // Check if game is over now
        GameOver = checkGameOver(GameBoard,players,Player1,Player2);

        if (!GameOver){
            // Switch players
            ActivePlayer = ActivePlayer == Player1 ? Player2 : Player1;
        }
    }

    printf("Game Board\n");
    printGameBoard(GameBoard);

    printf("Thank you for playing Tic Tac Toe.\n");

}

void printGameBoard(char GameBoard_x[numRows][numCols]){
    
    for (int i=0;i<numRows;++i){
        printf("[");
        for (int j=0;j<numCols;++j){
            if (j!=0){
                printf(", %c",GameBoard_x[i][j]);
            }
            else {
                printf("%c",GameBoard_x[i][j]);
            }
        }
        printf("]\n");
    }
}

bool checkGameOver(char GameBoard_x[numRows][numCols],char players_x[2],int Player1Ord,int Player2Ord){
    bool WinFlag = false;
    int Player1Count = 0;
    int Player2Count = 0;
    // Check if horizontal win
    for (int i=0;i<numRows;++i){
        WinFlag = false;
        Player1Count = 0;
        Player2Count = 0;
        for (int j=0;j<numCols;++j){
            if (GameBoard_x[i][j] == players_x[Player1Ord]){
                Player1Count++;
            }
            else if (GameBoard_x[i][j] == players_x[Player2Ord]){
                Player2Count++;
            }
        }
        if (Player1Count == numCols || Player2Count == numCols){
            WinFlag = true;
            if (Player1Count == numCols) {
                printf("\nPlayer 1 Wins!\n");
            }
            else {
                printf("\nPlayer 2 Wins!\n");
            }
            break;
        }
    }
    if (!WinFlag){
    // Check if vertical win
        for (int j=0;j<numCols;++j){
            WinFlag = false;
            Player1Count = 0;
            Player2Count = 0;
            for (int i=0;i<numRows;++i){
                if (GameBoard_x[i][j] == players_x[Player1Ord]){
                    Player1Count++;
                }
                else if (GameBoard_x[i][j] == players_x[Player2Ord]){
                    Player2Count++;
                }
            }
            if (Player1Count == numRows || Player2Count == numRows){
                WinFlag = true;
                if (Player1Count == numRows) {
                    printf("\nPlayer 1 Wins!\n");
                }
                else {
                    printf("\nPlayer 2 Wins!\n");
                }
                break;
            }
        }
    }
    if (!WinFlag){
    // Check if diagonal win
        // Left to Right
        Player1Count = 0;
        Player2Count = 0;
        for (int i=0,j=0;i<numRows && j<numCols;++i,++j){
            if (GameBoard_x[i][j] == players_x[Player1Ord]){
                Player1Count++;
            }
            else if (GameBoard_x[i][j] == players_x[Player2Ord]){
                Player2Count++;
            }
        }
        if (Player1Count == numCols || Player2Count == numCols){
            WinFlag = true;
            if (Player1Count == numCols) {
                printf("\nPlayer 1 Wins!\n");
            }
            else {
                printf("\nPlayer 2 Wins!\n");
            }
        }        
            
        if (!WinFlag){
        // Right to Left
            Player1Count = 0;
            Player2Count = 0;
            for (int i=numRows-1,j=0;i>=0 && j<numCols;--i,++j){
                if (GameBoard_x[i][j] == players_x[Player1Ord]){
                    Player1Count++;
                }
                else if (GameBoard_x[i][j] == players_x[Player2Ord]){
                    Player2Count++;
                }
            }
            if (Player1Count == numCols || Player2Count == numCols){
                WinFlag = true;
                if (Player1Count == numCols) {
                    printf("\nPlayer 1 Wins!\n");
                }
                else {
                    printf("\nPlayer 2 Wins!\n");
                }
            }
        }
    }
    // Check for Cats Game
    if (!WinFlag){
        Player1Count = 0;
        Player2Count = 0;
        for (int i=0;i<numRows;++i){
            for (int j=0;j<numCols;++j){
                if (GameBoard_x[i][j] == players_x[Player1Ord]){
                    Player1Count++;
                }
                else if (GameBoard_x[i][j] == players_x[Player2Ord]){
                    Player2Count++;
                }
            }
        }
        if ((Player1Count+Player2Count) == (numRows * numCols)){
            WinFlag = true;
            printf("\nCat's Game.\n");
        }
    }
    return WinFlag;
}

bool makeSelection(char GameBoard_x[numRows][numCols],char playerChoice){
    bool validChoice_x = false;
    for (int i=0;i<numRows;++i){
        for (int j=0;j<numCols;++j){
            if (GameBoard_x[i][j] == playerChoice){
                validChoice_x = true;
                break;
            }
        }
        if (validChoice_x){
            break;
        }
    }
    return validChoice_x;

}