# RayTracing

A very basic ray tracer.

## Instructions

Build with:

```
cmake -B build
cmake --build build
```

You can run the program with 

```
./build/bin/Render
```

to render the hard-coded scene to an image, `SphereRender.pbm`. 

## Features

The ray tracer currently emits a single from the camera per pixel, although a ray may spawn others if it hits certain kinds of materials. 

Lighting is largely based on a simple Phong shader model. 

Reflection and refraction are included, which will cause more rays to be created and traced in order to get the colour for that pixel. 

## Anti-Aliasing

If you run the current code, you may notice that the edges of objects are highly pixelated. This is because there is only a single ray per pixel, so boundary transitions are not smooth; this problem is solved (or mitigated) by a process called "anti-aliasing". Anti-aliasing can be implemented by generating more than one ray per pixel, at slight offsets, and then taking the average of the resulting colours to get the final colour of that pixel. The simplest approach would be to use 4 rays and divide each pixel into four sub-pixels, although any number of rays could in principle be used. 
