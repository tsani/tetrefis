#include "basic_types.h"

rotation const ZERO_ROTATION = 0;

vec2 vec2_add(vec2 p, vec2 q) {
  return (vec2) { p.x + q.x, p.y + q.y };
}

rect rect_add(rect r, vec2 p) {
  return (rect) { r.x + p.x, r.y + p.y, r.w, r.h };
}

vec2 vec2_flip(vec2 p) {
  return (vec2) { -p.x, -p.y };
}

vec2 vec2_mult(INT32 k, vec2 p) {
  return (vec2) { k * p.x, k * p.y };
}

rotation rot_inc(rotation r) {
  return (r + 1) % 4;
}

rotation rot_dec(rotation r) {
  return r == 0 ? 3 : r - 1;
}

vec2 apply_rotation(rotation r, vec2 p) {
  while(r-->0)
    p = rotate_90_degrees(p);
  return p;
}

vec2 rotate_90_degrees(vec2 p) {
  return (vec2) { -p.y, p.x };
}
