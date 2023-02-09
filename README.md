# 3D-Voxel-Engine

This is my 3D voxel engine coded entirely in SFML, a 2D graphics API. Everything in this project was made by me from scratch.

https://user-images.githubusercontent.com/103447109/217927286-8c6a10ce-06dd-4b3e-9c35-2670a05db66e.mp4

My program allows 360 degree rotation in all directions. My program uses quaternions to uniquely define every possible rotation. Furthermore, quaternions are much faster than rotation matrices and are not prone to gimbal lock.

Right now, you can place a cube anywhere in 3D space, and my program will automatically project it onto a two-dimensional screen.

# BUGS

This project proved to be much more difficult than I thought. When looking from everything at a distance, it appears to be perfectly fine. However, when you get very close to a cube, unpredictable behavior starts to happen. Furthermore, drawing textures on the sides of the cubes leads to the textures becoming stretched, so only solid colors work well right now.
