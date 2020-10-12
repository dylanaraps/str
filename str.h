#ifndef KISS_STR_H_
#define KISS_STR_H_

#include <stdlib.h>

typedef char str;

void str_alloc(str **, size_t);
void str_push_l(str **, const char *, size_t);
void str_push(str **, const char *);
void str_undo_l(str **, size_t);
void str_undo(str **, const char *);
void str_zero(str **);
void str_free(str **);
void str_set_cap(str **, size_t);
void str_set_len(str **, size_t);
size_t str_get_cap(const str *);
size_t str_get_len(const str *);

#define str_init(s, l) str_alloc(s, l)

#endif
