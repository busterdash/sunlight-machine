BM_DIR = bitmap-machine
include $(BM_DIR)/make_sm_vars
OBJECTS = main.o raytracer.o smd_model_reader.o geometry.o $(BM_OBJECTS)
TARGET = sun
CPP = g++
FLAGS = -std=c++11

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CPP) -o $(TARGET) $(OBJECTS)

main.o: main.cpp
	$(CPP) $(FLAGS) -c -o main.o main.cpp

raytracer.o: raytracer.cpp
	$(CPP) $(FLAGS) -c -o raytracer.o raytracer.cpp

smd_model_reader.o: smd_model_reader.cpp
	$(CPP) $(FLAGS) -c -o smd_model_reader.o smd_model_reader.cpp

geometry.o: geometry.cpp
	$(CPP) $(FLAGS) -c -o geometry.o geometry.cpp

include $(BM_DIR)/make_sm_rules

.PHONY: clean
clean:
	rm -f *.o *.exe $(BM_DIR)/*.o
