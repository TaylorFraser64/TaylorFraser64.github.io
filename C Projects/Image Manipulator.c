

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME_SIZE 25
#define FILE_EXT ".bmp"
#define EXT_LENGTH 4
#define HEADER_SIZE 50
#define RAW_OFFSET_LOC 0x0A
#define RAW_SIZE_LOC 0x22
#define WIDTH_LOC 0x12
#define HEIGHT_LOC 0x16
#define COMPRESSION_LOC 0x1E
#define BIT_DEPTH 24
#define BITS_PER_BYTE 8
#define BYTE_ALIGNMENT 4
#define FALSE 0
#define TRUE 1
#define BLUE 0
#define GREEN 1
#define RED 2
#define FILTER 0
#define BW 1
#define NEGATIVE 2
#define OPERATION 0
#define COLOUR_FILTER 1

/* function prototypes */
int getUserOption( int );
int isValid( int );
void printMenu( int );
void addExtension( char[] );
int readFile( char[], char[], int**, int**, int**, int*, int* );
int writeFile( char[], char[], int*, int*, int*, int, int );
int readRawData( int*, int*, int*, int, int, FILE* );
int readHeader( char[], FILE* );
int isBMP( char[] );
int writeHeader( char[], FILE* );
int writeRawData( int*, int*, int*, int, int, FILE* );
void freeAll( int*, int*, int* );
void greyScale( int[], int[], int[], int );
void createNegative( int[], int[], int[], int );
void filterColour( int[], int[], int[], int, int );
int getMax( int, int, int );


/* image manipulation functions start here */

/* Function: filterColour
 * Purpose: Applies a red, green or blue filter to the image.
 * input: red - red component of image pixels (stored row by row)
 * input: green - green component of image pixels (stored row by row)
 * input: blue - blue component of image pixels (stored row by row)
 * input: imgSize - size of image in pixels
 * input: colour - one of RED, GREEN or BLUE to specify colour of filter
 * Returns: None
 */
void filterColour( int red[], int green[], int blue[], int imgSize, int colour )
{
	int index;
	for(index = 0; index < imgSize; index++){
		if (colour == 1){
			green[index] = 0;
			blue[index] = 0;
		}
		if (colour == 2){
			red[index] = 0;
			blue[index] = 0;
		}
		if (colour == 3){
			green[index] = 0;
			red[index] = 0;
		}

	}
}

/* Function: createNegative
 * Purpose: Creates a colour negative of the image.
 * input: red - red component of image pixels (stored row by row)
 * input: green - green component of image pixels (stored row by row)
 * input: blue - blue component of image pixels (stored row by row)
 * input: imgSize - size of image in pixels
 */
void createNegative( int red[], int green[], int blue[], int imgSize )
{
	int index;
	for(index = 0; index < imgSize; index++){
		green[index] = abs(255-green[index]);
		blue[index] = abs(255-blue[index]);
		red[index] = abs(255-red[index]);

	}
}

/* Function: greyScale
 * Converts image to grey scale
 * input: red - red component of image pixels (stored row by row)
 * input: green - green component of image pixels (stored row by row)
 * input: blue - blue component of image pixels (stored row by row)
 * input: imgSize - size of image in pixels
 * Returns: None
 */
void greyScale( int red[], int green[], int blue[], int imgSize )
{
	int index;
	int max;
	for(index = 0; index<imgSize; index++){
		max = getMax(red[index],green[index],blue[index]);
		red[index] = max;
		green[index] = max;
		blue[index] = max;
	}

}

/* Function: Get max
 * Purpose: Computes the maximum of the values passed as parameters
 * input: num1, num2, num3: values whose max we wish to compute
 * Returns: maximum of num1, num2, num3
 */
int getMax( int num1, int num2, int num3 )
{
	int max;
	if(num1>num2&&num1>num3){
		max = num1;
	}
	else{
		if(num2>num1&&num2>num3){
			max=num2;
		}
		else{
			max = num3;
		}
	}

	return max;
}

/* end of image manipulation functions */




