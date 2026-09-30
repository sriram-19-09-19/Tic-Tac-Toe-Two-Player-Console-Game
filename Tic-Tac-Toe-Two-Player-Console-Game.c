#include <stdio.h>
#include <stdlib.h>


char board[3][3];


void resetBoard();
void printBoard();
int checkWin();
int isValidMove(int position);
int checkDraw();

void resetBoard() {
    int count = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            
            board[i][j] = '0' + count;
            count++;
        }
    }
}

void printBoard() {
    


    printf("=== TIC-TAC-TOE ===\n");
    printf(" Player 1 [X]  vs  Player 2 [O]\n");
   
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", board[0][0], board[0][1], board[0][2]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", board[1][0], board[1][1], board[1][2]);
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c  \n", board[2][0], board[2][1], board[2][2]);
    printf("     |     |     \n\n");
}

int isValidMove(int position) {
    
    if (position < 1 || position > 9) {
        return 0;
    }
   
   
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;
   
   
    if (board[row][col] == 'X' || board[row][col] == 'O') {
        return 0;
    }
   
    return 1;
}

int checkWin() {
    
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return 1;
        }
    }
   
    
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return 1;
        }
    }
   
   
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return 1;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return 1;
    }
   
    return 0;
}

int checkDraw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                return 0;
            }
        }
    }
    return 1; 
}

int main() {
    char restart_choice;
   
    do {
        int game_status = 0; // 0 = Ongoing, 1 = Win, 2 = Draw
        int current_player = 1; // Player 1 = X, Player 2 = O
        int position_input;
       
        resetBoard();
       
        while (game_status == 0) {
            printBoard();
           
            char current_mark = (current_player == 1) ? 'X' : 'O';
            printf("Player %d [%c], select an available position (1-9): ", current_player, current_mark);
           
            // Validate integer input parsing
            if (scanf("%d", &position_input) != 1) {
                printf("Invalid character type token sequence. Press enter and try again.\n");
                while (getchar() != '\n');
                continue;
            }
           
           
            if (!isValidMove(position_input)) {
                printf("Error: That move is out of bounds or the spot is already taken!\n");
                // Wait briefly for user acknowledgement without blocking infinite sweeps
                printf("Press enter to choose another position...");
                while (getchar() != '\n');
                getchar();
                continue;
            }
           
           
            int row = (position_input - 1) / 3;
            int col = (position_input - 1) % 3;
            board[row][col] = current_mark;
           
           
            if (checkWin()) {
                game_status = 1; // Win flag triggered
            } else if (checkDraw()) {
                game_status = 2; // Draw flag triggered
            } else {
                // Alternating player toggle state logic
                current_player = (current_player == 1) ? 2 : 1;
            }
        }
       
        
        printBoard();
        if (game_status == 1) {
            printf(" You Wins the Match \n");
        } else if (game_status == 2) {
            printf(" IT'S A DRAW! \n");
        }
       
       
        printf("Would you like to restart a fresh match? (y/n): ");
       
        scanf("%c", &restart_choice);
       
    } while (restart_choice == 'y' || restart_choice == 'Y');
   
  
    return 0;
}
