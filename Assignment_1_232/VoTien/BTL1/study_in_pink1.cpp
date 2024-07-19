#include "study_in_pink1.h"

bool readFile(
        const string & filename,
        int & HP1,
        int & HP2,
        int & EXP1,
        int & EXP2,
        int & M1,
        int & M2,
        int & E1,
        int & E2,
        int & E3
) {
    // This function is used to read the input file,
    // DO NOT MODIFY THIS FUNTION
    ifstream ifs(filename);
    if (ifs.is_open()) {
        ifs >> HP1 >> HP2
            >> EXP1 >> EXP2
            >> M1 >> M2
            >> E1 >> E2 >> E3;
        return true;
    }
    else {
        cerr << "The file is not found" << endl;
        return false;
    }
}

////////////////////////////////////////////////////////////////////////
/// STUDENT'S ANSWER BEGINS HERE
/// Complete the following functions
/// DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////
void checkitem(int &exp1, int &exp2){
    if(exp1 > 600) exp1 = 600;
    if(exp1 < 0) exp1 = 0;
    if(exp2 > 600) exp2 = 600;
    if(exp2 < 0) exp2 = 0;
}

void checkexp(int &exp1){
    if(exp1 > 600) exp1 = 600;
    if(exp1 < 0) exp1 = 0;
}

void checkhp(int &hp1){
    if(hp1 > 666) hp1 = 666;
    if(hp1 < 0) hp1 = 0;
}

void checkmoney(int &m1){
    if(m1 > 3000) m1 = 3000;
    if(m1 < 0) m1 = 0;
}

int nearest_square_number(int exp1){
    double number = sqrt(exp1);
    int higher = pow(ceil(number),2);
    int lower = pow(floor(number),2);

    if (higher - exp1 >= exp1 - lower)
    {
        return lower;
    }else return higher;
}

// Task 1
int firstMeet(int & exp1, int & exp2, int e1) {
    // TODO: Complete this function
    if(e1 < 0 || e1 > 99) return -99;
    // case 1
    checkitem(exp1,exp2);
    if(e1>=0 && e1<=3){
        switch (e1)
        {
        case 0:
            exp2 += 29;
            break;
        case 1:
            exp2 += 45;
            break;
        case 2:
            exp2 += 75;
            break;
        default:
            exp2 += 149;
            break;
        }
        int D = e1*3 + exp1*7;
        //cout << "D = " << D << endl;
            if(D%2==0){
                exp1 = exp1 + D/200.0 + 0.999;
                //cout << "exp1 = " << exp1 << endl; 
            }else exp1 = exp1 - D/100.0 + 0.999;
        checkitem(exp1,exp2);
    }

    // case 2
    if(e1>= 4 && e1 <= 99){
        bool flag = false;
        if(e1 >=4 && e1 <= 19){
            exp2 += (e1/4.0 + 19) + 0.999;
        }else if(e1 >= 20 && e1 <= 49){
            exp2 += e1/9.0 + 21 + 0.999;
        }else if(e1 >= 50 && e1 <= 65){
            exp2 += e1/16.0 + 17 + 0.999;
        }else if(e1 >= 66 && e1 <= 79){
            exp2 += e1/4.0 + 19 + 0.999;
            if(exp2 > 200){
                exp2 += e1/9.0 + 21 + 0.999;
            }
        }else if(e1 >= 80 && e1 <= 99){
            exp2 += e1/4.0 + 19 + 0.999;
            exp2 += e1/9.0 + 21 + 0.999;
            if (exp2 > 400)
            {
                flag = true;
                exp2 += e1/16.0 + 17 + 0.999;
            }
        }
        if(flag){
            exp2 = exp2*1.15 + 0.999;
        }
        exp1 -= e1;
        checkitem(exp1,exp2);
    }
    return exp1 + exp2;
}

