# MATRIX VIEWER

Imagine you are observing the matrix world without a gpu......

And you want to check out yoda

![yoda in terminal](https://github.com/txstc55/matrix_viewer/raw/master/pic/matrix_effect.png)



## How to download with submodules?
```bash
git clone --recurse-submodules https://github.com/txstc55/matrix_viewer
```

## Why?
I have no idea, I was bored.

## How to build?
```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j2
./matrix_viewer_bin path/to/object.off
```
The object.off is optional, without it you will just have a plain cmatrix effect.

## ~~How to get x_pixel and y_pixel?~~
Now the x and y pixel will be detected so no need to support it externally.

## Free meshes?
Yes, in the mesh folder.

## Issues?
- [ ] To avoid too many if loops, the size of the item is limited so that it will not exceed the screen.
- [ ] The current Eigen submodule I am using is doing too many stuffs to say the least, may need to look for a new one.
- [x] The tbb submodule I am using generates some tests regardless I turned that option off in cmake.
- [ ] I still have no idea how to use opencl, will be nice to have it.
- [x] Will be nice if I can get the terminal size in pixel value in c++, so that I can resize the terminal easily.
- [ ] Unable to custome the scene related settings, because I am lazy.
- [ ] Unable to move the mesh, because I am lazy.
- [ ] Unable to move the camera, because it is unnecessary.
- [x] **Who am I kidding I probably won't touch those issues in the future**.

## Key presses?
*wasd* for rotations, *k* and *l* for scaling, go figure, there are only 6 keys.

## New feature, camera
Now, run the code as
```bash
./matrix_viewer_bin camera
```
And you will have your face in matrix world.

Note that in order to have this feature, you will need opencv downloaded on your machine, and make sure the path can be searched by cmake.

Note, that there might be some line in main.cpp you need to change, those lines are:

Line 73:
```c++
if (!cap.open(1))
```

Since you may have created a virtual camera at this point, it is likely your default camera device is not 0 anymore. Here I changed to 1 because that is my webcam, you may have to test around from 0 to whatever number works for you.

Line 168:
```c++
attron(COLOR_PAIR(matrix.color_map[i][j]) + int(average_brightness) * 25);
```

And line 173:
```c++
attroff(COLOR_PAIR(matrix.color_map[i][j]) + int(average_brightness) * 25);
```

The 25 can be increased or decreased for adjustment of brightness, just make sure to use the same number.

With the help of (obs)[https://obsproject.com/], you can even create a virtual camera, use the terminal window as your camera, then join virtual meetings, a demo is at (here)[https://twitter.com/txstc55/status/1306084073518100481], have fun!
