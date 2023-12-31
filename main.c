/**
 * ENGG1110 Problem Solving by Programming
 *
 * Course Project
 *
 * I declare that the project here submitted is original
 * except for source material explicitly acknowledged,
 * and that the same or closely related material has not been
 * previously submitted for another course.
 * I also acknowledge that I am aware of University policy and
 * regulations on honesty in academic work, and of the disciplinary
 * guidelines and procedures applicable to breaches of such
 * policy and regulations, as contained in the website.
 *
 * University Guideline on Academic Honesty:
 *   https://www.cuhk.edu.hk/policy/academichonesty/
 *
 * Student Name  : NoBirds
 * Student ID    : <NULL>
 * Class/Section : <NULL>
 * Date          : <?>
 */

#include <stdio.h>
/* NO other header files are allowed */ // <- wtf ??

/* NO global variables are allowed */ // <- wtf ?????? seriously ?????? const int NUM = 9; typedef struct {int mat[9][9]} board; is gone

typedef signed char byte;
void initGameBoard(int gameBoard[][9], int puzzle[][9]);
void printGameBoard(int gameBoard[][9]);
int inputBoard(int gameBoard[][9], int x, int y, int sol[][9], int gameMode);
int checkFinish(int gameBoard[][9], int sol[][9]);
int checkSolutionDetail(int gameBoard[][9], int x, int y);
int checkFillable(int gameBoard[][9], int x, int y);
int isLockBoard(int gameBoard[][9]);
int savePuzzle(int gameBoard[][9], int sol[][9]);
int loadPuzzle(int gameBoard[][9], int sol[][9], int lsave);
void printSolution(int puzzle[][9],int solution[][9]);


