#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "../../include/str_utils.h"


size_t length(string str) {
    assert(str != NULL);

    size_t i = 0;
    while (str[i++] != STR_NULL);
    return i-1;
}


bool no_spaces(string str) {
    assert(str != NULL);

    while (*str != STR_NULL) {
        if (isspace(*str++))
            return false;
    }

    return true;
}


// TODO check if slice_until() can use this function
size_t skip_until(char limit, char *str) {
    assert(str != NULL);

    char *tmp = str;

    size_t i = 0;
    while ((*str != limit) && (*str != STR_NULL)) {
        str++;
        i++;
    }

    while (*str++ != STR_NULL) {
        *tmp++ = *str;
    }
    *tmp = STR_NULL;

    return i;
}


void slice_until(char limit, char *str, char *slice) {
    assert(str != NULL);
    assert(slice != NULL);

    char *tmp = str;

    // assign chars to slice up to limit
    while ((*str != limit) && (*str != STR_NULL)) {
        *slice++ = *str++;
    }
    *slice = STR_NULL;

    // assign chars to str past limit
    while (*str++ != STR_NULL) {
        *tmp++ = *str;
    }
    *tmp = STR_NULL;
}


size_t split(const char limit, string buffer, char **split) {
    assert(buffer != NULL);
    assert(split != NULL);

    size_t i = 0;
    char *dup = strdup(buffer);
    char *str = strtok(dup, &limit);

    if (str == NULL) {
        split[i] = STR_NULL;
    }

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
    *tmp = STR_NULL;
}
// isspace(int) needs cast to expected range for char!
// https://stackoverflow.com/questions/28654792/what-do-i-need-to-do-so-the-function-isspace-work-in-c

