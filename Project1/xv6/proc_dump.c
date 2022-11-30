#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
int 
main(int argc, char const *argv[]) {
  int arr[14] = {200, 500, 1200, 1500, 2000, 5000, 8000, 10000, 12000, 15000, 20000, 50000, 80000, 100000};
  int num = sizeof(arr)/sizeof(arr[0]);
  for (int i = 0; i < num; i++)
  {
    int r = fork();
    if (r == 0)
    {
      int* b = malloc(arr[i] * sizeof(int));
      *b = 0;
      while (1) 
        continue;
      exit();
    }
  }
  proc_dump();
  exit();
}
