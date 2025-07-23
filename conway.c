#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define HEIGHT 16
#define WIDTH 16

int display[HEIGHT][WIDTH] = {0};
int next_display[HEIGHT][WIDTH] = {0};

void printArray(int *arr) {
  for (int i = 0; i < (int)sizeof(arr) / sizeof(int); i++) {
    printf("%d\n", arr[i]);
  }
}

void init_display() {
  display[0][1] = 1;
  display[1][2] = 1;
  display[2][0] = 1;
  display[2][1] = 1;
  display[2][2] = 1;
}

void print_current_display() {
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      if (display[y][x]) {
        printf("X");
      } else {
        printf(".");
      }
    }
    printf("\n");
  }
}

int mod(int a, int b) { return (a % b + b) % b; }

int count_neighbours(int cx, int cy) {
  int count = 0;
  for (int dx = -1; dx <= 1; ++dx) {
    for (int dy = -1; dy <= 1; ++dy) {
      if (!(dx == 0 && dx == 0)) {
        int x = mod(cx + dx, WIDTH);
        int y = mod(cy + dy, HEIGHT);
        if (display[y][x])
          count += 1;
      }
    }
  }
  return count;
}

void next_step() {
  int is_alive;
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      int neighbours = count_neighbours(x, y);
      if (display[y][x]) {
        next_display[y][x] = (neighbours == 3 || neighbours == 2);
      } else {
        next_display[y][x] = neighbours == 3;
      }
    }
  }
}

int main(int argc, char *argv[]) {
  init_display();

  for (;;) {
    print_current_display();
    next_step();
    memcpy(display, next_display, sizeof(display));
    printf("----------------------------------\n");
    usleep(100 * 1000);
  }
}