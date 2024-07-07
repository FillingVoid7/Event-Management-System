# Define the compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Iincludes

# List of all .cpp files in the src directory
SRCS = main.cpp \
       src/Login.cpp \
       src/CreateUserAccount.cpp \
       src/AdminPanel.cpp \
       src/JoinEvents.cpp \
       src/UserProfile.cpp \
       src/AdminReports.cpp \
       src/Database.cpp

# List of all .o files in the build directory
OBJS = $(SRCS:%.cpp=build/%.o)

# Name of the executable
TARGET = bin/event_management_system

# Default rule
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) -lsqlite3

# Rule to compile .cpp files to .o files in the build directory
build/%.o: %.cpp
	@mkdir -p $(@D)  # Create directories if they do not exist
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f build/*.o $(TARGET)

# Phony targets
.PHONY: all clean
