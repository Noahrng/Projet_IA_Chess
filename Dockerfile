FROM ubuntu:22.04

# Evite les prompts interactifs
ENV DEBIAN_FRONTEND=noninteractive

# Installer dépendances
RUN apt update && apt install -y \
    build-essential \
    valgrind \
    cmake \
    git \
    libgl1-mesa-dev \
    libx11-dev \
    libxcursor-dev \
    libxrandr-dev \
    libxi-dev \
    libasound2-dev \
    libpulse-dev \
    libudev-dev \
    libxinerama-dev

# Installer Raylib
RUN git clone https://github.com/raysan5/raylib.git \
    && cd raylib/src \
    && make PLATFORM=PLATFORM_DESKTOP \
    && make install

# Dossier de travail
WORKDIR /app

# Copier tout le projet
COPY . .

# Compiler
RUN make clean
RUN make

CMD ["./build/AICHESS"]
