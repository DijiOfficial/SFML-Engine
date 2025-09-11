# <ins>**SFML Engine**</ins>

**My SFML Engine is a lightweight C++ engine built with [Simple and Fast Multimedia Library or SFML](https://www.sfml-dev.org), with [Four Simple Games]() each showcasing new capabilities of the engine, implemented following the C++ Core Guidelines.**

# <ins>**Overview**</ins>

This Engine is built on the foundation of my [**Diji-Engine**](https://github.com/DijiOfficial/Diji-Engine), using [**SFML**]() over [**SDL**]() this project aims to improve my knowledge of programming, programming guidelines, game programming and learning capacities using new library.
Since it's based of my Diji-Engine the structure is based of the Unity Engine as well as The Unreal Engine using systems appropritate for my use case. With an Improved more robust Pipeline simplyfying systems while expanding on them.

The [**Four Games**]() included in this repo serves as proof of the engine's capabilites. A complete, [**playable example**]() that ties the engine’s core systems together.

# <ins>**Contents**</ins>

- [**The Engine**](#the-engine)
    - [**Features**](#features--architecture)
    	- [**Core Engine Systems**](#core-engine-systems)
     	- [**Component System**](#component-system)
      	- [**Graphics & Rendering**](#graphics--rendering)
      	- [**Audio System**](#audio-system)
      	- [**Input & Controls**](#input--controls)
      	- [**Advanced Features**](#advanced-features)
      	- [**Development Tools**](#development-tools)
    - [**Game Programming Patterns**](#game-programming-patterns)
    	- [**Command Pattern**](#command-pattern) 
    	- [**Observer Pattern**](#observer-pattern) 
    	- [**Singleton Pattern**](#singleton-pattern) 
    	- [**Game Loop**](#game-loop) 
    	- [**Update Method**](#update-method) 
    	- [**Component Pattern**](#component-pattern) 
    	- [**Dirty Flag**](#dirty-flag) 
    	- [**Event Queue Pattern**](#event-queue-pattern) 
    	- [**Service Locator Pattern**](#service-locator-pattern) 
    	- [**GameObject Parent-Child Relationship**](#gameobjects-parent-child-relationships) 
    - [**Pipeline**](#pipeline)
    - [**Improvements & todos**](#improvements--todos)
- [**Pac-Man**](#pac-man)
    - [**Intro**](#intro)
    - [**Overview**](#overview-1)
    - [**Controls**](#controls)
    - [**Single Player**](#single-player)
    	- [**AI**](#ai) 
    - [**CO-OP**](#co-op)
    - [**VERSUS**](#versus)
    	- [**FREEMODE**](#freemode)
    	- [**GHOST RULES**](#ghost-rules)
     - [**Create Level**](#create-level)
     - [**Play The Game**](#play-the-game)
  - [**Conclusion**](#conclusion)
    - [**References**](#references) 

# The Engine

In this section I will cover the changes and improvements over my first engine. I won't go over the features and programming patterns as they are essentially the same as my [**Diji-Engine**](). I will instead cover the transition and differences with an extensive focus on the Improvements made.

<details>
	 <summary>Click to expand Library porting details</summary>

## From SDL to SFML

As this engine was made with a different library than my orginal a few systems had to be modified. Where SDL provides a low-level, C-based API focused on maximum portability across platforms, SFML is built for modern C++ and offers a more object-oriented, user-friendly library, making it easier to use and understand, thus the change was not a difficult challenge as SDL needed more abstractions already ocvered by SFML.

The biggest changes related to the libraries will be about resources and renderering having vastly different handling methods between the two.

### ResourceManager

The resource manager saw changes all across as SDL provides raw pointers to the information needed for textures, fonts and other resources. Needing RAII Wrappers to encaspulate those resources. SFML already provides Wrappers for those making it much easier to use and therefore seeing the removal of all the existing RAII wrappers. 

As for the logic it remained the same.

### Renderer & Render Component

The renderer was simplified, used in tandem with the SFML RenderWindow. SFML also offers vertex rendering, by using an SFML vertexArray altough not changing much for the Renderer will see the introduciton of the [Sprtie compoenet]() able to calculate and create its vertex array for rendering from SPriteSheets. Render component was adapted with the RAII wrappers for Texture, fonts, ect...

### Why SFML

Changing library is more than just swapping APIs. it's an exercise in problem-solving, and learning to manage wide-reaching changes across a codebase. Migrating the engine involved rethinking abstractions, understanding dependencies and cor concepts that have grown around the old library. Migrating the engine also exposes areas for modularity, decoupling, and improved maintainability, where core systems have to be adapdted they are also updated and improved turning the challenge itself into a valuable engine development milestone rather than just a technical challenge. And for all of That SFML was a perfect fit, a very different yet similar library. It's also a great API for gameDevleopment.

</details>

## Improvements and Additions

<details>
	 <summary>Click to expand engine improvements and roadmap details</summary>

With the library changes out of the way let's get into the improvenets and additions to the engine.

### Engine Pipeline

The first major changes come in the form of the engine pipeline, While keeping the pipeline simple was the objective of my first engine it quickly became obvious that many workarounds needed to be made for more complex games and such the pipeline saw the addition of `start` and `onDestroy`, while components saw the addition of `OnEnable` and `OnDisable` for entry and exit logic it is not fully implemented within the pipeline and GameObjects but are rather helpers, marked as an improvement to be fully inclided within the piepline. the pipeline aslo saw changes in the form of EndFrameUpdate moving the scenehandling and cleanup to the end of the frame as well as an expansion on the render pipeline with the addition of the HUDs being draw later in the pipeline.

For reference we can see here the previous pipeline,

![Picture of the Pipeline](https://github.com/DijiOfficial/Diji-Engine/blob/master/GitHubAssets/Pipeline.png)

and the current Pipeline:

![Picture of the Pipeline]()

While it is not shown in the diagram, part of loading the new scene is calling the `Init` And `Start`, same thing for destroying object at the end of the frame, the `onDestroy` is called. While the pipeline has been expanded on almost all fronts we can see the `FixedUpdated` lagging a bit behind. One of the [improvemtns]() will be the expansion of the physics part of the engine with the fixed upadte.

#### Engine Optimizations

VIEWPORT and Window are now global static variables allowing access anywhere this prevents having to duplicate pass reference down and helps with keeping miantainable code. Altough I'm aware the user can cause issues having global acces to the window it can be improved through the use of a wrapper class see [improvemtns]().

### Pause Singleton

Addition of the pause Singleton allowing players to easily pause or unpause the game when needed. This feature is in its early stages. see [improvements & todos]() on how this feature can be expanded in the future.

### GameObjects

Addition of OnEnable and OnDisable methods, though the methods are not fully supported within the engine yet they can be used independantly within the gameobjec herarchy.
GameObjects can now be duplicated, keeping a memory footrpint of their creation to use as a blueprint for the creation of duplicated assets. Both for compile and runtime.

### RandNumber Helper

Introduction of the static RandomNumber helper class with thread safety to generate any int or float random number given a min and max value.

### InputManager

The input manager saw major changes compared to the original. Now has working HELP/PRESSED/RELEASED states for keys using unordered maps. 
Optimized the call to assiociated Command with Hash Map to have O(1) execution over the previous O(n)

![image of hash map optimization]()

Further addition of mouse movements and mouse buttons, using templates.

### Event System

Complete removal of Observer/Listener Pattern. Instead completly replaced by an event system like the unreal engine one. All components now have access to creating and subscribing to events as well as passing information to those events using templates. Heavily inspired by the unreal engine Event system it is a very close replica. It allows me to simplify the pattern and the code while keeping it clean and decoupled. A massive improvement from the original

![image of hash map optimization]()
image of use case

### Timers

Addition of Timers, Once again inspired from Unreal Engine's timers Users can now create Timers while passing a function or lambda to be executed. The come with multiple parameters, including initial delay, delay, isLooping. Timers are also stored and mapped with TimerHandles to be canceled at any time.

image of code
image of use case

### Camera

Addition of Camera. Engine now supports cameras using the view class from smfl. Cameras can be set to follow gameobjects, locked/unlocked to prevent movement, offset for needed adjustments, and can be clamped within the game's boundaries.

### RectRender

Addition of the RectRender class to easily draw rectangles. Can be used for simple shapes or debugging.

### ScoreCounter

Addition of ScoreCounter component, it serves as a generic counter for score, lives or any other counters needed. It can send event on increase/decrease and goal reached for ease of use.
Purpose

A reusable component for tracking numeric gameplay values (score, lives, counters) and exposing changes to other systems and the UI.
- Finds attached TextComp to display a formatted score string (default: "Score = ").
	- Ability to change the string
- ScoreValue can be fetched or reset.
- Increase and decrease score with overloaded IncreaseScore / DecreaseScore methods and a configurable increment.
- Set and check a goal score; the component can notify when the goal is reached.
- Emits events on score changes so other systems remain decoupled.
A useful generic counter: it can track lives, currency, or any incremental metric beyond “score.” as well as update displays

### Transform

Addition of basic Seek behavior, Altough a usefull features it is noted as to be expanded and impletemented seperatly see [improvemtns and todos]()

### Scene & Scene Manager

inspired from Unreal engine.
SceneManager now allows users to find any gameobject within the scene. Set object to be destroyed, when the loop is finished pending destoy object will be safely destroyed. 
SpawnGameObject, you can now spawn any gameobject similar to UnrealEngine given a gameobject template.
(image)
Scene was adapted to Engine's new functions and SceneManager's new additions.

SceneManager now loads scenes automatically when switched, granted the user registers the sceneLoader. Previously when changing the scene, the new scene needed to be called from the Loader. Now users can register a scene from the sceneLoader to be loaded automatically when switching the scene. see [improvemtns and todos]() on how I plan to expand this ssytem

## Improvements & Todos

</details>

# The Four Games
## Intro
    
# Overview

# The Games
## Timber
## Pong
## Zombie Game
## Tom?Other?

## Playe The Games

# Conclusion
## References
