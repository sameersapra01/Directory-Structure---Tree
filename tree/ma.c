
#include"header.h"
#include"constants.h"
#include"prototypes.h"

#pragma warning(disable:4996)

/*
FUNCTION NAME	: void find_files_in_directory( HANDLE d , WIN32_FIND_DATA file_data , char path[] , int tab , char argv[] )

PARAMETERS		: HANDLE d					 :  
				  WIN32_FIND_DATA file_data  : Stores the file attributes of the directory.
				  char path[]				 : Stores the current working directory.
				  int tab					 : Used to indent the structure of the directory.
				  char argv[]				 : Stores the command argument.

DESCRIPTION		: The function is used to print the tree format of the directory passed as char path[] in parameters.
RETURN			: Return nothing.
*/

void find_files_in_directory( HANDLE d , WIN32_FIND_DATA file_data , char path[] , int tab , char argv[] , FILE *ofp )
{
	//Initializing variables.
	int check_directory = 0 ;
	int loop1 = 0 ;
	int loop2 = 0 ;

	char temp_path[200] = "" ;
	char prev_path[200] = "" ;
	
	strcpy( prev_path , path ) ;

	do
	{	
		//Check whether the file_data.cfilename is DIRECTORY or FILE.
		if( ( file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) != kZERO )
		{
				
			//For "." and ".." directories skip the processing.
			if( ( strcmp( file_data.cFileName , ".") == kZERO ) || strcmp( file_data.cFileName , "..") == kZERO )
			{
				continue ;
			}
			else
			{
				int length = 0 ;
				char temp_path_new[ 200 ] = "";
				
				check_directory = 1 ;
				
				for( loop1 = kZERO ; loop1 < tab ; loop1++ )
				{
					fprintf(ofp ,"\t") ;
				}
				
				fprintf( ofp , "%s\n" , file_data.cFileName ) ;
				
				length = strlen( path ) ;
				
				strncpy( temp_path_new , path , length - kONE ) ;
				strcat( temp_path_new , file_data.cFileName ) ;

				length = strlen( temp_path_new ) ;
				
				strcat( temp_path_new + length , "\\\*" ) ;
				strcpy( temp_path, temp_path_new );
				
				if( strcmp ( prev_path , temp_path ) != kZERO )
				{
					tab++ ;
				}
			}

			if( check_directory == kONE )
			{
				WIN32_FIND_DATA		file_d = { 0 } ;
				HANDLE				e      = FindFirstFile( temp_path , &file_d ) ;
				
				if( e != INVALID_HANDLE_VALUE )
				{
					find_files_in_directory( e , file_d , temp_path , tab , argv , ofp  ) ;
					if( strcmp ( prev_path , argv ) == kZERO ) 
					{
						tab = 1 ;
					}
					else
					{
						tab = 2 ;
					}
				}
				
			}
		}
		else
		{
			if( tab == kONE )
			{
				fprintf( ofp , "\t%s\n" , file_data.cFileName ) ;
			}
			else
			{
				for( loop2 = kZERO ; loop2 < tab ; loop2++ )
				{
					fprintf( ofp , "\t" ) ;
				}
				fprintf( ofp , "--%s\n" , file_data.cFileName ) ;
			}
		}
	}while( FindNextFile( d , &file_data ) ) ;
}
