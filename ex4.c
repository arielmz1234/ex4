/******************
Name: Ariel Mizrahi
ID: 2
Assignment: ex4
*******************/
#include <stdio.h>
#include <string.h>
#define NUM_OF_CHEERLEADERS 15
#define NUM_OF_ROWS 5
#define NUM_OF_COLUMNS 5
#define MAX_SIZE4 20
#define MAX_SIZE5 30
#define DET_LENGTH 4
#define MAX_WORD_LENGTH 15
#define MAX_INPUT 100
#define MAX_ATTEMPTS 1000
#define ROW 0
#define COLUMN 1
#define COORDINATES 2
#define DETAIL_ROW 0
#define DETAIL_COLUMN 1
#define DETAIL_LENGTH 2
#define DETAIL_DIRECTION 3
int task1RobotPaths(int column, int row);
float task2_human_pyramid(float weightMatrix[NUM_OF_ROWS][NUM_OF_COLUMNS], int column, int row);
int task3ParenthesisValidator(char c);
int task4QueensBattle(int dim, char grid[][MAX_SIZE4], char symbols[],int symbolsStart[][COORDINATES],int symbolsEnd[][COORDINATES], char placements[][MAX_SIZE4],
                        char placementsRows[], char placementsColumns[], int currentSymbol, int currentROW, int currentColumn);
int findAndAdd(int index, char c, char symbols[]);
int task5CrosswordGenerator(char grid[][MAX_SIZE5],char details[][DET_LENGTH+1], char words[][MAX_WORD_LENGTH+1],int slots,int dicSize, int placedWords[MAX_INPUT], int detailIndex,
    int wordIndex, int attempt, int maxSize5, int maxInput, int maxAttempts);
void insertWord(char direction, char grid[][MAX_SIZE5],char details[DET_LENGTH+1], char word[MAX_WORD_LENGTH+1]);
int canPlaceWord(char grid[][MAX_SIZE5],char details[DET_LENGTH+1],char word[MAX_WORD_LENGTH+1], int letterIndex);
int checkIfSizesMatch(char details[][DET_LENGTH+1],char words[][MAX_WORD_LENGTH+1],int dicSize,int slots,int detailIndex, int wordIndex);
void insertVerticalWord(char grid[][MAX_SIZE5],int row, int column, char word[MAX_WORD_LENGTH+1],int wordIndex);
void insertHorizontalWord(char grid[][MAX_SIZE5],int row, int column, char word[MAX_WORD_LENGTH+1],int letterIndex);
void resetArray(int array[MAX_INPUT], int index, int maxInput);
void resetGrid(char grid[][MAX_SIZE5], int row, int column, int maxSize5);
void swap(char words[][MAX_WORD_LENGTH + 1], int index1, int index2);
void reorderWords(char words[][MAX_WORD_LENGTH + 1], int index, int current);
void reorder(char words[][MAX_WORD_LENGTH + 1], int index);


