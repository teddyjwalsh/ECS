# ECS
Basic Entity Component System game engine.

The goal of this project is to explore the development of a modular, fast, entity-component system game engine. There are a couple key things I wanted to accomplish with this engine that solve issues that I have run into with previous engines.

1. A strict, established design philosophy to guide decisions in a way that is somewhat already trusted by the industry
2. A design that lends itself to networking and ease of conversion to net-capable projects
3. Performant enough for intensive voxel game designs

These three things are what led to the decision of using the established ECS architecture. The inspiration for how I approached the fundamental design decisions came from a GDC talk by one of the lead Overwatch (a popular shooting game) developers: https://www.youtube.com/watch?v=W3aieHjyNvw.
I really liked the strictness of their abstraction of systems as well as the strictness of their separation of data and function. 

With these considerations, I created the framework out of a few basic constructs.

### Entity
The entity is the fundamental game object. It is a simple collection of components and isn't intended to have any behavior and cannot be inherited from. It is basically an identifier and an association with component data.
C++ Implementation: entity.h, class Entity

### Component
The component is the unit of data that the engine operates on. It is the smallest unit of data that the base engine is aware of and is what the user of the engine builds their data model from. To the user, it should conceptually just be a struct. However in practice, the Component class also provides an interface for systems to find sibling (same type) components.
C++ Implementation: component.h, class Component

### Component Array
The component array is the way the engine stores components and is a data interface for Systems (description below). The component array is intended to provide contiguous storage for each type of component as well as provide an iterable interface for the Systems to use data.
C++ Implementation: component_array.h, class ComponentArray

### System
The System is the model through which all game behavior is defined. The system should be, essentially, as a black box, outwardly stateless. It must access data through Components and Component Arrays.
C++ Implementation: system.h, class System

### Component Manager
The Component Manager is what ties everything together. It allocates memory for components, runs systems, and currently provides the basic interface for starting and running the game.
C++ Implementation: component_manager.h, class ComponentManager

Upon this basic framework, some basic common helper classes are build including user input, graphics (using my ugli library), player, and voxel systems/components are implemented.
