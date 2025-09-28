// This program is a simple test for scheduler behavior. It spawns child
// processes, which cycle for a non-trivial, but not substantial, time,
// while printing a unique ID periodically, in order to allow you to
// visualize the proportional share of CPU time given to each child. In
// general, visualizing the scheduler behavior will be easiest when the
// OS has a single processor, such as with `CPUS=1 make qemu`. When
// there are more processors than processes, there will be no contention
// that would force proportional sharing to kick in.
#include "kernel/types.h"
#include "user/user.h"

#define CHILD_COUNT 2
#define LOOPS       1000000000
#define PRINT_FREQ  (LOOPS / 1000)

int main() {
  for (int i = 0; i < CHILD_COUNT; i++) {
    int pid = fork();
    if (pid < 0) {
      printf("failed to fork\n");
      return -1;
    }

    if (pid == 0) {
      int start = uptime();
      for (int j = 0; j < LOOPS; j++) {
        if ((j % PRINT_FREQ) == 0) {
          printf("%d", i);
        }
      }
      int end = uptime();
      printf("child %d finished in %d ticks\n", i, end - start);
      return 0;
    }

    if ((i % 2) != 0) {
      setpriority(pid, 100);
    }
  }

  for (int i = 0; i < CHILD_COUNT; i++) {
    wait(0);
  }

  printf("\n");
  printf("exiting...\n");
  return 0;
}
