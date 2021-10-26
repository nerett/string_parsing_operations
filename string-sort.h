#ifndef STRING_SORT_H_INCLUDED
#define STRING_SORT_H_INCLUDED

#include "string-operations.h"

int cmp_strings( const void* string_1_ptr, const void* string_2_ptr ); ///< Returns -1 if the second string is greater than first, 0 if they're equal and 1 if first string is greater
int cmp_strings_back( const void* string_1_ptr, const void* string_2_ptr ); ///< This function is like cmp_strings, but compares strings from their end (soon it'll be overwritten and merged with cmp_strings)

int sort_strings( struct text* some_text, bool enable_reverse ); ///< Choses string sorting algorithm and sorting mode (reverse or not)
int change_strings( struct text* some_text, int first_string, int second_string ); ///< Swaps pointers to two input strings

static int qsort_strings( struct text* some_text, int start, int finish ); ///< Custom qsort algorithm for strings (that doesn't work yet)
static int bubblesort_strings( struct text* some_text ); ///< Sorts the strings given with bubblesort algorithm
static int bubblesort_strings_back( struct text* some_text ); ///< This function is like bubblesort_strings, but it uses cmp_strings_back (soon it'll be overwritten and merged with bubblesort_strings)

int find_first_letter( char* some_string, bool find_from_end ); ///< Returns the number of the first letter in the string
bool is_letter( char symbol ); ///< Returns true if this symbol is letter, false if it isn't


#endif // STRING_SORT_H_INCLUDED
