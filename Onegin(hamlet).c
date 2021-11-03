#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>


#define $meow printf("\nMeow from line: %d\nfrom function %s\n", __LINE__, __PRETTY_FUNCTION__);
#define PHYPM HUINYA
#define EPSILON 5
#define STARTNUM 69
#define ass assert
#define SYMBOL_IS_USELESS *str == 'С' || *str == 'ц' || *str == 'е' || *str == 'н' || *str == 'а' || *str == 'M'       \
 ||*str == 'V' || *str == 'L' || *str == 'X' || *str == 'I' || *str == ' ' || *str == 'A' || *str == 'C' || *str == 'S'\
 || *str == 'e' || *str == 'n' || *str == 'A' || *str == 'Г' || *str == 'л' || *str == 'в'

typedef struct {
    char* strStart;
    char* strEnd;
} string;

enum {
    FROM_START,
    FROM_END,
    ENG = 0,
    RUS,
};

char* From_File_to_buffer (void);

string* Index_Make (char* ptrBuff, size_t* ptr_indexsize);

size_t Find_indexsize_and_str_make (char* ptrBuff);

void Str_bubble_Sort (string Index[], size_t indexsize, int mode);

void Output_to_File (string Index[], size_t indexsize);

int Is_malloc (const char* str);

void Poem_generator (string Index[], size_t indexsize);

//--------------------------------------------------------------------------------
//Sort from start

int Str_Compare_from_start (const char* str1, const char* str2);

char* Str_platinum_from_start (const char* str);

//--------------------------------------------------------------------------------
//Sort from end

int Str_Compare_from_end (const char* str1, const char* str2);

char* Str_platinum_from_end (const char* str);

//---------------------------------------------------------------------------------



int main (void)
{
    setlocale (LC_ALL, "Rus");

    size_t indexsize = 0;
    char* ptrBuff = From_File_to_buffer ();
    ass (ptrBuff != NULL);

    string* Index = Index_Make (ptrBuff, &indexsize);
    ass (Index != NULL);

    Str_bubble_Sort (Index, indexsize, FROM_END);

    Poem_generator (Index, indexsize);

    Output_to_File (Index, indexsize);

    free (ptrBuff);
    free (Index);

    return 0;
}

char* From_File_to_buffer (void)
{
    FILE* buffer = fopen ("onegin.txt", "r");
    ass (buffer != NULL);

    fseek(buffer, 0, SEEK_SET);
    long start_of_File = ftell (buffer);

    fseek(buffer, 0, SEEK_END);
    long end_of_File = ftell (buffer);

    fseek(buffer, 0, SEEK_SET);
    long size_File = end_of_File - start_of_File;

    char* ptrBuff = (char*) calloc (size_File + 1, sizeof (char));
    ass (ptrBuff != NULL);

    long real_size_File = fread (ptrBuff + 1, sizeof (char), size_File, buffer);

    fclose (buffer);

    *ptrBuff = '\n';
    *(ptrBuff + real_size_File + 1) = '\0';

    ptrBuff = (char*) realloc (ptrBuff, real_size_File + 1);
    ass (ptrBuff != NULL);

    return (char*)ptrBuff;
}

string* Index_Make (char* ptrBuff, size_t* ptr_indexsize)
{
    size_t i = 0;
    *ptr_indexsize = Find_indexsize_and_str_make (ptrBuff);

    string* Index =  (string*) calloc (*ptr_indexsize, sizeof (char*) + sizeof (size_t));
    ass (Index != NULL);

    while (i < *ptr_indexsize)
    {
        if (*ptrBuff == '\0')
        {
            if (Is_malloc (ptrBuff + 1) == 0)
            {
                ass (ptrBuff != NULL);
                Index[i].strStart = ptrBuff + 1;
                i++;
            }
        }
        ptrBuff++;
    }

    for (i = 0; i < *ptr_indexsize; i++)
    {
        Index[i].strEnd = Index[i].strStart + strlen (Index[i].strStart) - 1;
    }

    return (string*) Index;
}

int Str_Compare_from_start (const char* str1, const char* str2)
{
    ass (str1 != NULL);
    ass (str2 != NULL);

    str1 = Str_platinum_from_start (str1);
    str2 = Str_platinum_from_start (str2);
    while (*str1 == *str2 && *str1 != '\0' && *str2 != '\0')
    {
        str1++;
        str2++;
        str1 = Str_platinum_from_start (str1);
        str2 = Str_platinum_from_start (str2);
    }
    return *str2 - *str1;
}

int Str_Compare_from_end (const char* str1, const char* str2)
{
    ass (str1 != NULL);
    ass (str2 != NULL);

    str1 = Str_platinum_from_end (str1);
    str2 = Str_platinum_from_end (str2);
    while (*str1 == *str2 && *str1 != '\0' && *str2 != '\0')
    {
        str1--;
        str2--;
        str1 = Str_platinum_from_end (str1);
        str2 = Str_platinum_from_end (str2);
    }

    return *str2 - *str1;
}

char* Str_platinum_from_start (const char* str)
{
    ass (str != NULL);

    while (isalpha (*str) == 0 && *str != '\0')
    {
        str++;
    }

    ass (str != NULL);

    return (char*)str;
}

char* Str_platinum_from_end (const char* str)
{
    ass (str != NULL);

    while (isalpha (*str) == 0 && *str != '\0')
    {
        str--;
    }

    ass (str != NULL);

    return (char*)str;

}


