#ifndef KISS_STR_H_
#define KISS_STR_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct str {
    size_t len;
    size_t cap;
    size_t err;
    char buf[];
} str;

enum str_error {
    STR_OK,
    STR_ERROR,
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
void str_getline(str **s, FILE *f);
void str_free(str *s);

#define str_printf(s, ...) do { \
    int l1 = snprintf(NULL, 0, __VA_ARGS__);          \
                                                      \
    if (l1 > 0 && (*s)->err == STR_OK) {              \
        if (((*s)->len + (size_t) l1) >= (*s)->cap) { \
            str_alloc(s, (size_t) l1);                \
        }                                             \
                                                      \
        if ((*s)->err == STR_OK) {                    \
            int l2 = snprintf((*s)->buf + (*s)->len,  \
                (size_t) l1 + 1, __VA_ARGS__);        \
                                                      \
            if (l1 == l2) {                           \
                (*s)->len += (size_t) l1;             \
                                                      \
            } else {                                  \
                (*s)->err = STR_ERROR;                \
            }                                         \
        }                                             \
    } else {                                          \
        (*s)->err = STR_ERROR;                        \
    }                                                 \
} while (0)

#endif
