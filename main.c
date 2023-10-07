#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

char mapDef[10] = {' ','1','2','3','4','5','6','7','8','9'};
char map[10] = {' ','1','2','3','4','5','6','7','8','9'};
int level = 0;
int mask = 0;

// create 3*3 map
void updateBoard(){
        printf("                     _________________\n");
        printf("                    |     |     |     |\n");
        printf("                    |  %c  |  %c  |  %c  |\n", map[1], map[2], map[3]);
        printf("                    |_____|_____|_____|\n");
        printf("                    |     |     |     |\n");
        printf("                    |  %c  |  %c  |  %c  |\n", map[4], map[5], map[6]);
        printf("                    |_____|_____|_____|\n");
        printf("                    |     |     |     |\n");
        printf("                    |  %c  |  %c  |  %c  |\n", map[7], map[8], map[9]);
        printf("                    |_____|_____|_____|\n\n");
}

struct Player{
    char name[50];
    char style;
    int arr[5];
}p1,p2;

//save data in a file
void saveDataToFile(int gameType,int win){
    FILE *ptr;
    ptr = fopen("gameData.txt","a");
    if(ptr == NULL){
      printf("File could not be found !\n");
      return;
    }
    if(gameType == 0){
        fprintf(ptr,"Game Type: Player vs Player\n");
    } else if(gameType == 1){
        fprintf(ptr,"Game Type: Player vs Computer (Easy)\n");
    } else if(gameType == 2){
        fprintf(ptr,"Game Type: Player vs Computer (Hard)\n");
    }else if(gameType == 3){
        fprintf(ptr,"Game Type: Player vs Computer (Insane)\n");
    }
    fprintf(ptr,"Player 1 : %s (%c)\n",p1.name,p1.style);
    fprintf(ptr,"Player 2 : %s (%c)\n",p2.name,p2.style);
    fprintf(ptr,"Game moves -> \n");
    for(int i = 0; i < 5; i++){
        if(p1.arr[i] != 0){
            fprintf(ptr,"    Player 1 : %d\n",p1.arr[i]);
        }
        if(p2.arr[i] != 0){
            fprintf(ptr,"    Player 2 : %d\n",p2.arr[i]);
        }
    }
    if(win == 0){
        fprintf(ptr,"Match has drawn");
    } else if (win == 1){
        fprintf(ptr,"Player 1 has won the match");
    } else if (win == 2){
        fprintf(ptr,"Player 2 has won the match");
    }
    fprintf(ptr,"\n_____________________________________\n\n");
    fclose(ptr);


}

//reset 3*3 map
void resetMap(){
    for(int i = 0; i < 10; i++){
        map[i] = mapDef[i];
    }
    level = 0;
    for(int i = 0; i < 5; i++){
        p1.arr[i] = 0;
        p2.arr[i] = 0;
    }

}

//check the win precedent
int checkWin(){
    char wonMark = ' ';
    if(map[1] == map[2] && map[2] == map[3]){
        wonMark = map[1];
    } else if(map[4] == map[5] && map[5] == map[6]){
        wonMark = map[4];
    } else if(map[7] == map[8] && map[8] == map[9]){
        wonMark = map[7];
    } else if(map[1] == map[4] && map[4] == map[7]){
        wonMark = map[1];
    } else if(map[2] == map[5] && map[5] == map[8]){
        wonMark = map[2];
    } else if(map[3] == map[6] && map[6] == map[9]){
        wonMark = map[3];
    } else if(map[1] == map[5] && map[5] == map[9]){
        wonMark = map[1];
    } else if(map[3] == map[5] && map[5] == map[7]){
        wonMark = map[3];
    } else if(map[1] != '1' && map[2] != '2' && map[3] != '3' && map[4] != '4' && map[5] != '5' && map[6] != '6' && map[7] != '7' && map[8] != '8' && map[9] != '9'){
        return 3;
    } else {
        return 4;
    }
    if(wonMark == 'O'){
        return 1;
    } else if(wonMark == 'X'){
        return 2;
    }
}


