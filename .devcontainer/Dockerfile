
FROM ubuntu:22.04
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y     build-essential cmake ninja-build clang-format clang-tidy cppcheck     python3 python3-pip doxygen graphviz git pkg-config nodejs npm golang &&     rm -rf /var/lib/apt/lists/*
WORKDIR /work
