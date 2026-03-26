# Bit-Twiddling

A small collection of header-only C utilities for low-level bit manipulation,
merged from [darrelllong's GitHub repositories](https://github.com/darrelllong).
Originally developed for CSE 13S at UC Santa Cruz.

---

## rotate.h — Circular Bit Rotations

Provides inline functions for circular (barrel) left and right rotation of
8-, 16-, 32-, and 64-bit unsigned integers.  Written as `static inline`
functions rather than macros to avoid compatibility and type-safety issues.

### Functions

| Function | Description |
|---|---|
| `rotR_8(v, n)` | Rotate `uint8_t v` right by `n` bits |
| `rotL_8(v, n)` | Rotate `uint8_t v` left by `n` bits |
| `rotR_16(v, n)` | Rotate `uint16_t v` right by `n` bits |
| `rotL_16(v, n)` | Rotate `uint16_t v` left by `n` bits |
| `rotR_32(v, n)` | Rotate `uint32_t v` right by `n` bits |
| `rotL_32(v, n)` | Rotate `uint32_t v` left by `n` bits |
| `rotR_64(v, n)` | Rotate `uint64_t v` right by `n` bits |
| `rotL_64(v, n)` | Rotate `uint64_t v` left by `n` bits |

A negative rotation count reverses direction: `rotR(v, -n) == rotL(v, n)`.

### Usage

```c
#include "rotate.h"

uint32_t x = 0x12345678;
uint32_t y = rotR_32(x, 8);   // 0x78123456
uint32_t z = rotL_32(x, 8);   // 0x34567812
```

---

## set.h — Fixed-Size Sets

A simple, efficient implementation of fixed-size sets backed by a single
`uint64_t` machine word.  Each bit position represents a set element (0–63).
All operations pass and return sets by value, so there is no heap allocation.

Set negation is intentionally omitted: the complement of a set is not well-
defined without first specifying a universe.

### Type

```c
typedef uint64_t set;
```

### Functions

| Function | Description |
|---|---|
| `memberSet(x, s)` | Returns `true` if element `x` is in set `s` |
| `insertSet(x, s)` | Returns `s` with element `x` added |
| `deleteSet(x, s)` | Returns `s` with element `x` removed |
| `unionSet(s, t)` | Returns `s ∪ t` |
| `intersectSet(s, t)` | Returns `s ∩ t` |
| `differenceSet(s, t)` | Returns `s ∖ t` (elements in `s` but not `t`) |

### Known Issue

The shift expression `0x1 << (x & mask)` uses a 32-bit integer literal.
Elements 32–63 invoke undefined behaviour.  Use `(set)1 << (x & mask)` for
full 64-bit range.

### Usage

```c
#include "set.h"

set vowels = insertSet(0, insertSet(4, insertSet(8, insertSet(14, insertSet(20, 0)))));
// A=0, E=4, I=8, O=14, U=20

if (memberSet(4, vowels)) { /* 'E' is a vowel */ }

set letters = 0;
for (int i = 0; i < 26; i++) letters = insertSet(i, letters);

set consonants = differenceSet(letters, vowels);
```

---

## endian.h — Endianness Detection and Byte Swapping

Detects the byte order of the host machine and provides branch-free byte-swap
functions for 16-, 32-, and 64-bit integers.  A good compiler will optimize
the detection functions to a compile-time constant and eliminate the swap
overhead entirely.

### Functions

| Function | Description |
|---|---|
| `isBig()` | Returns `true` if the host is big-endian |
| `isLittle()` | Returns `true` if the host is little-endian |
| `swap16(x)` | Reverses the byte order of a `uint16_t` |
| `swap32(x)` | Reverses the byte order of a `uint32_t` |
| `swap64(x)` | Reverses the byte order of a `uint64_t` |

### Usage

```c
#include "endian.h"

uint32_t network_word = 0xDEADBEEF;
uint32_t host_word = isLittle() ? swap32(network_word) : network_word;

uint16_t a = swap16(0x1234);   // 0x3412
uint32_t b = swap32(0x12345678); // 0x78563412
```

---

## Building and Testing

```
make        # compile all test binaries
make check  # build and run all tests
make clean  # remove test binaries
```

Test files live in `tests/`.  Each is a standalone C program that prints
`PASS`/`FAIL` for each assertion and exits with a non-zero status if any
check fails.

All tests should pass.
