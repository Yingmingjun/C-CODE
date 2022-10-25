#include <stdio.h>

void bubble_sort(int array[], int length);


int main(void)
{
        int array1[] = {12,34,567,67,34,4534,45,45,4,435,342,9};
        char array[] = {"abjkhjghd"};
        int i, length;
        
        length = sizeof(array) / sizeof(array[0]);
        bubble_sort(array, length);
		printf("The length of the array is %d\n",length);
        printf("The result is£º");
        
        for (i = 0; i < length; i++)
        {
            printf("%d ", array[i]);
        }
        putchar('\n');
        printf("Peace&Love!");		
        return 0;
}

void bubble_sort(char array[], int length)
{
        int i, j;
        char temp;

        for (i = 0; i < length - 1; i++)
        {
                for (j = 0; j < length - 1 - i; j++)
                {
                        if (array[j] > array[j+1])
                        {
                            temp = array[j];
                            array[j] = array[j + 1];
                            array[j+1] = temp;
                        }
                }
        }
}

