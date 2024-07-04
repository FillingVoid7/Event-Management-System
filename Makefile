# Define the compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -I.

# List of all .cpp files
SRCS = main.cpp Login.cpp CreateUserAccount.cpp AdminPanel.cpp JoinEvents.cpp UserProfile.cpp EventSearch.cpp Comment.cpp Notification.cpp AdminReports.cpp EventReminder.cpp EventFeedback.cpp Database.cpp

# List of all .o files
OBJS = $(SRCS:.cpp=.o)

# Name of the executable
TARGET = event_management_system

# Default rule
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) -lsqlite3

# Rule to compile .cpp files to .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
