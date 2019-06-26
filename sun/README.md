# Components

## SMD Reader:
* So far it doesn't keep track of bones, it will only read root bones.
* It doesn't care about materials. For this project we're only concerned about geometry.

## Basic Bitmap File I/O:
* Submodule can be read about here: https://github.com/busterdash/basic-bitmap-fileio
* Writes windows bitmaps with of type ```BITMAPINFOHEADER```.
* Images compatible with Windows 3.1 and above.

## Raytracer:
* Tosses a two-dimensional grid of photons at the input model.
* Each photon that hits the model is converted to a coordinate on the texture and plotted by the Bitmap Writer.

This program is available to you as free software licensed under the GNU General Public License (GPL-3.0-or-later)