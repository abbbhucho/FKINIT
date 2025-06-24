# Use the official Ubuntu 22.04 as the base image
FROM ubuntu:22.04

# Set the DEBIAN_FRONTEND to noninteractive to prevent prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Update the package list and install the specified dependencies in a single layer
# This is a common practice for creating development or build environments.
RUN apt-get update && apt-get install -y \
    build-essential \
    curl \
    vim \
    sudo \
    libssl-dev \
    bison \
    flex \
    libdb-dev \
    libedit-dev \
    libncurses5-dev \
    libldap2-dev \
    libsasl2-dev \
    libkeyutils-dev \
    libpam0g-dev \
    chrpath \
    pkg-config \
    python3 \
    python3-pip \
    autoconf \
    automake \
    locales \
    tzdata \
    net-tools \
    # Clean up the apt cache to reduce the final image size
    && rm -rf /var/lib/apt/lists/*

# Set a working directory inside the container
WORKDIR /app

# The default command to execute when the container starts.
# Here, we start a bash shell.
CMD ["/bin/bash"]