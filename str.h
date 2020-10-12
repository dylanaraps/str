#ifndef KISS_STR_H_
#define KISS_STR_H_

#include <stdlib.h>

typedef char str;

#define str_get_cap(s) \
    ((s) ? ((size_t *)(s))[-2] : (size_t) 0)

#define str_get_len(s) \
    ((s) ? ((size_t *)(s))[-1] : (size_t) 0)

#define str_init(s, l) str_alloc(s, l)

void str_alloc(str **, size_t);
void str_push_l(str **, const char *, size_t);
void str_push(str **, const char *);
void str_undo_l(str **, size_t);
void str_undo(str **, const char *);
void str_zero(str **);
void str_free(str **);
void str_set_cap(str **, size_t);
void str_set_len(str **, size_t);

#define str_fmt(s, f, ...) do { \
    int _str_l1 = snprintf(NULL, 0, f, __VA_ARGS__); \
                                                     \
    assert(_str_l1 > 0);                             \
    str_alloc(s, (size_t) _str_l1);                  \
                                                     \
    int _str_l2 = snprintf(                          \
        *s + str_get_len(*s), (size_t) _str_l1 + 1,  \
        f, __VA_ARGS__);                             \
                                                     \
    assert(_str_l1 == _str_l2);                      \
    str_set_len(s, (size_t) _str_l1);                \
} while (0)

#endif
