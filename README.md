# Skeleton Animation with OpenGL

A C++ OpenGL application that demonstrates skeleton-based character animation using the Assimp library for 3D model loading and animation playback.

## Features

- **3D Model Loading**: Supports various 3D model formats (OBJ, DAE, MD5, etc.) via Assimp
- **Skeleton Animation**: Implements bone-based character animation with interpolation
- **OpenGL Rendering**: Modern OpenGL 3.3+ with GLSL shaders
- **Camera Controls**: Interactive camera with mouse and keyboard controls
- **Animation Playback**: Real-time animation playback with frame interpolation
- **Bone Transformation**: Proper bone hierarchy and transformation calculations

## Project Structure

```
skeleton-animation/
├── main.cpp                 # Main application entry point
├── AnimatedModel.hpp/cpp    # Animated model class with bone data
├── Animator.hpp/cpp         # Animation playback and interpolation
├── Model.hpp/cpp            # 3D model loading and rendering
├── Mesh.hpp/cpp             # Mesh data structures
├── MeshRaw.hpp/cpp          # Raw mesh processing
├── Shader.h/cpp             # OpenGL shader management
├── camera.h                 # Camera controls and transformations
├── particle.hpp/cpp         # Particle system (if implemented)
├── util.hpp/cpp             # Utility functions
├── stb_image.h              # Image loading library
├── shaders/                 # GLSL shader files
│   ├── vertex.glsl
│   ├── fragment.glsl
│   ├── model_loading_vertex.glsl
│   └── model_loading_frag.glsl
└── README.md
```

## Dependencies

### Required Libraries
- **OpenGL 3.3+**: Modern OpenGL for rendering
- **GLFW**: Window management and input handling
- **GLAD**: OpenGL function loading
- **GLM**: Mathematics library for vectors and matrices
- **Assimp**: 3D model loading and animation processing
- **STB Image**: Image loading utilities

### System Requirements
- C++11 or later compiler
- OpenGL 3.3+ compatible graphics card
- macOS, Linux, or Windows

## Building the Project

### Prerequisites
1. Install a C++ compiler (GCC, Clang, or MSVC)
2. Install CMake (version 3.10 or later)
3. Install required libraries:

#### macOS (using Homebrew)
```bash
brew install glfw glm assimp
```

### Build Instructions

1. Clone the repository:
```bash
git clone <repository-url>
cd skeleton-animation
```
## Usage

### Running the Application
```bash
make run
```

### Controls
- **Mouse**: Look around (camera rotation)
- **WASD**: Move camera forward/backward/left/right
- **Scroll**: Zoom in/out
- **ESC**: Exit application

### Loading Models
The application can load various 3D model formats. Update the model path in `main.cpp`:


### Animation System
The animation system consists of several key components:

1. **AnimatedModel**: Handles bone data and vertex-bone relationships
2. **Animator**: Manages animation playback and bone transformations
3. **Bone Hierarchy**: Maintains parent-child relationships between bones
4. **Interpolation**: Smooth transitions between keyframes



## Future Enhancements

- [ ] Support for multiple animations
- [ ] Animation blending
- [ ] Physics integration
- [ ] GUI for model/animation selection