//play with computer easy mod automatically enter data check
int getPointEasy(){
    if(mask == 1){
        if (map[4] == map[5] && map[5] == 'X' && map[6] == '6'){
            return 6;
        } else if (map[7] == map[8] && map[8] == 'X' && map[9] == '3'){
            return 9;
        } else if (map[5] == map[6] && map[6] == 'X' && map[4] == '4'){
            return 4;
        } else if (map[1] == map[3] && map[3] == 'X' && map[2] == '2'){
            return 2;
        } else if (map[5] == map[8] && map[8] == 'X' && map[2] == '2'){
            return 2;
        } else if (map[2] == map[8] && map[8] == 'X' && map[5] == '5'){
            return 5;
        } else if (map[9] == map[5] && map[5] == 'X' && map[1] == '1'){
            return 1;
        } else if (map[3] == map[7] && map[7] == 'X' && map[5] == '5'){
            return 5;
        } else if (map[7] == map[8] && map[8] == 'O' && map[9] == '3'){
            return 9;
        } else if (map[2] == map[5] && map[5] == 'O' && map[8] == '8'){
            return 8;
        } else if (map[5] == map[6] && map[6] == 'O' && map[4] == '4'){
            return 4;
        } else if (map[4] == map[7] && map[7] == 'O' && map[1] == '1'){
            return 1;
        } else if (map[6] == map[9] && map[9] == 'O' && map[3] == '3'){
            return 3;
        } else if (map[1] == map[5] && map[5] == 'O' && map[9] == '9'){
            return 9;
        }
    } else if (mask == 2){
        if(map[5] == '5'){
            return 5;
        } else if (map[7] == map[8] && map[8] == 'X' && map[9] == '3'){
            return 9;
        } else if (map[2] == map[5] && map[5] == 'X' && map[8] == '8'){
            return 8;
        } else if (map[4] == map[6] && map[6] == 'X' && map[5] == '5'){
            return 5;
        } else if (map[1] == map[7] && map[7] == 'X' && map[4] == '4'){
            return 4;
        } else if (map[3] == map[5] && map[5] == 'X' && map[7] == '7'){
            return 7;
        } else if (map[4] == map[5] && map[5] == 'O' && map[6] == '6'){
            return 6;
        } else if (map[3] == map[6] && map[6] == 'O' && map[9] == '9'){
            return 9;
        } else if (map[5] == map[6] && map[6] == 'O' && map[4] == '4'){
            return 4;
        } else if (map[4] == map[6] && map[6] == 'O' && map[5] == '5'){
            return 5;
        } else if (map[2] == map[8] && map[8] == 'O' && map[5] == '5'){
            return 5;
        } else if (map[3] == map[9] && map[9] == 'O' && map[6] == '6'){
            return 6;
        } else if (map[3] == map[7] && map[7] == 'O' && map[5] == '5'){
            return 5;
        } else if (map[7] == map[5] && map[5] == 'O' && map[3] == '3'){
            return 3;
        }
    } else {
        if(map[5] == '5'){
            return 5;
        } else if (map[1] == map[2] && map[2] == 'X' && map[3] == '3'){
            return 3;
        } else if (map[1] == map[3] && map[3] == 'X' && map[2] == '2'){
            return 2;
        } else if (map[2] == map[8] && map[8] == 'X' && map[5] == '5'){
            return 5;
        } else if (map[9] == map[5] && map[5] == 'X' && map[1] == '1'){
            return 1;
        } else if (map[2] == map[5] && map[5] == 'O' && map[8] == '8'){
            return 8;
        } else if (map[5] == map[6] && map[6] == 'O' && map[4] == '4'){
            return 4;
        } else if (map[8] == map[9] && map[9] == 'O' && map[7] == '7'){
            return 7;
        } else if (map[5] == map[8] && map[8] == 'O' && map[2] == '2'){
            return 2;
        } else if (map[1] == map[7] && map[7] == 'O' && map[4] == '4'){
            return 4;
        } else if (map[3] == map[9] && map[9] == 'O' && map[6] == '6'){
            return 6;
        } else if (map[9] == map[5] && map[5] == 'O' && map[1] == '1'){
            return 1;
        } else if (map[3] == map[5] && map[5] == 'O' && map[7] == '7'){
            return 7;
        } else if (map[7] == map[5] && map[5] == 'O' && map[3] == '3'){
            return 3;
        }
    }
    while(1){
        int r = rand() % 9;
        if(r != 0 && map[r] != 'O' && map[r] != 'X'){
            return r;
        }
    }
}

