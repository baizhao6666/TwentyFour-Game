/**------------------------------------------
Program 1: TwentyFour
Course: CS 211, Spring 2023, UIC
System: CLion on MacOs
Author: Baizhao Zhao, starter code provided by Dr. Ellen Kidane
-------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

/**
 * display the message to introduce the game
 */
void displayMenu(){
    printf("Welcome to the game of TwentyFour.\n"
           "Use each of the four numbers shown below exactly once,\n"
           "combining them somehow with the basic mathematical operators (+,-,*,/)\n"
           "to yield the value twenty-four. \n\n");

}

/**
 * calculate the result of the nums and operators
 * @param nums array for numbers in use
 * @param operator pointer to operators
 * @param printResult 1-print result, 0-not print result
 * @return
 */
int checkResult(int nums[4], const char *operator, int printResult) {
    double result = nums[0] * 1.0;
    int temp = nums[0];
    int resTemp;
    int *pInt = &nums[1];
    for (int i = 0; i < 3; ++i) {
        resTemp = temp;
        switch (*operator) {
            case '+':
                result += *pInt;
                temp += *pInt;
                break;
            case '-':
                result -= *pInt;
                temp -= *pInt;
                break;
            case '*':
                result *= *pInt;
                temp *= *pInt;
                break;
            case '/':
                result /= *pInt;
                temp /= *pInt;
                break;
        }
        if (printResult) {
            printf("%d %c %d = %d.\n", resTemp, *operator, *pInt, temp);
        }
        pInt++;
        operator++;
    }

    if (fabs(result - 24) < 0.001) {
        if (printResult) {
            printf("Well done! You are a math genius.\n\n");
        }
        return 1;
    } else {
        if (printResult) {
            printf("Sorry. Your solution did not evaluate to 24.\n\n");
        }
        return 0;
    }
}

/**
 * get the solutions for debug mode
 * @param debugNums array for debug numbers
 * @param debugMode 1-debug mode is on, 0-debug mode is off
 */
void getDebugNums(int debugNums[][4], int debugMode){
    char operators[] = {'+', '-', '*', '/'};
    int cnt = 0;
    for (int i = 1111; i < 10000; ++i) {
        int nums[4];
        nums[0] = i / 1000;
        nums[1] = (i % 1000) / 100;
        nums[2] = (i % 100) / 10;
        nums[3] = (i % 10);
        // omit the 0s
        if (nums[0] == 0 || nums[1] == 0 || nums[2] == 0 || nums[3] == 0) {
            continue;
        }
        char op[3];
        for (int j = 0; j < 4; ++j) {
            op[0] = operators[j];
            for (int k = 0; k < 4; ++k) {
                op[1] = operators[k];
                for (int l = 0; l < 4; ++l) {
                    op[2] = operators[l];
                    if (checkResult(nums, op, 0)) {
                        debugNums[cnt][0] = nums[0];
                        debugNums[cnt][1] = nums[1];
                        debugNums[cnt][2] = nums[2];
                        debugNums[cnt][3] = nums[3];
                        cnt++;
                        if (debugMode) {    // print the solutions
                            printf("%d. %d%c%d%c%d%c%d\n", cnt, nums[0], op[0], nums[1], op[1], nums[2], op[2],
                                   nums[3]);
                        }
                    }
                }
            }
        }
    }
}

/**
 * check if the input are valid operator
 * @param input
 * @return
 */
int checkValid(char *input){
    int cnt = 0;    // count for valid operators
    char *pTemp = input;
    while (*pTemp != '\0') {
        cnt++;
        pTemp++;
    }
    if (cnt != 3) {
        printf("Error! The number of operators is incorrect. Please try again.\n");
        return 0;
    }

    for (int i = 0; i < 3; ++i) {
        if (input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/') {
            printf("Error! Invalid operator entered. Please try again.\n");
            return 0;
        }
    }

    return 1;
}

int main(int argc, char *argv[]) {

    srand(1);	// Initialize random number generator.
    // Only do this ONCE in your program!
    // Use srand( time(0)); to give different values each time.

    // In this example we use the % operator to give 5 random numbers
    // that range from 0 to 4

    // easy mode numbers
    int easyNum[][4] = {
            3, 9, 4, 1,
            8, 5, 8, 1,
            6, 1, 5, 1,
            2, 8, 7, 8,
            5, 2, 9, 2,
            2, 6, 8, 4,
            5, 5, 4, 3,
            6, 6, 2, 6,
            8, 4, 2, 6,
            6, 2, 8, 1
    };
    int debugNum[3188][4]; // array for numbers in debug mode
    char *input = (char*) malloc(3 * sizeof(char)); // used to store the operators
    int (*numInUse)[4]; // used to store the numbers that are used for game
    int easyMode = 1;   // default easy mode is on
    int debugMode = 0;  // default debug mode is off

    displayMenu();  // display a message to introduce the game
    // for command line
    while ((argc -= 2) > 0) {
        switch (argv[1][1]) {
            case 'd':
                if (*argv[2] == '1') {  // debug mode is on
                    debugMode = 1;
                    getDebugNums(debugNum, debugMode);
                }
                break;
            case 'e':
                if (*argv[2] == '0') {  // easy mode is off
                    easyMode = 0;
                    getDebugNums(debugNum, 0);
                }
                break;
        }   // end of switch
        argv += 2;
    }   // end of while


    while (1) {
        int option; // get random number
        char exit;  // get the input for continuing or not

        if (easyMode) {
            option = rand() % 10;   // random number for easy mode
            numInUse = &easyNum[0]; // reset the pointer
        } else {
            option = rand() % 3188;   // random number for debug mode
            numInUse = &debugNum[0];        // reset the pointer
        }

        numInUse += option; // set the pointer to selected numbers

        printf("The numbers to use are: ");

        // display the numbers
        for (int i = 0; i < 4; ++i) {
            printf("%d", (*numInUse)[i]);
            i != 3 ? printf(", ") : printf(".\n");
        }

        printf("Enter the three operators to be used, in order (+,-,*, or /):");
        scanf("%s", input); // get user input for operators
        getchar();  // consume the '\n'

        // if the input is not valid, skip the rest of the while
        if (!checkValid(input)) {
            continue;
        }

        checkResult(*numInUse, input, 1);

        printf("Would you like to play again? Enter N for no and any other character for yes.\n");

        scanf("%c", &exit); // get user input for continuing or not
        getchar();  // consume the '\n'
        if (exit == 'N') {
            printf("Thanks for playing!\n");
            break;
        }
    }// end of while

    free(input);    // free the heap memory

    return 0;
}