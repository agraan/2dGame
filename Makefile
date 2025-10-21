# === User variables ===
BUILD_DIR := build
CMAKE_DIR := cmake
TARGET := $(CMAKE_DIR)/MyGame

# === Default rule ===
all: $(BUILD_DIR)/Makefile
	@$(MAKE) --no-print-directory -C $(BUILD_DIR)

# === Configure CMake if needed ===
$(BUILD_DIR)/Makefile:
	@echo "==> Creating build directory and configuring CMake..."
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=Debug ../$(CMAKE_DIR)

# === Run the game ===
run:
	@./$(TARGET)

# === Clean build files ===
clean:
	@echo "==> Cleaning build directory..."
	@rm -rf $(BUILD_DIR)

# === Full rebuild ===
rebuild: clean all

