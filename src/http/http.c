#include "../../include/http.h"
#include "curl/curl.h"

/**
 * Writes contents to buffer object
*/
size_t writeMemoryCallback(void *contents, size_t size, size_t nmemb, Buffer *buffer);
void copyTo(Buffer *buf, void *contents, size_t size);


void get(string url, DoomUResponse *response) {
    CURL *curl = curl_easy_init();
    CURLcode res;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEHEADER, response->header);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response->body);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("%lu bytes retrieved\n", response->body->size + response->header->size);
        }

        curl_easy_cleanup(curl);
    }
}

void copyTo(Buffer *buf, void *contents, size_t size) {
    memcpy(&(buf->memory[buf->size]), contents, size);
    buf->size += size;
}

size_t writeMemoryCallback(void *contents, size_t size, size_t nmemb, Buffer *buf) {
    size_t realsize = size * nmemb;

    buf->memory = (char*) realloc(buf->memory, buf->size + realsize + 1);
    if (buf->memory == NULL) {
        fprintf(stderr, "Out of memory error: could not allocate %lu\n", realsize);
        return 0;
    }

    copyTo(buf, contents, realsize);
    return realsize;
}


DoomUResponse newDoomUResponse(Buffer *header, Buffer *body) {
    header->memory = (char*) malloc(1);
    header->size = 0;
    body->memory = (char*) malloc(1);
    body->size = 0;
    return (DoomUResponse) { .header=header, .body=body };
}


void destroyDoomUResponse(DoomUResponse *response) {
    if (response->header->memory)
        free(response->header->memory);
    if (response->body->memory)
        free(response->body->memory);
}
