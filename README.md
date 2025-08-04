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

#### Ubuntu/Debian
```bash
sudo apt-get install libglfw3-dev libglm-dev libassimp-dev
```

#### Windows (using vcpkg)
```bash
vcpkg install glfw3 glm assimp
```

### Build Instructions

1. Clone the repository:
```bash
git clone <repository-url>
cd skeleton-animation
```

2. Create a build directory:
```bash
mkdir build
cd build
```

3. Configure and build:
```bash
cmake ..
make
```

## Usage

### Running the Application
```bash
./skeleton-animation
```

### Controls
- **Mouse**: Look around (camera rotation)
- **WASD**: Move camera forward/backward/left/right
- **Scroll**: Zoom in/out
- **ESC**: Exit application

### Loading Models
The application can load various 3D model formats. Update the model path in `main.cpp`:

```cpp
// Example model loading
Model model("path/to/your/model.obj", 1);
// or
Model model("path/to/animated/model.dae", 1);
```

### Supported Model Formats
- OBJ (.obj)
- COLLADA (.dae)
- MD5 (.md5mesh)
- FBX (.fbx)
- 3DS (.3ds)
- And other formats supported by Assimp

## Implementation Details

### Animation System
The animation system consists of several key components:

1. **AnimatedModel**: Handles bone data and vertex-bone relationships
2. **Animator**: Manages animation playback and bone transformations
3. **Bone Hierarchy**: Maintains parent-child relationships between bones
4. **Interpolation**: Smooth transitions between keyframes

### Shader Pipeline
- **Vertex Shader**: Handles vertex transformations and bone influences
- **Fragment Shader**: Processes lighting and material properties
- **Model Loading Shaders**: Specialized shaders for model rendering

### Key Features
- **Bone Weight Calculation**: Proper vertex-bone weight assignment
- **Animation Interpolation**: Smooth keyframe interpolation for position, rotation, and scale
- **Hierarchical Transformations**: Correct bone hierarchy traversal
- **Real-time Performance**: Optimized for real-time rendering

## Troubleshooting

### Common Issues

1. **OpenGL Version Error**: Ensure your graphics card supports OpenGL 3.3+
2. **Model Loading Failures**: Check file paths and ensure models are in supported formats
3. **Build Errors**: Verify all dependencies are properly installed
4. **Performance Issues**: Reduce model complexity or optimize shaders

### Debug Information
Enable debug output by setting appropriate flags in your build configuration.

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

## License

This project is open source. Please check individual file headers for specific licensing information.

## Acknowledgments

- **LearnOpenGL**: For OpenGL tutorials and examples
- **Assimp**: For 3D model loading capabilities
- **GLM**: For mathematics utilities
- **GLFW**: For window management

## Future Enhancements

- [ ] Support for multiple animations
- [ ] Animation blending
- [ ] Physics integration
- [ ] GUI for model/animation selection
- [ ] Performance optimizations
- [ ] Additional rendering effects
