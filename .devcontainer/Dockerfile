FROM debian:12.10-slim as build-base

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    git\
    ninja-build\
    cmake\
    build-essential\
    ca-certificates\
    python3

FROM build-base as llvm-build
ARG LLVM_VERSION=20.1.3

WORKDIR /tmp
RUN git clone https://github.com/llvm/llvm-project.git &&\
    cd llvm-project &&\
    git checkout llvmorg-${LLVM_VERSION}
RUN cd llvm-project &&\
    cmake -G Ninja -S llvm -B build -DLLVM_ENABLE_PROJECTS="clang;lld;clang-tools-extra" -DCMAKE_BUILD_TYPE=Release &&\
    cmake --build build --parallel
RUN cd llvm-project &&\
    cmake --install build --prefix /opt/llvm

FROM build-base as cmake-build
ARG CMAKE_VERSION=4.0.1

RUN git clone https://gitlab.kitware.com/cmake/cmake.git &&\
    cd cmake &&\
    git checkout v${CMAKE_VERSION}
RUN apt-get install -y --no-install-recommends \
    libssl-dev
RUN cd cmake &&\
    ./bootstrap --prefix=/opt/cmake &&\
    make -j$(nproc) &&\
    make install

FROM build-base as gcc-build
ARG GCC_VERSION=15.1.0

RUN apt-get install -y --no-install-recommends \
    wget \
    tar \
    gzip

WORKDIR /tmp
RUN wget https://ftp.fu-berlin.de/unix/languages/gcc/releases/gcc-${GCC_VERSION}/gcc-${GCC_VERSION}.tar.gz &&\
    tar xzf gcc-${GCC_VERSION}.tar.gz &&\
    cd gcc-${GCC_VERSION} &&\
    ./contrib/download_prerequisites &&\
    cd .. &&\
    mkdir build &&\
    cd build
RUN apt-get update && \
    apt-get install -y --no-install-recommends\
        libc6-dev\
        linux-headers-amd64\
        gawk\
        libstdc++-12-dev\
        gcc-12
RUN cd build &&\
    $PWD/../gcc-${GCC_VERSION}/configure \
        --prefix=/opt/gcc \
        --host=x86_64-pc-linux-gnu \
        --enable-languages=c,c++\
        --disable-multilib\
        --disable-libada \
        &&\
    make -j6 &&\
    make install

FROM debian:12.10-slim  as final

COPY --from=gcc-build /opt/gcc /usr
COPY --from=llvm-build /opt/llvm /usr
COPY --from=cmake-build /opt/cmake /usr

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    git\
    ninja-build\
    cmake\
    build-essential\
    ca-certificates\
    python3 \
    gdb\
    python3-pip \
    python3-venv
    
RUN update-alternatives --install /usr/bin/cc cc /usr/bin/clang 100 &&\
    update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++ 100 

ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Create the user
RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME -s /bin/bash\
    && apt-get update \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME

USER $USERNAME
WORKDIR /home/${USERNAME}

RUN python3 -m venv .venv &&\
    source .venv/bin/activate &&\
    pip install conan

ENV LD_LIBRARY_PATH=/usr/lib64/:$LD_LIBRARY_PATH