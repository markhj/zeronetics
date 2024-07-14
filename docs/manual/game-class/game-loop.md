@page game-loop Game loop

The **game loop**, also often referred to as **render loop**, handles
all the logic as the in-game is running. Anything from calculating
enemy health to rendering fog.

## 🔁 How it works

The game loop in Zeronetics is managed by ZEN::Game::run.

For each iteration, it will:

- Clear render buffers
- Process requests by @ref entity-system "entities"
- Render the scene
- Handle user inputs
- Swap render buffers

In between it also calculates @ref FPS, and true render time.

## See also

- @ref input-manager
- @ref delta
- @ref fps
