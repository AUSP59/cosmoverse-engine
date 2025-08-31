FROM ubuntu:24.04 AS build
RUN apt-get update && apt-get install -y --no-install-recommends build-essential cmake git doxygen graphviz && rm -rf /var/lib/apt/lists/*
WORKDIR /src
COPY . .
RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build -j && ctest --test-dir build --output-on-failure
RUN cmake --build build --target package
FROM scratch AS artifact
COPY --from=build /src/build/*.zip /


LABEL org.opencontainers.image.title="COSMOVERSE ENGINE"       org.opencontainers.image.description="Portable C++ library and CLI"       org.opencontainers.image.licenses="Apache-2.0"
