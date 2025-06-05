# Integrated Library System

This project is a Qt based application for managing a small library. It was originally built with qmake but now provides a modern **CMake** build system.

## Building

```bash
cmake -S . -B build
cmake --build build
```

The resulting executable is `build/ils`. Pass a custom database path as the first argument or place `ils.sqlite` next to the executable.

```bash
./ils /path/to/ils.sqlite
```
