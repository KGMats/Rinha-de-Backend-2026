FROM debian:trixie-20260518-slim as build
LABEL Description="Build environment"

WORKDIR /app

SHELL ["/bin/bash", "-c"]

RUN apt-get update && apt-get -y --no-install-recommends install \
    build-essential \
    cmake \
    curl \
    ca-certificates \
    gzip

# Downloading the references file
RUN curl -L --fail \
    https://github.com/zanfranceschi/rinha-de-backend-2026/raw/refs/heads/main/resources/references.json.gz \
    -o /app/references.json.gz

RUN gunzip /app/references.json.gz

# Building the server
COPY src ./src
COPY include ./include
COPY CMakeLists.txt ./CMakeLists.txt

RUN ls .
RUN cat CMakeLists.txt

RUN mkdir build && cmake . -B build -DCMAKE_BUILD_TYPE=Release
RUN cd build && make

# Runtime
FROM debian:trixie-20260518-slim
LABEL Description="Runtime environment"

WORKDIR /app

COPY --from=build /app/build/Rinha2026 /app/

COPY ./build/clusters_index_v2.bin /app
COPY ./build/vectors.bin /app

CMD ["/app/Rinha2026"]
