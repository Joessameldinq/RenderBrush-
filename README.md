# RenderBrush

A lightweight, real-time raster painting application built in C++17 using SDL2.
RenderBrush exposes low-level graphics primitives wrapped in a clean object-oriented architecture,
without relying on any high-level graphics frameworks.

---

## Table of Contents

- [About](#about)
- [Features](#features)
- [Project Structure](#project-structure)
- [Dependencies](#dependencies)
- [Building](#building)
- [Usage](#usage)
- [Keyboard Shortcuts](#keyboard-shortcuts)
- [Architecture](#architecture)
- [Author](#author)

---

## About

RenderBrush is a personal project developed as part of learning systems-level graphics programming.
It demonstrates direct manipulation of SDL2's hardware-accelerated renderer, texture targeting,
and event-driven input handling — all implemented from scratch in modern C++17.

---

## Features

- Freehand drawing with adjustable brush size
- 10 preset colors selectable from a toolbar
- Real-time brush size preview
- Eraser tool
- Canvas clear functionality
- Save drawing as PNG
- Runs at a configurable FPS

---

## Project Structure

```
RenderBrush/
├── Makefile
├── README.md
├── src/
│   ├── main.cpp
│   ├── Gui.cpp
│   ├── Canvas.cpp
│   └── Toolbar.cpp
└── include/
    ├── Gui.h
    ├── Canvas.h
    ├── Toolbar.h
    ├── Colors.h
    └── Utils.h
```

---

## Dependencies

| Library      | Purpose                        | Install                          |
|--------------|--------------------------------|----------------------------------|
| SDL2         | Window, renderer, input        | `sudo apt install libsdl2-dev`   |
| SDL2\_image  | PNG export                     | `sudo apt install libsdl2-image-dev` |

---

## Building

Clone the repository and build using Make:

```bash
git clone https://github.com/Joessameldinq/RenderBrush-.git
cd RenderBrush-
make
```

Run the application:

```bash
make run
```

Clean build artifacts:

```bash
make clean
```


---

## Usage

- Left-click and drag on the canvas to draw.
- Click a color swatch in the toolbar to change brush color.
- Click the minus or plus buttons to decrease or increase brush size.
- Click the eraser button to switch to eraser mode.
- Click s key to export the canvas as a PNG file.

---

## Keyboard Shortcuts

| Key      | Action               |
|----------|----------------------|
| C        | Clear canvas         |
| E        | Toggle eraser        |
| S        | Save canvas as PNG   |
| Escape   | Quit application     |

---

## Architecture

The application is divided into three main components:

**Gui** manages the SDL window, renderer, main loop, and event dispatching.
It owns both the Canvas and Toolbar instances and coordinates communication between them.

**Canvas** owns an SDL\_Texture that serves as the persistent drawing surface.
All drawing operations target this texture directly, allowing the canvas state to persist
across frames. It exposes mouse event handlers that translate screen coordinates into
draw calls.

**Toolbar** renders the color palette, brush size controls, and eraser button.
It holds a reference to Canvas and calls its setters directly in response to user interaction.

```
Gui
 |-- Canvas   (SDL_Texture, draw primitives, mouse handlers)
 |-- Toolbar  (color swatches, brush controls, eraser)
```

---

## Author

Yousef Essam
- Computer Science Undergraduate
- GitHub: [@Joessameldinq](https://github.com/Joessameldinq) 
- Linkedin : [@Youssef Essam](https://www.linkedin.com/in/youssef-essam-469ba5244/)