# OpenGLPathfinder

![](res/demoImage.png)

## Introduction

Yet another Dijkstra's Algorithm visualization tool. What sets this one apart, you might ask? The fact that it's written in C++ and using raw OpenGL!

Writing a pathfinding visualizer has been something I had wanted to do for a while, initially in Pygame. However, around the time I had this idea, I had been reading into using OpenGL. This seemed like a good opportunity to kill two birds with one stone.

## Getting Started

### To clone

```bash
git clone --recursive https://github.com/rpuhalovich/OpenGLPathfinder.git
cd OpenGLPathfinder
```

### Build on Macos

```bash
make
``

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
