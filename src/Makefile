SHELL = /bin/sh
.SUFFIXES: .cpp .a .o

CXX=g++
CXXFLAGS= -I/usr/include/libusb-1.0 -I../../../gitrepo/pixy2/src/host/libpixyusb2/include -I../../../gitrepo/pixy2/src/host/arduino/libraries/Pixy2
INC=-I/
LDLIBS=-lwiringPi ../../../gitrepo/pixy2/build/libpixyusb2/libpixy2.a -lusb-1.0

SRCS=HC_SR04.cpp Sharp_IR.cpp flyintel.cpp
OBJS=$(patsubst %.cpp,%.o,$(SRCS))

BUILD_DIR=../build

$(BUILD_DIR)/main.out: $(BUILD_DIR)/main.o $(BUILD_DIR)/pixycam.o $(BUILD_DIR)/${OBJS}
	$(CXX) $(CPPFLAGS) -o $(BUILD_DIR)/main.out $(BUILD_DIR)/$@ $(LDLIBS)

$(BUILD_DIR)/main.o: main.cpp
	$(CXX) -c main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/pixycam.o: pixycam.cpp
	$(CXX) -c $(CPPFLAGS) pixycam.cpp -o $(BUILD_DIR)/pixycam.o

$(BUILD_DIR)/$(OBJS): $(BUILD_DIR)/$(SRCS) dirmake
	$(CXX) -c $(SRCS) -o $(BUILD_DIR)/$(OBJS)

dirmake:
	@mkdir -pv $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)/main.out $(BUILD_DIR)/*.o
