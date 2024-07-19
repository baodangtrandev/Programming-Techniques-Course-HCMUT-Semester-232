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
            if(D%2==0){
                exp1 += ceil(D/200);
            }else exp1 -= ceil(D/100);
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
    int S = nearest_square_number(EXP1);
    double P1;
    if(EXP1 >= S) P1 = 1;
    else P1 = round(((EXP1*1.0/S + 80)/123.0)*100)/100;
    //P1 = (EXP1*1.0/S + 80)/123.0;

    // the second way
    int before_M1 = ceil(M1/2.0);
    if(e2%2 == 1){
        while (M1 >= before_M1)
        {
            if(HP1 < 200){
        HP1 = ceil(HP1*1.3);
        M1 -= 150;
            }else{
        HP1 = ceil(HP1*1.1);
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
        EXP1 = ceil(EXP1*1.13);
        checkexp(EXP1);
        checkmoney(M1);
        if(M1 < before_M1){
            break;
        }
        if(EXP1 < 300){
        M1 -= 100;
        }else M1 -= 120;
        EXP1 = ceil(EXP1*0.9);
        checkexp(EXP1);
        checkmoney(M1);
    }
    checkexp(EXP1);
    checkhp(HP1);
    checkmoney(M1);
    HP1 = ceil(HP1*0.83);
    EXP1 = ceil(EXP1*1.17);
    checkexp(EXP1);
    checkhp(HP1);
    }else{
        if(HP1 < 200){
        HP1 = ceil(HP1*1.3);
        M1 -= 150;
            }else{
        HP1 = ceil(HP1*1.1);
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
        EXP1 = ceil(EXP1*1.13);
        checkexp(EXP1);
        checkmoney(M1);
        if(M1 <= 0){
            M1 = 0;
            goto end;
        }
        if(EXP1 < 300){
        M1 -= 100;
        }else M1 -= 120;
        EXP1 = ceil(EXP1*0.9);
        checkexp(EXP1);
        checkmoney(M1);
        if(M1 <= 0){
            M1 = 0;
        }
    end:
    HP1 = ceil(HP1*0.83);
    EXP1 = ceil(EXP1*1.17);
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

// Task 3
int chaseTaxi(int & HP1, int & EXP1, int & HP2, int & EXP2, int E3) {
    // TODO: Complete this function
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
   // cout << "col " << col << "row " << row << endl;
    int mark_taxi = arr[row][col];
    int max_l = max_left(arr,row,col);
    int max_r = max_right(arr,row,col);
    int max = max_l > max_r ? max_l : max_r;
    //cout << "max " << max << endl;
    if(abs(max) > abs(mark_taxi)){
        HP1 *= 1.1;
        HP1 = ceil(HP1);
        HP2 *= 1.1;
        HP2 = ceil(HP2);
        EXP1 *= 1.12;
        EXP1 = ceil(EXP1);
        EXP2 *= 1.12;
        EXP2 = ceil(EXP2);
    }else{
        HP1 *= 0.9;
        HP1 = ceil(HP1);
        HP2 *= 0.9;
        HP2 = ceil(HP2);
        EXP1 *= 0.88;
        EXP1 = ceil(EXP1);
        EXP2 *= 0.88;
        EXP2 = ceil(EXP2);
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
    // TODO: Complete this function
    // char se[] = "";
    // int i = 0;
    // while(email[i] != '@'){
    //     se[i]= email[i];
    //     i++;
    // }

    // //cout << "se " << se << endl;

    // int length_s = strlen(s);

    // if(length_s < 8){
    //     return -1;
    // }
    // if(length_s > 20){
    //     return -2;
    // }
    // const char *found = strstr(s, se);
    // int index = found - s;
    // // cout << "found " << found  << endl;
    // // cout << "index " << index << endl;

    // if(found != NULL){
    //     return -(300 + index);
    // }

    // for(int i = 0; i < length_s-2; i++){
    //     if(s[i] == s[i+1] && s[i+1] == s[i+2]){
    //         return -(400 + i);
    //     }
    // }
    // bool flag = false;
    // for(int i = 0; i < length_s; i++){
    //     if(s[i] == '@' || s[i] == '#' || s[i] == '%' || s[i] == '$' || s[i] == '!'){
    //         flag = true;
    //         break;
    //     }
    // }
    // if(flag == false){
    //     return -5;
    // }
    // int ok = 0;
    // // for(int i = 0 ; i < strlen(email); i++){
    // //     if(email[i] == '@'){
    // //         ok++;
    // //     }
    // //     if(ok ==2){
    // //         return i;
    // //     }
    // //     if(i == 100){
    // //         return i;
    // //     }
    // // }
    // for(int i = 0 ; i < length_s; i++){
    //     if(!isalpha(s[i]) && !isdigit(s[i])&& s[i] != '@' && s[i] != '#' && s[i] != '%' && s[i] != '$' && s[i] != '!'){
    //         return i;
    //     }
    // }


    // return -10;
    
    // Xác định chuỗi se từ email
    char se[101]; // Đủ lớn để chứa phần trước '@' và ký tự kết thúc chuỗi
    int seLength = 0;
    for (const char* p = email; *p != '@' && *p != '\0'; ++p, ++seLength) {
        se[seLength] = *p;
    }
    se[seLength] = '\0'; // Kết thúc chuỗi

    int sLength = strlen(s);
    if (sLength < 8) return -1; // Độ dài ngắn hơn tối thiểu
    if (sLength > 20) return -2; // Độ dài dài hơn tối đa

    // Kiểm tra điều kiện về ký tự đặc biệt và tính hợp lệ của ký tự
    int specialCharFound = 0;
    for (int i = 0; i < sLength; ++i) {
        char c = s[i];
        if (c == '@' || c == '#' || c == '%' || c == '$' || c == '!') {
            specialCharFound = 1; // Tìm thấy ký tự đặc biệt
        } else if (!isalnum(c)) {
            return i; // Ký tự không hợp lệ
        }

        // Kiểm tra chuỗi se có xuất hiện trong s không
        if (i <= sLength - seLength && strncmp(s + i, se, seLength) == 0) {
            return -(300 + i); // Trả về vị trí xuất hiện đầu tiên của se
        }

        // Kiểm tra có hơn 2 ký tự liên tiếp giống nhau không
        if (i > 1 && s[i] == s[i-1] && s[i] == s[i-2]) {
            return -(400 + (i-2)); // Vị trí đầu tiên của chuỗi ký tự liên tiếp
        }
    }

    if (!specialCharFound) return -5; // Không tìm thấy ký tự đặc biệt

    // Nếu không có điều kiện nào bị vi phạm
    return -10;
}

// Task 5
int findCorrectPassword(const char * arr_pwds[], int num_pwds) {
    // TODO: Complete this function
    int max_freq = 0;
    string max_str = arr_pwds[0];
    for(int i = 0; i < num_pwds; i++){
        int freq = 1;
        for(int j = i+1; j < num_pwds; j++){
            if(arr_pwds[i] == arr_pwds[j]){
                freq++;
            }
        }
        if(freq > max_freq){
            max_freq = freq;
            max_str = arr_pwds[i];
        }
        if(freq == max_freq){
            if(strlen(arr_pwds[i]) > max_str.length()){
                max_str = arr_pwds[i];
            }
        }
    }

    for(int i = 0; i < num_pwds; i++){
        if(arr_pwds[i] == max_str){
            return i;
        }
    }

    return -1;
}

////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////