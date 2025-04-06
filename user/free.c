// free prints the amount of free memory available
// in the system.
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  uint64 mem = getfree();
  fprintf(1, "free memory (kb): %ld\n", (mem / 1024));

  exit(0);
}
