/* Defenition of the two boolean types: true and false */
#ifndef BOOL_H
#define BOOL_H
typedef enum {FALSE /*= 0*/, TRUE /*= 1*/, ERROR = -1 } boolean;
/* The ERROR type is added to the regular boolean types for sending a calling function 
 the message that an unexpected error acurred while running the program - such as failed
 memory allocation */
#endif