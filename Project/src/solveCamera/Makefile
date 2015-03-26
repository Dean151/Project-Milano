# the build target executable:
TARGET = solveCamera

# the compiler: gcc for C program, define as g++ for C++
CC = g++

# compiler flags:
#  -g         adds debugging information to the executable file
#  -Wall      turns on most, but not all, compiler warnings
#  -std=c++11
CFLAGS  = -g -Wall -std=c++11

CV_CORE    = -lopencv_core
CV_HIGHGUI = -lopencv_highgui
CV_IMGPROG = -lopencv_imgproc
CV_CALIB3D = -lopencv_calib3d

CV_FLAGS = $(CV_CORE) $(CV_HIGHGUI) $(CV_IMGPROG) $(CV_CALIB3D)



all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) $(CV_FLAGS) -o $(TARGET).out $(TARGET).cpp

clean:
	$(RM) $(TARGET)
