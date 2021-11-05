#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define $meow printf("\nMeow from line: %d\nfrom function %s\n", __LINE__, __PRETTY_FUNCTION__);
#define PHYPM HUINYA
#define ass assert
#define SYMBOL_IS_USELESS *str == 'S' || *str == 'c' || *str == 'e' || *str == 'n' || *str == 'M' || *str == 'V' || *str == 'L' || *str == 'X' || *str == 'I' || *str == ' ' || *str == 'A' || *str == 'C'

typedef struct {
    char* strStart;
    char* strEnd;
} string;

enum {
    FROM_START,
    FROM_END
};

char* From_File_to_buffer (void);

string* Index_Make (char* ptrBuff, size_t* ptr_indexsize);

size_t Find_indexsize_and_str_make (char* ptrBuff);

void Str_bubble_Sort (string Index[], size_t indexsize, int mode);

void Output_to_File (string Index[], size_t indexsize, int mode);

char Small_equal_Big (char c);

int Is_malloc (const char* str);

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
    size_t indexsize = 0;
    char* ptrBuff = From_File_to_buffer ();
    ass (ptrBuff != NULL);
    int mode = FROM_END;

    string* Index = Index_Make (ptrBuff, &indexsize);
    ass (Index != NULL);

    Str_bubble_Sort (Index, indexsize, mode);

    Output_to_File (Index, indexsize, mode);

    free (ptrBuff);

    return 0;
}

char* From_File_to_buffer (void)
{
    FILE* buffer = fopen ("hamlet.txt", "r");
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

    printf ("%zd", *ptr_indexsize);

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
    while (Small_equal_Big (*str1) == Small_equal_Big (*str2) && *str1 != '\0' && *str2 != '\0')
    {
        str1++;
        str2++;
        str1 = Str_platinum_from_start (str1);
        str2 = Str_platinum_from_start (str2);
    }
    return Small_equal_Big (*str2) - Small_equal_Big (*str1);
}

int Str_Compare_from_end (const char* str1, const char* str2)
{
    ass (str1 != NULL);
    ass (str2 != NULL);

    str1 = Str_platinum_from_end (str1);
    str2 = Str_platinum_from_end (str2);
    while (Small_equal_Big (*str1) == Small_equal_Big (*str2) && *str1 != '\0' && *str2 != '\0')
    {
        str1--;
        str2--;
        str1 = Str_platinum_from_end (str1);
        str2 = Str_platinum_from_end (str2);
    }

    return Small_equal_Big (*str2) - Small_equal_Big (*str1);
}

char* Str_platinum_from_start (const char* str)
{
    ass (str != NULL);

    while ((*str > '\0' && *str < 'A') || (*str > 'Z' && *str < 'a') || *str > 'z')
    {
        str++;
    }

    ass (str != NULL);

    return (char*)str;
}

char* Str_platinum_from_end (const char* str)
{
    ass (str != NULL);

    while ((*str > '\0' && *str < 'A') || (*str > 'Z' && *str < 'a') || *str > 'z')
    {
        str--;
    }

    ass (str != NULL);

    return (char*)str;

}



char Small_equal_Big (char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return c - ('a' - 'A');
    }
    else
    {
        return c;
    }
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

void Output_to_File (string Index[], size_t indexsize, int mode)
{
    FILE* sort_buffer = fopen ("sort_hamlet.txt", "w");

    if (mode == FROM_START)
    {
        for (size_t i = 0; i < indexsize; i++)
        {
            fputs (Index[i].strStart, sort_buffer);
            fputc ('\n', sort_buffer);
        }
    }
    else if (mode == FROM_END)
    {

        size_t maxsize = Index[0].strEnd - Index[0].strStart + 1;
        for (size_t i = 1; i < indexsize; i++)
        {
            if (Index[i].strEnd - Index[i].strStart + 1 > maxsize)
            {
                maxsize = Index[i].strEnd - Index[i].strStart + 1;
            }
        }


        for (size_t i = 0; i < indexsize; i++)
        {
            fprintf (sort_buffer,"%*s\n", maxsize, Index[i].strStart);
        }
    }
    fclose (sort_buffer);
    free (Index);
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
        if (SYMBOL_IS_USELESS)
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





