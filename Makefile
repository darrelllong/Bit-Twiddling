CC      = cc
CFLAGS  = -Wall -Wextra -std=c11 -pedantic

TESTS   = test_rotate test_set test_endian

all: $(TESTS)

test_rotate: tests/test_rotate.c rotate.h
	$(CC) $(CFLAGS) -o $@ tests/test_rotate.c

test_set: tests/test_set.c set.h
	$(CC) $(CFLAGS) -o $@ tests/test_set.c

test_endian: tests/test_endian.c endian.h
	$(CC) $(CFLAGS) -o $@ tests/test_endian.c

check: all
	@echo "--- test_rotate ---" && ./test_rotate
	@echo "--- test_set ---"    && ./test_set
	@echo "--- test_endian ---" && ./test_endian

clean:
	rm -f $(TESTS)

.PHONY: all check clean
