#ifndef STRING_OPERATIONS_H_INCLUDED
#define STRING_OPERATIONS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <algorithm>
#include <ctype.h>
//#include "string-utils/string-utils.h"
//!TODO перевести программу на самописные функции (библиотека string-utils)

// FOPEN_ERR
enum err_code { OK, FOPEN_ERR, FSEEK_ERR, FTELL_ERR, FREAD_ERR, CALLOC_ERR }; ///< Enum of error codes, returned by functions below
//enum sort_algo { QSORT_DEFAULT, QSORT_CUSTOM, BUBBLESORT };

//const int MAX_STRING_LENGTH = 100;
const char NOT_A_LETTER[] = ".,-!?\"( )':;"; ///< String of non-letter symbols
const int MIN_ARGUMENTS_NUMBER = 2; ///< Minimal number of command line arguments to start arguments parsing

struct text ///< Structture which is text you can easilly work with
{
    char** index_string = NULL; ///< Array pf pointers that point at the strings beginnings // struct string { char * data, int size}
    char* text_line = NULL; ///< Line holding all text // buffer
    int N_symbols = 0; ///< Number of symbols in the text
    int N_strings = 0; ///< Number of strings in the text
};

err_code input_text( struct text* some_text, char* filename = "input_text.txt" ); ///< Reads text from input_text.txt (by default; if you want you can choose a different filename using command line argument <FILENAME>), determines it's size, allocates memory, puts text into text_line and puts pointers from index_stringto the beginnings of lines (with a help of find_strings_beginnings). Returns error code
err_code text_file_output( struct text* some_text, bool enable_loseless_adding ); ///< Puts strings given into the output_text.txt
err_code text_file_add_delimiter(); ///< Ads awesome text label into the output_text.txt. Returns error code
err_code text_file_file_plain_output( struct text* some_text, bool enable_loseless_adding ); ///< Puts the contents of the text_line into the output_text.txt (usually text_line contains non-modified text red from file). Returns error code
int text_console_output( struct text* some_text ); ///< Displays strings into the console

static int count_strings( struct text* some_text ); ///< Counts number of strings in the text and result into N_strings
static int find_string_beginning( struct text* some_text ); ///< Puts pointers from index_stringto the beginnings of lines


void TryToExecute( err_code func_return_code, text* operand_to_free_mem ); ///< Frees memory and aborts program in case it returns non-OK error code
int free_memory( struct text* some_text ); ///< Frees all heap memory occupied by text

#endif // STRING-OPERATIONS_H_INCLUDED