//play with computer hard mod automatically enter data check
int getPointHard(){
    if(mask == 1){
        if(map[5] == '5'){
            return 5;
        } else if (map[1] == map[2] && map[2] == 'X' && map[3] == '3'){
            return 3;
        } else if (map[4] == map[5] && map[5] == 'X' && map[6] == '6'){
            return 6;
        } else if (map[7] == map[8] && map[8] == 'X' && map[9] == '3'){
            return 9;
        } else if (map[1] == map[4] && map[4] == 'X' && map[7] == '7'){
            return 7;
        } else if (map[3] == map[6] && map[6] == 'X' && map[9] == '9'){
            return 9;
        } else if (map[2] == map[3] && map[3] == 'X' && map[1] == '1'){
            return 1;
        } else if (map[5] == map[6] && map[6] == 'X' && map[4] == '4'){
            return 4;
        } else if (map[1] == map[3] && map[3] == 'X' && map[2] == '2'){
            return 2;
        } else if (map[4] == map[6] && map[6] == 'X' && map[5] == '5'){
            return 5;
        } else if (map[7] == map[9] && map[9] == 'X' && map[8] == '8'){
            return 8;
        } else if (map[4] == map[7] && map[7] == 'X' && map[1] == '1'){
            return 1;
        } else if (map[5] == map[8] && map[8] == 'X' && map[2] == '2'){
            return 2;
        } else if (map[6] == map[9] && map[9] == 'X' && map[3] == '3'){
            return 3;
        } else if (map[2] == map[8] && map[8] == 'X' && map[5] == '5'){
            return 5;
        } else if (map[3] == map[9] && map[9] == 'X' && map[6] == '6'){
            return 6;
        } else if (map[1] == map[5] && map[5] == 'X' && map[9] == '9'){
            return 9;
        } else if (map[9] == map[5] && map[5] == 'X' && map[1] == '1'){
            return 1;
        } else if (map[3] == map[5] && map[5] == 'X' && map[7] == '7'){
            return 7;
        } else if (map[3] == map[7] && map[7] == 'X' && map[5] == '5'){
            return 5;
        } else if (map[7] == map[5] && map[5] == 'X' && map[3] == '3'){
            return 3;
        } else if (map[1] == map[2] && map[2] == 'O' && map[3] == '3'){
            return 3;
        } else if (map[4] == map[5] && map[5] == 'O' && map[6] == '6'){
            return 6;
        } else if (map[7] == map[8] && map[8] == 'O' && map[9] == '3'){
            return 9;
        } else if (map[2] == map[5] && map[5] == 'O' && map[8] == '8'){
            return 8;
        } else if (map[3] == map[6] && map[6] == 'O' && map[9] == '9'){
            return 9;
        } else if (map[5] == map[6] && map[6] == 'O' && map[4] == '4'){
            return 4;
        } else if (map[4] == map[6] && map[6] == 'O' && map[5] == '5'){
            return 5;
        } else if (map[7] == map[9] && map[9] == 'O' && map[8] == '8'){
            return 8;
        } else if (map[4] == map[7] && map[7] == 'O' && map[1] == '1'){
            return 1;
        } else if (map[6] == map[9] && map[9] == 'O' && map[3] == '3'){
            return 3;
        } else if (map[1] == map[7] && map[7] == 'O' && map[4] == '4'){
            return 4;
        } else if (map[3] == map[9] && map[9] == 'O' && map[6] == '6'){
            return 6;
        } else if (map[1] == map[9] && map[9] == 'O' && map[5] == '5'){
            return 5;
        } else if (map[3] == map[5] && map[5] == 'O' && map[7] == '7'){
            return 7;
        } else if (map[3] == map[7] && map[7] == 'O' && map[5] == '5'){
            return 5;
        }
    } else if (mask == 2){
        if(map[5] == '5'){
            return 5;
        } else if (map[4] == map[5] && map[5] == 'X' && map[6] == '6'){
            return 6;
        } else if (map[7] == map[8] && map[8] == 'X' && map[9] == '3'){
            return 9;
        } else if (map[2] == map[5] && map[5] == 'X' && map[8] == '8'){
            return 8;
        } else if (map[3] == map[6] && map[6] == 'X' && map[9] == '9'){
            return 9;
        } else if (map[2] == map[3] && map[3] == 'X' && map[1] == '1'){
            return 1;
        } else if (map[8] == map[9] && map[9] == 'X' && map[7] == '7'){
            return 7;
        } else if (map[1] == map[3] && map[3] == 'X' && map[2] == '2'){
            return 2;
        } else if (map[7] == map[9] && map[9] == 'X' && map[8] == '8'){
            return 8;
        } else if (map[4] == map[7] && map[7] == 'X' && map[1] == '1'){
            return 1;
        } else if (map[6] == map[9] && map[9] == 'X' && map[3] == '3'){
            return 3;
        } else if (map[1] == map[7] && map[7] == 'X' && map[4] == '4'){
            return 4;
        } else if (map[3] == map[9] && map[9] == 'X' && map[6] == '6'){
            return 6;
        } else if (map[1] == map[5] && map[5] == 'X' && map[9] == '9'){
            return 9;
        } else if (map[9] == map[5] && map[5] == 'X' && map[1] == '1'){
            return 1;
        } else if (map[3] == map[5] && map[5] == 'X' && map[7] == '7'){
            return 7;
        } else if (map[7] == map[5] && map[5] == 'X' && map[3] == '3'){
            return 3;
        } else if (map[1] == map[2] && map[2] == 'O' && map[3] == '3'){
            return 3;
        } else if (map[7] == map[8] && map[8] == 'O' && map[9] == '3'){
            return 9;
        } else if (map[1] == map[4] && map[4] == 'O' && map[7] == '7'){
            return 7;
        } else if (map[3] == map[6] && map[6] == 'O' && map[9] == '9'){
            return 9;
        } else if (map[2] == map[3] && map[3] == 'O' && map[1] == '1'){
            return 1;
        } else if (map[8] == map[9] && map[9] == 'O' && map[7] == '7'){
            return 7;
        } else if (map[1] == map[3] && map[3] == 'O' && map[2] == '2'){
            return 2;
        } else if (map[4] == map[6] && map[6] == 'O' && map[5] == '5'){
            return 5;
        } else if (map[4] == map[7] && map[7] == 'O' && map[1] == '1'){
            return 1;
        } else if (map[5] == map[8] && map[8] == 'O' && map[2] == '2'){
            return 2;
        } else if (map[6] == map[9] && map[9] == 'O' && map[3] == '3'){
            return 3;
        } else if (map[1] == map[7] && map[7] == 'O' && map[4] == '4'){
            return 4;
        } else if (map[3] == map[9] && map[9] == 'O' && map[6] == '6'){
            return 6;
        } else if (map[1] == map[5] && map[5] == 'O' && map[9] == '9'){
            return 9;
        } else if (map[1] == map[9] && map[9] == 'O' && map[5] == '5'){
            return 5;
        } else if (map[9] == map[5] && map[5] == 'O' && map[1] == '1'){
            return 1;
        } else if (map[3] == map[5] && map[5] == 'O' && map[7] == '7'){
            return 7;
        } else if (map[3] == map[7] && map[7] == 'O' && map[5] == '5'){
            return 5;
        } else if (map[7] == map[5] && map[5] == 'O' && map[3] == '3'){
            return 3;
        }
    } else {
        if (map[1] == map[2] && map[2] == 'X' && map[3] == '3'){
            return 3;
        } else if (map[7] == map[8] && map[8] == 'X' && map[9] == '3'){
            return 9;
        } else if (map[1] == map[4] && map[4] == 'X' && map[7] == '7'){
            return 7;
        } else if (map[2] == map[5] && map[5] == 'X' && map[8] == '8'){
            return 8;
        } else if (map[3] == map[6] && map[6] == 'X' && map[9] == '9'){
            return 9;
        } else if (map[5] == map[6] && map[6] == 'X' && map[4] == '4'){
            return 4;
        } else if (map[8] == map[9] && map[9] == 'X' && map[7] == '7'){
            return 7;
        } else if (map[1] == map[3] && map[3] == 'X' && map[2] == '2'){
            return 2;
        } else if (map[4] == map[6] && map[6] == 'X' && map[5] == '5'){
            return 5;
        } else if (map[4] == map[7] && map[7] == 'X' && map[1] == '1'){
            return 1;
        } else if (map[5] == map[8] && map[8] == 'X' && map[2] == '2'){
            return 2;
        } else if (map[1] == map[7] && map[7] == 'X' && map[4] == '4'){
            return 4;
        } else if (map[2] == map[8] && map[8] == 'X' && map[5] == '5'){
            return 5;
        } else if (map[1] == map[5] && map[5] == 'X' && map[9] == '9'){
            return 9;
        } else if (map[1] == map[9] && map[9] == 'X' && map[5] == '5'){
            return 5;
        } else if (map[3] == map[5] && map[5] == 'X' && map[7] == '7'){
            return 7;
        } else if (map[3] == map[7] && map[7] == 'X' && map[5] == '5'){
            return 5;
        } else if (map[1] == map[2] && map[2] == 'O' && map[3] == '3'){
            return 3;
        } else if (map[4] == map[5] && map[5] == 'O' && map[6] == '6'){
            return 6;
        } else if (map[7] == map[8] && map[8] == 'O' && map[9] == '3'){
            return 9;
        } else if (map[1] == map[4] && map[4] == 'O' && map[7] == '7'){
            return 7;
        } else if (map[2] == map[5] && map[5] == 'O' && map[8] == '8'){
            return 8;
        } else if (map[3] == map[6] && map[6] == 'O' && map[9] == '9'){
            return 9;
        } else if (map[5] == map[6] && map[6] == 'O' && map[4] == '4'){
            return 4;
        } else if (map[8] == map[9] && map[9] == 'O' && map[7] == '7'){
            return 7;
        } else if (map[1] == map[3] && map[3] == 'O' && map[2] == '2'){
            return 2;
        } else if (map[7] == map[9] && map[9] == 'O' && map[8] == '8'){
            return 8;
        } else if (map[4] == map[7] && map[7] == 'O' && map[1] == '1'){
            return 1;
        } else if (map[5] == map[8] && map[8] == 'O' && map[2] == '2'){
            return 2;
        } else if (map[1] == map[7] && map[7] == 'O' && map[4] == '4'){
            return 4;
        } else if (map[2] == map[8] && map[8] == 'O' && map[5] == '5'){
            return 5;
        } else if (map[3] == map[9] && map[9] == 'O' && map[6] == '6'){
            return 6;
        } else if (map[1] == map[5] && map[5] == 'O' && map[9] == '9'){
            return 9;
        } else if (map[9] == map[5] && map[5] == 'O' && map[1] == '1'){
            return 1;
        } else if (map[3] == map[5] && map[5] == 'O' && map[7] == '7'){
            return 7;
        }
    }
    while(1){
        int r = rand() % 9;
        if(r != 0 && map[r] != 'O' && map[r] != 'X'){
            return r;
        }
    }
}


