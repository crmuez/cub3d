# cub3d 🕹️👾

**cub3d** is a 3D game engine that simulates the classic 3D maze exploration experience. It's part of the 42 curriculum and was implemented using **C** and the **MLX42** library, focusing on understanding game rendering and the basic principles of raycasting.

## Description 📄

The `cub3d` program is a 3D exploration game that renders a maze using raycasting techniques. The player navigates through a 2D map, and the program calculates the 3D projection of walls, floors, and ceilings based on the player's position and orientation.

### Features ✨:

- **Raycasting**: This is the core technology behind the game, where rays are cast from the player's position to determine the visibility of walls and surfaces.
- **2D Map**: The game world is represented as a simple 2D grid with different types of tiles representing walls and spaces.
- **3D Rendering**: Using the raycasting technique, the program projects the 2D map into a 3D view, allowing the player to explore the environment.
- **Player Movement**: The player can move and rotate within the game world, allowing for free exploration of the maze.
- **Texture Mapping**: The game includes textures to represent the walls, floor, and ceiling of the maze, creating a more immersive experience.

## Progress ⚙️

The project is still in progress but is already quite advanced. The core functionality, including movement, raycasting, and basic rendering, is implemented, and the game is playable. Ongoing work is focused on optimizing performance, adding more advanced features, and refining the overall user experience.

## Notes 📝

This project was developed using **C** and the **MLX42** library on **Linux**. It requires understanding basic concepts in 3D rendering, game loops, and raycasting. The project also helped in mastering memory management and dealing with graphics in a low-level environment.
