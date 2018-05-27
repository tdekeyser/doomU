#ifndef DOOMU_STR_UTILS_H
#define DOOMU_STR_UTILS_H

#include <stdio.h>
#include <stdbool.h>


#define STR_NULL '\0'
#define PAREN_OPEN '('
#define PAREN_CLOSED ')'
#define COMMA ','
#define COLON ':'
#define QUOTE '\"'
#define SQUARE_BRACKET_OPEN '['
#define SQUARE_BRACKET_CLOSED ']'



size_t length(char const *);

bool contains(char const *, char);

bool no_spaces(char const *);

void skip_until(char limit, char *str);

void slice_until(char limit, char *str, char *slice);

size_t split(char limit, char const *buffer, char **split);

void strip(char *);

void strip_leave_quotes(char *);

long parse_long(char const *);


#endif /* DOOMU_STR_UTILS_H */