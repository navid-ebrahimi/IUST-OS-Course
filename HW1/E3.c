#include <stdio.h>
#include <math.h>
#include <stdlib.h>
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

void Remove_str(char str[], int start, int repeat)
{
    for(int j = 0; j < repeat; j++)
    {
        for (int i = start; i < 200; i++)
        {
            str[i] = str[i+1];
        }
    }
}

void delete_space(char str[])
{
    for(int i = 0; i<200; i++)
    {
        if (str[i] == ' ')
        {
            Remove_str(str, i, 1);
        }
    }
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

int Compute_Sum(int numbers[], int end)
{
    int sum = 0;
    for(int i = 0; i<end; i++)
    {
        sum += numbers[i];
    }
    return sum;
}

int* Split_numbers(char detail[], int start, int end, int n, int* len)
{
    int j=0;int ctr=0;
    char newString[n][200];
    int* numbers = (int*) malloc(3*n*sizeof(int));
    for(int k=start;k<= end;k++)
    {
        if(detail[k]==','|| detail[k]=='\0' || detail[k] == '\n' || detail[k] == '}')
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
    *len = ctr;
    return numbers;
}

int len_int(int n)
{
    int len = 0;
    if (n == 0)
        len++;
    while(n!=0)
    {
        len++;
        n/=10;
    }
    return len;
}

int Compute(char str[])
{
    for(int j = 0; j<200;j++)
    {
        int s = 0;
        int final_s;
        int final_e = 200;
        for(int i = 0; i < 200 ; i++)
        {
            if (str[i] == '{') 
            {
                final_s = i;
            }
            if (str[i] == '}' && final_e > i) 
            {
                final_e = i;
                break;
            }
        }
        int len;
        int *numbers;
        numbers = Split_numbers(str, final_s+1, final_e, 200, &len);
        int sum = Compute_Sum(numbers,len);
        if (sum == 0 && final_e == 200)
            break;
        Remove_str(str, final_e, 1);
        Remove_str(str, final_s, final_e - final_s - len_int(sum));
        printf("%d\n", sum);
        int sum_prim = sum;
        for(int i = 0; i < len_int(sum_prim);i++)
        {
            char num = floor(sum/power(10,len_int(sum)-1)) + '0';
            sum -= floor(sum/power(10,len_int(sum)-1)) * power(10,len_int(sum)-1);
            str[final_s] = num;
            final_s++;
        }
    }
}

int main(int argc, char const *argv[])
{
    char* str = (char*) malloc(200*sizeof(char));
    scanf("%[^\n]s", str);
    delete_space(str);
    Compute(str);
    return 0;
}