int main() {
    int task = -1;
    do {
        printf("Choose an option:\n"
            "1. Robot Paths\n"
            "2. The Human Pyramid\n"
            "3. Parenthesis Validation\n"
            "4. Queens Battle\n"
            "5. Crossword Generator\n"
            "6. Exit\n");
        if (scanf("%d", &task)) {
            switch (task) {
                case 6: {
                    printf("Goodbye!\n");
                    break;
                }
                case 1: {
                    int column, row;
                    printf("Please enter the coordinates of the robot (column, row):\n");
                    scanf("%d %d", &column, &row);
                    // This checks if the input we got is 0,0 if so we are at the home
                    if (column <= 0 || row <= 0) {
                        printf("The total number of paths the robot can take to reach home is: 0\n");
                    } else {
                        // We print the value from the function
                        printf("The total number of paths the robot can take to reach home is: %d\n",
                               task1RobotPaths(column, row));
                    }
                    break;
                }
                case 2: {
                    /*in weightMatrix we will input the weights we got from the user that will be in weightArr,
                    we arrange them in a pyramid like structure that will simplify the calculation*/
                    float weightMatrix[NUM_OF_ROWS][NUM_OF_COLUMNS] = {0};
                    float weightArr[NUM_OF_CHEERLEADERS];
                    /* isNeg is a "flag" that we use to check if the input we got from the user was negative so we
                    need to break out of the loop and out of the case*/
                    int isNeg = 0;
                    printf("Please enter the weights of the cheerleaders:\n");
                    for (int i = 0; i < 15; i++) {
                        scanf("%f", &weightArr[i]);
                        if (weightArr[i] < 0) {
                            printf("Negative weights are not supported.\n");
                            isNeg =1;
                            break;
                        }
                    }
                    if (isNeg) {
                        break;
                    }
                    /* Here we input the weights we got from the user that will be in weightArr,
                    we arrange them in a pyramid like structure that will simplify the calculation*/
                    int index = 0;
                    for (int i = 0; i < 5; i++) {
                        for (int j = 0; j <= i && index < 15; j++) {
                            weightMatrix[i][j] = weightArr[index++];
                        }
                    }
                    printf("The total weight on each cheerleader is:\n");
                    // Print the weight of each cheerleader as instructed
                    for (int i = 0; i < 5; i++) {
                        for (int j = 0; j < 5; j++) {
                            if (i == 0 && j == 0) {
                                printf("%.2f ", task2_human_pyramid(weightMatrix, i, j));
                                continue;
                            }
                            if (weightMatrix[i][j]) {
                                printf("%.2f ", task2_human_pyramid(weightMatrix, i, j));
                            }
                        }
                        printf("\n");
                    }
                    break;
                }
                case 3: {
                    /* Consume the last char in the buffer so the function won't start taking the number 3 that is in
                    the buffer from the case selection*/
                    scanf("%*c");
                    printf("Please enter a term for validation:\n");
                    // Call the function with the "initial closer" \n
                    if (task3ParenthesisValidator('\n')) {
                        printf("The parentheses are balanced correctly.\n");
                    }
                    else {
                        printf("The parentheses are not balanced correctly.\n");
                    }
                    break;
                }
                case 4: {
                    /* rows and cols initialized to 0, are arrays that will be used in the function to create a flag for
                    the corresponding row and column so when a queen in placed in the grid, the row that the queen was
                    placed in changes to 1 and column that the queen was placed in changes to 1*/
                    char rows[MAX_SIZE4 + 1] = {0};
                    char cols[MAX_SIZE4 + 1] = {0};
                    // dim is the dimension we get from the user
                    int dim = 0;
                    // grid is the grid we get from the user
                    char grid[MAX_SIZE4][MAX_SIZE4] = {0};
                    // symbols is an array that contains each area(unique symbol) once
                    char symbols[MAX_SIZE4 + 1] = {0};
                    /*  in symbolsStart we save the first place in the grid that a unique symbol was placed in, after that we find
                    where the last symbol of that type was placed and save the coordinates in symbolsEnd
                    creating a "cube" surrounding the symbol type*/
                    int symbolsStart[MAX_SIZE4 + 1][COORDINATES] = {0};
                    int symbolsEnd[MAX_SIZE4 + 1][COORDINATES] = {0};
                    int knownSymbols [MAX_SIZE4+1] ={0};
                    // finalGrid is an empty grid we give the function to create our output on
                    char finalGrid[MAX_SIZE4][MAX_SIZE4] = {0};

                    printf("Please enter the board dimensions:\n");
                    scanf("%d", &dim);
                    // We check if the dimension the user inputs is valid
                    if (dim <= 0) {
                        printf("Please enter a valid dimension (0<dimension<21).\n");
                        break;
                    }
                    // We ask the user to input a grid and clear the buffer before
                    printf("Please enter a %d*%d puzzle board:\n", dim, dim);
                    scanf("%*[^\n]");
                    scanf("%*c");
                    /* Here we build the grid from the inputs of the user, also we build the symbols with the findAndAdd
                    function and symbolsStart and symbolsEnd*/
                    for (int i = 0; i < dim; i++) {
                        for (int j = 0; j < dim; j++) {
                            int currentSymbol = 0;
                            scanf(" %c", &grid[i][j]);
                            currentSymbol = findAndAdd(0, grid[i][j], symbols);
                            if (i > symbolsEnd[currentSymbol][ROW]) {
                               symbolsEnd[currentSymbol][ROW] = i;
                            }
                            if (j > symbolsEnd[currentSymbol][COLUMN]) {
                                 symbolsEnd[currentSymbol][COLUMN] = j;
                            }
                            if (!knownSymbols[currentSymbol]) {
                                knownSymbols[currentSymbol] = 1;
                                symbolsStart[currentSymbol][ROW] = i;
                                symbolsStart[currentSymbol][COLUMN] = j;
                            }
                            if (i < symbolsStart[currentSymbol][ROW]) {
                                symbolsStart[currentSymbol][ROW] = i;
                            }
                            if (j < symbolsStart[currentSymbol][COLUMN]) {
                                symbolsStart[currentSymbol][COLUMN] = j;
                            }
                        }
                    }
                    /* Now we check if we got a solution from the function (true)
                     * if so we print the finalGrid as requested*/
                    if (task4QueensBattle(dim, grid, symbols,symbolsStart,symbolsEnd,
                        finalGrid, rows, cols, 0, 0, 0)) {
                        printf("Solution: \n");
                        for (int i = 0; i < dim; i++) {
                            for (int j = 0; j < dim; j++) {
                                if (finalGrid[i][j] == 1) {
                                    printf("X ");
                                } else {
                                    printf("* ");
                                }
                            }
                            printf("\n");
                        }
                    } else {
                        printf("This puzzle cannot be solved.\n");
                    }
                    break;
                }
                case 5: {
                    /* Into dim we input the dimension we get from the user,
                     * slots the number of slots, dicSize the number of words in the dictionary*/
                    int dim = 0;
                    int slots = 0;
                    int dicSize = 0;
                    // details gets the details the user input and words the words
                    char details[MAX_INPUT][DET_LENGTH+1] = {0};
                    char words[MAX_INPUT + 1][MAX_WORD_LENGTH+1] = {0};
                    /* placedWords is a "flag" array we use in the function to update if a word was placed in to the
                    crossword it will be true for that index corresponding
                    with the index of that word in the word array*/
                    int placedWords[MAX_INPUT] = {0};
                    // grid is the final grid that the function will build (the crossword)
                    char grid[MAX_SIZE5][MAX_SIZE5] = {0};
                    printf("Please enter the dimensions of the crossword grid: \n");
                    scanf("%d", &dim);
                    printf("Please enter the number of slots in the crossword: \n");
                    scanf("%d", &slots);
                    printf("Please enter the details for each slot (Row, Column, Length, Direction): \n");
                    // We want to clear the buffer before getting chars so that we won't consume leftovers from the buffer
                    scanf("%*[^\n]");
                    scanf("%*c");
                    // We get the inputs from the user into details matrix
                    for (int i = 0; i < slots; i++) {
                        for (int j = 0; j < DET_LENGTH; j++) {
                            scanf(" %c", &details[i][j]);
                        }
                    }
                    // And clear the buffer for future use
                    scanf("%*[^\n]");
                    scanf("%*c");
                    printf("Please enter the number of words in the dictionary: \n");
                    scanf("%d", &dicSize);
                    // We want to validate that the number of words is at least the number of slots
                    while (dicSize < slots) {
                        printf(
                            "The dictionary must contain at least %d words. Please enter a valid dictionary size: \n",
                            slots);
                        scanf("%d", &dicSize);
                    }
                    printf("Please enter the words for the dictionary: \n");
                    // We want to clear the buffer before getting chars so that we won't consume leftovers from the buffer
                    scanf("%*[^\n]");
                    scanf("%*c");
                    // We get the inputs from the user into words matrix
                    for (int i = 0; i < dicSize; i++) {
                        scanf("%s", words[i]);
                    }
                    // And clear the buffer for future use
                    scanf("%*[^\n]");
                    scanf("%*c");
                    /* checkIfSizesMatch checks if every word length got a slot with the same length,
                    if not we know that the crossword isn't solvable */
                    if (!checkIfSizesMatch(details,words,dicSize,slots,0,0)) {
                        printf("This crossword cannot be solved.\n");
                    }
                    else {
                        /* We check if the crossword is solvable in this function, if so the function returns 1 and
                        builds the grid of the crossword into grid, otherwise it returns 0, and
                        we can print that the crossword isn't solvable*/
                        if (!task5CrosswordGenerator(grid, details, words, slots, dicSize, placedWords, 0,
                            0, 0, MAX_SIZE5, MAX_INPUT, MAX_ATTEMPTS)){
                            printf("This crossword cannot be solved.\n");
                        } else {
                            // We print the crossword as requested
                            for (int i = 0; i < dim; i++) {
                                for (int j = 0; j < dim; j++) {
                                    printf("|");
                                    if (grid[i][j] == 0) {
                                        printf(" # ");
                                    } else {
                                        printf(" %c ", grid[i][j]);
                                    }
                                    if (j == dim - 1) {
                                        printf("|");
                                    }
                                }
                                printf(" \n");
                            }
                        }
                    }
                    break;
                }
                default: {
                    printf("Please choose a task number from the list.\n");
                    break;
                }
            }
        } else {
            scanf("%*s");
        }
    } while (task != 6);
}

