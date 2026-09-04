# StarFall Engine

**StarFall Engine** is a component-based 2D/3D game engine written in
**C++20**. The engine is being developed from the ground up with a focus
on learning how the major systems of a game engine work while keeping
the architecture modular and extensible.

The project also includes a demo game that uses the engine and serves as
a practical example of how its systems and components fit together.

## Features

-   **C++20** codebase
-   **Component-based architecture**
-   **SDL3** for windowing, rendering support, and platform-level
    functionality
-   **FMOD** for audio
-   **Box2D** for 2D physics
-   **RapidJSON** for serialization
-   2D and 3D rendering systems
-   Input handling
-   Audio management
-   Physics and collision systems
-   Resource management
-   Game objects and scenes
-   Texture and font handling
-   Tile map support
-   Particle systems
-   Sprite rendering and animation
-   JSON-based serialization

## Engine Architecture

StarFall Engine is organized around several independent systems. Game
objects can be composed from reusable components rather than requiring
every object to inherit from a large class hierarchy.

A typical object can therefore be built from components such as:

-   Physics components
-   Collider components
-   Renderer components
-   Sprite animation components
-   Other gameplay-specific components

This approach allows different types of game objects to share
functionality without tightly coupling the systems together.

### Core Systems

#### Audio

The audio system provides the engine's interface to **FMOD** and is
responsible for managing audio functionality.

#### Input

The input system handles keyboard and other input state used by the game
and engine.

#### Physics

The physics system contains the engine's physics functionality,
including integration with **Box2D** for 2D physics and the engine's own
collision/physics components.

#### Renderer

The renderer contains the engine's 2D and 3D rendering functionality,
including:

-   Meshes
-   Textures
-   Fonts
-   Text rendering
-   Sprite rendering
-   Sprite animation
-   Particle systems
-   Tile maps
-   3D mesh rendering

#### Serialization

The serialization system uses **RapidJSON** to read and write
engine/game data in JSON format.

#### Resources

The resource system provides centralized management of assets used by
the engine, such as textures and other resources.

## Project Structure

The engine is separated into several directories, with each directory
containing a specific part of the engine.

``` text
Engine/
├── Audio/
│   ├── Audio.cpp
│   └── Audio.h
│
├── Components/
│   ├── Box2DPhysicsComponent.*
│   ├── CircleColliderComponent.*
│   ├── ColliderComponent.h
│   ├── Component.h
│   ├── MeshColliderComponent.*
│   ├── MeshRenderer3DComponent.*
│   ├── PhysicsComponent.*
│   ├── RendererComponent.h
│   ├── RigidBodyPhysicsComponent.*
│   ├── SpriteAnimationRenderer2DComponent.*
│   ├── SpriteAnimator2DRendererComponent.*
│   ├── SpriteRenderer2DComponent.*
│   └── TileMapRendererComponent.*
│
├── Core/
│   ├── Factory.h
│   ├── File.*
│   ├── Random.h
│   ├── Singleton.h
│   ├── StarTime.*
│   └── StringUtils.h
│
├── Framework/
│   ├── Game.*
│   ├── GameObject.*
│   ├── Object.h
│   └── Scene.*
│
├── Input/
│   └── Input.*
│
├── Math/
│   ├── Constants.h
│   └── Structs.*
│
├── Physics/
│   ├── Physics.*
│   └── PhysicsBody.*
│
├── Renderer/
│   ├── Font.*
│   ├── Mesh.h
│   ├── ParticleSystem.*
│   ├── Renderer.*
│   ├── Text.*
│   ├── Texture.*
│   ├── TextureFrames.*
│   └── TileMap.*
│
├── Resources/
│   ├── Resource.*
│   └── ResourceManager.*
│
├── Serialization/
│   ├── Json.*
│   └── Json.h
│
├── StarFallEngine.cpp
├── StarFallEngine.h
├── pch.cpp
├── pch.h
└── README.md
```

The exact implementation is split into `.h` and `.cpp` files where
appropriate; the `*` notation above is only used to keep the structure
readable.

## Components

Components are the primary way functionality is attached to game
objects.

