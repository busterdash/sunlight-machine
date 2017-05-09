# Raytrace Final Project

### There are two versions of this project:
* Serial - Runs on windows or linux.
* Threaded - Runs exclusively on linux; uses POSIX threads.

## Common Components

### SMD Reader:
* So far it doesn't keep track of bones, it will only read root bones.
* It doesn't care about materials. For this project we're only concerned about geometry.
* Accessing a value is done like this: triangle->v[0]->u;

### Bitmap Writer:
* Writes windows bitmaps with a DIB of type BITMAPINFOHEADER.
* Images compatible with Windows 3.1 and above.
