/**
 *	 This module provides facilities to file manipulation 
 */
 
 
#ifndef _ANALYSERPXFILE_H_
#define _ANALYSERPXFILE_H_

#include "analyserpxTypes.h"

/**
  * Save string to a log file
  *
  * @param *fileName		log file name
  * @param *str		string to be saved into log file
  * @param *errbuff		string buffer used to report error. Pass NULL to ignore it
  */
void writeStringToLogFile (const char *fileName, const char *str, char *errbuff);

/**
  * Open a file
  *
  * @param *fileName		file name
  * @param *mode		open mode, e.g., a+, r, w...
  * @param *errbuff		string buffer used to report error. Pass NULL to ignore it
  * @param *logFile  		log file name, to report errors. Use NULL to ignore. Valid only if errbuff is not NULL
  */
FILE *openFile (const char *fileName, const char *mode, char *errbuff, char *logFile);

/**
  * Close a file
  *
  * @param *p 			FILE pointer to be closed
  */
void closeFile(FILE *p);

/**
  * Verifies the existence of a file
  *
  * @param *fileName 		file's name
  * @return 			A non zero number is return if the file exist.
  */
int existFile(char *fileName);

#endif
