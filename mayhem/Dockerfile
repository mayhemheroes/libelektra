FROM alpine:3.15.0 as builder

RUN apk update \
    && apk add --no-cache --upgrade\
    augeas \
    augeas-dev \
    bash \
    bison \
    build-base \
    cmake \
    curl \
    git \
    libgit2 \
    libgit2-dev \
    ninja \
    sudo \
    yajl \
    yajl-dev \
    yaml-cpp \
    yaml-cpp-dev

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
FROM alpine:3.15.0 as package
RUN apk update \
    && apk add --no-cache --upgrade\
    build-base libgit2
COPY --from=builder /opt/elektra/build/bin/kdb /
COPY --from=builder /opt/elektra/build/lib /install/lib
ENV LD_LIBRARY_PATH=/install/lib