//play with computer insane mod automatically enter data check
int getPointInsane(){
    if(map[5] == '5'){
        return 5;
    } else if (map[1] == map[2] && map[2] == 'X' && map[3] == '3'){
        return 3;
    } else if (map[4] == map[5] && map[5] == 'X' && map[6] == '6'){
        return 6;
    } else if (map[7] == map[8] && map[8] == 'X' && map[9] == '3'){
        return 9;
    } else if (map[1] == map[4] && map[4] == 'X' && map[7] == '7'){
        return 7;
    } else if (map[2] == map[5] && map[5] == 'X' && map[8] == '8'){
        return 8;
    } else if (map[3] == map[6] && map[6] == 'X' && map[9] == '9'){
        return 9;
    } else if (map[2] == map[3] && map[3] == 'X' && map[1] == '1'){
        return 1;
    } else if (map[5] == map[6] && map[6] == 'X' && map[4] == '4'){
        return 4;
    } else if (map[8] == map[9] && map[9] == 'X' && map[7] == '7'){
        return 7;
    } else if (map[1] == map[3] && map[3] == 'X' && map[2] == '2'){
        return 2;
    } else if (map[4] == map[6] && map[6] == 'X' && map[5] == '5'){
        return 5;
    } else if (map[7] == map[9] && map[9] == 'X' && map[8] == '8'){
        return 8;
    } else if (map[4] == map[7] && map[7] == 'X' && map[1] == '1'){
        return 1;
    } else if (map[5] == map[8] && map[8] == 'X' && map[2] == '2'){
        return 2;
    } else if (map[6] == map[9] && map[9] == 'X' && map[3] == '3'){
        return 3;
    } else if (map[1] == map[7] && map[7] == 'X' && map[4] == '4'){
        return 4;
    } else if (map[2] == map[8] && map[8] == 'X' && map[5] == '5'){
        return 5;
    } else if (map[3] == map[9] && map[9] == 'X' && map[6] == '6'){
        return 6;
    } else if (map[1] == map[5] && map[5] == 'X' && map[9] == '9'){
        return 9;
    } else if (map[1] == map[9] && map[9] == 'X' && map[5] == '5'){
        return 5;
    } else if (map[9] == map[5] && map[5] == 'X' && map[1] == '1'){
        return 1;
    } else if (map[3] == map[5] && map[5] == 'X' && map[7] == '7'){
        return 7;
    } else if (map[3] == map[7] && map[7] == 'X' && map[5] == '5'){
        return 5;
    } else if (map[7] == map[5] && map[5] == 'X' && map[3] == '3'){
        return 3;
    } else if (map[1] == map[2] && map[2] == 'O' && map[3] == '3'){
        return 3;
    } else if (map[4] == map[5] && map[5] == 'O' && map[6] == '6'){
        return 6;
    } else if (map[7] == map[8] && map[8] == 'O' && map[9] == '3'){
        return 9;
    } else if (map[1] == map[4] && map[4] == 'O' && map[7] == '7'){
        return 7;
    } else if (map[2] == map[5] && map[5] == 'O' && map[8] == '8'){
        return 8;
    } else if (map[3] == map[6] && map[6] == 'O' && map[9] == '9'){
        return 9;
    } else if (map[2] == map[3] && map[3] == 'O' && map[1] == '1'){
        return 1;
    } else if (map[5] == map[6] && map[6] == 'O' && map[4] == '4'){
        return 4;
    } else if (map[8] == map[9] && map[9] == 'O' && map[7] == '7'){
        return 7;
    } else if (map[1] == map[3] && map[3] == 'O' && map[2] == '2'){
        return 2;
    } else if (map[4] == map[6] && map[6] == 'O' && map[5] == '5'){
        return 5;
    } else if (map[7] == map[9] && map[9] == 'O' && map[8] == '8'){
        return 8;
    } else if (map[4] == map[7] && map[7] == 'O' && map[1] == '1'){
        return 1;
    } else if (map[5] == map[8] && map[8] == 'O' && map[2] == '2'){
        return 2;
    } else if (map[6] == map[9] && map[9] == 'O' && map[3] == '3'){
        return 3;
    } else if (map[1] == map[7] && map[7] == 'O' && map[4] == '4'){
        return 4;
    } else if (map[2] == map[8] && map[8] == 'O' && map[5] == '5'){
        return 5;
    } else if (map[3] == map[9] && map[9] == 'O' && map[6] == '6'){
        return 6;
    } else if (map[1] == map[5] && map[5] == 'O' && map[9] == '9'){
        return 9;
    } else if (map[1] == map[9] && map[9] == 'O' && map[5] == '5'){
        return 5;
    } else if (map[9] == map[5] && map[5] == 'O' && map[1] == '1'){
        return 1;
    } else if (map[3] == map[5] && map[5] == 'O' && map[7] == '7'){
        return 7;
    } else if (map[3] == map[7] && map[7] == 'O' && map[5] == '5'){
        return 5;
    } else if (map[7] == map[5] && map[5] == 'O' && map[3] == '3'){
        return 3;
    } else {
        while(1){
            int r = rand() % 9;
            if(r != 0 && map[r] != 'O' && map[r] != 'X'){
                return r;
            }
        }
    }
}



