//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef _H_STUDY_IN_PINK_1_H_
#define _H_STUDY_IN_PINK_1_H_

#include "main.h"



bool readFile( const string & filename, int & HP1, int & HP2, int & EXP1, int & EXP2, int & M1, int & M2, int & E1, int & E2, int & E3);

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

// Task 1
int firstMeet(int & exp1, int & exp2, int e1);

// Task 2
int traceLuggage(int & HP1, int & EXP1, int & M1, int E2);

// Task 3
int chaseTaxi(int & HP1, int & EXP1, int & HP2, int & EXP2, int E3);

// Task 4
int checkPassword(const char * s, const char * email);

// Task 5
int findCorrectPassword(const char * arr_pwds[], int num_pwds);

void checkitem(int &exp1, int &exp2);

void checkexp(int &exp1);

void checkhp(int &hp1);

void checkmoney(int &m1);

int nearest_square_number(int exp1);

int max_left(int arr[][10], int row, int col);

int max_right(int arr[][10], int row, int col);

void print_matrix(int arr[10][10], int row, int col);

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_1_H_ */
