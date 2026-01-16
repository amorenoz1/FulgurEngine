# Game Engine and City Simulator Roadmap

This document outlines the development roadmap for the Fulgur Engine and the city-building game.

## Fulgur Engine Development

### Phase 1: Core Engine Infrastructure

-   [ ] **Core Systems:**
    -   [x] Logging System
    -   [ ] Assertion System
    -   [ ] Memory Management (e.g., custom allocators)
    -   [ ] Basic Math Library (Vectors, Matrices)
-   [ ] **Windowing and Input:**
    -   [ ] Create a platform-agnostic windowing layer (e.g., using GLFW, SDL)
    -   [ ] Handle keyboard, mouse, and controller input
-   [ ] **Rendering Engine (Initial):**
    -   [ ] Abstract rendering API (e.g., to support OpenGL, Vulkan, DirectX)
    -   [ ] Implement an OpenGL renderer as the first backend.
    -   [ ] Basic 2D rendering (sprites, shapes)
    -   [ ] Basic 3D rendering (cubes, simple models)
-   [ ] **Scene and Entity Management:**
    -   [ ] Scene graph or Entity-Component-System (ECS) architecture
    -   [ ] Serialization/Deserialization of scenes and entities

### Phase 2: Advanced Engine Features

-   [ ] **Advanced Rendering:**
    -   [ ] Lighting (Phong, PBR)
    -   [ ] Shadows (Shadow mapping)
    -   [ ] Text rendering
    -   [ ] Model loading (e.g., using Assimp)
    -   [ ] Material system
-   [ ] **Physics Engine:**
    -   [ ] Integrate a physics library (e.g., Bullet, PhysX)
    -   [ ] Collision detection (2D and 3D)
    -   [ ] Rigid body dynamics
-   [ ] **Audio Engine:**
    -   [ ] Abstract audio API
    -   [ ] Sound loading and playback (e.g., using OpenAL, FMOD)
    -   [ ] Spatial audio
-   [ ] **UI System:**
    -   [ ] Basic UI elements (buttons, text boxes, sliders)
    -   [ ] UI layout system
    -   [ ] Integration with the rendering engine

### Phase 3: Tooling and Refinement

-   [ ] **Editor:**
    -   [ ] Scene editor with a viewport
    -   [ ] Entity/Component inspector
    -   [ ] Asset browser
-   [ ] **Scripting:**
    -   [ ] Integrate a scripting language (e.g., Lua, Python)
-   [ ] **Performance and Optimization:**
    -   [ ] Profiling tools
    -   [ ] Multithreading the engine (e.g., render thread, physics thread)

## City Simulator Game Development

### Phase 1: Core Gameplay Loop

-   [ ] **World Representation:**
    -   [ ] Grid-based world for placing buildings and infrastructure
    -   [ ] Basic terrain system (heightmaps)
-   [ ] **Construction:**
    -   [ ] Place roads
    -   [ ] Zone areas (Residential, Commercial, Industrial)
-   [ ] **Simulation (Initial):**
    -   [ ] Basic game loop (day/night cycle)
    -   [ ] Buildings develop in zones
    -   [ ] Basic economy (income from taxes, expenses for services)

### Phase 2: Advanced Simulation

-   [ ] **Infrastructure:**
    -   [ ] Power grid (power plants, transmission lines)
    -   [ ] Water and sewage system
-   [ ] **Services:**
    -   [ ] Police
    -   [ ] Fire department
    -   [ ] Hospitals
    -   [ ] Schools
-   [ ] **Citizen Simulation (Agents):**
    -   [ ] Citizens (Cims) with homes and workplaces
    -   [ ] Traffic simulation (Cims driving to work)
-   [ ] **Economy and Progression:**
    -   [ ] More detailed budget management
    -   [ ] Unlocking new buildings and services based on population/milestones

### Phase 3: Polish and Expansion

-   [ ] **UI/UX:**
    -   [ ] Build menus and information panels
    -   [ ] Data visualizations (e.g., traffic overlays, land value)
-   [ ] **Graphics and Audio:**
    -   [ ] Unique 3D models for buildings
    -   [ ] Ambient city sounds
    -   [ ] Music
-   [ ] **Procedural Generation:**
    -   [ ] Procedural map generation
-   [ ] **Modding Support:**
    -   [ ] Allow users to create and import custom assets
