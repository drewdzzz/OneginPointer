#include <stdio.h>
#include <assert.h>
#include <math.h>
#define INPUTFILE_NAME  "onegin.txt"
#define OUTPUTFILE_NAME "oneginOut.txt"
#define MAX_STRING_SIZE 50
#define MAX_STRING_NUM  50
//#define DEBUG

//{----------------------------------------------------------------------------
//!
//! @brief Функция позволяет поместить поэму в массив
//!
//! @param fp поток, из которого осуществляется ввод
//!
//! @param poem двумерный массив типа char, в который будет осуществляться ввод
//!
//! @param *lines_in_poem параметр, в который передаётся размер кол-во строк (ограничивается константой MAX_STRING_NUM)
//!
//! @par как юзать:
//! @code
//! readInput ( fp, poem, &lines_in_poem);
//! @endcode
//}----------------------------------------------------------------------------

void readInput ( FILE* fp, char* poem, int* lines_in_poem, int );

//{----------------------------------------------------------------------------
//!
//! @brief An usual BubbleSort:)
//!
//! @param poem double-dimensional array that will be sorted
//!
//! @param arraySize size of sorted array
//}----------------------------------------------------------------------------

void bubbleSort ( char* poem, int arraySize, int string_length );
void mySwap (char* mySwappingArray, int a, int b, int string_length);
int strcmp (char*, char*);
int main ()
{
    FILE* fp;
    if ( !(fp = fopen ( INPUTFILE_NAME, "r")) )
    {
        fprintf (stderr,"Input file is not open");
        return 1;
    }
    int lines_in_poem = MAX_STRING_NUM;
    char poem_arr[MAX_STRING_NUM][MAX_STRING_SIZE];
    char* poem = &poem_arr[0][0];
    readInput ( fp, poem, &lines_in_poem, MAX_STRING_SIZE );

    #ifdef DEBUG
    printf ("Reading complete!\n");
            for ( int i = 0; i < lines_in_poem; i++)
            puts(poem[i]);
    #endif

    bubbleSort ( poem, lines_in_poem, MAX_STRING_SIZE);
    #ifdef DEBUG
    printf ("Poem Sorted!");
    #endif
    fclose(fp);
    if ( !(fp = fopen ( OUTPUTFILE_NAME, "w")) )
    {
        fprintf (stderr, "Output file is not open");
        return 1;
    }
    for (int i = 0; i < lines_in_poem; i++)
        fputs ( ( poem + i*MAX_STRING_SIZE*sizeof(char) ), fp);
    return 0;
}

void readInput ( FILE* fp, char* inputArray, int* lines_in_poem, int string_length)
{
    assert (isfinite(*lines_in_poem));
    assert (!feof(fp));

    int poemlines = *lines_in_poem;
    for (int i = 0; i < poemlines; i++)
        if (!feof (fp))
            fgets ( (inputArray+i*string_length*sizeof(char)), MAX_STRING_SIZE, fp);
        else
        {
            *lines_in_poem = i;
            return;
        }
}


void bubbleSort( char* poem, int arraySize, int string_length)
{
    assert ( poem != NULL );
    assert ( isfinite (arraySize) );
    for (int i = 0; i < arraySize; i++)
        for (int j = i; j < arraySize; j++)
            if ( strcmp ( poem + i*string_length*sizeof(char), poem + j*string_length*sizeof(char)) > 0 )
            {
                mySwap (poem, i, j, string_length);
                #ifdef DEBUG
                    printf("mySwapPED!\n");
                #endif
            }
}




//{----------------------------------------------------------------------------
//! @brief Компоратор строк (понижает регистры)
//!
//! @return Возвращает разницу кодов между первыми попавшимися разными символами строк (0 если равны, >0 если a>b, <0 если a<b)
//!
//!
//!
//!
//}----------------------------------------------------------------------------

int strcmp ( char* string1, char* string2 )
{
    assert ( string1 != NULL );
    assert ( string2 != NULL );
    #ifdef DEBUG
        printf ("IS COMPARING...\n");
    #endif
    int i = 0;
    while ( string1[i] != '\0' && string2[i] != '\0' )
    {
        if ( string1[i] >= 'A' && string1[i] <= 'Z' ) string1[i] += ('a' - 'A');
        if ( string2[i] >= 'A' && string2[i] <= 'Z' ) string2[i] += ('a' - 'A');
        if ( string1[i] != string2[i] ) return string1[i] - string2[i];
        i++;
    }

    return string1[i] - string2[i];
}


//{----------------------------------------------------------------------------
//!
//! @brief Функция меняется местами два элемента в массиве char
//!
//! @param array массив, в котором меняются элементы
//! @param a индекс первого элемента
//! @param b индекс второго элемента
//!
//}----------------------------------------------------------------------------

void mySwap (char* mySwappingArray, int a, int b, int string_length)
{
    assert (isfinite(a));
    assert (isfinite(b));
    assert (mySwappingArray != NULL);
    #ifdef DEBUG
        printf("IS mySwapPING...\n");
    #endif
    for (int i = 0; i < MAX_STRING_SIZE; i++)
    {
        *(mySwappingArray + a*string_length*sizeof(char) + i) += *(mySwappingArray + b*string_length*sizeof(char) + i);
        *(mySwappingArray + b*string_length*sizeof(char) + i) = *(mySwappingArray + a*string_length*sizeof(char) + i) - *(mySwappingArray + b*string_length*sizeof(char) + i);
        *(mySwappingArray + a*string_length*sizeof(char) + i) -= *(mySwappingArray + b*string_length*sizeof(char) + i);
    }
}

