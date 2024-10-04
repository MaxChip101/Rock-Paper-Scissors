# Compiler
CXX = g++
CXX_WIN = x86_64-w64-mingw32-g++

# Directories
SRC_DIR = src
BUILD_LINUX_DIR = build/linux
BUILD_WINDOWS_DIR = build/windows

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Executable names
EXEC_LINUX = rock_paper_scissors
EXEC_WINDOWS = rock_paper_scissors.exe

# Flags
CXXFLAGS = -Wall -std=c++17

# Default rule
all: linux

# Linux build
linux: $(BUILD_LINUX_DIR)/$(EXEC_LINUX)

$(BUILD_LINUX_DIR)/$(EXEC_LINUX): $(SOURCES)
	@mkdir -p $(BUILD_LINUX_DIR)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $@

# Windows build
windows: $(BUILD_WINDOWS_DIR)/$(EXEC_WINDOWS)

$(BUILD_WINDOWS_DIR)/$(EXEC_WINDOWS): $(SOURCES)
	@mkdir -p $(BUILD_WINDOWS_DIR)
	$(CXX_WIN) $(CXXFLAGS) $(SOURCES) -o $@

# Clean up the build directories
clean:
	rm -rf $(BUILD_LINUX_DIR)/$(EXEC_LINUX) $(BUILD_WINDOWS_DIR)/$(EXEC_WINDOWS)

# Make sure nothing else runs if the Makefile targets are up-to-date
.PHONY: all clean linux windows
