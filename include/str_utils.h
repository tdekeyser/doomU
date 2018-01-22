#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>


#define STR_NULL '\0'
#define PAREN_OPEN '('
#define PAREN_CLOSED ')'
#define COMMA ','
#define COLON ':'



typedef const char * string;


size_t length(string buffer);

size_t slice_until(char limit, string buffer, char *slice);

size_t split(char limit, string buffer, char **split);



#endif /* UTILS_H */