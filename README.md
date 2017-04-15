# Raytrace Final Project

### SMD Reader
* So far it doesn't keep track of bones, it will only read root bones.
* It doesn't care about materials. For this project we're only concerned about geometry.
* Written in Dev-C++, easily portable to linux.
* Accessing a value is done like this: triangle->v[0]->u;

### Bitmap Writer
* Writes windows bitmaps with a DIB of type BITMAPINFOHEADER.
* Images compatible with Windows 3.1 and above.

### Triangle Transformer
* Takes a triangle from SMD Reader, poops out a vertex which can be written to an image by BitmapWriter.
