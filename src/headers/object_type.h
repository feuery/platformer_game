#ifndef OBJECT_TYPES_H
#define OBJECT_TYPES_H
enum object_type {
  start
 , coinless_block
 , railway_bridge
 , warp_start
 , warp_end
 , coin_block
 , railway_start
 , railway_end
 , railway
 , flashlight_guard
  , finish
};

object_type operator ++ (object_type &type, int) ;
object_type operator -- (object_type &type, int) ;

const char* otype_to_string(object_type t) ;
void otype_to_rgb(object_type& type, int& r, int& g, int& b);

const int UNLIMITED = 9999;
int amount_of_otypes_allowed(object_type type);
    
  
#endif //OBJECT_TYPES_H
