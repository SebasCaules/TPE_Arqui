#include <snake.h>
#include <stdLib.h>
#include <random.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

#define CANVAS_SIDE 768
#define SQUARE_SIDE 32
#define GRID_SIZE (CANVAS_SIDE / SQUARE_SIDE)

#define INITIAL_SNAKE_LENGTH 3

#define BLACK 0x00000000
#define FOOD_COLOR 0x00FF0000
#define GREEN 0x0000FF00
#define BLUE 0x000000FF
#define BACKGROUND_COLOR 0x003b3b3b

#define BASE_TIME 200

#define INITIAL_SPACING 4

int leftBorder;

int numOfPlayers;
int gameHasStarted;

int difficulty;

char pressedKey;

typedef struct {
    int x, y;
} Position;

typedef struct {
    Position positions[GRID_SIZE * GRID_SIZE];;
    int length;
    Position direction;
    int color;
    int score;
} Snake;

Snake snake1;
Snake snake2;
Position food;

int snake() {
    leftBorder = (WINDOW_WIDTH - CANVAS_SIDE - 1);

    while (1) {
        gameHasStarted = 0;
        numOfPlayers = 1;
        presentStartView();
        startGame();

        if (!askReplay()) {
            break;
        }

    }

    clearView();
    return 0;

}

void presentStartView() {
    clearView();
    puts("Welcome to Snake game!");
    puts("Player 1 uses W/A/S/D. Player 2 uses I/J/K/L.");
    numOfPlayers = askNumOfPlayers();
    difficulty = askDifficulty();
    clearView();

}

void startGame() {
    awaitStart();
    play();
}

void awaitStart() {
    puts("Press SPACE to start playing...");

    while (1) {
        pressedKey = toLowercase(getchar());
        if (pressedKey == ' ') {
            if (gameHasStarted) {
                continue;
            }
            clearView();
            drawCanvas();
            gameHasStarted = 1;
            initializeSnakes();
            updatePlayerScores();
            placeFood();
            break;
        }
    }
}

void play() {
    int bufferSize;

    while(1) {

        bufferSize = 0;
        bufferSize = readInput(&pressedKey);

        if (bufferSize > 0) {
            handleKeyPresses(pressedKey);
        }

        checkSnake(&snake1);
        if (numOfPlayers == 2) {
            checkSnake(&snake2);
        }

        int collisionedSnake = checkCollisions(&snake1, &snake2);
        if (collisionedSnake && numOfPlayers == 1) {
            endWithMessage("Game Over!");
            break;
        } else if (collisionedSnake == 1) {
            endWithMessage("Player 2 Wins!");
            break;
        } else if (collisionedSnake == 2) {
            endWithMessage("Player 1 Wins!");
            break;
        }
        sleep(BASE_TIME / difficulty);
    }
}

void checkSnake(Snake * snake) {
    updateSnake(snake);
    if (checkFood(snake)) {

        // no anda el beep
        beep(500, 200);
        growSnake(snake);
        updateSnake(snake);
        snake->score++;
        updatePlayerScores();
        placeFood();
    }
}

void endWithMessage(char * message) {
    clearView();
    puts(message);
    printf("Player 1: %d\n", snake1.score);
    if (numOfPlayers == 2) {
        printf("Player 2 : %d\n", snake2.score);
    }
    sleep(2000);
    clearView();
}

int askReplay() {
    puts("Press SPACE to play again...");
    puts("Press q to quit...");

    while (1) {
        pressedKey = toLowercase(getchar());
        if (pressedKey == ' ') {
            return 1;
        } else if (pressedKey == 'q' || pressedKey == 'Q') {
            return 0;
        }
    }
}

void placeFood() {
    int randomPosition, xPos, yPos, isOnSnake;

    do {
        isOnSnake = 0;
        randomPosition = getRandomInt(0, GRID_SIZE * GRID_SIZE - 1);
        xPos = randomPosition / GRID_SIZE;
        yPos = randomPosition % GRID_SIZE;

        for (int i = 0; i < snake1.length; i++) {
            if (snake1.positions[i].x == xPos && snake1.positions[i].y == yPos) {
                isOnSnake = 1;
                break;
            }
        }

        if (numOfPlayers == 1) {
            continue;
        }

        for (int i = 0; i < snake2.length; i++) {
            if (snake2.positions[i].x == xPos && snake2.positions[i].y == yPos) {
                isOnSnake = 1;
                break;
            }
        }

    } while (isOnSnake);

    food.x = xPos;
    food.y = yPos;
    drawRectangle(leftBorder + xPos * SQUARE_SIDE, yPos * SQUARE_SIDE, SQUARE_SIDE, SQUARE_SIDE, FOOD_COLOR);
}

void initializeSnakes() {
    initializeSnake(&snake1, GREEN, -(INITIAL_SPACING / 2));
    if (numOfPlayers == 1) {
        return;
    }
    initializeSnake(&snake2, BLUE, INITIAL_SPACING / 2);
}

