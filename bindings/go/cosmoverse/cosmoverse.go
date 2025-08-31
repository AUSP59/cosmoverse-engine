
// SPDX-License-Identifier: Apache-2.0
package cosmoverse
/*
#cgo CFLAGS: -I../../include
#cgo LDFLAGS: -lcosmoverse
#include "cosmoverse/c_api.h"
#include <stdlib.h>
*/
import "C"
import "unsafe"

func Version() string {
  return C.GoString(C.cosmoverse_version_c())
}
func FNV1a64(b []byte) uint64 {
  if len(b)==0 { return 0 }
  return uint64(C.cosmoverse_fnv1a64_c((*C.char)(unsafe.Pointer(&b[0])), C.size_t(len(b))))
}
