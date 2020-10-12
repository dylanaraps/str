#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"

void str_alloc(str **s, size_t l) {
    size_t *p = realloc(*s ? (size_t *) *s - 2 : (size_t *) *s,
        (sizeof (size_t) * 2) + str_get_cap(*s) + l + 1);
    assert(p);

    p[0] = *s ? p[0] : (size_t) 0;
    p[1] = *s ? p[1] : (size_t) 0;
    *s = (char *)(&p[2]);
    str_set_cap(s, p[1] + l + 1);
}

void str_push_l(str **s, const char *d, size_t l) {
    if (str_get_len(*s) + l >= str_get_cap(*s)) {
        str_alloc(s, l * 2);
    }

    memcpy(*s + str_get_len(*s), d, l + 1);
    str_set_len(s, str_get_len(*s) + l);
}

void str_push(str **s, const char *d) {
    if (d && d[0]) {
        str_push_l(s, d, strlen(d));
    }
}

void str_undo_l(str **s, size_t l) {
    if (l <= str_get_len(*s)) {
        str_set_len(s, str_get_len(*s) - l);
    }
}

void str_undo(str **s, const char *d) {
    if (d && d[0]) {
        str_undo_l(s, strlen(d));
    }
}

void str_zero(str **s) {
    if (*s) {
       memset(*s, 0, str_get_len(*s));
       str_set_len(s, 0);
    }
}

void str_free(str **s) {
    free((size_t *) *s - 2);
}

void str_set_cap(str **s, size_t l) {
    if (*s) {
        ((size_t *)(*s))[-2] = l;
    }
}

void str_set_len(str **s, size_t l) {
    if (*s) {
        ((size_t *)(*s))[-1] = l;
        (*s)[str_get_len(*s)] = 0;
    }
}
