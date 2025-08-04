# Makefile for Skeleton Animation Project
# OpenGL, GLFW, GLM, Assimp, GLAD

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 -g

# Target executable name
TARGET = skeleton-animation

# Source files
SOURCES = main.cpp \
          glad.c \
          AnimatedModel.cpp \
          Animator.cpp \
          Model.cpp \
          Mesh.cpp \
          MeshRaw.cpp \
          Shader.cpp \
          util.cpp \
          particle.cpp \
          rawMesh.cpp \
          stb.cpp

# Header files
HEADERS = glad.h \
          AnimatedModel.hpp \
          Animator.hpp \
          Model.hpp \
          Mesh.hpp \
          MeshRaw.hpp \
          Shader.h \
          camera.h \
          util.hpp \
          particle.hpp \
          rawMesh.hpp \
          stb_image.h

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Platform detection
UNAME_S := $(shell uname -s)

# Default libraries (Linux)
LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lassimp -lm

# Platform-specific settings
ifeq ($(UNAME_S),Darwin)
    # macOS
    LIBS = -I/opt/homebrew/include \
    -L/opt/homebrew/lib \
	-lglfw -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -lassimp 
    CXXFLAGS += -D__APPLE__ -DGLM_ENABLE_EXPERIMENTAL
else ifeq ($(OS),Windows_NT)
    # Windows (MinGW)
    LIBS = -lglfw3 -lopengl32 -lgdi32 -lassimp
    CXXFLAGS += -D_WIN32 -DGLM_ENABLE_EXPERIMENTAL
endif

# Include directories
INCLUDES = -I. -I./shaders -I/opt/homebrew/include

# Library directories (adjust paths as needed)
LIBDIRS = 

# Compiler flags for includes and library directories
CXXFLAGS += $(INCLUDES) $(LIBDIRS)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LIBS)

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)

# Clean everything including object files
distclean: clean
	rm -f *.o *.a *.so

# Install dependencies (macOS)
install-deps-macos:
	brew install glfw glm assimp

# Install dependencies (Ubuntu/Debian)
install-deps-ubuntu:
	sudo apt-get update
	sudo apt-get install -y libglfw3-dev libglm-dev libassimp-dev

# Install dependencies (Fedora)
install-deps-fedora:
	sudo dnf install -y glfw-devel glm-devel assimp-devel

# Install dependencies (Arch Linux)
install-deps-arch:
	sudo pacman -S glfw-x11 glm assimp

# Run the application
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CXXFLAGS += -DDEBUG -g3 -O0
debug: $(TARGET)

# Release build
release: CXXFLAGS += -O3 -DNDEBUG
release: $(TARGET)

# Check if all dependencies are available
check-deps:
	@echo "Checking dependencies..."
	@echo "C++ compiler: $(CXX)"
	@$(CXX) --version
	@echo "GLFW:"
	@pkg-config --exists glfw3 && echo "✓ GLFW found" || echo "✗ GLFW not found"
	@echo "Assimp:"
	@pkg-config --exists assimp && echo "✓ Assimp found" || echo "✗ Assimp not found"

# Help target
help:
	@echo "Available targets:"
	@echo "  all              - Build the application (default)"
	@echo "  clean            - Remove object files and executable"
	@echo "  distclean        - Remove all build artifacts"
	@echo "  debug            - Build with debug flags"
	@echo "  release          - Build with optimization flags"
	@echo "  run              - Build and run the application"
	@echo "  check-deps       - Check if dependencies are available"
	@echo "  install-deps-*   - Install dependencies for specific platform"
	@echo "  help             - Show this help message"

# Phony targets
.PHONY: all clean distclean debug release run check-deps help install-deps-macos install-deps-ubuntu install-deps-fedora install-deps-arch

# Dependencies
main.o: main.cpp Model.hpp Shader.h camera.h
AnimatedModel.o: AnimatedModel.cpp AnimatedModel.hpp
Animator.o: Animator.cpp Animator.hpp Model.hpp util.hpp
Model.o: Model.cpp Model.hpp Shader.h Mesh.hpp AnimatedModel.hpp Animator.hpp
Mesh.o: Mesh.cpp Mesh.hpp Shader.h
MeshRaw.o: MeshRaw.cpp MeshRaw.hpp
Shader.o: Shader.cpp Shader.h
util.o: util.cpp util.hpp
particle.o: particle.cpp particle.hpp
rawMesh.o: rawMesh.cpp rawMesh.hpp
stb.o: stb.cpp stb_image.h 