// play with computer
void challengePC(){
    printf("Enter Player Name (O) : ");
    scanf("%s", &p1.name);
    p1.style = 'O';
    strcpy(p2.name,"Computer");
    p2.style = 'X';
    while(1){
        printf("%s play as \'O\' & %s play as \'X\'\n\n",p1.name,p2.name);
        updateBoard();
        int mark;
        int player;
        if(map[0] == 'X' || map[0] == ' '){
            printf("%s Enter a number : ", p1.name);
            player = 1;
            scanf("%d", &mark);
            if(mark > 9 || mark < 1){
                printf("Invalid point look at the board idiot!\n");
                system("pause");
                continue;
            }
        } else {
            if(level == 1){
                mark = getPointEasy();
            } else if(level == 2){
                mark = getPointHard();
            } else if(level == 3){
                mark = getPointInsane();
            }
            printf("Computer Choose %d : ", mark);
            player = 2;
        }

        if(map[mark] != 'O' && map[mark] != 'X'){
            if(player == 1){
                map[mark] = 'O';
                for(int i = 0; i < 5; i++){
                    if(p1.arr[i] == 0){
                       p1.arr[i] = mark;
                       break;
                    }
                }
                map[0] = 'O';
            } else {
                map[mark] = 'X';
                for(int i = 0; i < 5; i++){
                    if(p2.arr[i] == 0){
                       p2.arr[i] = mark;
                       break;
                    }
                }
                map[0] = 'X';
            }
        } else {
            printf("You can't use a marked point. Try another !\n");
            system("pause");
            continue;
        }
        if(checkWin() == 4){
            continue;
        } else {
            printf("%s play as \'O\' & %s play as \'X\'\n\n",p1.name,p2.name);
            updateBoard();
            if(checkWin() == 3){
                system("color 3");
                printf("No one wins Match has draw\n");
                saveDataToFile(level,0);
                break;
            } else if(checkWin() == 1){
                system("color 2");
                printf("%s has won the match\n", p1.name );
                saveDataToFile(level,1);
                break;
            } else if(checkWin() == 2){
                system("color 4");
                printf("%s has won the match\n", p2.name );
                saveDataToFile(level,2);
                break;
            }
        }
    }
    system("pause");
}

