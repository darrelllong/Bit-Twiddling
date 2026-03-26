#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "../set.h"

static int pass = 0, fail = 0;

#define CHECK(expr, name) do { \
    if (expr) { printf("PASS: %s\n", name); pass++; } \
    else       { printf("FAIL: %s\n", name); fail++; } \
} while (0)

int main(void) {
    printf("=== memberSet / insertSet ===\n");
    set s = 0;
    CHECK(!memberSet(0, s),              "0 not in empty set");
    CHECK(!memberSet(31, s),             "31 not in empty set");

    s = insertSet(0, s);
    CHECK( memberSet(0, s),              "0 in {0}");
    CHECK(!memberSet(1, s),              "1 not in {0}");

    s = insertSet(5, s);
    s = insertSet(10, s);
    CHECK( memberSet(5, s),              "5 in {0,5,10}");
    CHECK( memberSet(10, s),             "10 in {0,5,10}");
    CHECK(!memberSet(3, s),              "3 not in {0,5,10}");

    // inserting the same element twice is idempotent
    set s2 = insertSet(7, insertSet(7, 0));
    CHECK(s2 == insertSet(7, 0),         "insertSet is idempotent");

    printf("\n=== deleteSet ===\n");
    set d = insertSet(1, insertSet(2, insertSet(3, 0)));
    d = deleteSet(2, d);
    CHECK(!memberSet(2, d),              "2 removed from {1,2,3}");
    CHECK( memberSet(1, d),              "1 still in set after deleting 2");
    CHECK( memberSet(3, d),              "3 still in set after deleting 2");

    // deleting an absent element is a no-op
    // Note: set.h uses `0x1 << (x & mask)` with a 32-bit literal, so element
    // indices >= 32 invoke undefined behaviour.  Stay below 32 here.
    set before = d;
    d = deleteSet(15, d);                // element 15 not in {1, 3}
    CHECK(d == before,                   "deleting absent element is no-op");

    printf("\n=== unionSet ===\n");
    set a = insertSet(0, insertSet(1, insertSet(2, 0)));
    set b = insertSet(2, insertSet(3, insertSet(4, 0)));
    set u = unionSet(a, b);
    CHECK( memberSet(0, u), "0 in union");
    CHECK( memberSet(1, u), "1 in union");
    CHECK( memberSet(2, u), "2 in union");
    CHECK( memberSet(3, u), "3 in union");
    CHECK( memberSet(4, u), "4 in union");
    CHECK(!memberSet(5, u), "5 not in union");

    printf("\n=== intersectSet ===\n");
    set i = intersectSet(a, b);
    CHECK(!memberSet(0, i), "0 not in intersection");
    CHECK(!memberSet(1, i), "1 not in intersection");
    CHECK( memberSet(2, i), "2 in intersection");
    CHECK(!memberSet(3, i), "3 not in intersection");

    printf("\n=== differenceSet ===\n");
    set diff = differenceSet(a, b);   // a - b
    CHECK( memberSet(0, diff), "0 in a-b");
    CHECK( memberSet(1, diff), "1 in a-b");
    CHECK(!memberSet(2, diff), "2 not in a-b (shared)");
    CHECK(!memberSet(3, diff), "3 not in a-b (only in b)");

    printf("\n=== algebraic identities ===\n");
    set t = insertSet(7, insertSet(13, insertSet(20, 0)));
    CHECK(unionSet(t, 0) == t,                              "t | empty == t");
    CHECK(intersectSet(t, 0) == 0,                          "t & empty == empty");
    CHECK(differenceSet(t, t) == 0,                         "t - t == empty");
    CHECK(unionSet(a, b) == unionSet(b, a),                 "union is commutative");
    CHECK(intersectSet(a, b) == intersectSet(b, a),         "intersection is commutative");

    printf("\n%d passed, %d failed\n", pass, fail);
    return (fail > 0) ? 1 : 0;
}
