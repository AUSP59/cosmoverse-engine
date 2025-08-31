
#include "cosmoverse/log.hpp"
#include <sstream>
#include <iostream>

int main(){
  auto& L = cosmoverse::logger();
  L.set_level(cosmoverse::LogLevel::Debug);
  L.log(cosmoverse::LogLevel::Info, "test", "hello");
  L.set_level(cosmoverse::LogLevel::Error);
  // This should not print to stdout for levels below Error
  L.log(cosmoverse::LogLevel::Info, "test", "hidden");
  return 0;
}