//paler vs player game
void playGameWithPlayer(){
    printf("Enter Player 1 Name (O) : ");
    scanf("%s", &p1.name);
    p1.style = 'O';
    printf("Enter Player 2 Name (X) : ");
    scanf("%s", &p2.name);
    p2.style = 'X';
    while(1){
        printf("%s play as \'O\' & %s play as \'X\'\n\n",p1.name,p2.name);
        updateBoard();
        int mark;
        int player;
        if(map[0] == 'X' || map[0] == ' '){
            printf("%s Enter a number : ", p1.name);
            player = 1;
        } else {
            printf("%s Enter a number : ", p2.name);
            player = 2;
        }
        scanf("%d", &mark);
        if(mark > 9 || mark < 1){
            printf("Invalid point look at the board idiot!\n");
            system("pause");
            continue;
        }
        if(map[mark] != 'O' && map[mark] != 'X'){
            if(player == 1){
                map[mark] = 'O';
                for(int i = 0; i < 5; i++){
                    if(p1.arr[i] == 0){
                       p1.arr[i] = mark;
                       break;
                    }
                }
                map[0] = 'O';
            } else {
                map[mark] = 'X';
                for(int i = 0; i < 5; i++){
                    if(p2.arr[i] == 0){
                       p2.arr[i] = mark;
                       break;
                    }
                }
                map[0] = 'X';
            }
        } else {
            printf("You can't use a marked point. Try another !\n");
            system("pause");
            continue;
        }
        if(checkWin() == 4){
            continue;
        } else {
            printf("%s play as \'O\' & %s play as \'X\'\n\n",p1.name,p2.name);
            updateBoard();
            if(checkWin() == 3){
                system("color 3");
                printf("No one wins Match has draw\n");
                saveDataToFile(0,0);
                break;
            } else if(checkWin() == 1){
                system("color 2");
                printf("%s has won the match\n", p1.name );
                saveDataToFile(0,1);
                break;
            } else if(checkWin() == 2){
                system("color 2");
                printf("%s has won the match\n", p2.name );
                saveDataToFile(0,2);
                break;
            }
        }
    }
    system("pause");
}


