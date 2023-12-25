# Use a smaller, more specific base image
FROM ubuntu:22.04

# Avoid warnings by switching to noninteractive
ENV DEBIAN_FRONTEND=noninteractive

# Configure shell
SHELL ["/bin/bash", "-c"]

# Install dependencies in a single RUN layer to reduce image layers
RUN apt-get update && apt-get install -y --no-install-recommends \
    autoconf \
    autopoint \
    bash-completion \
    build-essential \
    ca-certificates \
    clang \
    cmake \
    cppcheck \
    curl \
    gdb \
    git \
    libtool \
    lldb \
    llvm \
    pkg-config \
    python3 \
    ninja-build \
    ssh \
    sudo \
    tar \
    unzip \
    valgrind \
    zip \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

# Set environment variables for vcpkg
ENV VCPKG_ROOT=/usr/local/vcpkg \
    VCPKG_DOWNLOADS=/usr/local/vcpkg-downloads \
    VCPKG_FORCE_SYSTEM_BINARIES=1
ENV PATH="${PATH}:${VCPKG_ROOT}"

# Install vcpkg
RUN git clone -b 2023.12.12 --depth 1 https://github.com/Microsoft/vcpkg.git $VCPKG_ROOT && \
    mkdir -p $VCPKG_DOWNLOADS && \
    $VCPKG_ROOT/bootstrap-vcpkg.sh -disableMetrics

# Install emsdk
ENV EMSDK=/usr/local/emsdk
ENV EMSDK_NODE=$EMSDK/node/16.20.0_64bit/bin/node
RUN git clone -b 3.1.47 --depth 1 https://github.com/emscripten-core/emsdk.git $EMSDK && \
    $EMSDK/emsdk install 3.1.47 && \
    $EMSDK/emsdk activate 3.1.47
# This emulates what source ./emsdk_env.sh does.
ENV PATH="${EMSDK}:${EMSDK}/upstream/emscripten:${EMSDK_NODE}:${PATH}"

# Create a non-root user
ARG USERNAME=ubuntu
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME \
    && chsh -s /bin/bash $USERNAME \
    && chown -R $USERNAME:$USERNAME $VCPKG_ROOT $VCPKG_DOWNLOADS $EMSDK

# Switch back to dialog for any ad-hoc use of apt-get
ENV DEBIAN_FRONTEND=dialog