The engine currently contains components for areas such as:

  Component                              Purpose
  -------------------------------------- --------------------------------
  `PhysicsComponent`                     Base physics-related component
  `Box2DPhysicsComponent`                Box2D-based physics
  `RigidBodyPhysicsComponent`            Rigid body behavior
  `ColliderComponent`                    Base collision functionality
  `CircleColliderComponent`              Circular collision geometry
  `MeshColliderComponent`                Mesh-based collision geometry
  `RendererComponent`                    Base renderer component
  `MeshRenderer3DComponent`              3D mesh rendering
  `SpriteRenderer2DComponent`            2D sprite rendering
  `SpriteAnimationRenderer2DComponent`   Animated sprite rendering
  `SpriteAnimator2DRendererComponent`    Sprite animation control
  `TileMapRendererComponent`             Tile map rendering

This list can be expanded as new engine components are added.

## Framework

The framework layer provides the higher-level structures used to build
games with the engine.

Important classes include:

-   `Game`
-   `GameObject`
-   `Object`
-   `Scene`

`Scene` manages the objects that exist in a game world, while
`GameObject` provides the foundation for objects that can be composed
from components.

## Rendering

The renderer supports both 2D and 3D functionality.

Current rendering-related functionality includes:

-   2D sprites
-   Sprite animation
-   Text
-   Fonts
-   Textures
-   Texture frame management
-   Tile maps
-   Particle systems
-   3D meshes
-   3D camera/projection functionality
-   Custom mesh rendering

The engine also contains its own mathematical structures for working
with vectors, matrices, transforms, and other geometry needed for 2D and
3D rendering.

## Physics and Collision

The engine contains both a physics system and collision components.

**Box2D** is used for 2D physics functionality, while the engine also
contains its own collision and geometry code for other collision
scenarios, including mesh-based collision detection.

This separation allows physics simulation and collision detection to be
treated as related but independently reusable systems.

## Serialization

Game and engine data can be serialized using **RapidJSON**.

The serialization layer is located in:

``` text
Serialization/
├── Json.cpp
└── Json.h
```

This system is intended to make it possible to save and load structured
game data without requiring every system to implement its own JSON
handling.

## Resources

Resources are managed through the resource system:

``` text
Resources/
├── Resource.cpp
├── Resource.h
├── ResourceManager.cpp
└── ResourceManager.h
```

The goal of the resource manager is to provide a centralized way for
engine systems to load and reuse assets.

## Demo Game

The repository includes a demo game built using StarFall Engine.

The demo serves two purposes:

1.  It demonstrates how the engine can be used to build an actual game.
2.  It provides a testing environment for developing and debugging
    engine systems.

As the engine develops, the demo game can be used to validate new
rendering, physics, input, audio, and component functionality.

## Dependencies

StarFall Engine currently uses the following external libraries:

  -----------------------------------------------------------------------
  Library                             Purpose
  ----------------------------------- -----------------------------------
  **SDL3**                            Windowing, input/platform
                                      functionality, and rendering
                                      support

  **FMOD**                            Audio

  **Box2D**                           2D physics

  **RapidJSON**                       JSON serialization
  -----------------------------------------------------------------------

The project is written using **C++20**.

## Building

The project is currently developed as a Visual Studio C++ project.

To build the engine:

1.  Open the solution/project in Visual Studio.
2.  Make sure the required third-party dependencies are available to the
    project.
3.  Select the desired configuration and platform.
4.  Build the project.
5.  Run the demo game to test the engine.

> **Note:** Dependency paths and project-specific build configuration
> may need to be adjusted depending on the development environment.

## Design Goals

The primary goal of StarFall Engine is to provide a modular game-engine
architecture while also serving as a learning project for understanding
how game engines work internally.

Areas of development include:

-   Rendering
-   Physics
-   Collision detection
-   Transform and matrix mathematics
-   Resource management
-   Serialization
-   Input
-   Audio
-   Component architecture
-   Scene management
-   Game-object organization

The engine is intentionally built from relatively low-level systems
rather than relying on a complete pre-existing game-engine framework.

## Project Status

StarFall Engine is an **actively developed project**. Systems are
continually being expanded and refactored as new engine functionality is
implemented.

Some parts of the engine may therefore change significantly as
development continues.

## License

No license has currently been specified for this project.
