#include <stdlib.h>
#include <string.h>

#include "str.h"

str *str_init(size_t l) {
    str *s = malloc(sizeof (str) + l);

    if (!s) {
        return NULL;
    }

    s->cap = l;
    s->len = 0;
    s->err = STR_OK;

    return s;
}

void str_alloc(str **s, size_t l) {
    if ((*s)->err == STR_OK) {
        str *s2 = realloc(*s, sizeof (str) + (*s)->cap + l + 1);

        if (!s2) {
            (*s)->err = STR_ENOMEM;
            return;
        }

        (*s) = s2;
        (*s)->cap += l + 1;
    }
}

void str_push_c(str **s, char d) {
    if ((*s)->len + 1 >= (*s)->cap) {
        str_alloc(s, 1);
    }

    if ((*s)->err == STR_OK) {
        (*s)->buf[(*s)->len] = d;
        (*s)->buf[(*s)->len += 1] = 0;
    }
}

void str_push_l(str **s, const char *d, size_t l) {
    if (!d || !d[0] || l < 1) {
        (*s)->err = STR_EINVAL;
        return;
    }

    if (((*s)->len + l) >= (*s)->cap) {
        str_alloc(s, l * 2);
    }

    if ((*s)->err == STR_OK) {
        memcpy((*s)->buf + (*s)->len, d, l);
        (*s)->buf[(*s)->len += l] = 0;
    }
}

void str_push(str **s, const char *d) {
    if (!d || !d[0]) {
        (*s)->err = STR_EINVAL;
        return;
    }

    if ((*s)->err == STR_OK) {
        str_push_l(s, d, strlen(d));
    }
}

void str_undo_l(str **s, size_t l) {
    if (l > (*s)->len) {
        (*s)->err = STR_EINVAL;
        return;
    }

    if ((*s)->err == STR_OK) {
        (*s)->buf[(*s)->len -= l] = 0;
    }
}

void str_undo(str **s, const char *d) {
    if (!d || !d[0]) {
        (*s)->err = STR_EINVAL;
        return;
    }

    if ((*s)->err == STR_OK) {
        str_undo_l(s, strlen(d));
    }
}

void str_zero(str **s) {
    if ((*s)->err == STR_OK) {
        memset((*s)->buf, 0, (*s)->len);
        (*s)->len = 0;
    }
}

void str_free(str *s) {
    if (s) {
        free(s);
    }
}
