# Use Ubuntu as base image
FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libgtest-dev \
    telnet \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy source files
COPY . .

# Build the project
RUN rm -rf build && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make

# Set working directory to build
WORKDIR /app/build

# Expose Redis port
EXPOSE 6379

# Run the server
CMD ["./mini-redis"] 