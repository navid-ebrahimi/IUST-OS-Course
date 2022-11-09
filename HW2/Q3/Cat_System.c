#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    char rule[1024] = "cat ";
    strcat(rule, argv[1]);
    system(rule);
    return 0;
}