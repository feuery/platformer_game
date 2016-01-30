#include <object_type.h>

object_type operator ++ (object_type &type, int) {

  if(finish < type + 1) type = start;
  else type = static_cast<object_type>(type + 1);

  return type;
}

object_type operator -- (object_type &type, int) {

  if(start > type - 1) type = finish;
  else type = static_cast<object_type>(type - 1);

  return type;
}

const char* otype_to_string(object_type t) {
    if (t == start) return "start";
    else if (t == coinless_block) return "coinless_block";
    else if (t == railway_bridge) return "railway_bridge";
    else if (t == warp_start) return "warp_start";
    else if (t == warp_end) return "warp_end";
    else if (t == coin_block) return "coin_block";
    else if (t == railway_start) return "railway_start";
    else if (t == railway_end) return "railway_end";
    else if (t == railway) return "railway";
    else if (t == flashlight_guard) return "flashlight_guard";
    else if (t == finish) return "finish";

    else return "Unknown object_type";
}

void otype_to_rgb(object_type& type, int& r, int& g, int& b) {
  switch (type) {
  case start:
    r = 255;
    break;
  case coinless_block:
    r = g = b = 0;
    break;
  case railway_bridge:
    b = 255;
    break;
  case warp_start:
    g = b = 255;
    break;
  case warp_end:
    b = 255;
    break;
  case coin_block:
    r = 255;
    g = 255;
    break;
  case railway_start:
    b = 255;
    r = g = 128;
    break;
  case railway_end:
    r = 255;
    b = g = 128;
    break;
  case railway:
    g = 255;
    r = b = 128;
    break;
  case flashlight_guard:
    r = g = b = 128;
    break;
  case finish:
    r = 255;
    break;
  }
}

int amount_of_otypes_allowed(object_type type) {
  switch (type) {
  case start:
  case finish:
    return 1;

  default:
    return UNLIMITED;
  }
}
