# Project: Raytracer
# Makefile created by Dev-C++ 5.11

CPP      = g++
CC       = gcc
WINDRES  = windres
OBJ      = main.o binary_writer.o device_independent_bitmap.o raster_image.o smd_model_reader.o windows_bitmap.o geometry.o raytracer.o
LINKOBJ  = main.o binary_writer.o device_independent_bitmap.o raster_image.o smd_model_reader.o windows_bitmap.o geometry.o raytracer.o
BIN      = Raytracer
CXXFLAGS = $(CXXINCS) -std=c++11
RM       = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN)

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(CXXFLAGS)

binary_writer.o: binary_writer.cpp
	$(CPP) -c binary_writer.cpp -o binary_writer.o $(CXXFLAGS)

device_independent_bitmap.o: device_independent_bitmap.cpp
	$(CPP) -c device_independent_bitmap.cpp -o device_independent_bitmap.o $(CXXFLAGS)

raster_image.o: raster_image.cpp
	$(CPP) -c raster_image.cpp -o raster_image.o $(CXXFLAGS)

smd_model_reader.o: smd_model_reader.cpp
	$(CPP) -c smd_model_reader.cpp -o smd_model_reader.o $(CXXFLAGS)

windows_bitmap.o: windows_bitmap.cpp
	$(CPP) -c windows_bitmap.cpp -o windows_bitmap.o $(CXXFLAGS)

geometry.o: geometry.cpp
	$(CPP) -c geometry.cpp -o geometry.o $(CXXFLAGS)

raytracer.o: raytracer.cpp
	$(CPP) -c raytracer.cpp -o raytracer.o $(CXXFLAGS)
