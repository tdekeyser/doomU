#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>


#define STR_NULL '\0'
#define PAREN_OPEN '('
#define PAREN_CLOSED ')'
#define COMMA ','
#define COLON ':'



typedef const char * string;


size_t length(string);

size_t slice_until(char limit, char *str, char *slice);

size_t split(char limit, string buffer, char **split);

void strip(char *);


#endif /* UTILS_H */