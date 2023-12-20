SOURCE = main.cpp

LIBRARY = ncurses

TARGET = $(SOURCE:.cpp=)

CXX = g++

all: $(TARGET)
$(TARGET): $(SOURCE)
	@echo "Commpiling..."
	@$(CXX) $(SOURCE) -o $(TARGET) -l $(LIBRARY)

run:
	@./$(TARGET)

clean:
	@echo "Cleaning.."
	@rm $(TARGET)

.PHONY: all run clean

