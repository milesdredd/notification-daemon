# Compiler settings
CXX = g++
CC  = gcc
PKG_CONFIG = pkg-config
CFLAGS = $(shell $(PKG_CONFIG) --cflags gio-2.0 glib-2.0)
LIBS   = $(shell $(PKG_CONFIG) --libs gio-2.0 glib-2.0)

# paths
SRC_DIR = src
BUILD_DIR = build
TARGET = notify

# src files
CPP_SOURCES = $(SRC_DIR)/daemon.cpp
C_SOURCES   = $(SRC_DIR)/notification-service.c

# files
OBJECTS = $(BUILD_DIR)/daemon.o $(BUILD_DIR)/notification-service.o

# def
all: $(TARGET)

# if missing
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# generating code if not avail
$(SRC_DIR)/notification-service.c $(SRC_DIR)/notification-service.h: $(SRC_DIR)/org.freedesktop.Notifications.xml
	gdbus-codegen --generate-c-code=$(SRC_DIR)/notification-service $<

# Compiling
$(BUILD_DIR)/daemon.o: $(CPP_SOURCES) | $(BUILD_DIR)
	$(CXX) -c $< -o $@ $(CFLAGS)

# Compile generated C source
$(BUILD_DIR)/notification-service.o: $(C_SOURCES) | $(BUILD_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

# link all
$(TARGET): $(OBJECTS)
	$(CXX) $^ -o $@ $(LIBS)

# Remove build stuff
clean:
	rm -rf $(BUILD_DIR) $(TARGET)
.PHONY: all clean
