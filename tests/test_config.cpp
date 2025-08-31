// SPDX-License-Identifier: Apache-2.0
#include "cosmoverse/config.hpp"
#include <cassert>
#include <fstream>
int main(){const char* p="tmp.ini"; std::ofstream o(p); o<<"[s]\nk=v\n"; cosmoverse::Config c; assert(c.load_file(p)); auto v=c.get("s.k"); assert(v && *v=="v"); std::remove(p); return 0;}
