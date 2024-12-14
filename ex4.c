/******************
Name: Ariel Mizrahi
ID: 213458821
Assignment: ex4
*******************/
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#define NUM_OF_CHEERLEADERS 15
#define NUM_OF_ROWS 5
#define NUM_OF_COLUMNS 5
#define MAX_SIZE 20
int	task1_robot_paths(int column, int row);
float task2_human_pyramid(float weightMatrix [5][5],int column, int row);
int task3_parenthesis_validator(char c);
int task4_queens_battle(int dim, char grid[][MAX_SIZE], char symbols[], char placements[][MAX_SIZE], char placements_x[], char placements_y[], int current_symbol, int current_x, int current_y);
void task5_crossword_generator();

void find_and_add(int i, char c, char* v){
  if(!v[i]){
    v[i]=c;
    return;
  }
  if(v[i]!=c)
    find_and_add(i+1,c,v);
}

int main()
{
    int task = -1;
    do{
        printf("Choose an option:\n"
               "1. Robot Paths\n"
               "2. The Human Pyramid\n"
               "3. Parenthesis Validation\n"
               "4. Queens Battle\n"
               "5. Crossword Generator\n"
               "6. Exit\n");

        if (scanf("%d", &task)){
            scanf("%*[^\n]");
            scanf("%*c");
            switch (task) {
                case 6: {
                    printf("Goodbye!\n");
                    break;
                }
                case 1: {
                    int column, row;
                    printf("Please enter the coordinates of the robot (column, row):\n");
                    scanf("%d %d", &column, &row);
                    if (column <= 0 || row <= 0) {
                        printf("The total number of paths the robot can take to reach home is: 0\n");
                    }
                    else {
                        printf("The total number of paths the robot can take to reach home is: %d\n", task1_robot_paths(column, row));
                    }
                    break;
                }
                case 2: {
                    float weightMatrix[NUM_OF_ROWS][NUM_OF_COLUMNS] = {0.0};
                    float weightArr[NUM_OF_CHEERLEADERS];
                    printf("Enter 15 floating-point numbers:\n");
                    for (int i = 0; i < 15; i++) {
                        scanf("%f", &weightArr[i]);
                    }
                    int index = 0;
                    for (int row = 0; row < 5; row++) {
                        for (int col = 0; col <= row && index < 15; col++) {
                            weightMatrix[row][col] = weightArr[index++];
                        }
                    }
                    printf("\nThe resulting matrix is:\n");
                    for (int i = 0; i < 5; i++) {
                        for (int j = 0; j < 5; j++) {
                            printf("%.2f ,", task2_human_pyramid(weightMatrix,i, j));
                        }
                        printf("\n");
                    }
                break;
            }
            case 3: {
                    printf("Please enter a term for validation:\n");
                    if (task3_parenthesis_validator('\n')) {
                        printf("The parentheses are balanced correctly.\n");
                    }
                    else {
                        printf("The parentheses are not balanced correctly.\n");
                    }
                break;
            }
            case 4: {
                    char rows[MAX_SIZE+1] = {0};
                    char cols[MAX_SIZE+1] = {0};
                    int dim =0;
                    char grid[MAX_SIZE][MAX_SIZE] = {0};
              		char symbols[MAX_SIZE+1] = {0};
                    printf("Please enter the board dimensions:\n");
                    scanf("%d", &dim);
                    printf("Please enter the %d*%d puzzle board:\n", dim, dim);
                    scanf("%*[^\n]");
                    scanf("%*c");
                    for (int i = 0; i < dim; i++) {
                      for (int j = 0; j < dim; j++) {
                          scanf(" %c", &grid[i][j]);
                          find_and_add(0,grid[i][j], symbols);
                      }
                    }
                    for (int i = 0; i < dim; i++) {
                        for (int j = 0; j < dim; j++) {
                            printf(" %c", grid[i][j]);
                        }
                        printf("\n");
                    }
                    for (int i = 0; i < dim; i++) {
                        printf(" %c", symbols[i]);
                    }
                    printf("\n");
                    char finalGrid[MAX_SIZE][MAX_SIZE];
                    for (int i = 0; i < dim; i++) {
                        for (int j = 0; j < dim; j++) {
                            finalGrid[i][j] = 0;
                        }
                    }
                if (task4_queens_battle(dim,grid,symbols,finalGrid, rows, cols, 0, 0, 0)) {
                    printf("board ok\n");
                    for (int i = 0; i < dim; i++) {
                        for (int j = 0; j < dim; j++) {
                            printf(" %c", finalGrid[i][j] + '0');
                        }
                        printf("\n");
                    }
                }
                else {
                    for (int i = 0; i < dim; i++) {
                        for (int j = 0; j < dim; j++) {
                            printf(" %c", finalGrid[i][j] + '0');
                        }
                        printf("\n");
                    }
                    printf("board not ok\n");
                }
                break;
            }
            case 5: {
                task5_crossword_generator();
                break;
            }
            default: {
                printf("Please choose a task number from the list.\n");
                break;
            }
            }
        }
        else
        {
            scanf("%*s");
        }

    } while (task != 6);
}

