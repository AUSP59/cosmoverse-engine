
#include <tunables/global>
profile cosmoverse flags=(attach_disconnected) {
  #include <abstractions/base>
  file,
  deny network,
  capability,
  /usr/local/bin/cosmoverse ix,
  /usr/local/** r,
}
