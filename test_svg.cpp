#include "svg.h"
#include <cassert>

test_empty_bin(){
string shade;
size_t color = 111;
size_t max_count = 100;
shade=color_choice(color,max_count,0);
assert(shade == "#999");
}
test_max_count(){
string shade;
size_t color = 111;
size_t max_count = 100;
shade=color_choice(color,max_count,100);
assert(shade == "#111");
}


int main(){
    test_empty_bin();
    test_max_count();
}
