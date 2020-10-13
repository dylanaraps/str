#include <stdio.h>
#include <stdlib.h>

#include "str.h"

int main (int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    str *s = str_init(10);

    if (!s) {
        fputs("failed to allocate memory\n", stderr);
        return EXIT_FAILURE;
    }

    str_push(&s, getenv("PWD"));

    if (s->buf[s->len - 1] != '/') {
        str_push_c(&s, '/');
    }

    str_push_l(&s, "test", 4);

    if (s->err != STR_OK) {
        str_free(s);
        fputs("failed to construct string\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%s\n", s->buf);

    str_free(s);
    return EXIT_SUCCESS;
}