int main( void )
{
    char header[ HEADER_SIZE ];
	char inFileName[ FILE_NAME_SIZE ];
    char outFileName[ FILE_NAME_SIZE ];
    int* red = NULL;
    int* green = NULL;
    int* blue = NULL;
    int userOption;
    int colour;
	int imgSize;
	int imgWidth;
	int imgHeight;

	printf( "Enter name of file to open:\n" );
	printf( "(no spaces and no more than %d chars including .bmp extension):\n",
		   FILE_NAME_SIZE - 1 );
	scanf( "%s", inFileName );
	
	inFileName[ FILE_NAME_SIZE - EXT_LENGTH - 1 ] = '\0';  /* in case user entered too many characters */
    
	if( readFile( inFileName, header, &red, &green, &blue, &imgWidth, &imgHeight ) )
    {
		imgSize = imgWidth * imgHeight;
		
        userOption = getUserOption( OPERATION );
        
		if( userOption == FILTER )
            colour = getUserOption( COLOUR_FILTER );

        if( userOption == BW )
            greyScale( red, green, blue, imgSize );
        else if( userOption == NEGATIVE )
            createNegative( red, green, blue, imgSize );
        else
            filterColour( red, green, blue, imgSize, colour );

        printf( "Enter name of file for modified image\n" );
        printf( "(no spaces and no more than %d chars - do not include .bmp extension):\n",
			   FILE_NAME_SIZE - EXT_LENGTH - 1 );
        scanf( "%s", outFileName );

        outFileName[ FILE_NAME_SIZE - EXT_LENGTH - 1 ] = '\0';  /* in case user entered too many characters */
        addExtension( outFileName );

        if( !writeFile( outFileName, header, red, green, blue, imgSize, imgWidth ) )
            printf( "Unable to save image to file %s\n", outFileName );
        else
            printf( "Modified image saved to file: %s\n", outFileName );
		
		freeAll( red, green, blue );
    }
    else
        printf( "Error opening or reading file!\n" );

    system( "PAUSE" );
    return 0;
}


/* Function: getUserOption
 * Purpose: Provides the user with a menu and returns user's choice, and
 * rejects selections that are not valid.
 * Param: whichOption - one of OPERATION (to choose which
 * an image transformation) or FILTER (to choose a filter colour)
 * Return: user's selection
 */
int getUserOption( int whichOption )
{
    int userOption;

    printMenu( whichOption );
    scanf( "%d", &userOption );

    while( ! isValid( userOption ) )
    {
        printf( "\nError: choice not valid!\n\n" );
        printMenu( whichOption );
        scanf( "%d", &userOption );
    }

    return userOption;
}


/* Function: isValid
 * Purpose: Checks validity of user's choice.   
 * input: userOption - option selected by user
 * Returns: true if userOption is a valid choice, false otherwise 
 */
int isValid( int userOption )
{
    return( userOption >= 0 && userOption <= 2 );
}


/* Function: printMenu
 * Purpose: Prints a menu of options for the user
 * input: whichMenu - currently one of OPERATION or COLOUR_FILTER
 * Returns: None
 */
void printMenu( int whichMenu )
{
    printf( "Please choose one of the following options: \n" );
   
    if( whichMenu == OPERATION )
    {
        printf( "    %d to apply a colour filter\n", FILTER );
        printf( "    %d to convert to black and white\n", BW );
        printf( "    %d to create colour negative\n", NEGATIVE );
    }
    else
    {
        printf( "    %d to apply a blue filter\n", BLUE );
        printf( "    %d to apply a green filtere\n", GREEN );
        printf( "    %d to apply a red filter\n", RED );
    }
}


/* Function: Add extension
 * Purpose: Adds .bmp extension to file name 
 * input: fileName - name of file
 * Returns: None
 */
void addExtension( char fileName[] )
{
    int index = 0;
    char extension[] = FILE_EXT;
    int extIndex = 0;

    while( index < FILE_NAME_SIZE && fileName[ index ] != '\0' )
        index++;

    while( extIndex < EXT_LENGTH )
    {
        fileName[ index++ ] = extension[ extIndex++ ];
    }

    fileName[ index ] = '\0';
}


