#ifndef KISS_STR_H_
#define KISS_STR_H_

#include <stdlib.h>

typedef struct str {
    size_t len;
    size_t cap;
    size_t err;
    char buf[];
} str;

enum str_error {
    STR_OK,
    STR_ENOMEM,
    STR_EINVAL
};

str *str_init(size_t l);
void str_alloc(str **s, size_t l);
void str_push_c(str **s, char d);
void str_push_l(str **s, const char *d, size_t l);
void str_push(str **s, const char *d);
void str_undo_l(str **s, size_t l);
void str_undo(str **s, const char *d);
void str_zero(str **s);
str *str_dup(str **s);
void str_free(str *s);

#endif
