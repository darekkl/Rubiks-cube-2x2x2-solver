#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char cube[6][4];

char cube_copied[6][4];

const long long powers_of_3[] = {
    3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147, 531441,
    1594323, 4782969, 14348907, 43046721, 129140163, 387420489,
    1162261467, 3486784401, 10460353203, 31381059609, 94143178827,
    282429536481
};

void cube_copy() {
    for(short i = 0; i < 6; i++)
        for(short ii = 0; ii < 4; ii++)
            cube_copied[i][ii] = cube[i][ii];
}

void cube_restore() {
    for(short i = 0; i < 6; i++)
        for(short ii = 0; ii < 4; ii++)
            cube[i][ii] = cube_copied[i][ii];
}

void cube_move_front() {
    char clone[6][4];
    
    for(short i = 0; i < 6; i++)
        for(short ii = 0; ii < 4; ii++)
            clone[i][ii] = cube[i][ii];

    cube[0][0] = clone[0][2];
    cube[0][1] = clone[0][0];
    cube[0][2] = clone[0][3];
    cube[0][3] = clone[0][1];

    cube[1][0] = clone[4][2];
    cube[1][2] = clone[4][3];
    cube[3][1] = clone[5][0];
    cube[3][3] = clone[5][1];
    cube[4][2] = clone[3][3];
    cube[4][3] = clone[3][1];
    cube[5][0] = clone[1][2];
    cube[5][1] = clone[1][0];
}

void cube_move_up() {
    char clone[6][4];
    
    for(short i = 0; i < 6; i++)
        for(short ii = 0; ii < 4; ii++)
            clone[i][ii] = cube[i][ii];
    
    cube[4][0] = clone[4][2];
    cube[4][1] = clone[4][0];
    cube[4][2] = clone[4][3];
    cube[4][3] = clone[4][1];

    cube[0][0] = clone[1][0];
    cube[0][1] = clone[1][1];
    cube[1][0] = clone[2][0];
    cube[1][1] = clone[2][1];
    cube[2][0] = clone[3][0];
    cube[2][1] = clone[3][1];
    cube[3][0] = clone[0][0];
    cube[3][1] = clone[0][1];
}

void cube_move_right() {
    char clone[6][4];
    
    for(short i = 0; i < 6; i++)
        for(short ii = 0; ii < 4; ii++)
            clone[i][ii] = cube[i][ii];

    cube[1][0] = clone[1][2];
    cube[1][1] = clone[1][0];
    cube[1][2] = clone[1][3];
    cube[1][3] = clone[1][1];
    
    cube[0][1] = clone[5][1];
    cube[0][3] = clone[5][3];
    cube[2][0] = clone[4][3];
    cube[2][2] = clone[4][1];
    cube[4][1] = clone[0][1];
    cube[4][3] = clone[0][3];
    cube[5][1] = clone[2][2];
    cube[5][3] = clone[2][0];
}

short cube_is_solved() {
    for(short i = 0; i < 6; i++) {
        char same = cube[i][0];
        
        if(cube[i][1] != same || cube[i][2] != same ||
                cube[i][3] != same)
            return 0;
    }

    return 1;
}

void end() {
    while(1)
        getchar();
}

int main(void) {
    printf(
        "       ----- \n"
        "      |17 18|\n"
        "      |19 20|\n"
        " ----- ----- ----- ----- \n"
        "|13 14|01 02|05 06|09 10|\n"
        "|15 16|03 04|07 08|11 12|\n"
        " ----- ----- ----- ----- \n"
        "      |21 22|\n"
        "      |23 24|\n"
        "       ----- \n\n"
    );
    
    printf("Enter colors string (w - white, g - green, y - yellow, b - blue, r - red, o - orange):\n");
    
    for(int i = 0; i < 6; i++) {
        cube[i][0] = getchar();
        cube[i][1] = getchar();
        cube[i][2] = getchar();
        cube[i][3] = getchar();
    }
    
    short w = 0, g = 0, o = 0, b = 0, r = 0, y = 0;
    for(short i = 0; i < 6; i++) {
        for(short ii = 0; ii < 4; ii++) {
            switch(cube[i][ii]) {
            case 'w':
                w++;
                break;
            case 'g':
                g++;
                break;
            case 'o':
                o++;
                break;
            case 'b':
                b++;
                break;
            case 'r':
                r++;
                break;
            case 'y':
                y++;
                break;
            }
        } 
    }
    
    if(w != 4 || g != 4 || o != 4 || b != 4 || r != 4 || y != 4) {
        printf("Bad cube pattern!\n");
        
        end();
    }
    
    if(cube_is_solved()) {
        printf("Cube is allready solved!\n");
        
        end();
    }
    
    printf("Trying to solve in 1 move...\n");
    
    long long cnt = 0;
    
    cube_copy();
    
    short max_moves = 1;
    short* moves = malloc(max_moves * sizeof(short));
    
    while(1) {
        if(cnt >= powers_of_3[max_moves - 1]) {
            printf("Trying to solve in %d moves...\n", ++max_moves);
            
            cnt = 0;
            if(max_moves > 23) {
                printf("Bad cube pattern!\n");
                
                end();
            }
            
            moves = realloc(moves, max_moves * sizeof(short));
        }
        
        short i;
        long long moves_to_do = cnt;
       
        for(i = 0; i < max_moves; i++, moves_to_do /= 3) {
            short move = moves_to_do % 3;
            
            moves[i] = move;
            
            switch(move) {
            case 0:
                cube_move_front();

                break;

            case 1:
                cube_move_up();

                break;

            case 2:
                cube_move_right();

                break;
            }
        }
        
        if(cube_is_solved()) {
            printf("Done.\n");
            
            for(short ii = 0; ii < max_moves; ii++) {
                switch(moves[ii]) {
                case 0:
                    printf("F ");
                    break;
                case 1:
                    printf("U ");
                    break;
                case 2:
                    printf("R ");
                    break;
                }
            }
            
            printf("\n");
            
            end();
        }

        cube_restore();
        
        cnt++;
    }
}

/*if(cnt % 500000 == 0) {
    printf("%d - ", cnt);

    for(short ii = 0; ii < i; ii++) {
        switch(moves[ii]) {
        case 0:
            printf("F ");
            break;
        case 1:
            printf("U ");
            break;
        case 2:
            printf("R ");
            break;
        }
    }

    printf("\n");
}*/

/*for(int i = 0; i < 4; i++)
    cube[0][i] = 'w';

for(int i = 0; i < 4; i++)
    cube[1][i] = 'g';

for(int i = 0; i < 4; i++)
    cube[2][i] = 'y';

for(int i = 0; i < 4; i++)
    cube[3][i] = 'b';

for(int i = 0; i < 4; i++)
    cube[4][i] = 'r';

for(int i = 0; i < 4; i++)
    cube[5][i] = 'o';*/

/*for(int i = 0; i < 6; i++)
    printf("%c %c %c %c\n", cube[i][0], cube[i][1], cube[i][2], cube[i][3]);*/
