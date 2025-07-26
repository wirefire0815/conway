#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define HEIGHT 16
#define WIDTH 16

typedef struct {
  int number;
  int display[HEIGHT][WIDTH];
} Frame;

struct Node {
  Frame head;
  struct Node *next;
  // add previous too
}; // come up with a better name

static int numerator = 0;

int display[HEIGHT][WIDTH] = {0};
int next_display[HEIGHT][WIDTH] = {0};

void init_node(struct Node *node) {
  node->head.number = numerator++;
  node->next = NULL;

  memset(node->head.display, 0, sizeof(node->head.display));
}

void print_display(Frame f) {
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      if (f.display[y][x]) {
        printf("X");
      } else {
        printf(".");
      }
    }
    printf("\n");
  }
}

int mod(int a, int b) { return (a % b + b) % b; }

int count_neighbours(int cx, int cy, Frame f) {
  int count = 0;
  for (int dx = -1; dx <= 1; ++dx) {
    for (int dy = -1; dy <= 1; ++dy) {
      if (!(dx == 0 && dy == 0)) {
        int x = mod(cx + dx, WIDTH);
        int y = mod(cy + dy, HEIGHT);
        if (f.display[y][x])
          count += 1;
      }
    }
  }
  return count;
}

void calc_next_frame(struct Node *n) {
  struct Node *cur_n = n;
  while (cur_n->next != NULL) {
    cur_n = cur_n->next;
  }

  struct Node *next_n = malloc(sizeof(struct Node));

  if (!next_n) {
    fprintf(stderr, "malloc failed\n");
    exit(1);
  }

  init_node(next_n);

  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      int neighbours = count_neighbours(x, y, cur_n->head);
      if (cur_n->head.display[y][x]) {
        next_n->head.display[y][x] = (neighbours == 3 || neighbours == 2);
      } else {
        next_n->head.display[y][x] = neighbours == 3;
      }
    }
  }
  cur_n->next = next_n;
}

void print_all_frames(struct Node *node) {
  struct Node *cur_n = node;
  while (cur_n != NULL) {
    print_display(cur_n->head);
    printf("-------------------------------\n");
    cur_n = cur_n->next;
  }
}

void delete_frame(struct Node **node, int index) {
  struct Node *cur_n = *node;

  if (index == 0) {
    *node = cur_n->next;
    free(cur_n);

  } else {
    while (cur_n->head.number != index - 1) {
      cur_n = cur_n->next;
    }

    struct Node *old_n = cur_n->next;
    cur_n->next = cur_n->next->next;
    free(old_n);
  }
}

int main() {

  struct Node *node = malloc(sizeof(struct Node));

  init_node(node);

  node->head.display[0][1] = 1;
  node->head.display[1][2] = 1;
  node->head.display[2][0] = 1;
  node->head.display[2][1] = 1;
  node->head.display[2][2] = 1;

  for (int i = 0; i < 5; ++i) {
    calc_next_frame(node);
  }
  // print_display(node->next->head);

  delete_frame(&node, 0);

  print_all_frames(node);

  /*
    for (;;) {
      print_head_display();
      calc_next_step();
      memcpy(display, next_display, sizeof(display));
      printf("----------------------------------\n");
      unosleep(100 * 10000);
    }*/
}