#include "string-sort.h"

//#define BUBBLESORT
//#define USER_QSORT
#define DEFAULT_QSORT

int cmp_strings( const void* string_1_ptr, const void* string_2_ptr )
{
    assert( string_1_ptr != NULL );
    assert( string_2_ptr != NULL );


    char* first_string = *( char** )string_1_ptr;
    char* second_string = *( char** )string_2_ptr;

/*
    int result = strcmp( first_string, second_string ); // это быстрее за счёт strcmp!

    if( result > 0 )
    {
        return 1;
    }
    else if( result < 0 )
    {
        return -1;
    }
*/

    int first_startfrom = 0, second_startfrom = 0;
    int i;

    first_startfrom = find_first_letter( first_string, false );
    second_startfrom = find_first_letter( second_string, false );

    i = 0;
    while( first_string[i] != '\n' || second_string[i] != '\0' ) //собственно сравниваем // \0
    {
        if( first_string[first_startfrom + i] < second_string[second_startfrom + i] )
        {
            return -1;
        }
        else if( first_string[first_startfrom + i] > second_string[second_startfrom + i] )
        {
            return 1;
        }
        i++;
    }

    return 0;
}



int cmp_strings_back( const void* string_1_ptr, const void* string_2_ptr )
{
    assert( string_1_ptr != NULL );
    assert( string_2_ptr != NULL );


    char* first_string = *( char** )string_1_ptr;
    char* second_string = *( char** )string_2_ptr;
/*
if(  find_first_letter( first_string, true ) != 0 )
{
    printf( "%d ", find_first_letter( first_string, true ) );
}
*/
    int i1 = strlen( first_string ) + find_first_letter( first_string, true );
    int i2 = strlen( second_string ) + find_first_letter( second_string, true );
    while( first_string[i1] != '\n' || second_string[i2] != '\n' || first_string[i1] != '\0' || second_string[i2] != '\0' ) //собственно сравниваем
    {
        if( first_string[i1] < second_string[i2] )
        {
            return -1;
        }
        else if( first_string[i1] > second_string[i2] )
        {
            return 1;
        }
        i1--;
        i2--;
    }
    return 0;
}



int change_strings( struct text* some_text, int first_string, int second_string )
{
    assert( some_text != NULL );
    assert( some_text->text_line != NULL );
    assert( some_text->index_string != NULL );
    assert( some_text->N_strings > 0 );
    assert( some_text->N_symbols > 0 );


    char* temporary = some_text->index_string[first_string];
    some_text->index_string[first_string] = some_text->index_string[second_string];
    some_text->index_string[second_string] = temporary;

    return 0;
}



int sort_strings( struct text* some_text, bool enable_reverse )
{
    assert( some_text != NULL );
    assert( some_text->text_line != NULL );
    assert( some_text->index_string != NULL );
    assert( some_text->N_strings > 0 );
    assert( some_text->N_symbols > 0 );

    #ifdef DEFAULT_QSORT

        if( enable_reverse )
        {
            qsort( some_text->index_string, some_text->N_strings, sizeof( char* ), cmp_strings_back );
        }
        else
        {
            qsort( some_text->index_string, some_text->N_strings, sizeof( some_text->text_line ), cmp_strings );
        }

    #endif
    #ifdef USER_QSORT

        if( enable_reverse )
        {

        }
        else
        {

        }

    #endif
    #ifdef BUBBLESORT

        if( enable_reverse )
        {
            bubblesort_strings_back( some_text );
        }
        else
        {
            bubblesort_strings( some_text );
        }

    #endif
    return 0;
}



int qsort_strings( struct text* some_text, const int start, const int finish ) //DOESN'T WORK!!
{
    //char** base_element = some_text->index_string + start + ( finish / 2 );
    //char** left_element = some_text->index_string + start;
    //char** right_element = some_text->index_string + start + finish;

    int base_element = start + ( finish / 2 );
    int left_element = start;
    int right_element = finish;

    while( left_element >= right_element )
    {
        for( int i = 0; i < ( ( finish - start ) / 2 ); i++ )
        {
            if( cmp_strings( &*some_text->index_string[left_element], &*some_text->index_string[base_element] ) > 0 ) //работа со значениями по адресу
            {
                break;
            }
            left_element++; //работа с адресами как с числами
        }

        for( int i = 0; i < ( ( finish - start ) / 2 ); i++ )
        {
            if( cmp_strings( &*some_text->index_string[right_element], &*some_text->index_string[base_element] ) <= 0 ) //работа со значениями по адресу
            {
                break;
            }
            right_element--; //работа с адресами как с числами
        }


        change_strings( some_text, left_element, right_element );
    }

    if( base_element > start ) //работа с адресами как с числами
    {
        qsort_strings( some_text, start, base_element ); //работа с адресами как с числами
    }
    if( base_element < finish ) //работа с адресами как с числами
    {
        qsort_strings( some_text, base_element, finish ); //работа с адресами как с числами
    }


    return 0;
}



int bubblesort_strings( struct text* some_text )
{
    assert( some_text != NULL );
    assert( some_text->text_line != NULL );
    assert( some_text->index_string != NULL );
    assert( some_text->N_strings > 0 );
    assert( some_text->N_symbols > 0 );


    int sort_step = 1; //изначально единица отнималась от длины сама, это просто оптимизация, так надо
    for( int sort_iterations = 0; sort_iterations <= some_text->N_strings; sort_iterations++ ) //повторить некое число раз
    {
        for( int i = 0; i < some_text->N_strings - sort_step; i++ ) //пробежаться по массиву и сравнить строки
        {
            if( cmp_strings( some_text->index_string[i], some_text->index_string[i+1] ) > 0 )
            {
                change_strings( some_text, i, i + 1 );
            }
        }

        printf( "sort_iterations = %d/%d\n", sort_iterations, some_text->N_strings );
        sort_step++;
    }

    return 0;
}



int bubblesort_strings_back( struct text* some_text )
{
    assert( some_text != NULL );
    assert( some_text->text_line != NULL );
    assert( some_text->index_string != NULL );
    assert( some_text->N_strings > 0 );
    assert( some_text->N_symbols > 0 );


    int sort_step = 1; //изначально единица отнималась от длины сама, это просто оптимизация, так надо
    for( int sort_iterations = 0; sort_iterations <= some_text->N_strings; sort_iterations++ ) //повторить некое число раз
    {
        for( int i = 0; i < some_text->N_strings - sort_step; i++ ) //пробежаться по массиву и сравнить строки
        {
            if( cmp_strings_back( some_text->index_string[i], some_text->index_string[i+1] ) > 0 )
            {
                change_strings( some_text, i, i + 1 );
            }
        }

        printf( "sort_iterations = %d/%d\n", sort_iterations, some_text->N_strings );
        sort_step++;
    }

    return 0;
}



int find_first_letter( char* some_string, bool find_from_end )
{
    assert( some_string != NULL );


    int i = 0;
    int increment = 1;
    int first_letter = 0;

    if( find_from_end )
    {
        i = strlen( some_string );
        increment = -1;
//first_letter = -1; ///DEBUG
    }

    while( some_string[i] != '\0' ) //ищем первую букву первой строки
    {
        if( is_letter( some_string[i] ) )
        {
            //first_letter = i;
            break;
        }
        i += increment;
        first_letter += increment;
    }

    return first_letter;
}



bool is_letter( char symbol )
{
    int i = 0;
    while( NOT_A_LETTER[i] != '\0' )
    {
        if( symbol == NOT_A_LETTER[i] )
        {
            return false;
        }
        i++;
    }

    return true;
}