/* The main function */
int main()
{
    /* Local variables */

    // Assume both mode uses same set of puzzle
    // In Part 2, read the puzzle and solution from puzzle.txt
    // You may input your puzzle to debug, e.g., replace some entries of the solution by 0 
    int myPuzzle[9][9];
    // The solution
    int mySolution[9][9];

    char ans;
    printf("Load the saved game (y/n)?", &ans);

    loadPuzzle(myPuzzle, mySolution, ans == 'y');

    // Game Board
    int gameBoard[9][9];

    // gameMode: {0: Easy  1: Hard}
    // chances is the no. of chances in hard mode
    // hintCount stores the no. of hint used.
    int gameMode = 0, chances = 3, hintCount = 0;
    
    while (1) {
        printf("Enter the game mode [0: Easy. 1: Hard]: ");
        scanf("%d", &gameMode);
        while(getchar() != '\n'); // consumes more than 1 characters
        if(gameMode == 1 || gameMode == 0) {
            printf("You have selected %s mode\n", gameMode ? "Hard" : "Easy");
            break;
        }
        else 
            printf("Invalid Input.\n");
    }

    // store x, y coordinate of a cell
    int x, y;

    // number will store the puzzle ID (player's puzzle selection)
    int number;

    // Create YOUR local variables
    /* Initialize the local variables */
    int win = 0, validIn = 0, inputValid = 0;
    int check = 0; 

    // Read the Game mode to gameMode
    // Repeats the input process for an invalid input
    // Set the Game mode and display the message

    // TODO: Read Game Mode and output selected mode

    // Call initGameBoard to read the puzzle to gameBoard
    // and call printGameBoard to print it
    /* Uncomment the following statements to test if they are implemented correctly.
       You can add more if you wish. But remember to delete them before submission*/

    initGameBoard(gameBoard, myPuzzle);
    printGameBoard(gameBoard);

    // The following line calls the helper function, which print the user inputs leading to a finished puzzle
    // printSolution(gameBoard, mySolution);

    // TODO: Your Easy/Hard mode Game starts
    // The following is the suggested workflow
    
    // While the game is not finished:
    while (win == 0){
        // Let the player select a cell
        //    Repeat the cell selection process if it is invalid
        printf("Select a row and column: ");
        scanf("%d%d", &x, &y);
        if (x > 9 || x < 0 || y > 9 || y < 0) {
            printf("Out of bound. Input Again.\n");
            continue;
        }
        else if (gameBoard[x][y] != 0) {
            printf("Occupied.\n");
            continue;
        } 
        
        // Print Game Board After player chose a valid cell (displayed as 'X')
        gameBoard[x][y] = -1;
        printGameBoard(gameBoard);

        // Receive input from the player by calling inputBoard().
        // Use the return value from inputBoard() for program control flow.
        int inp = inputBoard(gameBoard, x, y, mySolution, gameMode);
        // If inputBoard indicates invalid input, go back to cell selection
        if (inp == -1) {
            gameBoard[x][y] = 0;
            printGameBoard(gameBoard);
            continue;
        } 

        if (inp == 0) {
            int num = gameBoard[x][y];
            // check the answer for different game mode
            // e.g., call checkSolutionDetail() for Hard mode
            if (num != mySolution[x][y])
                if(gameMode == 0)
                    printf("Sorry, %d should not be placed at (%d, %d).\n", num, x, y); 
                else
                {
                    if(checkSolutionDetail(gameBoard, x, y)){
                        chances--;
                        printf("You have %d chances left.\n", chances);
                    }
                    
                    if (!chances) {
                        win = -1;
                        printf("You lost.\n");
                        break;
                    }
                }
                
            gameBoard[x][y] = 0;
        }
        else 
            hintCount++;

        // print the game board
        printGameBoard(gameBoard);
        if(isLockBoard(gameBoard)) {
            printf("Board is locked.\n");
            win = -1;
            printf("You lost.\n");
            break;
        }

        if (checkFinish(gameBoard, mySolution))
        {
            win = 1;
        }
        
        // If the player wins, exit the while loop, else continue the game.
    }

    if (win == 1)
        printf("Congratulations! You have finished a puzzle in %s mode %s %d %s",
            gameMode ? "hard" : "easy", 
            gameMode ? "with" : "and used",
            gameMode ? chances : hintCount,
            gameMode ? "chances left.\n" : "hints\n"
        );

    // Output the winning or losing message

    return 0;
}

// Initialize the specified game board.
void initGameBoard(int gameBoard[][9], int puzzle[][9]) {

    // TODO: Complete this part
    // Hint: Copies the content of puzzle to gameBoard
    for (byte i = 0; i < 9; i++)
        for (byte j = 0; j < 9; j++)
            gameBoard[i][j] = puzzle[i][j];
}

/* Display the specified game board on the screen.
   You are required to exactly follow the output format stated in the project specification.
   IMPORTANT: Using other output format will result in mark deduction. */
void printGameBoard(int gameBoard[][9]) {
    // TODO: Complete this part
    // Hint: 
    // 1. First, try to prints the content of gameBoard
    // 2. Use conditional statement to print ' ' or 'X' for the two cases (empty or selected cell).
    // 3. Add the borders, col/row numbers

    // brute force = nice
    printf("  012 345 678\n");

    for (byte i = 0; i < 9; i++) { 
        if (i % 3 == 0)
            printf(" +---+---+---+\n");

        printf("%d", i);
        for (byte j = 0; j < 9; j++) {
            if(j % 3 == 0) 
                printf("|");
            int n = gameBoard[i][j];
            if (n > 0)
                printf("%d", n);
            else if (n == 0)
                printf(" ");
            else if (n == -1) // selected
                printf("X");
            
        }
        printf("|\n");
    }

    printf(" +---+---+---+\n");
}

/* inputBoard() reads a char '1' to '9', or 'H' from the player.
    You need to apply input validation, output error message, and ask the player to retry if its input is invalid.
    gameMode indicates if the game is run in Easy (0) or Hard (1) mode, so that you can determine if hint is allowed.
    * The function returns 1 if 'H' is inputted (i.e., the player uses a hint), returns -1 if an invalid input is read, and 0 otherwise (valid input). *
    IMPORTANT: Using other output format will result in mark deduction. */