// Task 2
int traceLuggage(int & HP1, int & EXP1, int & M1, int e2) {
    // TODO: Complete this function
    if(e2 < 0 || e2 > 99) return -99;
    int S = nearest_square_number(EXP1);
    double P1;
    if(EXP1 >= S) P1 = 1;
    else P1 = round(((EXP1*1.0/S + 80)/123.0)*100)/100;
    //P1 = (EXP1*1.0/S + 80)/123.0;
    // the second way
    int before_M1 = M1/2.0 + 0.999;
    if(e2%2 == 1){
        while (M1 >= before_M1)
        {
            if(HP1 < 200){
        HP1 = HP1*1.3 + 0.999;
        M1 -= 150;
            }else{
        HP1 = HP1*1.1 + 0.999;
        M1 -= 70;
        }
        checkhp(HP1);
        checkmoney(M1);
        if(M1 < before_M1){
            break;
        }
        if(EXP1 < 400){
        M1 -= 200;
        }else M1 -= 120;
        EXP1 = EXP1*1.13 + 0.999;
        checkexp(EXP1);
        checkmoney(M1);
        if(M1 < before_M1){
            break;
        }
        if(EXP1 < 300){
        M1 -= 100;
        }else M1 -= 120;
        EXP1 = EXP1*0.9 + 0.999;
        checkexp(EXP1);
        checkmoney(M1);
    }
    checkexp(EXP1);
    checkhp(HP1);
    checkmoney(M1);
    HP1 = HP1*0.83 + 0.999;
    EXP1 = EXP1*1.17 + 0.999;
    checkexp(EXP1);
    checkhp(HP1);
    }else{
        if(HP1 < 200){
        HP1 = HP1*1.3 + 0.999;
        M1 -= 150;
            }else{
        HP1 = HP1*1.1 + 0.999;
        M1 -= 70;
        }
        checkhp(HP1);
        checkmoney(M1);
        if(M1 <= 0){
            M1 = 0;
            goto end;
        }
        if(EXP1 < 400){
        M1 -= 200;
        }else M1 -= 120;
        EXP1 = EXP1*1.13 + 0.999;
        checkexp(EXP1);
        checkmoney(M1);
        if(M1 <= 0){
            M1 = 0;
            goto end;
        }
        if(EXP1 < 300){
        M1 -= 100;
        }else M1 -= 120;
        EXP1 = EXP1*0.9 + 0.999;
        checkexp(EXP1);
        checkmoney(M1);
        if(M1 <= 0){
            M1 = 0;
        }
    end:
    HP1 = HP1*0.83 + 0.999;
    EXP1 = EXP1*1.17 + 0.999;
    checkexp(EXP1);
    checkhp(HP1);
    checkmoney(M1);
    }
    int S2 = nearest_square_number(EXP1);
    double P2;
    if(EXP1 >= S2) P2 = 1;
    else P2 = round(((EXP1*1.0/S2 + 80)/123.0)*100)/100;
    // the third way
    int arr[10] = {32, 47, 28, 79, 100, 50, 22, 83, 64, 11};
    int i;
    if(e2>=0 && e2<=9){
        i = e2;
    }else{
        i = (e2%10 + e2/10)%10;
    }
    double P3 = round((arr[i]*1.0/100)*100)/100;
    //cout << "P1 = " << P1 << ", P2 = " << P2 << ", P3 = " << P3 << endl;
    if(P1 == 1 && P2 == 1 && P3 == 1){
        EXP1 = ceil(EXP1*0.75);
    }else{
        double P = (P1 + P2 + P3)/3.0;
        // cout <<"P = " << P << endl;
        if(P < 0.5){
            HP1 = ceil(HP1*0.85);
            EXP1 = ceil(EXP1*1.15);
            checkexp(EXP1);
            checkhp(HP1);
        }else{
            HP1 = ceil(HP1*0.9);
            EXP1 = ceil(EXP1*1.2);
            checkexp(EXP1);
            checkhp(HP1);
        }
    }

    return HP1 + EXP1 + M1;

}

int max_left(int arr[][10], int row, int col){
    int max = arr[row][col];
    int s_row,s_col;
    if(row >= col){
        s_row = row - col;
        s_col = 0;
    }else{
        s_row = 0;
        s_col = col - row;
    }
    while(s_row < 10 && s_col < 10){
        if(arr[s_row][s_col] > max){
            max = arr[s_row][s_col];
        }
        s_row++;
        s_col++;
    }
    
    return max;
}