int task1RobotPaths(int column, int row) {
    // If we got home that means we found a path and we return 1
    if (column == 0 && row == 0) {
        return 1;
    }
    // If we reached beyond the grid that path isn't valid and we return 0
    if (column < 0 || row < 0) {
        return 0;
    }
    /* Here we check all possible routs where we move one left and
    one down and add all the number of viable paths we got*/
    return task1RobotPaths(column, row - 1) +
           task1RobotPaths(column - 1, row);
}

float task2_human_pyramid(float weightMatrix[NUM_OF_ROWS][NUM_OF_COLUMNS], int row, int column) {
    if (column == -1 || row == -1) {
        return 0;
    }
    if (column == 0 && row == 0) {
        return weightMatrix[0][0];
    }
    return weightMatrix[row][column] + (0.5 * task2_human_pyramid(weightMatrix, row - 1, column)) + (
               0.5 * task2_human_pyramid(weightMatrix, row - 1, column - 1));
}

int task3ParenthesisValidator(char closer) {
    // We input into c the next char that is in the buffer
    char c;
    // If scanf return something that isn't 1 that means we are done with the string
    if (scanf("%c", &c) != 1) {
        /* If we are done with the string and the last char we got from the buffer wasn't \n we clear the buffer
         * so the program won't get stuck or read chars from the buffer that we don't need*/
        if (c != '\n') {
            scanf("%*[^\n]");
            scanf("%*c");
        }
        return 0;
    }
    // If the char that was consumed from the buffer is equal to the closer (that matches each opener) we return 1
    if (c == closer) {
        return 1;
    }
    /* If the closer we got is not the closer that we are looking for and is another closer,
    that means the string is invalid and we return 0*/
    else if (c == ')' || c == ']' || c == '}' || c == '>' || c == '\n') {
        /* Once again we need to check if the last char we got from the buffer wasn't \n we clear the buffer
        so the program won't get stuck or read chars from the buffer that we don't need*/
        if (c != '\n') {
            scanf("%*[^\n]");
            scanf("%*c");
        }
        return 0;
    }
    /* In every if we check that the char we got from the buffer is one of the parenthesis openers
    if so we need to check the function with is matching closer, if the function returns false the if
    is true so we return 0 that means the string was invalid */
    if (c == '(') {
        if (!task3ParenthesisValidator(')')) {
            return 0;
        }
    }
    if (c == '{') {
        if (!task3ParenthesisValidator('}')) {
            return 0;
        }
    }
    if (c == '[') {
        if (!task3ParenthesisValidator(']')) {
            return 0;
        }
    }
    if (c == '<') {
        if (!task3ParenthesisValidator('>')) {
            return 0;
        }
    }
    // We get here if we didn't find any opener so we run the function again with the same closer
    return task3ParenthesisValidator(closer);
}
// This function helps with task4, in here we create the symbol array(each unique symbol is placed only once)
int findAndAdd(int index, char c, char symbols[]) {
    if (!symbols[index]) {
        symbols[index] = c;
        return index;
    }
    if (symbols[index] != c) {
        return findAndAdd(index + 1, c, symbols);
    }
    else {
        return index;
    }
}

