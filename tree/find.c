/*
FILE		 : SETTree.c
PROJECT		 : SETTree
BY			 : SAMEER SAPRA
DATE		 : 27-03-2014
DESCRIPTION	 : This program prints the structure of the directory mentioned as a command argument; in a tree structure.
*/
#include"header.h"
#include"constants.h"
#include"prototypes.h"


#pragma warning(disable:4996)

int main( int argc , char *argv[] )
{
	//Initializing variables.
	int indent = 1 ;
	int length = 0 ;
	
	char dir[200] = "" ;

	FILE *ifp = NULL ;
	
	WIN32_FIND_DATA		filedata =  { 0 } ;
	HANDLE				h  =		FindFirstFile( argv[ kONE ] , &filedata ) ;
	
	//Checking if directoy exist or not.
	if( h != INVALID_HANDLE_VALUE )
	{
		ifp = fopen( "c:\\directory_list.txt" , "w" ) ;
		if( ifp == NULL )
		{
			printf("Cannot open file\n") ;
		}
		else
		{
		
			length = strlen( argv[ kONE ] ) ;
			length -= 2 ;

			strncpy( dir , argv[ kONE ] , length) ;
			fprintf( ifp , "\nIN %s\n\n" , dir ) ;
		
			//Calling the function to print the tree structure of the directory.
			find_files_in_directory( h , filedata , argv[kONE] , indent , argv[ kONE ] , ifp ) ;
		}
	}

	//If there is no directory.
	else
	{
		printf("ERROR : Directory Entered Does Not Exist..\n" ) ;
	}
	return 0 ;
}

