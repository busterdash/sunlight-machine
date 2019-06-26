# The Sunlight Machine

See sun directory for additional readme content about available classes.

## Cloning
```
git clone https://github.com/busterdash/sunlight-machine
cd sunlight-machine
git submodule update --init
```

## Compiling
* For simplicity, I use Orwell Dev-C++ to compile on Windows.
* On Linux, a makefile is provided for compiling with the GNU C++ Compiler.

## Testing
* ```./sun.exe -in "house.smd" -out "texture.bmp"```

|Additional Flags|Default Value|
|----------------|-------------|
|-width [image_width]|512|
|-height [image_height]|512|
|-yaw [sun_angle]|15.0|
|-pitch [sun_angle]|30.0|
|-resolution [sqrt_of_number_of_rays]|512|
|-spread [scale]|1.0|

This program is available to you as free software licensed under the GNU General Public License (GPL-3.0-or-later)