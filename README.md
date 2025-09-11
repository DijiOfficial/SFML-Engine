# <ins>**SFML Engine**</ins>

**My SFML Engine is a lightweight C++ engine built with [SFML (Simple and Fast Multimedia Library)](https://www.sfml-dev.org), implemented following the C++ Core Guidelines.**

# <ins>**Overview**</ins>

This Engine is built on the foundation of my [**Diji-Engine**](https://github.com/DijiOfficial/Diji-Engine), using [**SFML**](https://www.sfml-dev.org) over [**SDL**](https://github.com/libsdl-org/SDL). The goal is to deepen my understanding of programming, software architecture, game engine design, and to improve development practices by exploring a new multimedia library.
While inspired by both Unity and Unreal Engine, this engine is tailored for my use case, focusing on a more streamlined yet expandable system architecture with a cleaner pipeline and more robust internal systems than its predecessor.

# <ins>**Contents**</ins>

- [**The Engine**](#the-engine)
    - [**SDL to SFML**](#sdl-to-sfml)
    	- [**Resource Manager**](#resource-manager)
     	- [**Renderer & Render Component**](#renderer--render-component)
      	- [**Why SFML**](#why-sfml)
	- [**Improvements & Additions**](#improvements--additions)
      	- [**Engine Pipeline**](#engine-pipeline)
      		- [**Engine Optimizations**](#engine-optimizations)
    	- [**Pause Singleton**](#pause-singleton) 
    	- [**GameObjects**](#gameobjects) 
    	- [**RandNumber Helper**](#randnumber-helper) 
    	- [**Input Manager**](#input-manager) 
    	- [**Event System**](#event-system) 
    	- [**Timers**](#timers) 
    	- [**Camera**](#camera) 
    	- [**RectRender**](#rectrender) 
    	- [**Score Counter**](#score-counter) 
    	- [**Transform**](#transform) 
    	- [**Scene & Scene Manager**](#scene--scene-manager) 
    - [**Future Improvements & Todo's**](#future-improvements--todos)
  - [**Conclusion**](#conclusion)
    - [**References**](#references) 

# <ins>**The Engine**</ins>

In this section, I will cover the changes and improvements over my [**Diji-Engine**](https://github.com/DijiOfficial/Diji-Engine). I won’t be going over all the features or programming patterns this time, for that please refer to the [**Diji-Engine README**](https://github.com/DijiOfficial/Diji-Engine).

Instead, I’ll focus on the transition from [**SDL**](https://github.com/libsdl-org/SDL) to [**SFML**](https://www.sfml-dev.org), the differences that arose from it, and give an extensive breakdown of improvements made, along with the future improvements I plan to implement.

## <ins>**SDL to SFML**</ins>

The switch from [**SDL**](https://github.com/libsdl-org/SDL) to [**SFML**](https://www.sfml-dev.org) introduced significant yet manageable changes. [**SDL**](https://github.com/libsdl-org/SDL) is a low-level, C-style library prioritizing portability, while [**SFML**](https://www.sfml-dev.org) provides a more modern, object-oriented C++ API. As a result, many abstractions previously implemented manually (e.g., RAII wrappers) became redundant. Which in turn made the port quite managebale.

The most notable differences relate to rendering and resource management.

### <ins>**Resource Manager**</ins>

In [**SDL**](https://github.com/libsdl-org/SDL), resource handling required manual memory management and custom RAII wrappers to encapsulate the resources. [**SFML**](https://www.sfml-dev.org) eliminates that need by managing its own resources (e.g., textures, fonts) internally. thus the logic behind the manager remained largely unchanged. 

### <ins>**Renderer & Render Component**</ins>

Rendering is now handled via `sf::RenderWindow`. [**SFML**](https://www.sfml-dev.org) also supports `sf::VertexArray`, enabling more advanced rendering operations. This laid the groundwork for introducing a Sprite Component capable of computing vertex arrays from sprite sheets.

The Render Component has also been adapted to leverage [**SFML's**](https://www.sfml-dev.org) resource management, removing the need for manual wrappers.

### <ins>**Why SFML**</ins>

Changing library is more than just swapping APIs. It's an exercise in **problem-solving**, and learning to manage **wide-reaching changes** across a codebase. 
Migrating the engine involved rethinking abstractions, understanding dependencies and core concepts that have grown around the old library. It also exposed areas where the engine could be made more modular, decoupled, and maintainable.
Where core systems had to be adapted, it was also updated and improved turning the challenge into a valuable engine development milestone rather than just a technical challenge. 
And for all of that, [**SFML**](https://www.sfml-dev.org)  was a perfect fit. A very different, yet in many ways similar library. It offers a clean, intuitive API and is overall a great tool for 2D game development. 

## <ins>**Improvements & Additions**</ins>

With the library changes out of the way let's get into the **improvenets and additions** to the engine.

### <ins>**Engine Pipeline**</ins>

The first major changes come in the form of the **engine pipeline**. While keeping the pipeline simple was the main objective in my first engine, it quickly became clear that many workarounds were needed for more complex games. 
To address this, the pipeline saw the addition of `Start` and `OnDestroy`, while components gained `OnEnable` and `OnDisable` methods for entry and exit logic. These are not yet fully integrated into the pipeline and GameObjects, but currently serve as helpers, marked for full inclusion in a [future update](future-improvements--todos).
The pipeline also saw changes in the form of an `EndFrameUpdate`, moving scene handling and cleanup to the end of the frame. Along with an expansion of the render pipeline, HUDs are now drawn later in the frame, after the rest of the game content.

For reference, here’s the previous pipeline:

![Picture of the Pipeline](https://github.com/DijiOfficial/Diji-Engine/blob/master/GitHubAssets/Pipeline.png)

And the current pipeline:

![Picture of the Pipeline](https://github.com/DijiOfficial/SFML-Engine/blob/main/GithubAssets/PipelineSFML.png)

While it’s not shown in the diagram, part of loading a new scene involves calling both `Init` and `Start`. Similarly, when destroying objects at the end of the frame, `OnDestroy` is called.

The pipeline has been expanded across nearly all fronts, but we can still see `FixedUpdate` lagging behind. One of the [future improvements](future-improvements--todos) will include an expansion of the physics system through the `FixedUpdate` cycle.

#### <ins>**Engine Optimizations**</ins>

`VIEWPORT` and `Window` are now global static variables, allowing access from anywhere in the codebase. This prevents the need to repeatedly pass references down through the hierarchy and helps keep the code more maintainable. 
Although I'm aware that giving global access to the window can lead to issues, this can be [improved in the future](future-improvements--todos) by wrapping the window pointer in a wrapper class.

### <ins>**Pause Singleton**</ins>

A Pause Singleton has been added, allowing the player to easily pause or unpause the game as needed. This feature is still in its early stages. See the [Improvements & Todos](future-improvements--todos) section for how it may be expanded in the future.

### <ins>**GameObjects**</ins>

`OnEnable` and `OnDisable` methods have been added to GameObjects. While these are not yet fully supported within the engine lifecycle, they can be used independently within the GameObject hierarchy.

GameObjects can now also be **duplicated**, with a memory footprint of their creation used as a blueprint for instantiating duplicated assets. This works both at **compile time** and **runtime**.

### <ins>**RandNumber Helper**</ins>

Introduced a static `RandomNumber` helper class with **thread safety**, capable of generating both `int` and `float` random numbers given a `min` and `max` value.

### <ins>**Input Manager**</ins>

The Input Manager saw **major improvements** over the original version. It now supports proper `HELD`, `PRESSED`, and `RELEASED` states for keys using **unordered maps**.

Mouse movement and mouse button support have also been added, implemented using templates for flexibility.

The call to the associated command has been optimized using a hash map, reducing lookup time from **O(n)** to** O(1)**:

![image of hash map optimization](https://github.com/DijiOfficial/SFML-Engine/blob/main/GithubAssets/inputHashMap.png)

If you're interested in how this work strap in because there is some witchraft at play here.

The first part of this puzzle is the `CommandKey` struct, combining a `KeyState` and `Input::InputType` to map a desired input to a command.<br>
We then hash both the `KeyState` and `Input::InputType` and XOR `h1` and `h2` (shifted left by 1) for an O(1) lookup time of the command.<br>
To hash the `KeyState` we turn it into an `int` from an enum class and use standard `int` hash `std::hash<int>`.<br>
Now to hash the input type it's a bit more complicated.	The `InputType` is a variant holding multiple types. `typedef std::variant<sf::Keyboard::Scancode, sf::Mouse::Button, Controller::Button> InputType;`.<br>
We want to hash the type but we don't know what it is, so we use `std::visit` which is some new fuckery that allows you to pass to a callback the type of the `std::variant`. So far so good?<br>
We then pass a lambda with a `size_t` return type because that's what we want to end up with. We then forward the `k.input` to the lambda, you might ask why forward it when you're hashing it anyways? Because I can and it works and I ain't touching it.<br>
With the input forwarded we then `std::decay_t` to remove any reference or qualifiers we want the "raw type" so to speak. we then cast that into it's underlying type using `std::underlying_type_t<>`. For example if we have an `enum class` it's underlying type would be an `int`. Well now that we have that, we do the same to pass it to the hash function and voila.

Templates are amazing aren't they?

### <ins>**Event System**</ins>

The original **Observer/Listener pattern** has been completely removed and replaced by an **event system** inspired by [**Unreal Engine's approach**](https://dev.epicgames.com/documentation/en-us/unreal-engine/custom-events-in-unreal-engine).

Now, all components have access to:
- Creating events
- Subscribing to events
- Passing data through events using templates

This new system is a very close replica of Unreal’s and brings massive improvements allowing me to simplify the code while keeping it clean and decoupled.

A significant step forward from the original engine:

![image of the event system](https://github.com/DijiOfficial/SFML-Engine/blob/main/GithubAssets/EventSystemCallback.png)

We can now create `Events`

```c++
	// Creating events
	diji::Event<> OnDeathEvent;
	diji::Event<int> OnHealthChangeEvent;

	// Broadcasting the event
	if (m_CurrentHealth <= 0)
    {
        OnDeathEvent.Broadcast();
        return true;
    }

	// Listening to the event when creating the scene
	player->GetComponent<zombieArena::Player>()->OnDeathEvent.AddListener(highScore->GetComponent<zombieArena::HighScore>(), &zombieArena::HighScore::SaveHighScore);
	
	// Alternatively you can listen to events by finding the object
	const auto player = diji::SceneManager::GetInstance().GetGameObject("X_player");
    player->GetComponent<PlayerBehaviour>()->OnPlayerMovedEvent.AddListener(this, &BranchBehaviour::MoveBranch);
```

### <ins>**Timers**</ins>

Timers have been added, once again inspired by [**Unreal Engine**](https://dev.epicgames.com/documentation/en-us/unreal-engine/using-timers-in-unreal-engine). Users can now create timers by passing a function or lambda to be executed.

Timers support multiple parameters, including:
- `initialDelay`
- `delay`
- `isLooping`

Timers are stored and mapped using **TimerHandles**, which allow them to be canceled at any time.

image of code
image of use case

### <ins>**Camera**</ins>

A Camera system has been added. The engine now supports cameras using SFML’s `View` class. Features include:
- Following GameObjects
- Locking or unlocking movement
- Applying offsets for precise adjustments
- Clamping movement within game boundaries

### <ins>**RectRender**</ins>

A **RectRender** component was added to simplify drawing rectangles. It can be used for simple shape rendering or collider debugging purposes.

### <ins>**Score Counter**</ins>

A reusable component for tracking numeric gameplay values.
The **ScoreCounter** component serves as a generic counter for score, lives, or any other numeric values needed in gameplay. It can emit events on score changes or when a goal is reached, making integration with other systems straightforward.

**Features:**

- Finds an attached `TextComponent` to display a formatted score string (default: `"Score = "`), with the ability to customize the string
- `ScoreValue` can be fetched or reset
- Increase or decrease the score with overloaded `IncreaseScore` / `DecreaseScore` methods, with a configurable increment
- Set a goal score for the component to notify when the goal is reached
- Emits events on score changes so other systems remain decoupled

This component is versatile: it can track lives, currency, or any incremental metric beyond “score,” while automatically updating displays.

### <ins>**Transform**</ins>

A basic Seek behavior has been added. Although this is a useful feature, it is noted as needing further expansion and separate implementation. See [**Improvements and Todos**](future-improvements--todos) for details.

### <ins>**Scene & Scene Manager**</ins>

Inspired by **Unreal Engine**, the **SceneManager** has been significantly enhanced:
- Users can now find any GameObject within the scene.
- Objects can be marked for destruction where at the end of the update loop pending objects are safely destroyed.
- `SpawnGameObject` allows users to spawn any GameObject using a template, similar to [**Unreal Engine**](https://dev.epicgames.com/documentation/en-us/unreal-engine/spawning-actors-in-unreal-engine).

(image)

The **Scene** was adapted to support the engine’s new functions and the SceneManager’s additions.

Additionally, **SceneManager now loads scenes automatically** when switching, provided the user has registered the scene with the `SceneLoader`. Previously, changing the scene required manually calling the loader. With the new system, scenes registered with the `SceneLoader` are loaded automatically during a scene switch.

See [**Improvements and Todos**](future-improvements--todos) for planned expansions to this system.

## <ins>**Future Improvements & Todo's**</ins>

While working on this project, I had to find the right balance between time invested and the value of implementing a feature. As a result, many features were left in early stages, as they worked for my use cases. Additionally, some systems need revisions due to inevitable mistakes and imperfections during development.

Here is a list of Potential Imporvemtns and marked todo's within the engine for future upgrades:

- **Physics and Collision system:** Having worked primarily on games without heavy physics, it was inevitable that the engine lacks depth in this area. This is reflected in the basic `FixedUpdate` pipeline. Collisions are currently handled via a singleton and are poorly optimized. Future updates should include:
	- Removing Collision as a singleton
 	- Integrating collision into the physics pipeline with events similar to Unreal Engine.
  	- Optimizations such as Unity's tags, Unreal's collision presets, spatial partitioning, and other methods
  	- Adding deeper physics simulation
  	- Optimizing collider updates
  	- Using static flags for objects to ignore updates
- Complete implementation of `OnEnable` and `OnDisable` systems, including optimization within GameObject logic
- Introduction of **wrapper class** for `ViewWindow `to allow safe, global access while keeping the code **maintainable** and **expandable**
- **Pause Singleton improvements:** Currently only compatible with the input system. Future updates should allow HUDs to update, separating pause commands from game commands, and ensure that game commands are ignored while pause commands continue functioning
- **Addition of TimerPhysics**, supporting timers capable of slowing down or accelerating physics
- **Deeper AI systems:** Separate AI behaviors from core components into an AI system complete with **Blackboards**, **Behavior Trees** (AI controllers), **Tasks**, **Services**, and **Decorators**
- **Navigation System** to work in tandem with AI systems
- **SceneManager improvements:** Automatically register SceneLoaders to remove user error during scene creation
- **Introduce static mathematical helpers**, since SFML does not provide helpers like GLM
- **Improve command registration system** to match the completeness of Unity or Unreal input systems
	- Find a solution for duplicate commands (manual destruction before creation is not ideal; consider mapping to scenes or static commands)
- Change all component base class methods to non-pure virtual (pure virtual unnecessary)
- Most GameObjects need custom logic. Simplify the addition of custom components to GameObjects (like Unreal Actors with built-in blueprints)
- Ensure all GameObjects come with a **Transform component** upon creation
- Improve the call to play audio. Audio files can be mapped to an enum and use that instead of the file name. it makes it easier to use and more readeable it also avoid user erros.
- Expand **InputManager** player indexes to allow more than four unique players (consider switching from enum class to size_t)
- Modify **Renderer** to accept textures as parameters instead of individual parameters, and update it to use the static window pointer
- **Render Component revamp:**
	- Option 1: Every object has a render component separate from normal components, allowing a `virtual Render` function to be edited when needed.
  	- Option 2: Rendering should be a separate system from components, clearly separating rendering logic from game logic
- Optimize `CreateGameObjectFromTemplate` by tracking the last used suffix or using an internal counter
- Optimize deletion of GameObjects at the end of the frame: currently O(n²), could be improved to O(n) by moving components to the end of the vector and resizing once, or by using a list
- **Asynchronous scene loading** to allow smooth transitions
- Rename `SetNextSceneToActivate` to `ChangeScene` and replace Scene `int` with a SceneId `enum` or `size_t` for readability
- Rename `ScoreCounter` to a more general counter name reflecting its broader usage
- Add **scaling** for text components
- Optimize **Timer class** by using a map or list to erase (stop) timers faster
- Add `DelayUntilNextTick` function to the **Timer class**
- Change `SetTimer` to take a `TimerHandle` parameter, assigning it instead of creating a new handle and returning it

# <ins>**Conclusion**</ins>

The **SFML Engine** represents a significant step forward from the original [**Diji-Engine**](https://github.com/DijiOfficial/Diji-Engine), not only in terms of library migration but also in system design, architecture, and extensibility. By transitioning from SDL to SFML, many systems were simplified, made more maintainable, and enhanced with new functionality inspired by industry-standard engines like **Unity** and **Unreal Engine**.

While the engine is still a work in progress, it provides a solid foundation for learning and game development in C++. Many features, such as the Event System, Input Manager, Timers, and SceneManager, have been redesigned to be more modular and flexible, while future improvements promise to further optimize performance and expand functionality.

I hope to expand on this engine in the coming months learning more about engine development and game development to solidify my knowledge and abilities to develop games!

## <ins>**References**</ins>
- [**Diji-Engine**](https://github.com/DijiOfficial/Diji-Engine) Original engine upon which SFML Engine is based.
- [**SFML**](https://www.sfml-dev.org) Simple and Fast Multimedia Library used as the core graphics and input library.
- [**Unreal Engine**](https://www.unrealengine.com) Inspiration for the event system, AI framework, scene management, and various design patterns.
- [**Unity Engine**](https://unity.com) Referenced for the engine pipeline, component architecture, input management, and naming conventions.
- [**C++ Core Guidelines**](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) Followed as best practices for modern, safe, and maintainable C++ code.
- [**Game Programming Patterns** by Robert Nystrom](https://gameprogrammingpatterns.com/) Used as guidance for architecture patterns and system design in a decoupled engine environment.
