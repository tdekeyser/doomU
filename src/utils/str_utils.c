#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "../../include/str_utils.h"


size_t length(string str) {
    assert(str != NULL);

    size_t i = 0;
    while (str[i++] != STR_NULL);
    return i - 1;
}


bool contains(string str, char c) {
    while (*str++ != STR_NULL) {
        if (*str == c)
            return true;
    }
    return false;
}


bool no_spaces(string str) {
    assert(str != NULL);

    while (*str != STR_NULL) {
        if (isspace(*str++))
            return false;
    }

    return true;
}


void skip_until(char limit, char *str) {
    assert(str != NULL);

    char tmp[64];
    slice_until(limit, str, tmp);
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

    split[i] = NULL;
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
        while (isspace(*str) && str++);

        *tmp++ = *str++;
    }
    *tmp = STR_NULL;
}


void strip_leave_quotes(char *str) {
    assert(str != NULL);

    bool in_quote = false;
    char *tmp = str;

    while (*str != STR_NULL) {
        if (*str == QUOTE)
            in_quote = in_quote ? false : true;

        if (isspace(*str) && !in_quote && str++)
            continue;

        *tmp++ = *str++;
    }

    *tmp = STR_NULL;
}


long parse_long(char const *str) {
    char *error;
    errno = 0;
    long l = strtoll(str, &error, 0);

    assert(*error == 0);
    assert(errno == 0);
    return l;
}

