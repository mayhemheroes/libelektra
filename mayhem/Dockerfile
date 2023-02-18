FROM ubuntu:22.04 as builder

RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y \
    libaugeas-dev \
    bash \
    bison \
    build-essential \
    cmake \
    curl \
    git \
    libgit2-dev \
    ninja-build \
    sudo \
    libyajl-dev \
    libyaml-cpp-dev \
    clang

ENV ELEKTRA_ROOT=/opt/elektra
ENV ELEKTRA_RELEASE=0.9.9
WORKDIR ${ELEKTRA_ROOT}
COPY . .

ENV PARALLEL=8
RUN mkdir build \
    && cd build \
    && cmake -DPLUGINS="ALL;-date" \
    -DTOOLS="ALL" \
    -DENABLE_DEBUG="OFF" \
    -DENABLE_LOGGER="OFF" \
    -DCMAKE_BUILD_TYPE="Release" \
    -DKDB_DB_SYSTEM='/home/elektra/.config/kdb/system' \
    -DKDB_DB_SPEC='/home/elektra/.config/kdb/spec' \
    -DKDB_DB_HOME='/home/elektra/.config/kdb/home' \
    .. \
    && make -j ${PARALLEL}
RUN clang++ /opt/elektra/mayhem/fuzz_elektraStrip.cpp -fsanitize=fuzzer,address /opt/elektra/build/lib/libelektra-utility.so -o /fuzz

FROM ubuntu:22.04 as package
RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y libgit2-dev build-essential
COPY --from=builder /opt/elektra/build/bin/kdb /
COPY --from=builder /opt/elektra/build/lib /install/lib
COPY --from=builder /fuzz /fuzz_elektraStrip
ENV LD_LIBRARY_PATH=/install/lib