// display the instructions
void displayInstructions(){
    printf("1. Select a game mode.\n");
    printf("2. Give player names.\n");
    printf("3. Use point numbers to add your mark.\n");
    printf("4. Play until win or draw.\n\n");
    printf("Note : for better view change console font size to 32\n");
    system("pause");
}


//display previous game records
void previousRecords(){
    char  row[255];
    FILE  *fp;
    fp = fopen( "gameData.txt", "r" );
    if ( fp == NULL ) {
        printf("No previous data !\n");
        system("pause");
        return;
    }
    while ( fgets( row, sizeof( row ), fp ) != NULL ) {
        printf(row);
    }
    fclose( fp );
    system("pause");
}


//clean previous game records
void clearPreviousRecords(){
    if (remove("gameData.txt") == 0){
      printf("Previous Records Cleared Successfully\n");
    } else {
      printf("Unable to Clear Data\n");
    }
    system("pause");
}

//display menu
void menu(){
    while(1){
        system("color 7");
        int n;
        resetMap();
        system("cls");
        printf("=============================================================\n");
        printf("                  --------TIC TAC TOE---------               \n");
        printf("=============================================================\n");
        printf("\n");
        printf("1. INSTRUCTIONS\n");
        printf("2. PLAY WITH A PLAYER\n");
        printf("3. PLAY WITH COMPUTER (EASY)\n");
        printf("4. PLAY WITH COMPUTER (HARD)\n");
        printf("5. PLAY WITH COMPUTER (INSANE)\n");
        printf("6. VIEW PREVIOUS RECORDS\n");
        printf("7. CLEAR PREVIOUS RECORDS\n");
        printf("8. EXIT\n");
        printf("\n");
        printf("Enter Menu Number : ");
        scanf("%d", &n);
        if(n == 1){
            displayInstructions();
        } else if (n == 2){
            playGameWithPlayer();
        } else if(n == 3){
            level = 1;
            mask = rand() % 3;
            challengePC();
        } else if(n == 4){
            level = 2;
            mask = rand() % 3;
            challengePC();
        } else if(n == 5){
            level = 3;
            challengePC();
        } else if(n == 6){
            previousRecords();
        } else if(n == 7){
            clearPreviousRecords();
        } else if(n == 8){
            system("cls");
            printf("=============================================================\n");
            printf("                  --------TIC TAC TOE---------               \n");
            printf("=============================================================\n");
            exit(0);
        } else {
            printf("Invalid Menu Number! Try Again...\n");
            system("pause");
        }
    }
}

int main(){
    system("color 7");
    time_t t;
    srand((unsigned) time(&t));
    menu();
}
