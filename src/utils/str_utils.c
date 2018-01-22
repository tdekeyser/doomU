#include <string.h>
#include "../../include/str_utils.h"


size_t length(string buffer) {
    size_t i = 0;
    while (buffer[i++] != STR_NULL);
    return i-1;
}


size_t slice_until(char limit, string buffer, char *slice) {
    size_t i = 0;
    while ((buffer[i] != limit) && (buffer[i] != '\0')) {
        slice[i] = buffer[i];
        i++;
    }
    slice[i] = STR_NULL;
    return i;
}


size_t split(const char limit, string buffer, char **split) {
    size_t i = 0;

    char *str = strtok((char *) buffer, &limit);

    while (str != NULL) {
        split[i++] = str;
        str = strtok(NULL, &limit);
    }

    return i;
}



// Alternative for split() which doesn't use strtok()
//size_t split(const int limit, string buffer, char **split) {
//    size_t n_sliced, i = 0;
//    char * buffer_copy = strdup(buffer);
//    char slice[VAR_LEN];
//    while ((n_sliced = slice_until(limit, buffer_copy, slice)) > 0) {
//        split[i++] = strdup(slice);
//        buffer_copy += n_sliced + 1;
//    }
//    return i-1;
//}