int inputBoard(int gameBoard[][9], int x, int y, int sol[][9], int gameMode){
    // TODO: Complete this part
    // Hint: Use while loop to keep scanning input from the player
    char choice;

    printf("Input a number [or H: hint]: ");
    scanf(" %c", &choice);
    while(getchar() != '\n');

    if (choice == 'H') {
        if (gameMode == 1) {
            printf("No hint in Hardmode.\n");
            return -1;
        }
        
        gameBoard[x][y] = sol[x][y];
        return 1;
    } 
    else if (choice <= '0' && choice > '9')
    {
        printf("Invalid input.\n");
        return -1;
    }
    
    int num = (int)(choice - '0');
    gameBoard[x][y] = num;
    return 0;

    
}



// This function outputs 1 if the gameBoard is finished (and identical to the solution), and 0 otherwise.
int checkFinish(int gameBoard[][9], int sol[][9]){
    // TODO: Complete this part
    for (byte i = 0; i < 9; i++)
        for (byte j = 0; j < 9; j++) {
            if(gameBoard[i][j] == 0 || gameBoard[i][j] != sol[i][j])
                return 0;
        }

    return 1;
}


/* * Hard Mode *
    Check the (x, y) cell in the game board to see if it conflicts with other numbers in the same row/column/subgrid.
    You need to output messages to indicate incorrect answer.
    if (x,y) cell causes conflict in 2 or more categories, all such messages will be printed.
    The function returns 1 if (x, y) causes conflicts, and 0 otherwise.
    Hint: The return value can be used to update chances in main.
    IMPORTANT: Using other output format will result in mark deduction. */

int checkSolutionDetail(int gameBoard[][9], int x, int y){
    // TODO: Complete this part
    int num = gameBoard[x][y];
    for (byte i = 0; i < 9; i++){
        if (i == y) continue;
        if (gameBoard[x][i] == num)
            return !!printf("Check again the numbers in row %d.\n", x);
    }
    for (byte j = 0; j < 9; j++) {
        if (j == x) continue;
        if (gameBoard[j][y] == num)
            return !!printf("Check again the numbers in column %d.\n", y);
    }

    byte subX = x / 3 * 3;
    byte subY = y / 3 * 3;

    for (byte i = 0; i < 3; i++)
        for (byte j = 0; j < 3; j++) {
            if (i+subX == x && j+subY == y) continue;
            if (gameBoard[i+subX][j+subY] == num)
                return !!printf("Check again the numbers in the subgrid where (%d, %d) is at.\n", x, y);
        }
    
    return 0;
}

/* * Part 2 *
    checkFillable() checks the row/column/subgrid that the cell (x, y) resides at given the current gameBoard.
    It determines if all the numbers in the same row + column + subgrid contain all numbers 1 - 9, i.e., the cell (x, y) cannot be filled (or is locked).
    It returns 0 if cell (x, y) is locked; and returns 1 if the cell (x, y) can be filled */
int checkFillable(int gameBoard[][9], int x, int y){
    // TODO: Complete this part
    int num[9] = {0};

    int num = gameBoard[x][y];
    for (byte i = 0; i < 9; i++){
        if (i == y) continue;
        int v = gameBoard[x][i];
        if (v == num || !v) continue;
        num[v-1]++;
    }
    for (byte j = 0; j < 9; j++) {
        if (j == x) continue;
        int v = gameBoard[j][y];
        if (v == num || !v) continue;
        num[v-1]++;
    }

    byte subX = x / 3 * 3;
    byte subY = y / 3 * 3;

    for (byte i = 0; i < 3; i++)
        for (byte j = 0; j < 3; j++) {
            if (i+subX == x && j+subY == y) continue;
            int v = gameBoard[i+subX][j+subY];
            if (v == num || !v) continue;
            num[v-1]++;
        }

    // checks if there are values not presented in the column, row and grid.
    for (byte i = 0; i < 9; i++) 
        if (num[i] == 0)
            return 1;

    return 0;
}

