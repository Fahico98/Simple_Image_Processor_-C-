
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_SIZE 100
#define MAX_COLUMN_SIZE 100
#define DIRECTORY_PATH "C:\\Users\\ASUS\\CLionProjects\\simpleImageProcessor\\"

char matrix[MAX_LINE_SIZE][MAX_COLUMN_SIZE];
int rows = 0, columns = 0;

void start();
void processSelection(int option);
void loadImage(char fileName[]);
void loadInMatrix(FILE *file);
void turnLeft();
void turnRight();
void deleteArea(int origin_x, int origin_y, int width, int height);
void deleteIsolatedPoints();
void computeWhitePercentage();
void printMatrix();
void resetMatrix();

int main() {
    printf("\n      [WELCOME TO THE SIMPLEST IMAGE PROCESSING PROGRAM IN THE WORLD]\n");
    printf("               *** Developed with the C programming language ***\n\n");
    start();
    return 0;
}

void start(){
    bool fileLoaded = false;
    int option = 0;
    while(option != 8){
        printf("\nOptions:\n");
        printf("  1. Load text file.\n");
        printf("  2. Print image.\n");
        printf("  3. Rotate image to left.\n");
        printf("  4. Rotate image to right.\n");
        printf("  5. Delete rectangular region.\n");
        printf("  6. Delete isolated points.\n");
        printf("  7. Calculate white percentage.\n");
        printf("  8. Exit.\n\n");
        printf("Your option:");
        scanf("%i", &option);
        printf("\n");
        if(option == 8) {
            printf("End of program. Good Bay...!\n");
        }else {
            if (fileLoaded == true) {
                processSelection(option);
            } else {
                if (option == 1) {
                    processSelection(option);
                    fileLoaded = true;
                } else {
                    printf("You must upload a file before attempting operations...!\n\n");
                }
            }
        }
    }
}

void processSelection(int option){
    switch(option){
        case 1:
            printf("Insert file name:");
            char fileName[] = {""};
            scanf("%s", fileName);
            loadImage(fileName);
            printf("File loaded successfully...\n\n");
            break;
        case 2:
            printMatrix();
            break;
        case 3:
            turnLeft();
            break;
        case 4:
            turnRight();
            break;
        case 5:
            printf("Insert your x coordinate of origin point of the region:");
            int x = 0;
            scanf("%i", &x);
            printf("\nInsert your y coordinate of origin point of the region:");
            int y = 0;
            scanf("%i", &y);
            printf("\nInsert the width of the region:");
            int width = 0;
            scanf("%i", &width);
            printf("\nInsert the height of the region:");
            int height = 0;
            scanf("%i", &height);
            deleteArea(x, y, width, height);
            printf("\nThe established region has been successfully deleted...\n\n");
            break;
        case 6:
            deleteIsolatedPoints();
            break;
        case 7:
            computeWhitePercentage();
            break;
        default:
            printf("The selected option is void...\n\n");
            break;
    }
}

void loadImage(char fileName[]){
    char filePath[1000];
    int i = 0, j = 0;
    while(DIRECTORY_PATH[i] != '\0'){
        filePath[i] = DIRECTORY_PATH[i];
        i++;
    }
    while(fileName[j] != '\0'){
        filePath[i] = fileName[j];
        i++;
        j++;
    }
    filePath[i] = '\0';
    FILE *imageFile = fopen(filePath, "r");
    loadInMatrix(imageFile);
    fclose(imageFile);
}

void loadInMatrix(FILE *file){
    resetMatrix();
    if(file == NULL){
        perror("An error has been occurred trying to load the file...");
        exit(0);
    }else{
        char line[MAX_LINE_SIZE];
        fgets(line, MAX_LINE_SIZE, file);
        char *token = strtok(line, " ");
        int i, j;
        for(i = 0; i < 2; i++) {
            if (i == 0) {
                rows = atoi(token) - 1;
            } else {
                columns = atoi(token);
            }
            token = strtok(NULL, " ");
        }
        int endLine = 0;
        for(i = 0; i <= rows; i++){
            fgets(line, MAX_COLUMN_SIZE, file);
            endLine = 0;
            for (j = 0; j < columns; j++) {
                if(endLine == 1){
                    matrix[i][j] = '-';
                }else{
                    if(line[j] == 'X'){
                        matrix[i][j] = 'X';
                    }else if(line[j] == '\0' || line[j] == '\n'){
                        matrix[i][j] = '-';
                        endLine = 1;
                    }else{
                        // For test...
                        if(line[j] == ' '){
                            matrix[i][j] = '-';
                        }else{
                            matrix[i][j] = line[j];
                        }
                    }
                }
            }
            matrix[i][columns] = '\n';
        }
    }
}

void turnLeft(){
    int i, j, k;
    char bufferMatrix[MAX_LINE_SIZE][MAX_COLUMN_SIZE];
    for(i = 0; i < rows; i++){
        for(j = columns - 1; j >= 0; j--){
            bufferMatrix[columns - j - 1][i] = matrix[i][j];
        }
    }
    resetMatrix();
    int temp = rows;
    rows = columns;
    columns = temp;
    for(k = 0; k < rows; k++){
        bufferMatrix[k][columns] = '\n';
    }
    for (i = 0; i < rows; i++) {
        for(j = 0; j <= columns; j++){
            matrix[i][j] = bufferMatrix[i][j];
        }
    }
}

