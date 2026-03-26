#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>

#include "../rotate.h"

static int pass = 0, fail = 0;

#define CHECK(expr, name) do { \
    if (expr) { printf("PASS: %s\n", name); pass++; } \
    else       { printf("FAIL: %s\n", name); fail++; } \
} while (0)

int main(void) {
    printf("=== rotR_8 / rotL_8 ===\n");
    CHECK(rotR_8(0x01, 1) == 0x80, "rotR_8(0x01,  1) == 0x80");
    CHECK(rotR_8(0x80, 1) == 0x40, "rotR_8(0x80,  1) == 0x40");
    CHECK(rotR_8(0xFF, 4) == 0xFF, "rotR_8(0xFF,  4) == 0xFF");
    CHECK(rotR_8(0x12, 0) == 0x12, "rotR_8(0x12,  0) == 0x12");
    CHECK(rotR_8(0xAB, 8) == 0xAB, "rotR_8(0xAB,  8) == 0xAB (full rotation)");

    CHECK(rotL_8(0x80, 1) == 0x01, "rotL_8(0x80,  1) == 0x01");
    CHECK(rotL_8(0x01, 1) == 0x02, "rotL_8(0x01,  1) == 0x02");
    CHECK(rotL_8(0xAB, 4) == 0xBA, "rotL_8(0xAB,  4) == 0xBA");
    CHECK(rotL_8(0x12, 0) == 0x12, "rotL_8(0x12,  0) == 0x12");

    // negative n reverses direction
    CHECK(rotR_8(0x01, -1) == rotL_8(0x01, 1), "rotR_8(v, -1) == rotL_8(v, 1)");
    CHECK(rotL_8(0x01, -1) == rotR_8(0x01, 1), "rotL_8(v, -1) == rotR_8(v, 1)");

    // full rotation (n == width) and multiples
    CHECK(rotR_8(0xAB, 8)  == 0xAB, "rotR_8(0xAB,  8) == 0xAB (n == width)");
    CHECK(rotR_8(0xAB, 16) == 0xAB, "rotR_8(0xAB, 16) == 0xAB (n == 2*width)");
    CHECK(rotL_8(0xAB, 8)  == 0xAB, "rotL_8(0xAB,  8) == 0xAB (n == width)");
    CHECK(rotR_8(0xAB, 9)  == rotR_8(0xAB, 1), "rotR_8(v, 9) == rotR_8(v, 1)");

    // roundtrip
    CHECK(rotL_8(rotR_8(0xAB, 3), 3) == 0xAB, "rotL_8(rotR_8(0xAB, 3), 3) == 0xAB");
    CHECK(rotR_8(rotL_8(0xAB, 5), 5) == 0xAB, "rotR_8(rotL_8(0xAB, 5), 5) == 0xAB");

    printf("\n=== rotR_16 / rotL_16 ===\n");
    CHECK(rotR_16(0x0001, 1)  == 0x8000, "rotR_16(0x0001,  1) == 0x8000");
    CHECK(rotR_16(0x8000, 1)  == 0x4000, "rotR_16(0x8000,  1) == 0x4000");
    CHECK(rotR_16(0x1234, 8)  == 0x3412, "rotR_16(0x1234,  8) == 0x3412");
    CHECK(rotR_16(0xFFFF, 7)  == 0xFFFF, "rotR_16(0xFFFF,  7) == 0xFFFF");
    CHECK(rotR_16(0x1234, 0)  == 0x1234, "rotR_16(0x1234,  0) == 0x1234");

    CHECK(rotL_16(0x8000, 1)  == 0x0001, "rotL_16(0x8000,  1) == 0x0001");
    CHECK(rotL_16(0x0001, 1)  == 0x0002, "rotL_16(0x0001,  1) == 0x0002");
    CHECK(rotL_16(0x1234, 8)  == 0x3412, "rotL_16(0x1234,  8) == 0x3412");

    CHECK(rotR_16(0x1234, -4) == rotL_16(0x1234, 4), "rotR_16(v, -4) == rotL_16(v, 4)");

    CHECK(rotR_16(0xABCD, 16) == 0xABCD, "rotR_16(0xABCD, 16) == 0xABCD (n == width)");
    CHECK(rotR_16(0xABCD, 32) == 0xABCD, "rotR_16(0xABCD, 32) == 0xABCD (n == 2*width)");
    CHECK(rotL_16(0xABCD, 16) == 0xABCD, "rotL_16(0xABCD, 16) == 0xABCD (n == width)");
    CHECK(rotR_16(0xABCD, 17) == rotR_16(0xABCD, 1), "rotR_16(v, 17) == rotR_16(v, 1)");

    CHECK(rotL_16(rotR_16(0xABCD, 5), 5) == 0xABCD, "rotL_16(rotR_16(0xABCD, 5), 5) == 0xABCD");

    printf("\n=== rotR_32 / rotL_32 ===\n");
    CHECK(rotR_32(0x00000001, 1)  == 0x80000000, "rotR_32(0x00000001,  1) == 0x80000000");
    CHECK(rotR_32(0x80000000, 1)  == 0x40000000, "rotR_32(0x80000000,  1) == 0x40000000");
    CHECK(rotR_32(0x12345678, 8)  == 0x78123456, "rotR_32(0x12345678,  8) == 0x78123456");
    CHECK(rotR_32(0xFFFFFFFF, 13) == 0xFFFFFFFF, "rotR_32(0xFFFFFFFF, 13) == 0xFFFFFFFF");
    CHECK(rotR_32(0x12345678, 0)  == 0x12345678, "rotR_32(0x12345678,  0) == 0x12345678");

    CHECK(rotL_32(0x80000000, 1)  == 0x00000001, "rotL_32(0x80000000,  1) == 0x00000001");
    CHECK(rotL_32(0x00000001, 1)  == 0x00000002, "rotL_32(0x00000001,  1) == 0x00000002");
    CHECK(rotL_32(0x12345678, 8)  == 0x34567812, "rotL_32(0x12345678,  8) == 0x34567812");

    CHECK(rotR_32(0x12345678, -8) == rotL_32(0x12345678, 8), "rotR_32(v, -8) == rotL_32(v, 8)");

    CHECK(rotR_32(0xDEADBEEF, 32) == 0xDEADBEEF, "rotR_32(0xDEADBEEF, 32) == 0xDEADBEEF (n == width)");
    CHECK(rotR_32(0xDEADBEEF, 64) == 0xDEADBEEF, "rotR_32(0xDEADBEEF, 64) == 0xDEADBEEF (n == 2*width)");
    CHECK(rotL_32(0xDEADBEEF, 32) == 0xDEADBEEF, "rotL_32(0xDEADBEEF, 32) == 0xDEADBEEF (n == width)");
    CHECK(rotR_32(0xDEADBEEF, 33) == rotR_32(0xDEADBEEF, 1), "rotR_32(v, 33) == rotR_32(v, 1)");

    CHECK(rotL_32(rotR_32(0xDEADBEEF, 11), 11) == 0xDEADBEEF,
          "rotL_32(rotR_32(0xDEADBEEF, 11), 11) == 0xDEADBEEF");

    printf("\n=== rotR_64 / rotL_64 ===\n");
    CHECK(rotR_64(UINT64_C(0x0000000000000001), 1) == UINT64_C(0x8000000000000000),
          "rotR_64(0x0000000000000001,  1) == 0x8000000000000000");
    CHECK(rotR_64(UINT64_C(0x8000000000000000), 1) == UINT64_C(0x4000000000000000),
          "rotR_64(0x8000000000000000,  1) == 0x4000000000000000");
    CHECK(rotR_64(UINT64_C(0x1234567890ABCDEF), 8) == UINT64_C(0xEF1234567890ABCD),
          "rotR_64(0x1234567890ABCDEF,  8) == 0xEF1234567890ABCD");

    CHECK(rotL_64(UINT64_C(0x8000000000000000), 1) == UINT64_C(0x0000000000000001),
          "rotL_64(0x8000000000000000,  1) == 0x0000000000000001");
    CHECK(rotL_64(UINT64_C(0x0000000000000001), 1) == UINT64_C(0x0000000000000002),
          "rotL_64(0x0000000000000001,  1) == 0x0000000000000002");

    CHECK(rotR_64(UINT64_C(0xDEADBEEFCAFEBABE), -8) ==
          rotL_64(UINT64_C(0xDEADBEEFCAFEBABE), 8),
          "rotR_64(v, -8) == rotL_64(v, 8)");

    CHECK(rotR_64(UINT64_C(0xDEADBEEFCAFEBABE), 64)  == UINT64_C(0xDEADBEEFCAFEBABE),
          "rotR_64(v, 64) == v (n == width)");
    CHECK(rotR_64(UINT64_C(0xDEADBEEFCAFEBABE), 128) == UINT64_C(0xDEADBEEFCAFEBABE),
          "rotR_64(v, 128) == v (n == 2*width)");
    CHECK(rotL_64(UINT64_C(0xDEADBEEFCAFEBABE), 64)  == UINT64_C(0xDEADBEEFCAFEBABE),
          "rotL_64(v, 64) == v (n == width)");
    CHECK(rotR_64(UINT64_C(0xDEADBEEFCAFEBABE), 65) ==
          rotR_64(UINT64_C(0xDEADBEEFCAFEBABE), 1),
          "rotR_64(v, 65) == rotR_64(v, 1)");

    CHECK(rotL_64(rotR_64(UINT64_C(0xDEADBEEFCAFEBABE), 32), 32) == UINT64_C(0xDEADBEEFCAFEBABE),
          "rotL_64(rotR_64(0xDEADBEEFCAFEBABE, 32), 32) == 0xDEADBEEFCAFEBABE");

    printf("\n%d passed, %d failed\n", pass, fail);
    return (fail > 0) ? 1 : 0;
}
