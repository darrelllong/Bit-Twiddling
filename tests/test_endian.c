#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../endian.h"

static int pass = 0, fail = 0;

#define CHECK(expr, name) do { \
    if (expr) { printf("PASS: %s\n", name); pass++; } \
    else       { printf("FAIL: %s\n", name); fail++; } \
} while (0)

int main(void) {
    printf("=== endianness detection ===\n");
    // Exactly one of isBig / isLittle must be true on any conforming platform
    CHECK(isBig() != isLittle(),     "isBig() != isLittle()");
    CHECK(isBig() || isLittle(),     "at least one of isBig/isLittle is true");
    CHECK(!(isBig() && isLittle()),  "not both isBig and isLittle");

    printf("\n=== swap16 ===\n");
    CHECK(swap16(0x1234) == 0x3412, "swap16(0x1234) == 0x3412");
    CHECK(swap16(0xFF00) == 0x00FF, "swap16(0xFF00) == 0x00FF");
    CHECK(swap16(0x0001) == 0x0100, "swap16(0x0001) == 0x0100");
    CHECK(swap16(0xABCD) == 0xCDAB, "swap16(0xABCD) == 0xCDAB");
    CHECK(swap16(0x0000) == 0x0000, "swap16(0x0000) == 0x0000");
    CHECK(swap16(0xFFFF) == 0xFFFF, "swap16(0xFFFF) == 0xFFFF");
    // roundtrip
    CHECK(swap16(swap16(0x1234)) == 0x1234, "swap16(swap16(0x1234)) == 0x1234");
    CHECK(swap16(swap16(0xBEEF)) == 0xBEEF, "swap16(swap16(0xBEEF)) == 0xBEEF");

    printf("\n=== swap32 ===\n");
    CHECK(swap32(0x12345678) == 0x78563412, "swap32(0x12345678) == 0x78563412");
    CHECK(swap32(0xFF000000) == 0x000000FF, "swap32(0xFF000000) == 0x000000FF");
    CHECK(swap32(0x00000001) == 0x01000000, "swap32(0x00000001) == 0x01000000");
    CHECK(swap32(0xDEADBEEF) == 0xEFBEADDE, "swap32(0xDEADBEEF) == 0xEFBEADDE");
    CHECK(swap32(0x00000000) == 0x00000000, "swap32(0x00000000) == 0x00000000");
    CHECK(swap32(0xFFFFFFFF) == 0xFFFFFFFF, "swap32(0xFFFFFFFF) == 0xFFFFFFFF");
    // roundtrip
    CHECK(swap32(swap32(0x12345678)) == 0x12345678, "swap32(swap32(0x12345678)) == 0x12345678");
    CHECK(swap32(swap32(0xCAFEBABE)) == 0xCAFEBABE, "swap32(swap32(0xCAFEBABE)) == 0xCAFEBABE");

    printf("\n=== swap64 ===\n");
    CHECK(swap64(UINT64_C(0x0102030405060708)) == UINT64_C(0x0807060504030201),
          "swap64(0x0102030405060708) == 0x0807060504030201");
    CHECK(swap64(UINT64_C(0xFF00000000000000)) == UINT64_C(0x00000000000000FF),
          "swap64(0xFF00000000000000) == 0x00000000000000FF");
    CHECK(swap64(UINT64_C(0x0000000000000001)) == UINT64_C(0x0100000000000000),
          "swap64(0x0000000000000001) == 0x0100000000000000");
    CHECK(swap64(UINT64_C(0xDEADBEEFCAFEBABE)) == UINT64_C(0xBEBAFECAEFBEADDE),
          "swap64(0xDEADBEEFCAFEBABE) == 0xBEBAFECAEFBEADDE");
    CHECK(swap64(UINT64_C(0x0000000000000000)) == UINT64_C(0x0000000000000000),
          "swap64(0) == 0");
    CHECK(swap64(UINT64_C(0xFFFFFFFFFFFFFFFF)) == UINT64_C(0xFFFFFFFFFFFFFFFF),
          "swap64(0xFFFFFFFFFFFFFFFF) == 0xFFFFFFFFFFFFFFFF");
    // roundtrip
    CHECK(swap64(swap64(UINT64_C(0x0102030405060708))) == UINT64_C(0x0102030405060708),
          "swap64(swap64(0x0102030405060708)) == 0x0102030405060708");
    CHECK(swap64(swap64(UINT64_C(0xDEADBEEFCAFEBABE))) == UINT64_C(0xDEADBEEFCAFEBABE),
          "swap64(swap64(0xDEADBEEFCAFEBABE)) == 0xDEADBEEFCAFEBABE");

    printf("\n%d passed, %d failed\n", pass, fail);
    return (fail > 0) ? 1 : 0;
}
