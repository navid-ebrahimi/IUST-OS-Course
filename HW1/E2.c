#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


int power(int a, int b)
{
    int power = 1;
    for(int i=1; i<=b; i++)
    {
        power *= a;
    }
    return power;
}

int char_to_int(char newString[])
{
    int size = strlen(newString);
    int number = 0;
    
    int sign = 0;
    if (newString[0] == '-')
    {
        sign++;
        size--;
    }
    int j = sign;
    while(size!=0)
    {
        number += (newString[j] - '0') * power(10,size - 1);
        j++;
        size--;
    }
    if (sign == 1)
        number *= -1;
    return number;
}

int* Split_numbers(char detail[], int n)
{
    int j=0;int ctr=0;
    char newString[n][20];
    int* numbers = (int*) malloc(3*n*sizeof(int));
    for(int k=0;k<=(strlen(detail));k++)
    {
        if(detail[k]==' '||detail[k]=='\0' || detail[k] == '\n')
        {
            newString[ctr][j]='\0';
            numbers[ctr] = char_to_int(newString[ctr]);
            ctr++;
            j=0;
        }
        else
        {
            newString[ctr][j]=detail[k];
            j++;
        }
    }
    return numbers;
}

int Compute_Sum(int numbers[], int start, int end)
{
    int sum = 0;
    for(int i = start; i<=end; i++)
    {
        sum += numbers[i];
    }
    return sum;
}

int Compute_Max(int numbers[], int n)
{
    int max_value = 0;
    for(int i = 0; i<n;i++)
    {
        for(int j = 0;j<n;j++)
        {
            int value = Compute_Sum(numbers,i,i+j);
            if (max_value < value)
                max_value = value;
        }
    }
    return max_value;
}

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d", &n);
    while ((getchar()) != '\n');
    char input[n*3];
    fgets(input, n*3, stdin);
    int *numbers;
    numbers = Split_numbers(input, n);
    int max_value = Compute_Max(numbers, n);
    free (numbers);
    if (max_value < 0)
        printf("0");
    else
        printf("%d\n", max_value);
    return 0;
}
