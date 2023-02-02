## Dodger

## What's Dodger?
Dodger is a minimalist racing game inspired by retro LCD handheld games. Gain score as you overtake other vehicles and speed up your racer to increase the challenge, just be careful not to crash! Listen to some catchy electronic beats while you try to increase your score.

## Play on Itch.io
https://justice-bole.itch.io/dodger
<br>
![Dodger Gameplay Gif](https://img.itch.zone/aW1hZ2UvMTgyMzE5My8xMDcxNTM2OS5naWY=/original/qDORKP.gif)

## How it Works
- Uses the Raylib C graphics library to open a window in OpenGL context and draw graphics.
- Uses C++20 and a mix of procedural and OOP to organize and structure code.
- Implements a playlist of music using Raylib's auido mananager and C++20 std::filesystem::directory_iterator to load in multiple tracks from a music folder.
- Graphics are drawn using Raylib's standard shape drawing functions, mainly rectangle.
- Uses game design patterns like the state, loop, double buffer, and update.
- Compiled with Emscripten to be ran in the web broswer.

## Read About Raylib Audio for Web
I wrote a blogpost detailing some common audio errors I encountered and how you can avoid/fix them.
<br>
https://justice-bole.itch.io/dodger/devlog/460605/audio-troubles-in-your-raylib-web-build-try-these-solutions
