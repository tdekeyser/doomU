#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>


#define STR_NULL '\0'
#define PAREN_OPEN '('
#define PAREN_CLOSED ')'
#define COMMA ','
#define COLON ':'
#define QUOTE '\"'


typedef const char *string;


size_t length(string);

bool contains(string, char);

bool no_spaces(string);

void skip_until(char limit, char *str);

void slice_until(char limit, char *str, char *slice);

size_t split(char limit, string buffer, char **split);

void strip(char *);

void strip_leave_quotes(char *);


#endif /* UTILS_H */