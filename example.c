#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"

int main (int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    str *name = NULL;

    str_init(&name, 10);
    assert(str_get_cap(name) == 10 + 1);

    str_push(&name, getenv("PWD"));
    assert(strcmp(name, getenv("PWD")) == 0);

    str_push_l(&name, "/", 1);
    assert(name[str_get_len(name) - 1] == '/');

    str_push(&name, "test");
    assert(name[str_get_len(name) - 4] == 't');
    assert(name[str_get_len(name) - 3] == 'e');
    assert(name[str_get_len(name) - 2] == 's');
    assert(name[str_get_len(name) - 1] == 't');
    assert(name[str_get_len(name)] == 0);

    str_undo(&name, "test");
    assert(name[str_get_len(name) - 1] == '/');

    str_undo_l(&name, 1);
    assert(strcmp(name, getenv("PWD")) == 0);

    str_zero(&name);
    assert(str_get_len(name) == 0);
    assert(strcmp(name, "") == 0);

    str_push(&name, "./example.c");
    assert(strcmp(name, "./example.c") == 0);

    str_free(&name);

    return 0;
}
