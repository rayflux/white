# white

My software renderer written in C++, mainly for practicing computer graphics, and, for fun.

## Features (TODO)
- tile based rendering with multithreading for better locality and less overdraw
  - lock-free, every threads work on different memory regions
  - using morton codes (Z-order curve) to organize framebuffer for an even better locality
- WebGPU-ish API with some tweaks tailored for CPU based rendering
- no vertex buffers -- every buffer for rendering is an uniformed 1D array, forcing explicit control
- dedicated shading language WHSL with an embedded bytecode VM, allowing hot reloads
- tolerant for errors like out of bounds, but will provide information for debugging
- load models via WaveFront OBJ format
