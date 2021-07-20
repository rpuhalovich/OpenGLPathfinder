# OpenGLPathfinder

![](res/demoImage.png)

## Introduction

Yet another Dijkstra's Algorithm visualization tool. What sets this one apart, you might ask? The fact that it's written in C++ and using raw OpenGL!

Writing a pathfinding visualizer has been something I had wanted to do for a while, initially in Pygame. However, around the time I had this idea, I had been reading into using OpenGL. This seemed like a good opportunity to kill two birds with one stone.

## Getting Started
To clone:

```
git clone --recursive https://github.com/rpuhalovich/OpenGLPathfinder.git
cd OpenGLPathfinder
```

Build for Windows:

```cmake -S . -B build -G"Visual Studio 16 2019"``` or ```scripts\build_visual_studio.bat```

Build for Mac:

```cmake -S . -B build -GXcode``` or ```./scripts/build_xcode.sh```

Build for Linux:

Install dependencies: ```sudo apt install -y libgl1-mesa-dev freeglut3-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libx11-dev```

## Usage

### Mechanics

White Square: Obstacle - cannot be traversed.

Dark Grey Square: UnVisited node.

Purple Square: Visited node.

Green Square: Start node.

Red Square: Finish node.

Dark Blue Square: Path node.

### Controls
#### Mouse
Left Click: Toggle node between obstacle and unVisited.

Right Click: Hold down to paint obstacles.

Middle Click: Hold down to erase.

#### Keyboard
Space Bar: Begin Dijkstra's Algorithm.

1: Random obstacles.

2: Recursive Backtracking Maze Algorithm (WIP).

C: Clear obstacles.

R: Reset the board.

## TODO

- Implement AStar.
- Replace the use of vector with a priority queue for the unVisited nodes.
- Some of the algorithms are not exactly the most efficient (not the point of this program but could still do with improvement). 
- Track down that pesky 32 byte memory leak on application termination.
- Others mentioned in the source code.
