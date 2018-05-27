#ifndef _DOOMU_CONFIG_H_
#define _DOOMU_CONFIG_H_

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define ERROR_HANDLER(condition, ...) \
    do { \
      if ((condition)) { \
        printf("\nError: in %s - function %s at line %d: ", __FILE__, __func__, __LINE__); \
        if (errno != 0) \
            printf("%s - ", strerror(errno)); \
        printf(__VA_ARGS__); \
        printf("\n"); \
        fflush(stdout); \
        exit(EXIT_FAILURE); \
      }    \
    } while(0)


#define MEM_ERROR(variable) \
    do { \
        ERROR_HANDLER((variable) == NULL, OOM); \
    } while (0)


#define SYNTAX_ERROR(condition, ...) \
    do { \
        ERROR_HANDLER((condition), "Syntax error: %s", __VA_ARGS__); \
    } while (0)


#define TYPE_ERROR(condition, ...) \
    do { \
        ERROR_HANDLER((condition && "Type error: %s"), __VA_ARGS__); \
    } while (0)


#define OOM "Out of memory error"

#define BUFFER 2048
#define VAR_LEN 64
#define ARG_LEN 3

#endif // _DOOMU_CONFIG_H_
