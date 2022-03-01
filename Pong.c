#include <stdio.h>
#define FIELD_length 80
#define FIELD_width 25

int field_gen(int x, int y, int position_1, int position_2, int pos_ball_x, int pos_ball_y, int points);
int win(int a);
int data_in(void);
int rocket1_pos(int chan, int position_1);
int rocket2_pos(int chan, int position_2);
int ball_pos_x(int ball_x, int ball_y, int position_1, int position_2);
int ball_pos_y(int angleC, int ball_y, int ball_x, int position_1, int position_2);

int points = 0, BallSpd = -1, angle = 0, a, b, c;
int position_1 = 11, position_2 = 11, pos_ball_x = 2, pos_ball_y = 12;

int main(void) {
    field_gen(FIELD_width, FIELD_length, position_1, position_2, pos_ball_x, pos_ball_y, points);
    while (c/10000 == 0) {
        a = data_in();
        if ((a > 0) && (a <= 5)) {
            position_1 = rocket1_pos(a, position_1);
            position_2 = rocket2_pos(a, position_2);
            b = ball_pos_x(pos_ball_x, pos_ball_y, position_1, position_2);
            pos_ball_x = b%100;
            pos_ball_y = ball_pos_y((b/100)%10, pos_ball_y, pos_ball_x, position_1, position_2);
            c = win(b/1000);
            points = c%10000;
            a = 0;
            printf("\033c");
            field_gen(FIELD_width, FIELD_length, position_1, position_2, pos_ball_x, pos_ball_y, points);
        } else {
            printf("Print a or z or m or k or \' \'\n");
        }
    }
    printf("                                 Player %d win\n", c/10000);
    return 0;
}

// Функция вывода всей графики на экран
int field_gen(int x, int y, int position_1, int position_2, int pos_ball_x, int pos_ball_y, int points) {
    for (int i = 0; i < x; i++) {
        for (int n = 0; n < y; n++) {
            if ((i == 0) || (i == x-1))
                printf("▓");
            else if ((i == pos_ball_y) && (n == pos_ball_x))  // вывод шарика
                printf("•");
            else if ((n == y/2 -1) || (n == y/2 -2))
                printf("|");
            else if ((i == 3) && (n == 33))
                printf("%1d", points/10%10);  // вывод десятков числа очков первоого игрока
            else if ((i == 3) && (n == 34))
                printf("%1d", points%10);  //  вывод единиц числа очков первоого игрока
            else if ((i == 3) && (n == 44))
                printf("%1d", points/100%10);  //  вывод единиц числа очков второго игрока
            else if ((i == 3) && (n == 43))
                printf("%1d", points/1000);  //  вывод десятков числа очков второго игрока
            else if (((i == position_1) || (i == position_1+1) || (i == position_1+2)) && (n == 1))
                printf("▐");
            else if (((i == position_2) || (i == position_2+1) || (i == position_2+2)) && (n == y-2))
                printf("▐");
            else if ((n == 0) ||(n == y-1))
                printf("▒");
            else
                printf(" ");
        }
        printf("\n");
     }
    return (0);
}

// Функция обработки вводимых пользователем символов управления, обработка ошибок ввода
int data_in(void) {
    char inp = 0, test = 0;
    short int state = 0;
    scanf("%c%c", &inp, &test);
    if (((inp != 'A') || (inp != 'Z') || (inp != 'K') || (inp != 'M') || (inp != ' ')) && (test != '\n')) {
        inp = 0;
        test = 0;
        state = 0;
        return 0;
    } else {
        switch (inp) {
            case 'A' :
                state = 1;
                break;
            case 'Z' :
                state = 2;
                break;
            case 'K' :
                state = 3;
                break;
            case 'M' :
                state = 4;
                break;
            case ' ' :
                state = 5;
                break;
            default :
                printf("ERROR data_in function\n");
                break;
        }
    }
    return state;
}

// Функция подсчета очков и определения окончания игры
int win(int a) {
    if (a == 1) {
        points++;
    } else if (a == 2) {
        points += 100;
    }
    if (points%100 == 21) {
        return 10000;
    } else if (points/100 == 21) {
        return 20000;
    }
    return points;
}

// Обработка изменения позиции первой ракетки
int rocket1_pos(int chan, int position_1) {
    switch (chan) {
        case 1 :
            position_1 > 1 ? position_1-- : position_1;
            break;
        case 2 :
            position_1 < FIELD_width-4 ? position_1++ : position_1;
            break;
        default :
            printf(" rocket1_pos function");
            break;
    }
    return position_1;
}

// Обработка изменения позиции второй ракетки
int rocket2_pos(int chan, int position_2) {
    switch (chan) {
        case 3 :
            position_2 > 1 ? position_2-- : position_2;
            break;
        case 4 :
            position_2 < FIELD_width-4 ? position_2++ : position_2;
            break;
        default :
            printf(" rocket2_pos function");
            break;
    }
    return position_2;
}

// Обработка изменения позиции x шарика
int ball_pos_x(int ball_x, int ball_y, int position_1, int position_2) {
    if ((ball_x == 2) && (position_1+1 == ball_y)) {
        BallSpd *= -1;
        ball_x += BallSpd;
        return ball_x;
    } else if ((ball_x == 77) && (position_2+1 == ball_y)) {
        BallSpd *= -1;
        ball_x += BallSpd;
        return ball_x;
    } else if ((ball_x == 2) && (position_1 == ball_y)) {
        BallSpd *= -1;
        ball_x += BallSpd;
        ball_x += 100;
        return ball_x;
    } else if ((ball_x == 2) && (position_1+2 == ball_y)) {
        BallSpd *= -1;
        ball_x += BallSpd;
        ball_x += 200;
        return ball_x;
    } else if ((ball_x == 77) && (position_2 == ball_y)) {
        BallSpd *= -1;
        ball_x += BallSpd;
        ball_x += 100;
        return ball_x;
    } else if ((ball_x == 77) && (position_2+2 == ball_y)) {
        BallSpd *= -1;
        ball_x += BallSpd;
        ball_x += 200;
        return ball_x;
    } else if (ball_x < 2) {
        BallSpd *= 1;
        ball_x = 2;
        ball_x += 2300;
        return ball_x;
    } else if (ball_x > 77) {
        BallSpd *= 1;
        ball_x = 77;
        ball_x += 1300;
        return ball_x;
    } else {
        ball_x += BallSpd;
        return ball_x;
    }
}

// Обработка изменения позиции y шарика
int ball_pos_y(int angleC, int ball_y, int ball_x, int position_1, int position_2) {
    if (ball_y == 1) {
        angle = 1;
        ball_y += angle;
        return ball_y;
    } else if (ball_y == 23) {
        angle = -1;
        ball_y += angle;
        return ball_y;
    } else if ((angleC == 1) && (angle == 0)) {
        angle = -1;
        ball_y += angle;
        return ball_y;
    } else if ((angleC == 2) && (angle == 0)) {
        angle = 1;
        ball_y += angle;
        return ball_y;
    } else if ((angleC == 1) && (angle != 0)) {
        angle *= -1;
        ball_y += angle;
        return ball_y;
    } else if ((angleC == 2) && (angle != 0)) {
        angle *= -1;
        ball_y += angle;
        return ball_y;
    } else if ((angleC == 3) && (ball_x < 40)) {
        angle = 0;
        ball_y = position_1+1;
        return ball_y;
    }  else if ((angleC == 3) && (ball_x > 40)) {
        angle = 0;
        ball_y = position_2+1;
        return ball_y;
    } else {
        ball_y += angle;
        return ball_y;
    }
}
