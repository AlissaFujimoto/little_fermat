CC = gcc
CFLAGS = -O3 -Wall
LDFLAGS = 

OUT_DIR = _out
TARGET = $(OUT_DIR)/little_fermat.exe
SOURCES = source/main.c

all: $(OUT_DIR) $(TARGET)

$(OUT_DIR):
	if not exist $(OUT_DIR) mkdir $(OUT_DIR)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

format:
	clang-format -style=file -i $(SOURCES)

clean:
	if exist $(OUT_DIR)\* del /q $(OUT_DIR)\*

rebuild: clean all

build: all

run: build
	$(TARGET)

.PHONY: all clean rebuild format build run
