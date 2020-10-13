#ifndef KISS_STR_H_
#define KISS_STR_H_

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef char str;

#define str_get_cap(s) ((s) ? ((size_t *)(s))[-2] : (size_t) 0)
#define str_get_len(s) ((s) ? ((size_t *)(s))[-1] : (size_t) 0)

#define str_init(s, l) str_alloc(s, l)

void str_alloc(str **s, size_t l);
void str_push_l(str **s, const char *d, size_t l);
void str_push(str **s, const char *d);
void str_undo_l(str **s, size_t l);
void str_undo(str **s, const char *d);
void str_zero(str **s);
void str_free(str **s);
void str_set_cap(str **s, size_t l);
void str_set_len(str **s, size_t l);

#define str_fmt(s, f, ...) do { \
    int _str_l1 = snprintf(NULL, 0, f, __VA_ARGS__);             \
                                                                 \
    assert(_str_l1 > 0);                                         \
                                                                 \
    if (str_get_len(*s) + (size_t) _str_l1 >= str_get_cap(*s)) { \
        str_alloc(s, (size_t) _str_l1);                          \
    }                                                            \
                                                                 \
    int _str_l2 = snprintf(                                      \
        *s + str_get_len(*s), (size_t) _str_l1 + 1,              \
        f, __VA_ARGS__);                                         \
                                                                 \
    assert(_str_l1 == _str_l2);                                  \
    str_set_len(s, str_get_len(*s) + (size_t) _str_l1);          \
} while (0)

#endif
