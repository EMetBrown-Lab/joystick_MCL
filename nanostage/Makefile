# Directories
BUILD_DIR = ./build

# Target pattern for the .so file
SO_FILE_PATTERN = nanostage.cpython-*.so

# Default target
all: build copy
# Create build directory, run cmake, and compile
build:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ..
	cd $(BUILD_DIR) && make

# Copy the generated .so file to the Joystick_app directory
copy: build
	cp $(BUILD_DIR)/$(SO_FILE_PATTERN) ./

# # Run pyinstaller
# install: copy
# 	cd $(JOYSTICK_APP_DIR) && pyinstaller joystick.spec

# # Clean up build files and output
clean:
	rm -rf $(BUILD_DIR)
	rm -f ./$(SO_FILE_PATTERN)

.PHONY: all build clean