void turnRight(){
    int i, j, k;
    char bufferMatrix[MAX_LINE_SIZE][MAX_COLUMN_SIZE];
    for(i = 0; i < rows; i++){
        for(j = 0; j < columns; j++){
            bufferMatrix[j][rows - i - 1] = matrix[i][j];
        }
    }
    resetMatrix();
    int temp = rows;
    rows = columns;
    columns = temp;
    for(k = 0; k < rows; k++){
        bufferMatrix[k][columns] = '\n';
    }
    for (i = 0; i < rows; i++) {
        for(j = 0; j <= columns; j++){
            matrix[i][j] = bufferMatrix[i][j];
        }
    }
}

void deleteArea(int origin_x, int origin_y, int width, int height){
    for(int i = origin_y; i < origin_y + height; i++){
        for(int j = origin_x; j < origin_x + width; j++){
            matrix[i][j] = '-';
        }
    }
}

void deleteIsolatedPoints(){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            if(matrix[i][j] == 'X') {
                char neighbours[8] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
                int isolated = 1;
                if (i == 0) {
                    if (j == 0) {
                        neighbours[0] = matrix[i][j + 1];
                        neighbours[1] = matrix[i + 1][j + 1];
                        neighbours[2] = matrix[i + 1][j];
                        for (int k = 0; k < 3; k++) {
                            if (neighbours[k] == 'X') {
                                isolated = 0;
                                break;
                            }
                        }
                        matrix[i][j] = (isolated == 1) ? '-' : 'X';
                    }else if(j == columns - 1){
                        neighbours[0] = matrix[i + 1][j];
                        neighbours[1] = matrix[i + 1][j - 1];
                        neighbours[2] = matrix[i][j - 1];
                        for (int k = 0; k < 3; k++) {
                            if (neighbours[k] == 'X') {
                                isolated = 0;
                                break;
                            }
                        }
                        matrix[i][j] = (isolated == 1) ? '-' : 'X';
                    }else{
                        neighbours[0] = matrix[i][j + 1];
                        neighbours[1] = matrix[i + 1][j + 1];
                        neighbours[2] = matrix[i + 1][j];
                        neighbours[3] = matrix[i + 1][i - 1];
                        neighbours[4] = matrix[i][j - 1];
                        for (int k = 0; k < 5; k++) {
                            if (neighbours[k] == 'X') {
                                isolated = 0;
                                break;
                            }
                        }
                        matrix[i][j] = (isolated == 1) ? '-' : 'X';
                    }
                }else if(i == rows - 1){
                    if (j == 0) {
                        neighbours[0] = matrix[i - 1][j];
                        neighbours[1] = matrix[i - 1][j + 1];
                        neighbours[2] = matrix[i][j + 1];
                        for (int k = 0; k < 3; k++) {
                            if (neighbours[k] == 'X') {
                                isolated = 0;
                                break;
                            }
                        }
                        matrix[i][j] = (isolated == 1) ? '-' : 'X';
                    }else if(j == columns - 1){
                        neighbours[0] = matrix[i][j - 1];
                        neighbours[1] = matrix[i - 1][j - 1];
                        neighbours[2] = matrix[i - 1][j];
                        for (int k = 0; k < 3; k++) {
                            if (neighbours[k] == 'X') {
                                isolated = 0;
                                break;
                            }
                        }
                        matrix[i][j] = (isolated == 1) ? '-' : 'X';
                    }else{
                        neighbours[0] = matrix[i][j - 1];
                        neighbours[1] = matrix[i - 1][j - 1];
                        neighbours[2] = matrix[i - 1][j];
                        neighbours[3] = matrix[i - 1][i + 1];
                        neighbours[4] = matrix[i][j + 1];
                        for (int k = 0; k < 5; k++) {
                            if (neighbours[k] == 'X') {
                                isolated = 0;
                                break;
                            }
                        }
                        matrix[i][j] = (isolated == 1) ? '-' : 'X';
                    }
                }else{
                    neighbours[0] = matrix[i][j + 1];
                    neighbours[1] = matrix[i + 1][j + 1];
                    neighbours[2] = matrix[i + 1][j];
                    neighbours[3] = matrix[i + 1][j - 1];
                    neighbours[4] = matrix[i][j - 1];
                    neighbours[5] = matrix[i - 1][j - 1];
                    neighbours[6] = matrix[i - 1][j];
                    neighbours[7] = matrix[i - 1][j + 1];
                    for (int k = 0; k < 8; k++) {
                        if (neighbours[k] == 'X') {
                            isolated = 0;
                            break;
                        }
                    }
                    matrix[i][j] = (isolated == 1) ? '-' : 'X';
                }
            }
        }
    }
}

void computeWhitePercentage(){
    int whites = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if(matrix[i][j] == 'X'){
                whites++;
            }
        }
    }
    int totalGrid = rows * columns;
    float result = ((float)whites) * 100 / ((float)totalGrid);
    printf("White percentage: %0.2f %%\n", result);
}

void printMatrix(){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j <= columns; j++){
            printf("%c", matrix[i][j]);
        }
    }
}

void resetMatrix(){
    for(int i = 0; i < MAX_LINE_SIZE; i++){
        for(int j = 0; j < MAX_COLUMN_SIZE; j++){
            matrix[i][j] = '\0';
        }
    }
}


