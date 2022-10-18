// Split words: https://www.w3resource.com/c-programming-exercises/string/c-string-exercise-31.php

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int power(int a, int b)
{
    int power = 1;
    for(int i=1; i<=b; i++)
        power *= a;
    return power;
}

int Find_Person(char names[][30], char person[30], int n)
{
    for (int j = 0; j < n; j++)
    {
        if (strcmp(names[j], person) == 0)
            return j;
    }
    return -1;
}

int char_to_int(char newString[])
{
    int size = strlen(newString);
    int number = 0;
    int j = 0;
    while(size!=0)
    {
        number += (newString[j] - '0') * power(10,size - 1);
        j++;
        size--;
    }
    return number;
}

void Compute(int numbers[], char names[][30], int n, char curr_person[], int* persons_money)
{
    if (numbers[1] != 0)
    {
        int income = floor(numbers[0] / numbers[1]);
        int reverse = numbers[0] % numbers[1];
        int d = Find_Person(names,curr_person,n);
        persons_money[d] = persons_money[d] - numbers[0] + reverse;
        for (int k = 0; k < numbers[1]; k++)
        {
            char person2[30];
            scanf("%s", person2);
            persons_money[Find_Person(names,person2,n)] += income;
        }   
    }
}

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d", &n);
    while ((getchar()) != '\n');
    char names[n][30];
    int* persons_money = (int*) malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
        persons_money[i] = 0;

    for (int i = 0; i < n; i++)
        scanf("%s", names[i]);

    for (int i = 0; i < n; i++)
    {
        int numbers[2];
        char curr_person[30];
        scanf("%s", curr_person);
        scanf("%d %d", &numbers[0], &numbers[1]);
        Compute(numbers, names, n, curr_person, persons_money);
    }
    for (int i = 0; i < n; i++)
        printf("%s %d\n", names[i], persons_money[i]);
    free (persons_money);
    return 0;
}