int max_right(int arr[][10], int row, int col){
    int max = arr[row][col];
    int s_row,s_col;
    if(row + col <= 9){
        s_row = 0;
        s_col = row + col;
    }else{
        s_row = row + col - 9;
        s_col = 9;
    }
    while(s_row < 10 && s_col >= 0){
        if(arr[s_row][s_col] > max){
            max = arr[s_row][s_col];
            //cout << "max " << max << "s_row " << s_row << "s_col " << s_col << endl;
        }
        s_row++;
        s_col--;
    }
    
    return max;
}

void print_matrix(int arr[10][10], int row, int col){
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
        
    }
    
}
// Task 3
int chaseTaxi(int & HP1, int & EXP1, int & HP2, int & EXP2, int E3) {
    // TODO: Complete this function
    if(E3 < 0 || E3 > 99) return -99;
    int arr[10][10];
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            arr[i][j] = 0;
        }
    }
    for(int i = 0 ; i < 10; i++){
        for(int j = 0 ; j < 10; j++){
            arr[i][j] = (E3*j + i*2)*(i-j);
        }
    }
    //cout << endl;
    //print_matrix(arr,10,10);
    int row = 0;
    int col = 0;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if(arr[i][j] > (E3*2)){
                row++;
            }
            if(arr[i][j] < (-E3)){
                col++;
            }
        }
    }
    while(row >= 10){
        row  = row%10 + row/10;
    }
    while(col >= 10){
        col  = col%10 + col/10;
    }
    //cout << "col " << col << "row " << row << endl;
    int mark_taxi = arr[row][col];
    int max_l = max_left(arr,row,col);
    int max_r = max_right(arr,row,col);
    int max = max_l > max_r ? max_l : max_r;
    //cout << "max " << max << endl;
    if(abs(max) >= abs(mark_taxi)){
        HP1 = HP1*1.1 + 0.999;
        HP2 = HP2*1.1 + 0.999;
        EXP1 = EXP1*1.12 + 0.999;
        EXP2 = EXP2*1.12 + 0.999;
    }else{
        HP1 = HP1*0.9 + 0.999;
        HP2 = HP2*0.9 + 0.999;
        EXP1 = EXP1*0.88 + 0.999;
        EXP2 = EXP2*0.88 + 0.999;
    }
    checkexp(EXP1);
    checkexp(EXP2);
    checkhp(HP1);
    checkhp(HP2);
    if(abs(max) >= abs(mark_taxi)){
        return max;
    }else return mark_taxi;
}
// Task 4
int checkPassword(const char * s, const char * email) {
    char se[101];
    int seLength = 0;
    for (const char* p = email; *p != '@' && *p != '\0'; ++p, ++seLength) {
        se[seLength] = *p;
    }
    se[seLength] = '\0';

    int sLength = strlen(s);
    if (sLength < 8) return -1; 
    if (sLength > 20) return -2; 
    for (int i = 0; i <= sLength - seLength; ++i) {
        if (strncmp(s + i, se, seLength) == 0) {
            return -(300 + i);
        }
    }
    int specialCharFound = 0;
    for (int i = 0; i < sLength; ++i) {
        char c = s[i];
        if (c == '@' || c == '#' || c == '%' || c == '$' || c == '!') {
            specialCharFound = 1;
        }
        if (i > 1 && s[i] == s[i-1] && s[i] == s[i-2]) {
            return -(400 + (i-2));
        }
    }
    if (!specialCharFound) return -5;
    for (int i = 0; i < sLength; i++) {
        char c = s[i];
        if (!isalnum(c) && (c != '@' && c != '#' && c != '%' && c != '$' && c != '!')) {
            return i; 
        }
    }
    return -10;
}
// Task 5
int findCorrectPassword(const char * arr_pwds[], int num_pwds) {
    int max_freq = 0;
    int max_length = 0;
    int index_of_max = -1;

    for (int i = 0; i < num_pwds; i++) {
        int freq = 1;
        int current_length = strlen(arr_pwds[i]);
        for (int j = i + 1; j < num_pwds; j++) {
            if (strcmp(arr_pwds[i], arr_pwds[j]) == 0) {
                freq++;
            }
        }
        if (freq > max_freq || (freq == max_freq && current_length > max_length)) {
            max_freq = freq;
            max_length = current_length;
            index_of_max = i;
        }
    }

    return index_of_max;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////