# Directories
MICRO_DIR = micro
BUILD_DIR = $(MICRO_DIR)/build
JOYSTICK_APP_DIR = Joystick_app

# Target pattern for the .so file
SO_FILE_PATTERN = microdrive.cpython-*.so

# Default target
all: build copy install

# Create build directory, run cmake, and compile
build:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake ..
	cd $(BUILD_DIR) && make

# Copy the generated .so file to the Joystick_app directory
copy: build
	cp $(BUILD_DIR)/$(SO_FILE_PATTERN) $(JOYSTICK_APP_DIR)

# Run pyinstaller
install: copy
	cd $(JOYSTICK_APP_DIR) && pyinstaller joystick.spec

# Clean up build files and output
clean:
	rm -rf $(BUILD_DIR)
	rm -f $(JOYSTICK_APP_DIR)/$(SO_FILE_PATTERN)
	rm -rf $(JOYSTICK_APP_DIR)/build/ $(JOYSTICK_APP_DIR)/dist/ $(JOYSTICK_APP_DIR)/__pycache__/

.PHONY: all build copy install clean
