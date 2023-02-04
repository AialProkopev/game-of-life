#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <math.h>

#define HEIGHT 25
#define WIDTH 80
#define DEAD ' '
#define ALIVE '*'
#define BORDER '#'
#define TIMER 50 // ms

void clear_screen();
char **init_screen();
void render(char **screen);
char **create_matrix();
void cycle(char **screen);
int calc_nbr(char **screen, int i, int j);
int convert_h(int num);
int convert_w(int num);

int main() {
    char **screen = init_screen();
    int status = 1;
    do {
        render(screen);
        cycle(screen);
        usleep(TIMER * 1000);
    } while (status);

    free(screen);
    return 0;
}

void clear_screen() { system("clear"); }
char **create_matrix() {
    char **matrix = (char **)malloc(HEIGHT * sizeof(char *) + HEIGHT * WIDTH * sizeof(char));
    char *p = (char *)(matrix + HEIGHT);
    for (int i = 0; i < HEIGHT; i++) {
        matrix[i] = p + WIDTH * i;
    }
    return matrix;
}

char **init_screen() {
    char **screen = create_matrix();
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if ((i == 0) || (i == HEIGHT - 1) || (j == 0) || (j == WIDTH - 1)) {
                screen[i][j] = BORDER;
            }
            else if (((j == 31) && (i == 8)) || 
                ((j == 32) && (i == 9)) ||
                (j >= 30) && (j <= 32) && (i == 10)) {
                screen[i][j] = ALIVE;
            } else {
                screen[i][j] = DEAD;
            }
        }
    }
    return screen;
}
void render(char **screen) {
    clear_screen();
    for (int i = 0; i < HEIGHT; i++) {
        if (i != 0) printf("\n");
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", screen[i][j]);
        }
    }
    printf("\n");
}
void cycle(char **screen) {
  char **copy = create_matrix();
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      copy[i][j] = screen[i][j];
    }
  }
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
            //Life
            if ((copy[i][j] == DEAD) && (calc_nbr(copy, i, j) == 3)) {
                screen[i][j] = ALIVE;
            }
            //Death
            if ((copy[i][j] == ALIVE) && ((calc_nbr(copy, i, j) < 2) ||
                        (calc_nbr(copy, i, j) > 3))) {
                screen[i][j] = DEAD;
            }
    }
  }
  free(copy);
}
int calc_nbr(char **screen, int i, int j) {
    int count = 0;
    if (screen[convert_h(i - 1)][convert_w(j - 1)] == ALIVE)
        count++;
    if (screen[convert_h(i - 1)][j] == ALIVE)
        count++;
    if (screen[convert_h(i - 1)][convert_w(j + 1)] == ALIVE)
        count++;
    if (screen[i][convert_w(j + 1)] == ALIVE)
        count++;
    if (screen[convert_h(i + 1)][convert_w(j + 1)] == ALIVE)
        count++;
    if (screen[convert_h(i + 1)][j] == ALIVE)
        count++;
    if (screen[convert_h(i + 1)][convert_w(j - 1)] == ALIVE)
        count++;
    if (screen[i][convert_w(j - 1)] == ALIVE)
        count++;
    return count;
}
int convert_h(int num) {
    int res = num;
    if (num < 1) {
        res = HEIGHT - 2 + res;
    } else if (num > HEIGHT - 2) {
        res = res - (HEIGHT - 2);
    }
    return res;
}
int convert_w(int num) {
    int res = num;
    if (num < 1) {
        res = WIDTH - 2 + res;
    } else if (num > WIDTH - 2) {
        res = res - (WIDTH - 2);
    }
    return res;
}

