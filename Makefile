.POSIX:

BUILD_FLAGS = \
	-std=c99 \
	-D_POSIX_C_SOURCE=200809L \
	-Wall \
	-Wextra \
	-pedantic \
	-Wmissing-prototypes \
	-Wstrict-prototypes \
	-Wwrite-strings \
	-Wshadow \
	-Wundef \
	-Wsign-conversion

VALGRIND = \
	--leak-check=full \
	--show-leak-kinds=all \
	--track-origins=yes \
	--error-exitcode=1 \
	--trace-children=yes \
	--show-reachable=no \

OBJ = example.o str.o
HDR = str.h

example: $(OBJ)
	$(CC) $(BUILD_FLAGS) $(CFLAGS) -o $@ $(OBJ) $(LDFLAGS)

.c.o:
	$(CC) $(BUILD_FLAGS) $(CFLAGS) -c -o $@ $<

$(OBJ): $(HDR)

check:
	valgrind $(VALGRIND) ./example

clean:
	rm -f example $(OBJ)

.PHONY: clean check
