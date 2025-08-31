#include "cosmoverse/c_api.h"
#include <assert.h>
#include <string.h>
int main(){ const char* v = cosmoverse_version_c(); assert(v && strlen(v)>0); unsigned long long h=cosmoverse_fnv1a64_c("abc",3); assert(h==cosmoverse_fnv1a64_c("abc",3)); return 0; }
