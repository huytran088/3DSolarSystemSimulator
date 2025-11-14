# Solar System Simulator - 3D Game Engine

A custom C++ game engine featuring an interactive 3D solar system simulation with a flyable UFO spaceship and moon-stealing mechanics.

![Build Status](https://github.com/huytran088/3DSolarSystemSimulator/actions/workflows/ci.yml/badge.svg)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux-blue)
![OpenGL](https://img.shields.io/badge/OpenGL-4.5-green)
![C++](https://img.shields.io/badge/C%2B%2B-17-orange)

## Features

- **Interactive Solar System**: Navigate through a simulated solar system featuring:
  - The Sun (with dynamic lighting)
  - Earth and its Moon
  - Mars with Phobos and Deimos
  - Venus
- **Flyable UFO Spaceship**: Control a Low-poly UFO with waypoint-based navigation between planets
- **Moon Stealing Mechanic**: Capture moons by proximity - fly close to moons to make them orbit your spaceship
- **3D Positional Audio**: Each celestial body emits unique sounds that change based on your position
- **Multiple Camera Views**:
  - Overhead view of the solar system
  - Ship-mounted camera for first-person perspective
- **Component-Based Architecture**: Modular game engine design with reusable components
- **Modern OpenGL Rendering**: Uses OpenGL 4.5 with custom GLSL shaders for per-pixel lighting

## Controls

| Key | Action |
|-----|--------|
| `W` / `S` | Move forward / backward |
| `A` / `D` | Strafe left / right |
| Arrow Keys | Rotate camera / steer ship |
| `Space` | Navigate to next waypoint |
| `C` | Toggle component visibility (customizable) |

*Note: Exact controls may vary based on game configuration in MyGame.h*

## Technical Stack

### Core Technologies
- **Language**: C++ (Visual Studio 2022, Platform Toolset v143)
- **Graphics**: OpenGL 4.5 with GLSL shaders
- **Audio**: OpenAL for 3D positional audio
- **Math**: GLM (OpenGL Mathematics) library

### External Dependencies
- **GLFW 3**: Window management and input handling
- **GLEW**: OpenGL extension loading
- **GLM**: Vector and matrix mathematics
- **OpenAL**: 3D audio engine
- **ALUT**: OpenAL Utility Toolkit
- **Assimp**: 3D model loading (.obj, .3ds, .fbx formats)

## CI/CD Pipeline

This project includes automated CI/CD workflows that build and test the project on multiple platforms:

### Supported Build Environments

- **Windows with Visual Studio 2022**: Builds both x86 and x64 configurations (Debug and Release)
- **Linux/WSL2**: Ubuntu-based builds compatible with WSL2 environments (Debug and Release)

### Automated Builds

The CI/CD pipeline automatically runs on:
- Push to `main`, `master`, `develop` branches, or any branch starting with `claude/`
- Pull requests to `main`, `master`, or `develop` branches
- Manual workflow dispatch

### Build Artifacts

After each successful build, compiled binaries are available as downloadable artifacts:
- `SolarSystem-x64-Debug` / `SolarSystem-x64-Release` (Windows 64-bit)
- `SolarSystem-Win32-Debug` / `SolarSystem-Win32-Release` (Windows 32-bit)
- `SolarSystem-Linux-Debug` / `SolarSystem-Linux-Release` (Linux/WSL2)

Artifacts are retained for 30 days.

### Dependencies Management

The pipeline uses vcpkg for automated dependency management, ensuring consistent builds across all environments. All dependencies from `vcpkg.json` are automatically installed during the build process.

## Building the Project

### Prerequisites

**System Requirements:**
- Windows 10 or later
- Visual Studio 2022 or later
- OpenGL 4.5 compatible graphics card (2014 or newer)
- Audio output device

**Install Dependencies using vcpkg (Recommended):**

```bash
# Install vcpkg if you haven't already
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat

# Install dependencies
./vcpkg install glfw3:x64-windows
./vcpkg install glew:x64-windows
./vcpkg install glm:x64-windows
./vcpkg install openal-soft:x64-windows
./vcpkg install assimp:x64-windows

# Integrate with Visual Studio
./vcpkg integrate install
```

**Manual Installation:**
If you prefer manual installation, download and install each library, then configure the include and library paths in Visual Studio project settings.

### Build Steps

1. **Clone the repository:**
   ```bash
   git clone <repository-url>
   cd tranquhProject3
   ```

2. **Open the solution:**
   - Open `tranquhProject3.sln` in Visual Studio 2022

3. **Configure build:**
   - Select your build configuration (Debug or Release)
   - Select platform (x86 or x64)

4. **Build:**
   - Press `F7` or Build > Build Solution

5. **Run:**
   - Press `F5` or Debug > Start Debugging

### Build Cleanup

To clean build artifacts:
```bash
clean.bat
```

## Project Structure

```
tranquhProject3/
├── GameEngine/              # Main source code
│   ├── *.h                  # Header files (40 files)
│   ├── *.cpp                # Implementation files (38 files)
│   ├── main.cpp             # Application entry point
│   ├── MyGame.h             # Main game scene setup
│   ├── Shaders/             # GLSL shader files
│   │   ├── vertexShader.glsl
│   │   ├── fragmentShader.glsl
│   │   └── perPixelLightingfragmentShader.glsl
│   ├── Textures/            # Planet and object textures (2K resolution)
│   ├── Sounds/              # Audio files (WAV format, MONO required for 3D audio)
│   └── My_object/           # 3D models (.obj, .mtl, textures)
├── README.md                # This file
├── clean.bat                # Build cleanup script
└── tranquhProject3.sln      # Visual Studio solution
```

## Architecture

### Component System
The engine uses a component-based entity system with the following key components:

**Base Classes:**
- `GameObject`: Base entity class
- `Component`: Base component class
- `SceneGraphNode`: Hierarchical transformation system

**Component Categories:**
- **Mesh Components**: BoxMesh, SphereMesh, CylinderMesh, ModelMesh
- **Movement Components**: SpaceTravel, Reparent, Spin, Steer, Waypoint
- **Lighting Components**: Positional, Directional, Spotlight
- **Camera Component**: Multi-viewport support
- **Sound Components**: SoundSource, SoundListener

### Rendering Pipeline
1. Scene graph traversal for hierarchical transformations
2. Shared uniform blocks for materials, transformations, and lighting
3. Per-pixel lighting using GLSL 4.5 shaders
4. Multi-light support (positional, directional, spotlights)

## Assets

### Textures
High-quality 2K resolution planet textures:
- Sun, Earth, Mars, Venus, Moon, Phobos

### 3D Models
- Low-poly UFO model with diffuse, normal, specular, and glow maps
- F-15C Eagle jet model (alternative ship option)

### Audio Files
**Important**: Current audio files include copyrighted music. For distribution, replace with royalty-free alternatives:
- ambient.wav
- space.wav/mp3

## Known Issues

1. **Large Binary Files**: Project contains ~293MB of assets (textures, models, sounds). Consider using Git LFS for better repository management.

2. **Audio Copyright**: Some audio files are copyrighted music. Replace with royalty-free audio for legal distribution.

3. **OpenAL Configuration**: You may need to modify OpenAL include paths depending on your installation. See `SoundEngine.h` lines 10-13 for details.

4. **Platform Support**: Currently Windows-only. Cross-platform support would require CMake build system.

## Development Notes

### Recent Changes
- **2023-10-16**: Updated README
- **2022-11-13**: Changed spaceship model to Low-poly UFO
- **2022-11-12**: Added ReparentComponent for moon-stealing mechanic
- **2022-11-12**: Implemented waypoint navigation system

### Code Quality Improvements
This update (2025-11-14) includes:
- Fixed duplicate file issues (CylinderMeshComponent typo)
- Corrected MakeVisableComponent → MakeVisibleComponent
- Added comprehensive documentation
- Added dependency management support

## Contributing

Contributions are welcome! Please ensure:
- Code follows existing style conventions
- New features include appropriate components
- Shaders are compatible with OpenGL 4.5
- Audio files are MONO format for 3D audio support

## License

This project uses MIT license. Please check the License page for more details.

## Acknowledgments

- Planet textures from [Source to be documented]
- 3D models: Low-poly UFO, F-15C Eagle
- Audio: [Replace with royalty-free sources]

## Contact

For questions or issues, please open an issue on the repository.

---

**Last Updated**: November 2025
**Engine Version**: 1.0.0
**OpenGL Version**: 4.5
