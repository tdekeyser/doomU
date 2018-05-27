#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "../../include/str_utils.h"
#include "../../include/config.h"


size_t length(char const *str) {
    assert(str != NULL);

    size_t i = 0;
    while (str[i++] != STR_NULL);
    return i - 1;
}


bool contains(char const *str, char c) {
    while (*str++ != STR_NULL) {
        if (*str == c)
            return true;
    }
    return false;
}


bool no_spaces(char const *str) {
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


size_t split(char limit, char const *buffer, char **split) {
    assert(buffer != NULL);
    assert(split != NULL);

    size_t i = 0;
    char *dup = strdup(buffer);
    MEM_ERROR(dup);
    char *str = strtok(dup, &limit);

    split[i] = NULL;
    while (str != NULL) {
        split[i++] = strdup(str);
        MEM_ERROR(split[i-1]);
        str = strtok(NULL, &limit);
    }

    free(dup);
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
    long l = strtol(str, NULL, 0);
    ERROR_HANDLER(errno != 0, "Could not parse to long: %s", str);
    return l;
}

