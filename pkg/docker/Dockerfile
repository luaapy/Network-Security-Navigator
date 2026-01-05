# NSN (Network Security Navigator) Dockerfile
# Based on Ubuntu for a full featured environment

FROM ubuntu:22.04 AS builder

# Prevent interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install build dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    autoconf \
    automake \
    libtool \
    libpcap-dev \
    libssl-dev \
    libssh-dev \
    git \
    python3 \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy source code
COPY . .

# Build NSN
RUN ./scripts/build.sh

# Production stage
FROM ubuntu:22.04

# Install runtime dependencies
RUN apt-get update && apt-get install -y \
    libpcap0.8 \
    libssl3 \
    libssh-4 \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Copy binary from builder
COPY --from=builder /app/nsn /usr/local/bin/nsn
COPY --from=builder /app/Lib /usr/local/lib/nsn

# Set NSN_PATH to include standard library
ENV NSN_PATH=/usr/local/lib/nsn

# Default command
ENTRYPOINT ["nsn"]
CMD ["--version"]
