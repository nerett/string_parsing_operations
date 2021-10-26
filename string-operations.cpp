#include "string-operations.h"


err_code input_text( struct text* some_text, char* filename ) // text *some_text
{
    int error_int = 0;  // ret  / retval / res
    if( filename == NULL )
    {
        filename = "input_text.txt";
    }

    FILE* input_file = fopen( filename, "r" ); // argc argv
    if( input_file == NULL ) // I LIKE IT BETTER (пробел перед if, но нет пробелов в скобках)
    {
        return FOPEN_ERR;
    }

    error_int = fseek( input_file, 0L, SEEK_END ); //определение размера файла
    if( error_int != 0 )
    {
        return FSEEK_ERR;
    }

    some_text->N_symbols = ftell( input_file );
    if( some_text->N_symbols < 0 )
    {
        return FTELL_ERR;
    }

    error_int = fseek( input_file, 0L, SEEK_SET );
    if( error_int != 0 )
    {
        return FSEEK_ERR;
    }

                                                                                        //!TODO read func
    some_text->text_line = ( char* ) calloc( some_text->N_symbols, sizeof( char ) ); //выделение памяти и чтение из файла
    error_int = fread( some_text->text_line, sizeof( char ), some_text->N_symbols, input_file );
    if( error_int != some_text->N_symbols )
    {
        return FREAD_ERR;
    }

    count_strings( some_text );

    some_text->index_string = ( char** ) calloc( some_text->N_strings, sizeof( char* ) ); //выделение памяти под массив указателей на начало строк
    if( some_text->index_string == NULL )
    {
        return CALLOC_ERR;
    }

    find_string_beginning( some_text );

    fclose( input_file );

    return OK;
}



int text_console_output( struct text* some_text )
{
    assert( some_text != NULL );
    assert( some_text->text_line != NULL );
    assert( some_text->index_string != NULL );
    assert( some_text->N_strings > 0 );
    assert( some_text->N_symbols > 0 );


    for( int i = 0; i < some_text->N_strings; i++ )
    {
        printf( "%s", some_text->index_string[i] );
    }

    return 0;
}



err_code text_file_output( struct text* some_text, bool enable_loseless_adding )
{
    assert( some_text != NULL );
    assert( some_text->text_line != NULL );
    assert( some_text->index_string != NULL );
    assert( some_text->N_strings > 0 );
    assert( some_text->N_symbols > 0 );


    FILE* output_file;
    if( enable_loseless_adding )
    {
        output_file = fopen( "output_text.txt", "a" );
    }
    else
    {
        output_file = fopen( "output_text.txt", "w" );
    }
    if( output_file == NULL )
    {
        return FOPEN_ERR;
    }

    for( int i = 0; i < some_text->N_strings; i++ )
    {
        fputs( some_text->index_string[i], output_file );
        fputs( "\n", output_file );
    }

    fclose( output_file );
    return OK;
}



int free_memory( struct text* some_text )
{
    assert( some_text != NULL );
    assert( some_text->text_line != NULL );
    assert( some_text->index_string != NULL );

    free( some_text->index_string );
    free( some_text->text_line );

    return 0;
}



int count_strings( struct text* some_text )
{
    assert( some_text != NULL );
    assert( some_text->text_line != NULL );
    assert( some_text->N_symbols > 0 );


    for( int i = 0; i < some_text->N_symbols; i++ ) // strchr
    {
        if( some_text->text_line[i] == '\n' ) //а если '\0' ну или выделять памяти на одну строку больше
        {
            some_text->N_strings++;
            some_text->text_line[i] = '\0';
        }
    }

    return some_text->N_strings;
}



int find_string_beginning( struct text* some_text ) // init_strings
{
    assert( some_text != NULL );
    assert( some_text->text_line != NULL );
    assert( some_text->index_string != NULL );
    assert( some_text->N_strings > 0 );
    assert( some_text->N_symbols > 0 );


    char last_read = '\n';
    int j = 0;

    for( int i = 0; i < some_text->N_symbols; i++ ) //начинать с нуля
    {
        if( last_read == '\n' || last_read == '\0' )
        {
            some_text->index_string[j] = some_text->text_line + i;
            j++;
        }
        last_read = some_text->text_line[i];
    }

    return 0;
}



err_code text_file_add_delimiter()
{
    FILE* output_file = fopen( "output_text.txt", "a" );
    if( output_file == NULL )
    {
        return FOPEN_ERR;
    }

    fputs( "\n", output_file );
    fputs( "================================", output_file );
    fputs( "СЛЕДУЮЩАЯ ЧАСТЬ ЗАДАНИЯ", output_file );
    fputs( "================================", output_file );
    fputs( "\n", output_file );

    fclose( output_file );

    return OK;
}



err_code text_file_file_plain_output( struct text* some_text, bool enable_loseless_adding )
{
    FILE* output_file;
    if( enable_loseless_adding )
    {
        output_file = fopen( "output_text.txt", "a" );
        if( output_file == NULL )
        {
            return FOPEN_ERR;
        }
    }
    else
    {
        output_file = fopen( "output_text.txt", "w" );
        if( output_file == NULL )
        {
            return FOPEN_ERR;
        }
    }


    for( int i = 0; i < some_text->N_symbols; i++ )
    {
        if( some_text->text_line[i] == '\0' )
        {
            fputs( "\n", output_file);
            continue;
        }
        fputc( some_text->text_line[i], output_file );
    }

    fclose( output_file );

    return OK;
}



void TryToExecute( err_code func_return_code, text* operand_to_free_mem )
{
    if( func_return_code != OK )
    {
        printf( "ERROR %d\n", func_return_code );
        printf( "You can find more information about error codes in enum err_code documentation.\n\n" );
        free_memory( operand_to_free_mem );

        abort();
    }
}



