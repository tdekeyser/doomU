#ifndef DOOMU_HTTP_H
#define DOOMU_HTTP_H

#include "utils.h"
#include <stdlib.h>
#include <string.h>


typedef struct write_buffer {
    char *memory;
    size_t size;
} Buffer;

typedef struct response {
    Buffer *header;
    Buffer *body;
} DoomUResponse;

/**
 * Create and destroy response object. Header and body contain
 * a memory buffer to which a response can be written.
 */
DoomUResponse newDoomUResponse(Buffer *header, Buffer *body);
void destroyDoomUResponse(DoomUResponse *response);

/**
 * Get request for the given url. The response is written to the
 * provided response object.
*/
void get(string url, DoomUResponse *response);

void post(string url, string params, DoomUResponse *response);


#endif /* DOOMU_HTTP_H */