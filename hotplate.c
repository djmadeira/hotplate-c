#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int build_grid(double grid[], int gridw, int gridh) {
  int row = 0;
  int col = 0;
  int count = gridw * gridh;

  int i=0;
  while(i < count) {
    // find the corners
    if (i == 0 || i == count - 1 ||
        (row == 0 && col == gridw - 1) ||
        (row == gridh - 1 && col == 0)) {
      grid[i] = 0;
      goto increment;
    }

    // find the middle
    if ((row == 7 || row == 8) &&
        (col == 7 || col == 8)) {
      grid[i] = 100;
      goto increment;
    }

    grid[i] = 50;

    // set up row and col vars
 increment:
    i++;
    if (i % gridw == 0) {
      row++;
      col=0;
    } else {
      col++;
    }
  }

  return 0;
}

int print_grid(double grid[], int gridw, int gridh) {
  int i = 0;
  int count = gridw * gridh;

  while (i < count) {
    printf("| %03.02f ", grid[i]);

    i++;
    if (i % gridw == 0) {
      printf("|\n");
    }
  }

  return 0;
}

double step_grid(double grid[], int gridw, int gridh) {
  double change = 0.0f; 
  double avg = 0.0f;
  int row = 0;
  int col = 0;
  int count = gridw * gridh;
  double sum;
  int i = 0;
  int siblings;

  double grid_dup[gridw * gridh];

  for (i=0; i < count; i++) {
    grid_dup[i] = grid[i];
  }

  i=0;
  while(i < count) {
    // skip the corners
    if (i == 0 || i == count - 1 ||
        (row == 0 && col == gridw - 1) ||
        (row == gridh - 1 && col == 0)) {
      goto increment;
    }

    // skip the middle
    if ((row == 7 || row == 8) &&
        (col == 7 || col == 8)) {
      goto increment;
    }

    // take the average
    sum = 0.0f;
    siblings = 0;

    if (col > 0) {
      siblings++;
      sum += grid[i-1];
    }

    if (col < gridw - 1) {
      siblings++;
      sum += grid[i+1];
    }

    if (i - gridw >= 0) {
      siblings++;
      sum+= grid[i-gridw];
    }

    if (i + gridw > gridh) {
      siblings++;
      sum += grid[i+gridw];
    }

    avg = (double)sum / (double)siblings;
    if (avg - grid[i] > change) {
      change = avg - grid[i];
    }

    grid_dup[i] = avg;
    
    // increment row and col vars
 increment:
    i++;
    if (i % gridw == 0) {
      row++;
      col=0;
    } else {
      col++;
    }
  }

  for (i=0; i < count; i++) {
    grid[i] = grid_dup[i];
  }

  return change;
}

int main (int argc, char *argv[]) {
  int gridw = 16;
  int gridh = 16;
  double grid[gridw * gridh];
  int rc;
  double change = 1.0f;
  int turns = 0;

  rc = build_grid(grid, gridw, gridh);
  
  while(change > 0.01f) {
    change = step_grid(grid, gridw, gridh);
    turns++;
  }

  rc = print_grid(grid, gridw, gridh);
  printf("Turns: %d\n", turns);

  return 0;
}