/* Function: ReadFile 
 * Purose: Reads header information and red/green/blue components of each pixel in image
 * input: header - will contain file header information at end of function call
 * input: red - address of array that will contain red component of image pixels at end of function call
 * input: green - address of array that will contain green component of image pixels at end of function call
 * input: blue - address of array that will contain blue component of image pixels at end of function call
 * input: imgWidth - address of int that will store width of image in pixels
 * input: imgHeight - address of int that will store height of image in pixels
 * Returns: TRUE if uncompressed bmp image of size WIDTH by HEIGHT is read from file, FALSE otherwise
 */
int readFile( char inFileName[], char header[], 
			 int** red, int** green, int** blue, int* imgWidth, int* imgHeight )
{
    FILE* inFile;
    int bytesRead;
    int rawOffset;
    int compression;
	int imgSize;

    inFile = fopen( inFileName, "rb" );
    if( inFile != NULL )
    {
        bytesRead = readHeader( header, inFile );
        //printf( "%d bytes read to header\n", bytesRead );

        /* check magic number corresponds to BMP file */
        if( !isBMP( header ) )
            return FALSE;

        rawOffset = *( ( int* ) ( header + RAW_OFFSET_LOC ) );
        *imgWidth =  abs( *( ( int* ) ( header + WIDTH_LOC ) ) );
        *imgHeight = abs( *( ( int* ) ( header + HEIGHT_LOC ) ) );
        compression = *( ( int* ) ( header + COMPRESSION_LOC ) );

        if( compression != 0 )
            return FALSE;

		imgSize = *imgWidth * *imgHeight;
		
		// allocate memory for red/green/blue data
		
		*red = (int *) malloc( imgSize * sizeof( int ) );
		*green = (int *) malloc( imgSize * sizeof( int ) );
		*blue = (int *) malloc( imgSize * sizeof( int ) );
        
        fseek( inFile, rawOffset, SEEK_SET );
        bytesRead = readRawData( *red, *green, *blue, imgSize, *imgWidth, inFile );
        //printf( "%d bytes of raw data read from file.\n", bytesRead );

        fclose( inFile );
        return TRUE;
    }
    else 
        return FALSE;
}

/* Function: Read Header
 * Purpose: Reads header information from file
 * input: header - will contain file header information at end of function call
 * input: inFile - pointer to file containing image (assumed to be open for reading in binary mode)
 * Returns: number of bytes read
 */
int readHeader( char header[], FILE* inFile )
{
    return fread( header, sizeof( char ), HEADER_SIZE, inFile );
}

/*Function: isBMP
 * Purpose: Determines if file has bitmap format by checking magic number in first two bytes
 * - must be 'BM' in first two bytes
 * input: file header information
 * Returns: TRUE if bmp file, FALSE otherwise
 */
int isBMP( char header[] )
{
    return( header[0] == 0x42 && header[1] == 0x4D );        
}

/* Function: readRawData
 * Purpose: Reads raw image data into red/green/blue arrays
 * input: red - array that will contain red component of image pixels (stored row by row) at end of function call
 * input: green - array that will contain green component of image pixels (stored row by row) at end of function call
 * input: blue - array that will contain blue component of image pixels (stored row by row) at end of function call
 * input: imgSize - size of image in pixels
 * input: imgWidth - width of image in pixels
 * input: inFile - pointer to file containing image (assumed to be open for reading in binary mode)
 * Returns: number of bytes read from file
 */

