#ifndef BASIC_TYPES_H
#define BASIC_TYPES_H

#include <efi.h>

/**
 * \brief
 * Represents a rotation by increments of 90 degrees counterclockwise.
 */
typedef INT8 rotation;

#define ZERO_ROTATION ((rotation)0)

/**
 * \brief
 * A two-dimensional integer vector.
 */
typedef struct vec2 {
  INT32 x;
  INT32 y;
} vec2;

#define VEC2(x, y) ((vec2) { .x = (x), .y = (y) })

/**
 * \brief
 * Represents a rectangle by its top-left coordinate and its size.
 */
typedef struct rect {
  INT32 x;
  INT32 y;
  INT32 w;
  INT32 h;
} rect;

/**
 * \brief
 * Adds two vectors together.
 */
vec2 vec2_add(vec2 p, vec2 q);

/**
 * \brief
 * Shifts a rectangle by adding a vector.
 */
rect rect_add(rect r, vec2 p);

/**
 * \brief
 * Negates a vector.
 */
vec2 vec2_flip(vec2 p);

/**
 * \brief
 * Multiplies a vector by a scalar.
 */
vec2 vec2_mult(INT32 k, vec2 p);

/**
 * \brief
 * Adjusts a rotation by 90 degrees clockwise.
 */
rotation rot_inc(rotation r);

/**
 * \brief
 * Adjusts a rotation by 90 degrees counter-clockwise.
 */
rotation rot_dec(rotation r);

/**
 * \brief
 * Applies a rotation to a vector about the origin.
 */
vec2 apply_rotation(rotation r, vec2 p);

/**
 * \brief
 * Rotates the given vector 90 degrees counterclockwise.
 */
vec2 rotate_90_degrees(vec2 p);

#endif