void initializeSnake(Snake * snake, int color, int offset) {
    snake->length = INITIAL_SNAKE_LENGTH;
    snake->direction.x = 1;
    snake->direction.y = 0;
    snake->color = color;
    snake->score = 0;
    for (int i = 0; i < snake->length; i++) {
        snake->positions[i].x = GRID_SIZE / 2 - i;
        snake->positions[i].y = GRID_SIZE / 2 - offset;
        drawSnakeSection(snake->positions[i].x, snake->positions[i].y, snake->color);
    }
}

void updateSnake(Snake * snake) {
    removeSnakeSection(snake->positions[snake->length-1].x, snake->positions[snake->length-1].y);
    for (int i = snake->length - 1; i > 0; i--) {
        snake->positions[i] = snake->positions[i-1];
    }
    snake->positions[0].x += snake->direction.x;
    snake->positions[0].y += snake->direction.y;
    drawSnakeSection(snake->positions[0].x, snake->positions[0].y, snake->color);
}

void growSnake(Snake * snake) {
    snake->length++;
    snake->positions[snake->length - 1] = snake->positions[snake->length - 2];
}

int checkCollisions(Snake * snake1, Snake * snake2) {
    if (checkCollisionForSnake(snake1)) {
        return 1;
    }
    if (numOfPlayers == 1) {
        return 0;
    }
    if (checkCollisionForSnake(snake2)) {
        return 2;
    }
    if (checkInterSnakeCollision(snake1, snake2)) {
        return 1;
    }
    if (checkInterSnakeCollision(snake2, snake1)) {
        return 2;
    }
    return 0;
}

int checkCollisionForSnake(Snake * snake) {
    if (snake->positions[0].x < 0 || snake->positions[0].x >= GRID_SIZE || 
        snake->positions[0].y < 0 || snake->positions[0].y >= GRID_SIZE) {
            return 1;
    }
    for (int i = 1; i < snake->length; i++) {
        if (snake->positions[0].x == snake->positions[i].x && 
            snake->positions[0].y == snake->positions[i].y) {
            return 1;
        }
    }
    return 0;
}

int checkInterSnakeCollision(Snake * snake1, Snake * snake2) {
    for (int i = 0; i < snake2->length; i++) {
        if (snake1->positions[0].x == snake2->positions[i].x && 
        snake1->positions[0].y == snake2->positions[i].y) {
            return 1;
        }
    }
    return 0;
}

int checkFood(Snake * snake) {
    return (snake->positions[0].x == food.x && snake->positions[0].y == food.y);
}

void handleKeyPresses(char c) {
    switch (c) {
        case 'w':
        case 'W':
            if (snake1.direction.y == 1) {
                break;
            }
            snake1.direction.x = 0;
            snake1.direction.y = -1;
            break;
        case 'a':
        case 'A':
            if (snake1.direction.x == 1) {
                break;
            }
            snake1.direction.x = -1;
            snake1.direction.y = 0;
            break;
        case 's':
        case 'S':
            if (snake1.direction.y == -1) {
                break;
            }
            snake1.direction.x = 0;
            snake1.direction.y = 1;
            break;
        case 'd':
        case 'D':
            if (snake1.direction.x == -1) {
                break;
            }
            snake1.direction.x = 1;
            snake1.direction.y = 0;
            break;
    }

    if (numOfPlayers == 1) {
        return;
    }

    switch(c) {
        case 'i':
        case 'I':
            if (snake2.direction.y == 1) {
                break;
            }
            snake2.direction.x = 0;
            snake2.direction.y = -1;
            break;
        case 'j':
        case 'J':
            if (snake2.direction.x == 1) {
                break;
            }
            snake2.direction.x = -1;
            snake2.direction.y = 0;
            break;
        case 'k':
        case 'K':
            if (snake2.direction.y == -1) {
                break;
            }
            snake2.direction.x = 0;
            snake2.direction.y = 1;
            break;
        case 'l':
        case 'L':
            if (snake2.direction.x == -1) {
                break;
            }
            snake2.direction.x = 1;
            snake2.direction.y = 0;
    }

}

void drawSnakeSection(int x, int y, int color) {
    drawRectangle(leftBorder + x * SQUARE_SIDE, y * SQUARE_SIDE, SQUARE_SIDE, SQUARE_SIDE, color);
}

void removeSnakeSection(int x, int y) {
    drawRectangle(leftBorder + x * SQUARE_SIDE, y * SQUARE_SIDE, SQUARE_SIDE, SQUARE_SIDE, BACKGROUND_COLOR);
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

int askDifficulty() {
    char buffer[2];
    int difficulty;
    do {
        putsNoNewLine("Enter the difficulty (1 - 5): ");
        gets(buffer, 2);
        difficulty = stringToInt(buffer);
    } while (difficulty < 1 && difficulty > 5);
    return difficulty;
}

void updatePlayerScores() {
    resetCursor();
    drawRectangle(0, 0, 200, 200, BLACK);
    printf("Player 1: %d\n", snake1.score);
    if (numOfPlayers == 2) {
        printf("Player 2: %d\n", snake2.score);
    }
}

void drawCanvas() {
    if (gameHasStarted) {
        return;
    }
    drawRectangle(leftBorder, 0, CANVAS_SIDE, CANVAS_SIDE, BACKGROUND_COLOR);
}
