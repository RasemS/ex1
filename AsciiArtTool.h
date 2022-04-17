
#ifndef ASCIIARTTOOL_H
#define ASCIIARTTOOL_H

#include <stdio.h>
#include <stdbool.h>

/*  
*   asciiArtRead: compresses a file using the RLE method
* @param in_stream - file containing the image to be compressed 
* @return 
*   A RLEList containing every character in the image    
*/
RLEList asciiArtRead(FILE* in_stream);


/*  
*   asciiArtPrint: prints an image that's displayed as an RLEList into a file
* @param list - the image displayed as a RLEList 
* @param out_stream - the file to print the image into
* @return 
*   RLE_LIST_SUCCESS if the printing was successful
*   RLE_LIST_ERROR otherwise    
*/
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);


/*  
*   asciiArtPrintEncoded: prints a compressed image into a file
* @param list - the image displayed as a RLEList 
* @param out_stream - the file to print the compressed image into
* @return 
*   RLE_LIST_SUCCESS if the printing was successful
*   RLE_LIST_ERROR otherwise  
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);




#endif