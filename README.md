# The Sunlight Machine

This is a simple light simulation tool that "bakes" the appearance of sunlight
and shadows to a texture which is applied to a 3D model.

Converted to Rust from C++, see commit 665cc3c on master for the original
implementation. 

## Execution
* ```./sun.exe -in "house.smd" -out "texture.png"```

|Additional Flags|Default Value|
|----------------|-------------|
|-width [image_width]|512|
|-height [image_height]|512|
|-yaw [sun_angle]|15.0|
|-pitch [sun_angle]|30.0|
|-resolution [sqrt_of_number_of_rays]|512|
|-spread [scale]|1.0|

This program is available to you as free software licensed under the GNU General Public License (GPL-3.0-or-later)