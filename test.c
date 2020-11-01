#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"

static const char long_str[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Fusce fermentum commodo mauris non sodales. Vivamus ullamcorper consectetur urna vitae fringilla. Nulla eget libero est.";

int main (int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    int err = 0;

    str *s = str_init(10);
        assert(str_get_cap(&s) == 11);
        assert(str_get_len(&s) == 0);
        assert(s);

    err = str_push_s(&s, "hello, ");
        assert(str_get_cap(&s) == 11);
        assert(str_get_len(&s) == 7);
        assert(strcmp(s, "hello, ") == 0);
        assert(err == 0);

    err = str_push_l(&s, "world", 5);
        assert(str_get_cap(&s) == 19);
        assert(str_get_len(&s) == 12);
        assert(strcmp(s, "hello, world") == 0);
        assert(err == 0);

    str_set_len(&s, str_get_len(&s) - 5);
        assert(str_get_cap(&s) == 19);
        assert(str_get_len(&s) == 7);
        assert(strcmp(s, "hello, ") == 0);

    str_set_len(&s, str_get_len(&s) - 2);
        assert(str_get_cap(&s) == 19);
        assert(str_get_len(&s) == 5);
        assert(strcmp(s, "hello") == 0);

    str_set_len(&s, 0);
        assert(str_get_cap(&s) == 19);
        assert(str_get_len(&s) == 0);
        assert(strcmp(s, "") == 0);

    err = str_push_s(&s, long_str);
        assert(str_get_cap(&s) == 285);
        assert(str_get_len(&s) == 177);
        assert(strcmp(s, long_str) == 0);
        assert(err == 0);

    str_set_len(&s, 0);
        assert(str_get_cap(&s) == 285);
        assert(str_get_len(&s) == 0);
        assert(strcmp(s, "") == 0);

    err = str_push_s(&s, "ello, world");
        assert(str_get_cap(&s) == 285);
        assert(str_get_len(&s) == 11);
        assert(strcmp(s, "ello, world") == 0);
        assert(err == 0);

    err = str_printf(&s, " %d", 12345);
        assert(str_get_cap(&s) == 285);
        assert(str_get_len(&s) == 17);
        assert(strcmp(s, "ello, world 12345") == 0);
        assert(err == 0);

    str_free(&s);
        assert(!s);

    return EXIT_SUCCESS;
}

