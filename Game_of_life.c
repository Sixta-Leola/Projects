// [2022] <sixtaleo/-/-> [legal/copyright]
#include <stdio.h>
#include <stdlib.h>
#define LENGTH 80
#define HIGH 25

void check(int matrix[HIGH][LENGTH], int matrix_out[HIGH][LENGTH]);
int input(int matrix[HIGH][LENGTH]);
int step();
int loop(int matrix[HIGH][LENGTH], int m, int n);
void output(int matrix_out[HIGH][LENGTH]);
void cucle(int matrix[HIGH][LENGTH], int matrix_out[HIGH][LENGTH]);

int main() {
    int matrix_in[HIGH][LENGTH], matrix_out[HIGH][LENGTH], state, print = 0;
    input(matrix_in);
    output(matrix_in);
    state = step();
    while (state == 2) {
        check(matrix_in, matrix_out);
        system("clear");
        output(matrix_out);
        cucle(matrix_in, matrix_out);
        state = step();
        if (state == 1) {
            print = 1;
            break;
        } else if (state != 2) {
            printf("print correct simbol\n");
            state = step();
        }
    }
    if (print == 1)
        printf("Game end");
    else
        printf("Game over!!");
    return 0;
}
int step() {
    char step = 0, test1 = 0;
    int err = 0, test = 0;
    test = scanf("%c%c", &step, &test1);
    if ((test != 0) && (step == ' ') && (test1 == '\n')) {
        err = 2;
        test1 = 0;
    } else if ((test != 0) && (step == 'G')) {
        err = 1;
    }
    return err;
}
int input(int matrix[HIGH][LENGTH]) {
    for (int i = 0; i < HIGH; i++) {
        for (int j = 0; j < LENGTH; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    (void)freopen("/dev/tty", "rw", stdin);
    return 0;
}
void output(int matrix_out[HIGH][LENGTH]) {
    printf("\n");
    for (int i = 0; i < HIGH; i++) {
        for (int j = 0; j < LENGTH; j++) {
            if (matrix_out[i][j] == 0)
                printf("%c ", ' ');
            else if (matrix_out[i][j] == 1)
                printf("%c ", '*');
        }
        printf("\n");
    }
}
void check(int matrix[HIGH][LENGTH], int matrix_out[HIGH][LENGTH]) {
    int count;
    for (int i = 0; i < HIGH; i++) {
        for (int j = 0; j < LENGTH; j++) {
            count = loop(matrix, i, j);
            if ((matrix[i][j] == 0) && (count == 3)) {
                matrix_out[i][j] = 1;
            } else if ((matrix[i][j] == 1) && (count < 2)) {
                matrix_out[i][j] = 0;
            } else if ((matrix[i][j] == 1) && (count > 3)) {
                matrix_out[i][j] = 0;
            } else {
                matrix_out[i][j] = matrix[i][j];
            }
        }
    }
}
void cucle(int matrix[HIGH][LENGTH], int matrix_out[HIGH][LENGTH]) {
    for (int i = 0; i < HIGH; i++) {
        for (int j = 0; j < LENGTH; j++) {
            matrix[i][j] = matrix_out[i][j];
        }
    }
}
int loop(int matrix[HIGH][LENGTH], int m, int n) {
    int sum = 0;
    int col, row;
    for (int i = - 1; i <  2; i++) {
        for (int j = - 1; j < 2; j++) {
            col = (m + i + HIGH) % HIGH;
            row = (n + j + LENGTH) % LENGTH;
            sum += matrix[col][row];
        }
    }
    sum -= matrix[m][n];
    return sum;
}