void Str_bubble_Sort (string Index[], size_t indexsize, int mode)
{
    if (mode == FROM_START)
    {
        for (size_t j = 1; j < indexsize; j++)
        {
            for (size_t i = 0; i < indexsize - j; i++)
            {
                ass ((char*)Index[i].strStart != NULL);
                ass ((char*)Index[i + 1].strStart != NULL);
                if(Str_Compare_from_start (Index[i].strStart, Index[i + 1].strStart) < 0)
                {
                    string temp = Index[i];
                    Index[i] = Index[i + 1];
                    Index[i + 1] = temp;
                }
            }
        }
    }

    else if (mode == FROM_END)
    {
        for (size_t j = 1; j < indexsize; j++)
        {
            for (size_t i = 0; i < indexsize - j; i++)
            {
                ass ((char*)Index[i].strEnd != NULL);
                ass ((char*)Index[i + 1].strEnd != NULL);
                if(Str_Compare_from_end (Index[i].strEnd, Index[i + 1].strEnd) < 0)
                {
                    string temp = Index[i];
                    Index[i] = Index[i + 1];
                    Index[i + 1] = temp;
                }
            }
        }
    }
}

void Output_to_File (string Index[], size_t indexsize)
{
    FILE* sort_buffer = fopen ("sort_onegin.txt", "w");
    ass (sort_buffer != NULL);

    for (size_t i = 0; i < indexsize; i++)
    {
        fputs (Index[i].strStart, sort_buffer);
        fputc ('\n', sort_buffer);
    }

    fclose (sort_buffer);
}

size_t Find_indexsize_and_str_make (char* ptrBuff)
{
    size_t indexsize = 0;
    size_t strsize = 0;

    while (*ptrBuff != '\0')
    {
        if (*ptrBuff == '\n')
        {
            *ptrBuff = '\0';
            if (Is_malloc ((char*)(ptrBuff - strsize + 1)) == 0)
            {
                indexsize++;
            }
            strsize = 0;
        }
        ptrBuff++;
        strsize++;
    }

    return indexsize - 1;
}

int Is_malloc (const char* str)
{
    char* ptr = (char*)str;
    size_t counter_of_bad = 0;

    while (*str != '\0')
    {
        if (SYMBOL_IS_USELESS || isalpha (*str) == 0)
        {
            counter_of_bad++;
        }
        str++;
    }

    if (counter_of_bad > 0.75*(str - ptr) || (str - ptr) < 9)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Poem_generator (string Index[], size_t indexsize)
{
    FILE* poem = fopen ("Poem.txt", "w");
    ass (poem != NULL);

    size_t rifm1[7] = {0};
    size_t rifm2[7] = {0};
    unsigned seed = STARTNUM;

    for (int i = 0; i < 7; i++)
    {
        do{
        seed *= time (NULL);
        srand (seed);
        rifm1[i] = rand () % (indexsize - EPSILON);
        rifm2[i] = rifm1[i] + rand () % EPSILON;
        } while (rifm2[i] == rifm1[i]);
    }

    fprintf (poem, "%s\n", Index[rifm1[0]].strStart);
    fprintf (poem, "%s\n", Index[rifm1[1]].strStart);
    fprintf (poem, "%s\n", Index[rifm2[0]].strStart);
    fprintf (poem, "%s\n", Index[rifm2[1]].strStart);

    fprintf (poem, "%s\n", Index[rifm1[2]].strStart);
    fprintf (poem, "%s\n", Index[rifm2[2]].strStart);
    fprintf (poem, "%s\n", Index[rifm1[3]].strStart);
    fprintf (poem, "%s\n", Index[rifm2[3]].strStart);

    fprintf (poem, "%s\n", Index[rifm1[4]].strStart);
    fprintf (poem, "%s\n", Index[rifm1[5]].strStart);
    fprintf (poem, "%s\n", Index[rifm2[5]].strStart);
    fprintf (poem, "%s\n", Index[rifm2[4]].strStart);

    fprintf (poem, "%s\n", Index[rifm1[6]].strStart);
    fprintf (poem, "%s\n", Index[rifm2[6]].strStart);

    fprintf (poem, "Автор: void Poem_generator (string Index[], size_t indexsize)\n");

    fclose (poem);

    printf ("%s\n", Index[rifm1[0]].strStart);
    printf ("%s\n", Index[rifm1[1]].strStart);
    printf ("%s\n", Index[rifm2[0]].strStart);
    printf ("%s\n", Index[rifm2[1]].strStart);

    printf ("%s\n", Index[rifm1[2]].strStart);
    printf ("%s\n", Index[rifm2[2]].strStart);
    printf ("%s\n", Index[rifm1[3]].strStart);
    printf ("%s\n", Index[rifm2[3]].strStart);

    printf ("%s\n", Index[rifm1[4]].strStart);
    printf ("%s\n", Index[rifm1[5]].strStart);
    printf ("%s\n", Index[rifm2[5]].strStart);
    printf ("%s\n", Index[rifm2[4]].strStart);

    printf ("%s\n", Index[rifm1[6]].strStart);
    printf ("%s\n", Index[rifm2[6]].strStart);

    printf ("Автор: void Poem_generator (string Index[], size_t indexsize)\n");
}

















