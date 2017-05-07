NVCC = /usr/local/cuda/bin/nvcc
NVCC_FLAGS = -I/usr/local/cuda/include -lineinfo
OBJ      = main.o binary_writer.o device_independent_bitmap.o raster_image.o smd_model_reader.o windows_bitmap.o geometry.o raytracer.o
LINKOBJ  = main.o binary_writer.o device_independent_bitmap.o raster_image.o smd_model_reader.o windows_bitmap.o geometry.o raytracer.o
BIN      = Raytracer
RM       = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(NVCC) $(LINKOBJ) -o $(BIN)

main.o: main.cpp
	$(NVCC) -c main.cpp -o main.o $(NVCC_FLAGS)

binary_writer.o: binary_writer.cpp
	$(NVCC) -c binary_writer.cpp -o binary_writer.o $(NVCC_FLAGS)

device_independent_bitmap.o: device_independent_bitmap.cpp
	$(NVCC) -c device_independent_bitmap.cpp -o device_independent_bitmap.o $(NVCC_FLAGS)

raster_image.o: raster_image.cpp
	$(NVCC) -c raster_image.cpp -o raster_image.o $(NVCC_FLAGS)

smd_model_reader.o: smd_model_reader.cpp
	$(NVCC) -c smd_model_reader.cpp -o smd_model_reader.o $(NVCC_FLAGS)

windows_bitmap.o: windows_bitmap.cpp
	$(NVCC) -c windows_bitmap.cpp -o windows_bitmap.o $(NVCC_FLAGS)

geometry.o: geometry.cpp
	$(NVCC) -c geometry.cpp -o geometry.o $(NVCC_FLAGS)

raytracer.o: raytracer.cpp
	$(NVCC) -c raytracer.cpp -o raytracer.o $(NVCC_FLAGS)
