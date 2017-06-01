# Raytrace Final Project

### There are two versions of this project:
* Serial - Runs on Windows or Linux.
* Threaded - Runs exclusively on Linux; uses POSIX threads.

## Common Components

### SMD Reader:
* So far it doesn't keep track of bones, it will only read root bones.
* It doesn't care about materials. For this project we're only concerned about geometry.
* Accessing a value is done like this: triangle->v[0]->u;

### Bitmap Writer:
* Writes windows bitmaps with a DIB of type BITMAPINFOHEADER.
* Images compatible with Windows 3.1 and above.

## Compiling
* Use Orwell Dev-C++ to compile on Windows.
* "make clean; make" on Linux.

## Running
* ./Raytracer -in "model.smd" -out "texture.bmp"

|Additional Flags|Default Value|
|----------------|-------------|
|-width [image_width]|512|
|-height [image_height]|512|
|-yaw [sun_angle]|15.0|
|-pitch [sun_angle]|30.0|
|-resolution [sqrt_of_number_of_rays]|512|
|-spread [scale]|1.0|
