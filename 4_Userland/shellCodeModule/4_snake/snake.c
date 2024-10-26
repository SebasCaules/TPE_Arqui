#include <snake.h>
#include <stdLib.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

#define SQUARE_SIDE 768

void presentStartView();
int askNumOfPlayers();
void showPlayerScores();

int leftBorder;
int rightBorder;
int topBorder;
int bottomBorder;

int numOfPlayers;
int player1Score;
int player2Score;
int gameHasStarted;

int snake() {
    gameHasStarted = 0;
    leftBorder = (WINDOW_WIDTH - SQUARE_SIDE - 1);
    rightBorder = (WINDOW_WIDTH - 1);
    topBorder = 0;
    bottomBorder = SQUARE_SIDE - 1;
    presentStartView();

    startGame();
}

void presentStartView() {
    clearView();
    puts("Welcome to Snake game");
    puts("Player 1 uses W/A/S/D. Player 2 uses I/J/K/L.");
    puts("Press ESC to finish the game.");
    numOfPlayers = askNumOfPlayers();
    player1Score = player2Score = 0;
    clearView();
    puts("Press SPACE to start playing");

    // 32x32 grid
    // drawRectangle(0, 0, 24, 24, 0x00008000);

}

void startGame() {
    char key;

    while (1) {
        key = toLowercase(getchar());
        if (key == 32) {
            if (gameHasStarted) {
                continue;
            }
            clearView();
            drawPlayingView();
            gameHasStarted = 1;
            showPlayerScores();
        } else if (key == 'q') {
            // idealmente usar ESC cuando veamos como
            clearView();
            break;
        }


    }

}

void handleKeyPresses(char c) {
    switch (c) {
        case 'w':
        case 'a':
        case 's':
        case 'd':

        case 'i':
        case 'j':
        case 'k':
        case 'l':
    }
}

int askNumOfPlayers() {
    char buffer[2];
    int numOfPlayers;
    do {
        putsNoNewLine("Enter the number of players (1 / 2): ");
        gets(buffer, 2);
        numOfPlayers = stringToInt(buffer);
    } while (numOfPlayers != 1 && numOfPlayers != 2);
    return numOfPlayers;
}

void showPlayerScores() {
    printf("Player 1: %d\n", player1Score);
    if (numOfPlayers == 2) {
        printf("Player 2: %d\n", player2Score);
    }
}

void drawPlayingView() {
    if (gameHasStarted) {
        return;
    }
    drawRectangle(leftBorder, 0, 0, SQUARE_SIDE, 0x00FFFFFF); // left
    drawRectangle(leftBorder, 0, SQUARE_SIDE, 1, 0x00FFFFFF); // top
    drawRectangle(leftBorder, bottomBorder, SQUARE_SIDE, 1, 0x00FFFFFF); // bottom
    drawRectangle(rightBorder, 0, 0, SQUARE_SIDE, 0x00FFFFFF); // right
}
