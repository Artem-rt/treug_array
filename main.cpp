#include <stdio.h>
#include <assert.h>
#include <math.h>

//почему проблема с неиспольз. free() - называется утечкой памяти?

#define A1_IN_PROGRESSION_ARRAY 1
#define ZERO_ARRAY_START 1
#define CANARY 1

int get (int str, int elem, int data[]);

int main()
{
    FILE* data_elements;

    data_elements = fopen("DATA.txt","r");

    int num_array = 0;
    fscanf (data_elements, "%d", &num_array);

    int * data = (int *)calloc (num_array, sizeof(int));

    for (int i = 1; i <= num_array; i++)
    {
        fscanf (data_elements, "%d", &data [i-1]);
    }

    int num_str = 1;
    int num_elem = 0;

    for (int i = 0; i < num_array - CANARY; i++)
    {
        printf ("%d ", data [i]);
        num_elem ++;
        if (num_elem == num_str)
        {
            printf ("\n");
            num_str ++;
            num_elem = 0;
        }
    }

    printf ("%d\n", get (1, 1, data));

    if (fclose (data_elements) != 0)
    {
        printf ("\e[32m" "Warning! The file was not closed correctly!\n" "\e[0m");
    }

    free (data);

    return 0;

}

int get (int str, int elem, int data [])
{
    int cnt_array = 0;
    for (int i = 0; data[i] != 0xDED; i++)
        cnt_array++;

    if (  (str < elem) ||
        (cnt_array < ((A1_IN_PROGRESSION_ARRAY + str)* str/2) - (str - elem))  )
        //used the formula for an arithmetic progression

    {
        printf ("Error!This element does not exist. There are %d elements in the entered string.\n", str);
        exit (1);
        // return 0xBEDA
    }

    return data [((A1_IN_PROGRESSION_ARRAY + str)* str /2)  - (str - elem) - ZERO_ARRAY_START];
    //used the formula for an arithmetic progression
}
