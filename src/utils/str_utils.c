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


size_t slice_until(char limit, char *str, char *slice) {
    assert(str != NULL);
    assert(slice != NULL);

    size_t i = 0;
    while ((str[i] != limit) && (str[i] != STR_NULL)) {
        slice[i] = str[i];
        i++;
    }
    slice[i] = STR_NULL;
    return i;
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
// Alternative for split() which doesn't use strtok()
// size_t split(const char limit, string buffer, char **split) {
//    size_t n_sliced, i = 0;
//    char * buffer_copy = strdup(buffer);
//    char slice[64];
//    while ((n_sliced = slice_until(limit, buffer_copy, slice)) > 0) {
//        split[i++] = strdup(slice);
//        buffer_copy += n_sliced + 1;
//    }
//    return i;
// }


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
