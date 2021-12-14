COMPILER = gcc
TARGET = available_wpns
OBJECTS = ./src/*.obj

ifeq ($(OS),Windows_NT)
    RM = del /F /Q 
else
    RM = rm -rf 
endif

default: $(TARGET)
	$(RM) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(COMPILER) $(OBJECTS) -o $(TARGET)

$(OBJECTS): ./src/avawpns.c ./src/resource.rc
	$(COMPILER) -c ./src/avawpns.c -o ./src/avawpns.obj