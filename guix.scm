(use-modules (guix packages)
             (guix profiles)
             (guix download)
             (guix build-system cmake)
             (gnu packages base)
             (gnu packages commencement)
             (gnu packages cmake)
             (gnu packages valgrind)
             (gnu packages gl)
             (gnu packages xorg)
             (gnu packages audio)
             (gnu packages pulseaudio)
             (gnu packages linux)
             (gnu packages pkg-config))

;; Définition manuelle de raylib
(define raylib
  (package
    (name "raylib")
    (version "5.0")
    (source
      (origin
        (method url-fetch)
        (uri "https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz")
        (sha256
          (base32 "10ilg74qpy9crb22klywxf831v57l7p3wm2f9shl171axawlkw4q"))))
    (build-system cmake-build-system)
    (arguments
      '(#:configure-flags
        (list "-DBUILD_SHARED_LIBS=ON"
              "-DPLATFORM=Desktop")))
    (inputs
      (list mesa libx11 libxcursor libxrandr libxi libxinerama))
    (synopsis "Simple game programming library")
    (description "Raylib game programming library")
    (license #f)
    (home-page "https://raylib.com")))

(packages->manifest
  (list
    gcc-toolchain
    cmake
    gnu-make
    pkg-config
    valgrind
    raylib
    mesa
    libx11
    libxcursor
    libxrandr
    libxi
    libxinerama
    libxext
    libxxf86vm
    alsa-lib
    pulseaudio
    eudev))