int task4QueensBattle(int dim, char grid[][MAX_SIZE4], char symbols[], int symbolsStart[][COORDINATES],
                        int symbolsEnd[][COORDINATES], char placements[][MAX_SIZE4], char placementsRows[],
                        char placementsColumns[], int currentSymbol, int currentROW, int currentColumn) {
    // If we got here that means we placed a queen for each symbol and we can return 0
    if (currentSymbol == dim || symbols[currentSymbol] == 0) {

        return 1;
    }

    // Check if we reached the end of the grid.
    if (currentColumn > symbolsEnd[currentSymbol][ROW]) {

        return 0;
    }

    // Check if we can't put the Queen at this row at all, then we move to the next row completely.
    if (placementsColumns[currentColumn]) {
        return task4QueensBattle(dim, grid, symbols, symbolsStart, symbolsEnd, placements, placementsRows, placementsColumns,
                                   currentSymbol, symbolsStart[currentSymbol][COLUMN], currentColumn + 1);
    }
    /* Check if we can't place the queen here, (if we are not at the wanted area,
    if the column is free to place, and if all the diagonal are free*/
    else if (grid[currentColumn][currentROW] != symbols[currentSymbol] ||
             placementsRows[currentROW] ||
             (currentROW > 0 && currentColumn > 0 && placements[currentColumn - 1][currentROW - 1]) ||
             (currentROW < dim - 1 && currentColumn > 0 && placements[currentColumn - 1][currentROW + 1]) ||
             (currentROW > 0 && currentColumn < dim - 1 && placements[currentColumn + 1][currentROW - 1]) ||
             (currentROW < dim - 1 && currentColumn < dim - 1 && placements[currentColumn + 1][currentROW + 1])) {
        /* Then we need to move to the next place the is withing the grid of symbol start and symbol end
        (in symbolsStart we saved the first place in the grid that a unique symbol was placed in, after that we found
        where the last symbol of that type was placed and saved the coordinates in symbolsEnd
        creating a "cube" surrounding the symbol type*/
        int next_x = (currentROW + 1) % (symbolsEnd[currentSymbol][COLUMN] + 1);
        next_x = next_x == 0 ? symbolsStart[currentSymbol][COLUMN] : next_x;
        int next_y = currentColumn + ((currentROW + 1) / (symbolsEnd[currentSymbol][COLUMN] + 1));
        return task4QueensBattle(dim, grid, symbols,symbolsStart, symbolsEnd, placements, placementsRows,
                                    placementsColumns, currentSymbol,next_x, next_y);
             }

    // Try to place the queen here changing all the values corresponding to that placement to 1(true).
    placements[currentColumn][currentROW] = 1;
    placementsRows[currentROW] = 1;
    placementsColumns[currentColumn] = 1;
    // And then move on to the next symbol
    int next_symbol = currentSymbol + 1;
    /* If we return the function with the next symbol and get true that means we got true for all the symbols until we
    reached the final symbol, which means we solved the problem*/
    if (task4QueensBattle(dim, grid, symbols, symbolsStart, symbolsEnd, placements, placementsRows, placementsColumns,
                            next_symbol, symbolsStart[next_symbol][COLUMN], symbolsStart[next_symbol][ROW])) {
        return 1;
    }
    /* If we got here that means we were not able to place any queen for the current grid with all his previous
    placements so we need to "backtrack" resetting the current values to 0*/
    placements[currentColumn][currentROW] = 0;
    placementsRows[currentROW] = 0;
    placementsColumns[currentColumn] = 0;
    /* Then we need to move to the next place the is withing the grid of symbol start and symbol end
    (in symbolsStart we saved the first place in the grid that a unique symbol was placed in, after that we found
    where the last symbol of that type was placed and saved the coordinates in symbolsEnd
    creating a "cube" surrounding the symbol type*/
    int next_x = (currentROW + 1) % (symbolsEnd[currentSymbol][COLUMN] + 1);
    next_x = next_x == 0 ? symbolsStart[currentSymbol][COLUMN] : next_x;
    int next_y = currentColumn + ((currentROW + 1) / (symbolsEnd[currentSymbol][COLUMN] + 1));
    return task4QueensBattle(dim, grid, symbols,symbolsStart, symbolsEnd, placements, placementsRows, placementsColumns,
                                currentSymbol,next_x, next_y);
}

