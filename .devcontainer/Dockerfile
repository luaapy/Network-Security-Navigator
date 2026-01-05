FROM mcr.microsoft.com/vscode/devcontainers/base:ubuntu-22.04

RUN apt-get update && apt-get install -y \
    build-essential \
    autoconf \
    automake \
    libtool \
    libpcap-dev \
    libssl-dev \
    libssh-dev \
    gdb \
    python3 \
    python3-pip

USER vscode
