#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "../../include/str_utils.h"


size_t length(string buffer) {
    assert(buffer != NULL);

    size_t i = 0;
    while (buffer[i++] != STR_NULL);
    return i-1;
}


void slice_until(char limit, char *str, char *slice) {
    assert(str != NULL);
    assert(slice != NULL);

    char *tmp = str;

    // assign chars to slice up until limit
    while ((*str != limit) && (*str != STR_NULL)) {
        *slice++ = *str++;
    }
    *slice = STR_NULL;

    // assign chars to str past limit
    while (*str++ != STR_NULL) {
        *tmp++ = *str;
    }
}


size_t split(const char limit, string buffer, char **split) {
    assert(buffer != NULL);
    assert(split != NULL);

    size_t i = 0;
    char *dup = strdup(buffer);
    char *str = strtok(dup, &limit);

    while (str != NULL) {
        split[i++] = str;
        str = strtok(NULL, &limit);
    }

    return i;
}


void strip(char *str) {
    assert(str != NULL);

    char *tmp = str;
    while (*str != STR_NULL) {
        while (isspace(*str))
            str++;

        *tmp++ = *str++;
    }
}
// isspace(int) needs cast to expected range for char!
// https://stackoverflow.com/questions/28654792/what-do-i-need-to-do-so-the-function-isspace-work-in-c

