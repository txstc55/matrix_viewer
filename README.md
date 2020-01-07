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
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j
./matrix_viewer_bin y_pixel x_pixel path/to/object.off
```

## How to get x_pixel and y_pixel?
If your terminal supports xterm control sequence, do the following:
```bash
echo -e '\e[14t'
```
And you will get y_pixel, then x_pixel, use those.

## Free meshes?
Yes, in the mesh folder.

## Issues?
- [ ] To avoid too many if loops, the size of the item is limited so that it will not exceed the screen.
- [ ] The current Eigen submodule I am using is doing too many stuffs to say the least, may need to look for a new one.
- [ ] The tbb submodule I am using generates some tests regardless I turned that option off in cmake.
- [ ] I still have no idea how to use opencl, will be nice to have it.
- [ ] Will be nice if I can get the terminal size in pixel value in c++, so that I can resize the terminal easily.
- [ ] Unable to custome the scene related settings, because I am lazy.
- [ ] Unable to move the mesh, because I am lazy.
- [ ] Unable to move the camera, because it is unnecessary.
- [x] **Who am I kidding I probably won't touch those issues in the future**.

## Key presses?
*wasd* for rotations, *k* and *l* for scaling, go figure, there are only 6 keys.
