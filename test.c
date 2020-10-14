#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include "str.h"

static const char long_str[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Fusce fermentum commodo mauris non sodales. Vivamus ullamcorper consectetur urna vitae fringilla. Nulla eget libero est.";

int main (int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    str *s = str_init(10);
        assert(s);
        assert(s->cap == 11);
        assert(s->len == 0);
        assert(s->err == STR_OK);

    str_alloc(&s, 30);
        assert(s->cap == 41);
        assert(s->len == 0);
        assert(s->err == STR_OK);

    str_push(&s, "hello, ");
        assert(strcmp(s->buf, "hello, ") == 0);
        assert(s->cap == 41);
        assert(s->len == 7);
        assert(s->err == STR_OK);

    str_push_l(&s, "world", 5);
        assert(s->cap == 41);
        assert(strcmp(s->buf, "hello, world") == 0);
        assert(s->len == 12);
        assert(s->err == STR_OK);

    str_undo(&s, "world");
        assert(s->cap == 41);
        assert(strcmp(s->buf, "hello, ") == 0);
        assert(s->len == 7);
        assert(s->err == STR_OK);

    str_undo_l(&s, 2);
        assert(s->cap == 41);
        assert(strcmp(s->buf, "hello") == 0);
        assert(s->len == 5);
        assert(s->err == STR_OK);

    str_push_c(&s, '!');
        assert(s->cap == 41);
        assert(strcmp(s->buf, "hello!") == 0);
        assert(s->len == 6);
        assert(s->err == STR_OK);

    str_zero(&s);
        assert(s->cap == 41);
        assert(s->len == 0);
        assert(strcmp(s->buf, "") == 0);
        assert(s->err == STR_OK);

    str_push(&s, long_str);
        assert(strcmp(s->buf, long_str) == 0);
        assert(s->len == 177);
        assert(s->cap == 395);
        assert(s->err == STR_OK);

    str_zero(&s);
        assert(s->len == 0);
        assert(s->cap == 395);
        assert(strcmp(s->buf, "") == 0);
        assert(s->err == STR_OK);

    {
        str_push_c(&s, 'h');
            assert(strcmp(s->buf, "h") == 0);
            assert(s->len == 1);
            assert(s->cap == 395);
            assert(s->err == STR_OK);

        str_push(&s, NULL);
            assert(s->err == STR_EINVAL);

        str_push_l(&s, "ello", 4);
        str_push_l(&s, "worl", 4);
            assert(s->err == STR_EINVAL);
            assert(strcmp(s->buf, "h") == 0);
            assert(s->len == 1);
            assert(s->cap == 395);

        s->err = STR_OK;
    }

    str_push(&s, "ello, world");
        assert(s->len == 12);
        assert(s->cap == 395);
        assert(strcmp(s->buf, "hello, world") == 0);
        assert(s->err == STR_OK);

    str *s2 = str_dup(&s);
    str_free(s);
        assert(s2->len == 12);
        assert(s2->cap == 13);
        assert(strcmp(s2->buf, "hello, world") == 0);
        assert(s2->err == STR_OK);

    FILE *f = fopen("./test.c", "r");
    if (f) {
        str_zero(&s2);
        str_getline(&s2, f);
        assert(strcmp(s2->buf, "#include <assert.h>") == 0);
        assert(s2->len == 19);
        assert(s2->cap == 39);
        str_zero(&s2);
        str_getline(&s2, f);
        assert(strcmp(s2->buf, "#include <stdio.h>") == 0);
        assert(s2->len == 18);
        assert(s2->cap == 39);
        str_zero(&s2);
        str_getline(&s2, f);
        assert(strcmp(s2->buf, "#include <stdlib.h>") == 0);
        assert(s2->len == 19);
        assert(s2->cap == 39);
        fclose(f);
    }

    f = fopen("sdasldlasdjladjl", "r");
    str_getline(&s2, f);
        assert(s2->err == STR_EINVAL);
    s2->err = STR_OK;

    str_zero(&s2);
        assert(s2->cap == 39);
        assert(s2->len == 0);
        assert(strcmp(s2->buf, "") == 0);
        assert(s2->err == STR_OK);

    str_printf(&s2, "%d", 9876);
        assert(strcmp(s2->buf, "9876") == 0);

    str_zero(&s2);
        assert(s2->cap == 39);
        assert(s2->len == 0);
        assert(strcmp(s2->buf, "") == 0);
        assert(s2->err == STR_OK);

    str_push_l(&s2, "h", 0);
        assert(s2->err == STR_EINVAL);
        assert(s2->cap == 39);
        assert(s2->len == 0);
        assert(strcmp(s2->buf, "") == 0);

    s2->err = STR_OK;

    str_push_l(&s2, NULL, 10);
        assert(s2->err == STR_EINVAL);
        assert(s2->cap == 39);
        assert(s2->len == 0);
        assert(strcmp(s2->buf, "") == 0);

    s2->err = STR_OK;

    str_undo_l(&s2, 999);
        assert(s2->err == STR_EINVAL);
        assert(s2->cap == 39);
        assert(s2->len == 0);
        assert(strcmp(s2->buf, "") == 0);

    s2->err = STR_OK;

    str_undo(&s2, NULL);
        assert(s2->err == STR_EINVAL);
        assert(s2->cap == 39);
        assert(s2->len == 0);
        assert(strcmp(s2->buf, "") == 0);

    s2->err = STR_OK;

    str_printf(&s2, "hello");
        assert(s2->err == STR_OK);
        assert(s2->cap == 39);
        assert(s2->len == 5);
        assert(strcmp(s2->buf, "hello") == 0);

    str_free(s2);

    return EXIT_SUCCESS;
}
