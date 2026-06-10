CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = alarme

all: $(TARGET)

$(TARGET): main.cpp ComandoAlarme.cpp Sensor.cpp Simulacao.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp ComandoAlarme.cpp Sensor.cpp Simulacao.cpp

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run