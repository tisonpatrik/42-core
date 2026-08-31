*This project has been created as part of the 42 curriculum by ptison, jakrajic.*

# cub3D - My first RayCaster with MLX42

## Description
**cub3D** is a 3D graphical project inspired by the world-famous *Wolfenstein 3D* game, which is considered the first First-Person Shooter (FPS) in video game history. The goal of this project is to create a dynamic first-person perspective rendering inside a maze using the **Ray-casting** technique.

The program reads a map configuration file (`.cub`), parses its settings and map structure, and renders a smooth 3D view using the **MLX42** graphics library.

### Key Features
- **3D Raycasting Engine:** Renders walls in a 3D perspective based on a 2D map grid.
- **Wall Texturing:** Distinct textures for North, South, East, and West facing walls.
- **Customizable Colors:** Configurable floor and ceiling RGB colors.
- **Smooth Navigation:** Movement (WASD) and camera rotation (Left/Right arrows) with clean event/window handling.

### Bonus Features Included
- **Interactive Doors (`'2'`):** Extended map parsing and dynamic door rendering when built with the bonus flag (`src/parser/`).
- **Wall Collisions:** Prevents the player from walking through walls or clipping into edges (`src/world/collision.c`).
- **Minimap Overlay:** Real-time 2D minimap rendering player position and collected items (`src/render/minimap/`).
- **Mouse Look Controls:** Smooth camera view rotation guided by mouse movement (`src/player/mouse.c`).
- **Fire & Scorch Mechanics:** Dynamic fire interactions and surface scorch rendering (`src/fire/`, `src/render/fire/`).
- **Orb Collectibles:** Random orb generation, collection mechanics, and dynamic rendering (`src/orb/`, `src/render/orb/`).

---

## Map Parsing Requirements

The program validates and parses configuration files with the `.cub` extension. A valid map file must fulfill the following rules:

### 1. Configuration & Textures
- **Wall Textures:** Paths to 4 PNG/XPM texture files corresponding to wall directions: `NO` (North), `SO` (South), `WE` (West), and `EA` (East).
- **Floor & Ceiling Colors:** RGB color definitions for Floor (`F`) and Ceiling (`C`) in `R,G,B` format (values in range `0-255`).

### 2. Map Layout Rules
- **Map Characters:**
  - `0` for an empty walkable space.
  - `1` for a solid wall.
  - `N`, `S`, `E`, or `W` for the player's starting position and orientation.
  - `2` for interactive doors *(Bonus part)*.
  - Space (` `) for empty padding outside the map layout.
- **Enclosure:** The map layout must be completely surrounded/enclosed by walls (`1`). No walkable space (`0`, player start, or doors) can touch the outside boundary or a space character (` `).
- **Single Player Start:** Exactly **one** starting orientation character (`N`, `S`, `E`, or `W`) must be present in the entire map.

### Example `.cub` File Structure
~~~text
NO ./textures/north.png
SO ./textures/south.png
WE ./textures/west.png
EA ./textures/east.png

F 220,100,0
C 225,30,0

111111111111
100000000001
10000N000001
100000000001
111111111111
~~~

---

## Instructions

### Requirements & Dependencies
- C compiler: [GCC](https://gcc.gnu.org/) or [Clang](https://clang.llvm.org/)
- [GNU Make](https://www.gnu.org/software/make/)
- [CMake](https://cmake.org/) (required because the Makefile uses it to build MLX42)
- [GLFW](https://www.glfw.org/) (required for MLX42)

### Compilation
To compile the project, run the Makefile rules in the repository root:

- **Compile mandatory part:**
```bash
make
```

- **Compile bonus part (enables `-DBONUS_BUILD`):**
```bash
make bonus
```

- **Clean object files and build directories:**
```bash
make clean
```

- **Full clean (removes executable and dependencies build):**
```bash
make fclean
```

- **Recompile mandatory part:**
```bash
make re
```

### Execution
Run the executable followed by the path to a valid `.cub` map file:

```bash
./cub3D assets/maps/map_title.cub
```
### Memory Leak Testing (Valgrind)
To check for memory leaks while suppressing internal GLFW/MLX42 library false positives, use the provided suppression file:

~~~bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=valgrind_mlx_suppr ./cub3D assets/maps/map_title.cub
~~~

### Controls
| Input | Action |
| :--- | :--- |
| `W` `A` `S` `D` | Move Forward / Left / Backward / Right |
| `Left Arrow` / `Right Arrow` | Rotate Camera View |
| `Mouse Movement` *(Bonus)* | Look / Rotate Camera View |
| `Space` *(Bonus)* | Interact / Open / Close Doors (`'2'`) |
| `ESC` / `Red Cross` | Close window and exit program cleanly |
| `TAB` *(Bonus)* | Toggle mouse lock (Enable/Disable Cursor)|

---

## Resources

### Documentation & Tutorials
- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) - In-depth guide on raycasting math, DDA algorithm, textured walls, and sprite rendering.
- [MLX42 GitHub Repository](https://github.com/codam-coding-college/MLX42) - Official MLX42 documentation, API reference, and installation guides.
- [Wolfenstein 3D History](https://en.wikipedia.org/wiki/Wolfenstein_3D) - Background on id Software's classic game.

### Asset Credits
- [SimonKraft](https://www.curseforge.com/minecraft/texture-packs/simonkraft) by `simonk0` - Source of the Minecraft-inspired textures used in this project.

### AI Usage
AI tools were used as learning and support tools for:
- Designing the project structure to support collaboration between two developers while following [Data-Oriented Design (DoD)](https://www.dataorienteddesign.com/dodbook/) best practices.
- Diagnosing a memory leak in the map parser.
- Guidance on the structure and wording of this README.
