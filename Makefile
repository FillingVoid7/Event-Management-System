# Define the compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Iincludes

# List of all .cpp files in the src directory
SRCS = src/main.cpp \
       src/Login.cpp \
       src/CreateUserAccount.cpp \
       src/AdminPanel.cpp \
       src/JoinEvents.cpp \
       src/UserProfile.cpp \
       src/AdminReports.cpp \
       src/Database.cpp \
       src/PasswordField.cpp \
       src/HashInputPassword.cpp

# List of all .o files in the build directory
OBJS = $(SRCS:src/%.cpp=build/%.o)

# Name of the executable
TARGET = bin/event_management_system

# Default rule
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) -lsqlite3 -lsodium

# Rule to compile .cpp files to .o files in the build directory
build/%.o: src/%.cpp
	@mkdir -p $(@D)  # Create directories if they do not exist
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f build/*.o $(TARGET)

# Phony targets
.PHONY: all clean

