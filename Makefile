CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = alarme
TARGET_MENU = alarmeMenu

all: $(TARGET)

$(TARGET): main.cpp ComandoAlarme.cpp Sensor.cpp Simulacao.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp ComandoAlarme.cpp Sensor.cpp Simulacao.cpp

$(TARGET_MENU): mainMenu.cpp ComandoAlarme.cpp Sensor.cpp Simulacao.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET_MENU) mainMenu.cpp ComandoAlarme.cpp Sensor.cpp Simulacao.cpp

menu: $(TARGET_MENU)
	./$(TARGET_MENU)

clean:
	rm -f $(TARGET) $(TARGET_MENU)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run menu