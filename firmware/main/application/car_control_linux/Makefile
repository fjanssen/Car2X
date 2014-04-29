CC=g++
CFLAGS=-c -pthread -w
LDFLAGS= -pthread

SOURCES  = ../../etc/utility.cpp

SOURCES += ../../networking/CarMessage.cpp 
SOURCES += ../../networking/ADCMessage.cpp 
SOURCES += ../../networking/ADCValuesMessage.cpp 
SOURCES += ../../networking/GSensorMessage.cpp 
SOURCES += ../../networking/MotorMeasurementMessage.cpp 
SOURCES += ../../networking/MotorVelocityMessage.cpp 
SOURCES += ../../networking/UltrasoundDistanceMessage.cpp 
SOURCES += ../../networking/WelcomeMessage.cpp 
SOURCES += ../../networking/CarProtocol.cpp 

SOURCES += ../../car_control_linux/SensorState.cpp 
SOURCES += ../../car_control_linux/ADCSensorState.cpp 
SOURCES += ../../car_control_linux/GSensorState.cpp
SOURCES += ../../car_control_linux/UltrasoundSensorState.cpp

SOURCES += ../../web_interface/client_list.cpp
SOURCES += ../../web_interface/webserver.cpp
SOURCES += ../../car_control_linux/RemoteConnection.cpp
SOURCES += ../../car_control_linux/CarAPI.cpp
SOURCES += ../../car_control_linux/main.cpp

INCLUDES  = ../../car_control_linux

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=car_control

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ -I $(INCLUDES) -D CENTRAL_ECU_BUILD
