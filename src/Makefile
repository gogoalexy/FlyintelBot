SHELL = /bin/sh
.SUFFIXES: .cpp .a .o
.PHONY: clean

CXX=g++
CXXFLAGS= -I/usr/include/libusb-1.0 -I../../../gitrepos/pixy2/src/host/libpixyusb2/include -I../../../gitrepos/pixy2/src/host/arduino/libraries/Pixy2 -DDEBUG -DPI
INC=-I/
LDLIBS=-lwiringPi ../../../gitrepos/pixy2/build/libpixyusb2/libpixy2.a -lusb-1.0
OPT=-O1

SRCS=HC_SR04.cpp Sharp_IR.cpp flyintel.cpp
OBJS=$(patsubst %.cpp,%.o,$(SRCS))

BUILD_DIR=../build

$(BUILD_DIR)/main.out: $(BUILD_DIR)/spikesHandler.o $(BUILD_DIR)/SCXmodel.o $(BUILD_DIR)/cltcmd.o $(BUILD_DIR)/connect_to_flysim.o $(BUILD_DIR)/main.o $(BUILD_DIR)/pixycam.o $(BUILD_DIR)/flyintel.o $(BUILD_DIR)/max7219.o $(BUILD_DIR)/SPIadc.o $(BUILD_DIR)/Sharp_IR.o $(BUILD_DIR)/HC_SR04.o $(BUILD_DIR)/DCmotor.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDLIBS) -Wall $(OPT)

$(BUILD_DIR)/main.o: main.cpp timer.h
	$(CXX) -c $(CXXFLAGS) $(INC) $< -o $(BUILD_DIR)/main.o $(OPT)

$(BUILD_DIR)/pixycam.o: pixycam.cpp pixycam.h
	$(CXX) -c $(CXXFLAGS) $< -o $(BUILD_DIR)/pixycam.o $(OPT)

$(BUILD_DIR)/spikesHandler.o: spikesHandler.cpp spikesHandler.h
	$(CXX) -c $< -o $(BUILD_DIR)/spikesHandler.o $(OPT)

$(BUILD_DIR)/SCXmodel.o: SCXmodel.cpp SCXmodel.h
	$(CXX) -c $< -o $(BUILD_DIR)/SCXmodel.o $(OPT)

$(BUILD_DIR)/flyintel.o: flyintel.cpp flyintel.h
	$(CXX) -c $< -o $(BUILD_DIR)/flyintel.o $(OPT)

$(BUILD_DIR)/Sharp_IR.o: Sharp_IR.cpp Sharp_IR.h
	$(CXX) -c $< -o $(BUILD_DIR)/Sharp_IR.o $(OPT)

$(BUILD_DIR)/max7219.o: max7219.cpp max7219.h
	$(CXX) -c $< -o $(BUILD_DIR)/max7219.o $(OPT)

$(BUILD_DIR)/connect_to_flysim.o: connect_to_flysim.cpp connect_to_flysim.h
	$(CXX) -c $< -o $(BUILD_DIR)/connect_to_flysim.o $(OPT)

$(BUILD_DIR)/HC_SR04.o: HC_SR04.cpp HC_SR04.h
	$(CXX) -c $< -o $(BUILD_DIR)/HC_SR04.o $(OPT)

$(BUILD_DIR)/cltcmd.o: cltcmd.cpp cltcmd.h
	$(CXX) -c $< -o $(BUILD_DIR)/cltcmd.o $(OPT)

$(BUILD_DIR)/SPIadc.o: SPIadc.cpp SPIadc.h adc.h
	$(CXX) -c $< -o $(BUILD_DIR)/SPIadc.o $(OPT)

$(BUILD_DIR)/DCmotor.o: DCmotor.cpp DCmotor.h
	$(CXX) -c $< -o $(BUILD_DIR)/DCmotor.o $(OPT)

clean:
	rm -rf $(BUILD_DIR)/main.out $(BUILD_DIR)/*.o