int readRawData( int* red, int* green, int* blue, int imgSize, int imgWidth, FILE* inFile )
{
    int index;
    int bytesRead = 0;
    int padSize;
    unsigned char buffer[ BIT_DEPTH / BITS_PER_BYTE ];
	
    for( index = 0; index < imgSize; index++ )
    {
        bytesRead += fread( buffer, sizeof( char ), BIT_DEPTH / BITS_PER_BYTE, inFile );
        blue[ index ] = (unsigned) buffer[ BLUE ];
        green[ index ] = (unsigned) buffer[ GREEN ];
        red[ index ] = (unsigned) buffer[ RED ];

        /* check for end of row */
        if( index % imgWidth == imgWidth - 1 )
        {
            padSize = ( imgWidth * BIT_DEPTH / BITS_PER_BYTE ) % BYTE_ALIGNMENT;
            bytesRead += fread( buffer, sizeof( char ), padSize, inFile );
        }
    }

    return bytesRead;
}

/* Function: writeFile
 * Purpose: Writes image data to file.
 * input: fileName - name of file to which image is to be written
 * input: header - image header information
 * input: red - array that contains red component of image pixels (stored row by row)
 * input: green - array that contains green component of image pixels (stored row by row)
 * input: blue - array that contains blue component of image pixels (stored row by row)
 * input: imgSize - size of image in pixels
 * input: imgWidth - width of image in pixels
 * Returns: TRUE if image was written to file, FALSE otherwise
 */
int writeFile( char fileName[], char header[], int* red, int* green, int* blue, int imgSize, int imgWidth )
{
    FILE* outFile;
    int bytesWritten;
    int rawOffset;

    outFile = fopen( fileName, "wb" );
    if( outFile != NULL )
    {
        bytesWritten = writeHeader( header, outFile );
        //printf( "%d bytes written to header\n", bytesWritten );

        rawOffset = *( ( int* ) ( header + RAW_OFFSET_LOC ) );
        fseek( outFile, rawOffset, SEEK_SET );
        
        bytesWritten = writeRawData( red, green, blue, imgSize, imgWidth, outFile );
        //printf( "%d bytes of raw data written to file.\n", bytesWritten );
        fclose( outFile );
        return TRUE;
    }
    else
        return FALSE;
}

/* Function: writeHeader
 * Purpose: Writes image header information to file 
 * input: header - image header information
 * input: outFile - pointer to file to which image is to be written (assumed to be open for writing in binary mode)
 * Returns: number of bytes written to file
 */
int writeHeader( char header[], FILE* outFile )
{
    return fwrite( header, sizeof( char ), HEADER_SIZE, outFile );
}

/* Function: writeRawData
 * Purpose: Writes raw image data to file
 * input: red - array that contains red component of image pixels (stored row by row)
 * input: green - array that contains green component of image pixels (stored row by row)
 * input: blue - array that contains blue component of image pixels (stored row by row)
 * input: imgSize - size of image in pixels
 * input: imgWidth - width of image in pixels
 * input: outFile - pointer to file to which image is to be written (assumed to be open for writing in binary mode)
 * Returns: number of bytes written to file
 */
int writeRawData( int* red, int* green, int* blue, int imgSize, int imgWidth, FILE* outFile )
{
    int index;
    int bytesWritten = 0;
    int padSize;
    unsigned char buffer[ BIT_DEPTH / BITS_PER_BYTE ];

    for( index = 0; index < imgSize; index++ )
    {
        buffer[ BLUE ] = (unsigned char) blue[ index ];
        buffer[ GREEN ] = (unsigned char) green[ index ];
        buffer[ RED ] = (unsigned char) red[ index ];

        bytesWritten += fwrite( buffer, sizeof( char ), BIT_DEPTH / BITS_PER_BYTE, outFile );

        /* check for end of row */
        if( index % imgWidth == imgWidth - 1 )
        {
            padSize = ( imgWidth * BIT_DEPTH / BITS_PER_BYTE ) % BYTE_ALIGNMENT;
            bytesWritten += fwrite( buffer, sizeof( char ), padSize, outFile );
        }
    }

    return bytesWritten;
}

/* Function: freeAll
 * Purpose: Free up memory allocated to red/green/blue arrays.
 * input: red - red component of image pixels
 * input: green - green component of image pixels
 * input: blue - blue component of image pixels
 */
void freeAll( int* red, int* green, int* blue )
{
	free( red );
	free( green );
	free( blue );
}
