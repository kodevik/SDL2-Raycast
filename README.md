# Raycaster-SDL2
A basic raycasting engine implemented in C++ using the SDL2 library. Mouse movement wraps around the window horizontally and movement is controlled by the WASD keys. Walls can have a colour associated with them and can be angled. No collision detection has been implemented as of yet.


The raycasting algorithm itself works by checking first whether the player is facing a wall. This is done by checking whether the area of a triangle formed by the player position, the wall start and wall end is equal to the sum of the areas of 3 triangles formed between combinations of two of these points and a point slightly in front of the player in the direction of the ray angle. 