#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"

str *str_init(size_t l) {
    str *s = malloc(sizeof (str) + l + 1);

    if (s) {
        s->cap = l + 1;
        s->len = 0;
        s->err = STR_OK;
    }

    return s;
}

void str_alloc(str **s, size_t l) {
    if ((*s)->err == STR_OK && l != 0) {
        str *s2 = realloc(*s, sizeof (str) + (*s)->cap + l);

        if (s2) {
            (*s) = s2;
            (*s)->cap += l;
        } else {
            (*s)->err = STR_ENOMEM;
        }
    }
}

void str_push_c(str **s, char d) {
    if ((*s)->len + 1 >= (*s)->cap) {
        str_alloc(s, (*s)->cap * 2);
    }

    if ((*s)->err == STR_OK) {
        (*s)->buf[(*s)->len] = d;
        (*s)->buf[(*s)->len += 1] = 0;
    }
}

void str_push_l(str **s, const char *d, size_t l) {
    if (d && d[0] && l > 0) {
        if (((*s)->len + l) >= (*s)->cap) {
            str_alloc(s, l * 2);
        }

        if ((*s)->err == STR_OK) {
            memcpy((*s)->buf + (*s)->len, d, l);
            (*s)->buf[(*s)->len += l] = 0;
        }
    } else {
        (*s)->err = STR_EINVAL;
    }
}

void str_push(str **s, const char *d) {
    if (d && d[0]) {
        if ((*s)->err == STR_OK) {
            str_push_l(s, d, strlen(d));
        }
    } else {
        (*s)->err = STR_EINVAL;
    }
}

void str_undo_l(str **s, size_t l) {
    if (l <= (*s)->len) {
        if ((*s)->err == STR_OK) {
            (*s)->buf[(*s)->len -= l] = 0;
        }
    } else {
        (*s)->err = STR_EINVAL;
    }
}

void str_undo(str **s, const char *d) {
    if (d && d[0]) {
        if ((*s)->err == STR_OK) {
            str_undo_l(s, strlen(d));
        }
    } else {
        (*s)->err = STR_EINVAL;
    }
}

void str_zero(str **s) {
    if ((*s)->err == STR_OK) {
        memset((*s)->buf, 0, (*s)->len);
        (*s)->len = 0;
    }
}

void str_getline(str **s, FILE *f) {
    if (f) {
        int c;

        while ((c = fgetc(f)) != '\n' && c != EOF) {
            str_push_c(s, c);
        }

    } else {
        (*s)->err = STR_EINVAL;
    }
}

str *str_dup(str **s) {
    if ((*s)->err == STR_OK) {
        str *n = str_init((*s)->len);

        if (n) {
            str_push_l(&n, (*s)->buf, (*s)->len);

            if (n->err == STR_OK) {
                return n;
            }
        }

        str_free(n);
    }

    return NULL;
}

void str_free(str *s) {
    if (s) {
        free(s);
    }
}