int task1_robot_paths(int column, int row) {
    if (column == 0 && row == 0){
        return 1;
    }
    if (column < 0 || row < 0) {
        return 0;
    }
    return task1_robot_paths(column,row-1)+
           task1_robot_paths(column-1,row);
}

float task2_human_pyramid(float weightMatrix [5][5],int row, int column){
    if (column == -1 || row == -1) {
        return 0;
    }
    if (column == 0 && row == 0) {
        return weightMatrix[0][0];
    }
    return weightMatrix[row][column] + (0.5 * task2_human_pyramid(weightMatrix,row-1,column)) + (0.5 * task2_human_pyramid(weightMatrix,row-1,column-1));
}

int task3_parenthesis_validator(char closer) {
    char c;
    if (scanf("%c", &c)!= 1) {
        return 0;
    }
    if (c == closer) {
        return 1;
    }
    else if (c == ')' || c == ']' || c == '}' || c == '>' || c == '\n') {
        return 0;
    }
    if (c == '(') {
        if (!task3_parenthesis_validator(')')){
            return 0;
        }
    }
    if (c == '{') {
        if (!task3_parenthesis_validator('}')) {
            return 0;
        }
    }
    if (c == '[') {
        if (!task3_parenthesis_validator(']')) {
            return 0;
        }
    }
    if (c == '<') {
        if (!task3_parenthesis_validator('>')) {
            return 0;
        }
    }
    return task3_parenthesis_validator(closer);

}

int task4_queens_battle(int dim,
                        char grid[][MAX_SIZE],
                        char symbols[],
                        char placements[][MAX_SIZE],
                        char placements_x[],
                        char placements_y[],
                        int current_symbol,
                        int current_x,
                        int current_y) {

        printf("%d \n", current_symbol);

  	if(current_symbol == dim) {
      	return 1;
    }

  	// Checks if the symbol is the right one, and if we can place the queen in this spot.
  	if (grid[current_y][current_x] != symbols[current_symbol] ||
        placements_x[current_x] ||
        placements_y[current_y] ||
        placements[current_y-1][current_x-1] ||
        placements[current_y-1][current_x+1] ||
        placements[current_y+1][current_x-1] ||
        placements[current_y+1][current_x+1]) {
      	// Check if we reached the end of the grid.
      	if (current_x == dim-1 && current_y == dim -1) {
          return 0;
        }
      	return task4_queens_battle(dim, grid, symbols, placements, placements_x, placements_y, current_symbol, (current_x + 1) % dim, ((current_x + 1) / dim) + current_y);
    }

  	// Try to place the queen here.
  	placements[current_y][current_x] = 1;
  	placements_x[current_x] = 1;
  	placements_y[current_y] = 1;
  	if (task4_queens_battle(dim, grid, symbols, placements, placements_x, placements_y, current_symbol+1, 0, 0)) {
      	return 1;
    }
  	placements[current_y][current_x] = 0;
  	placements_x[current_x] = 0;
  	placements_y[current_y] = 0;
  	return task4_queens_battle(dim, grid, symbols, placements, placements_x, placements_y, current_symbol, (current_x + 1) % dim, ((current_x + 1) / dim) + current_y);
}

void task5_crossword_generator(){
}