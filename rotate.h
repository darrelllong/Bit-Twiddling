#pragma once

#include <stdint.h>

static uint8_t rotL_8(uint8_t, int32_t);

static inline uint8_t rotR_8(uint8_t v, int32_t n) {
  if (n < 0) {
    return rotL_8(v, -n);
  } else {
    n &= 0x07;
    return n ? (uint8_t)((v >> n) | (v << (8 - n))) : v;
  }
}

static inline uint8_t rotL_8(uint8_t v, int32_t n) {
  if (n < 0) {
    return rotR_8(v, -n);
  } else {
    n &= 0x07;
    return n ? (uint8_t)((v << n) | (v >> (8 - n))) : v;
  }
}

static uint16_t rotL_16(uint16_t, int32_t);

static inline uint16_t rotR_16(uint16_t v, int32_t n) {
  if (n < 0) {
    return rotL_16(v, -n);
  } else {
    n &= 0x0f;
    return n ? (uint16_t)((v >> n) | (v << (16 - n))) : v;
  }
}

static inline uint16_t rotL_16(uint16_t v, int32_t n) {
  if (n < 0) {
    return rotR_16(v, -n);
  } else {
    n &= 0x0f;
    return n ? (uint16_t)((v << n) | (v >> (16 - n))) : v;
  }
}

static uint32_t rotL_32(uint32_t, int32_t);

static inline uint32_t rotR_32(uint32_t v, int32_t n) {
  if (n < 0) {
    return rotL_32(v, -n);
  } else {
    n &= 0x1f;
    return n ? (v >> n) | (v << (32 - n)) : v;
  }
}

static inline uint32_t rotL_32(uint32_t v, int32_t n) {
  if (n < 0) {
    return rotR_32(v, -n);
  } else {
    n &= 0x1f;
    return n ? (v << n) | (v >> (32 - n)) : v;
  }
}

static uint64_t rotL_64(uint64_t, int32_t);

static inline uint64_t rotR_64(uint64_t v, int32_t n) {
  if (n < 0) {
    return rotL_64(v, -n);
  } else {
    n &= 0x3f;
    return n ? (v >> n) | (v << (64 - n)) : v;
  }
}

static inline uint64_t rotL_64(uint64_t v, int32_t n) {
  if (n < 0) {
    return rotR_64(v, -n);
  } else {
    n &= 0x3f;
    return n ? (v << n) | (v >> (64 - n)) : v;
  }
}
