SHELL = /bin/sh
.SUFFIXES: .cpp .a .o

CXX=g++
CXXFLAGS= -I/usr/include/libusb-1.0 -I../../../gitrepos/pixy2/src/host/libpixyusb2/include -I../../../gitrepos/pixy2/src/host/arduino/libraries/Pixy2
INC=-I/
LDLIBS=-lwiringPi ../../../gitrepos/pixy2/build/libpixyusb2/libpixy2.a -lusb-1.0

SRCS=HC_SR04.cpp Sharp_IR.cpp flyintel.cpp
OBJS=$(patsubst %.cpp,%.o,$(SRCS))

BUILD_DIR=../build

$(BUILD_DIR)/main.out: $(BUILD_DIR)/SCXmodel.o $(BUILD_DIR)/cltcmd.o $(BUILD_DIR)/connect_to_flysim.o $(BUILD_DIR)/SPIadc.o $(BUILD_DIR)/main.o $(BUILD_DIR)/pixycam.o $(BUILD_DIR)/flyintel.o $(BUILD_DIR)/max7219.o $(BUILD_DIR)/SPIadc.o $(BUILD_DIR)/Sharp_IR.o $(BUILD_DIR)/HC_SR04.o $(BUILD_DIR)/DCmotor.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS) -Winline

$(BUILD_DIR)/main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) $(INC) main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/pixycam.o: pixycam.cpp
	$(CXX) -c $(CXXFLAGS) pixycam.cpp -o $(BUILD_DIR)/pixycam.o

$(BUILD_DIR)/SCXmodel.o: SCXmodel.cpp
	$(CXX) -c SCXmodel.cpp -o $(BUILD_DIR)/SCXmodel.o

$(BUILD_DIR)/flyintel.o: flyintel.cpp
	$(CXX) -c flyintel.cpp -o $(BUILD_DIR)/flyintel.o

$(BUILD_DIR)/Sharp_IR.o: Sharp_IR.cpp
	$(CXX) -c Sharp_IR.cpp -o $(BUILD_DIR)/Sharp_IR.o

$(BUILD_DIR)/max7219.o: max7219.cpp
	$(CXX) -c max7219.cpp -o $(BUILD_DIR)/max7219.o

$(BUILD_DIR)/connect_to_flysim.o: connect_to_flysim.cpp
	$(CXX) -c connect_to_flysim.cpp -o $(BUILD_DIR)/connect_to_flysim.o

$(BUILD_DIR)/HC_SR04.o: HC_SR04.cpp
	$(CXX) -c HC_SR04.cpp -o $(BUILD_DIR)/HC_SR04.o

$(BUILD_DIR)/cltcmd.o: cltcmd.cpp
	$(CXX) -c cltcmd.cpp -o $(BUILD_DIR)/cltcmd.o

$(BUILD_DIR)/SPIadc.o: SPIadc.cpp
	$(CXX) -c SPIadc.cpp -o $(BUILD_DIR)/SPIadc.o

$(BUILD_DIR)/DCmotor.o: DCmotor.cpp
	$(CXX) -c DCmotor.cpp -o $(BUILD_DIR)/DCmotor.o

#dirmake:
#	mkdir -pv $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)/main.out $(BUILD_DIR)/*.o