int task5CrosswordGenerator(char grid[][MAX_SIZE5],char details[][DET_LENGTH+1],
    char words[][MAX_WORD_LENGTH+1],int slots,int dicSize, int placedWords[MAX_INPUT], int detailIndex,
    int wordIndex, int attempt, int maxSize5, int maxInput, int maxAttempts) {
    /* If the detailIndex is equal to the number of details(slots)
    that means we found a word for each detail, and we built the crossword*/
    if (detailIndex == slots) {
        return 1;
    }
    // If the word that we are checking is used in another slot we enter here
    if (placedWords[wordIndex]) {
        /* Then we check if we got to the last word, if so we reorder the words array placing this word first and try
        again from the start with the grid and the array(placedWords) reset, rising the attempts counter by 1*/
        if (wordIndex >= dicSize-1) {
            reorder(words, wordIndex);
            resetGrid(grid, 0, 0,maxSize5);
            resetArray(placedWords, 0,maxInput);
            return task5CrosswordGenerator(grid, details, words, slots, dicSize, placedWords, 0,
                0, attempt + 1, maxSize5, maxInput, maxAttempts);;
        }
        // If we got here that means that we can check another word so we raise the wordIndex by 1
        return task5CrosswordGenerator(grid, details, words, slots, dicSize, placedWords, detailIndex,
            wordIndex + 1, attempt, maxSize5,  maxInput, maxAttempts);
    }
    // If we cant place a word on the grid we enter here
    if (!canPlaceWord(grid,details[detailIndex],words[wordIndex], 0)) {
        /* If we got to the last word and the attempt got to 1000 that means we tried every combination,
        and we return 0 because the crossword isn't solvable*/
        if (wordIndex >= dicSize - 1) {
            if (attempt == maxAttempts) {
                return 0;
            }
            /* If we got to here that means we got to the last word so we reorder the words array placing this word first
             and try  again from the start with the grid and the array(placedWords) reset, rising the attempts counter by 1*/
            reorder(words, wordIndex);
            resetGrid(grid, 0, 0,maxSize5);
            resetArray(placedWords, 0,maxInput);
           return task5CrosswordGenerator(grid, details, words, slots, dicSize, placedWords, 0,
               0, attempt + 1, maxSize5,  maxInput, maxAttempts);
        }
        // If we got here that means that we can check another word so we raise the wordIndex by 1
        return task5CrosswordGenerator(grid, details, words, slots, dicSize, placedWords, detailIndex,
            wordIndex + 1, attempt, maxSize5,  maxInput, maxAttempts);
    }
    /* If we got here that means we can place the word in that slot,
    so we use insert word and change the value in the placedWords array to 1 (true) for that word*/
    insertWord(details[detailIndex][DETAIL_DIRECTION], grid, details[detailIndex], words[wordIndex]);
    placedWords[wordIndex] = 1;
    // So now we move on to the next slot
    return task5CrosswordGenerator(grid, details, words, slots, dicSize, placedWords, detailIndex + 1,
        0, attempt, maxSize5,  maxInput, maxAttempts);
}
/* checkIfSizesMatch checks if every word length got a slot with the same length,
if not we know that the crossword isn't solvable*/
int checkIfSizesMatch(char details[][DET_LENGTH+1],char words[][MAX_WORD_LENGTH+1], int dicSize,int slots,
    int detailIndex, int wordIndex) {
    if (detailIndex == slots-1 && (int)strlen(words[wordIndex]) != (int)details[detailIndex][DETAIL_LENGTH] - '0') {
        return 0;
    }
    if ((int)strlen(words[wordIndex]) != (int)details[detailIndex][DETAIL_LENGTH] - '0') {
        return checkIfSizesMatch(details, words, dicSize, slots, detailIndex + 1, wordIndex);
    }
    if (wordIndex == dicSize-1) {
        return 1;
    }
     return checkIfSizesMatch(details, words, dicSize, slots,0, wordIndex + 1);
}
// insertHorizontalWord inserts the word horizontally
void insertHorizontalWord(char grid[][MAX_SIZE5],int row, int column, char word[MAX_WORD_LENGTH+1],int letterIndex) {
    if (!word[letterIndex])
        return;
    grid[row][column] = word[letterIndex];
    insertHorizontalWord(grid, row, column + 1, word, letterIndex+1);
}
// insertVerticalWord inserts the word vertically
void insertVerticalWord(char grid[][MAX_SIZE5],int row, int column, char word[MAX_WORD_LENGTH+1],int wordIndex) {
    if (!word[wordIndex])
        return;
    grid[row][column] = word[wordIndex];
    insertVerticalWord(grid, row + 1, column, word, wordIndex+1);
}
// insertWord checks if the direction of the detail is H or V and calls the corresponding functions to insert
void insertWord(char direction, char grid[][MAX_SIZE5],char details[DET_LENGTH+1], char word[MAX_WORD_LENGTH+1]) {
    int row = details[DETAIL_ROW] - '0';
    int column = details[DETAIL_COLUMN] - '0';
    if (direction == 'H') {
        insertHorizontalWord(grid,row,column,word,0);
    }
    else if (direction == 'V') {
        insertVerticalWord(grid,row,column,word,0);
    }
}
// canPlaceWord check if you can place a word in a detail
int canPlaceWord(char grid[][MAX_SIZE5],char details[DET_LENGTH+1],char word[MAX_WORD_LENGTH+1],int letterIndex) {
    int row = details[DETAIL_ROW] - '0';
    int column = details[DETAIL_COLUMN] - '0';
    int wordLength = details[DETAIL_LENGTH] - '0';
    char direction = details[DETAIL_DIRECTION];
    if ((int)(strlen(word)) != wordLength) {
        return 0;
    }
    int isFinished = wordLength - letterIndex;
    int currentRow = row + (direction== 'V' ? letterIndex : 0);
    int currentColumn = column + (direction == 'H' ? letterIndex : 0);
        if(grid[currentRow][currentColumn] == word[letterIndex] || !grid[currentRow][currentColumn]){
            if (isFinished == 1) {
                return 1;
            }
            return canPlaceWord(grid,details,word,letterIndex + 1);
        }
    return 0;
}
void resetGrid(char grid[][MAX_SIZE5], int row, int column, int maxSize5) {
    grid[row][column] = 0;
    if (row == maxSize5-1 && column == maxSize5-1) {
        return;
    }
    if (column == maxSize5-1) {
        return resetGrid(grid, row + 1, 0,maxSize5);
    }
    else {
        return resetGrid(grid, row, column + 1,maxSize5);
    }
}
void resetArray(int array[MAX_INPUT], int index, int maxInput) {
    array[index] = 0;
    if(index >= maxInput-1) {
        return;
    }
    return resetArray(array, index + 1, maxInput);
}
// Swaps between words in the array
void swap(char words[][MAX_WORD_LENGTH + 1], int index1, int index2) {
    char temp[MAX_WORD_LENGTH + 1];
    strcpy(temp, words[index1]);
    strcpy(words[index1], words[index2]);
    strcpy(words[index2], temp);
}

// Reorders the array
void reorderWords(char words[][MAX_WORD_LENGTH + 1], int index, int current) {
    // We need to stop when we reach the word at index 0
    if (current == 0) {
        return;
    }
    // Swap the current word with the previous one
    swap(words, current, current - 1);

    // Continue reordering
    reorderWords(words, index, current - 1);
}
// used to start reorderWords function
void reorder(char words[][MAX_WORD_LENGTH + 1], int index) {
    reorderWords(words, index, index);
}