/* 
    isLockBoard() determines if the input gameBoard contains a locked cell.
    If there is a locked cell, it prints a locked cell and returns 1.
    It returns 0 if the game board is free of locked cell
    Hint: loop through all empty cell and use checkFillable to aid in checking the cell.
    */
int isLockBoard(int gameBoard[][9]){
    // TODO: Complete this part

    for (byte i = 0; i < 9; i++)
        for (byte j = 0; j < 9; j++) {
            if (gameBoard[i][j] == 0) continue;
            if (!checkFillable(gameBoard, i, j))
            {
                printf("Cell (%d, %d) is locked.\n", i, j);
                return 1;
            }
        }

    return 0;
}


/* * Part 2: Save and Load* */
// the savePuzzle function saves the gameBoard and solution to the file "saveGame.txt"
// You may add parameter to this function, e.g, the file to save.
// The program returns 1 if it successfully saves the file, and 0 otherwise.
int savePuzzle(int gameBoard[][9], int sol[][9]){
    // TODO: Complete this part
    FILE *fs = fopen("../saveGame.txt", "w");
    
    if (fs == NULL)
        return !!printf("Error in writing file.");

    for (byte i = 0; i < 9; i++) {
        for (byte j = 0; j < 9; j++) {
            fprintf(fs, "%d ", gameBoard[i][j]);
        }
        fprintf(fs, "\n");
    }
    fprintf(fs, "\n");

    for (byte i = 0; i < 9; i++) {
        for (byte j = 0; j < 9; j++) {
            fprintf(fs, "%d ", sol[i][j]);
        }
        fprintf(fs, "\n");
    }

    fclose(fs);
    printf("Game Saved.\n");
}

// the loadPuzzle function load the gameBoard and solution from the file "saveGame.txt"
// You may add parameter to this function, e.g, the file to load.
// The program returns 1 if it successfully loads the file, and 0 otherwise.
int loadPuzzle(int gameBoard[][9], int sol[][9], int lsave){
    // TODO: Complete this part
    FILE *fs;
    fs = fopen(lsave ? "saveGame.txt" : "../puzzle.txt", "r");
    if (fs == NULL)
        return !!printf("Error in reading file.\n");
    for (byte i = 0; i < 9; i++) {
        for (byte j = 0; j < 9; j++) {
            
            fscanf(fs, "%d ", &gameBoard[i][j]);
        }
        fscanf(fs, "\n");
    }
    for (byte i = 0; i < 9; i++) {
        for (byte j = 0; j < 9; j++) {
            
            fscanf(fs, "%d ", &sol[i][j]);
        }
        fscanf(fs, "\n");
    }
    fclose(fs);
}

// A helper function to craft a text file containing the inputs to fill in the puzzle according to the solution.
// Execute it to generate a text file that prints the inputs leading to a finished puzzle
// To Debug:
//  In Powershell, run: Get-Content .\textInput.txt | & .\main.exe
//  or simply run the program, copy and paste contents of the text file to console.
// You may modify the function as you wish
void printSolution(int puzzle[][9],int solution[][9]){
    FILE *fp;
    fp = fopen("textInput.txt", "w");
    if (fp == NULL) {printf("Error in writing file."); return;}

    fprintf(fp,"0\n"); // Change to 1 if runns in Hard mode
    for(int i=0; i<9; i++)
    for (int j=0; j<9; j++){
        if (puzzle[i][j]==0){
            fprintf(fp, "%d %d\n", i, j);
            fprintf(fp, "%d\n", solution[i][j]); // You may print a character to test Hint/Save-load function.
        }
    }
    fclose(fp);
}