CFLAGS = -Wall -Wextra -std=c11 -pedantic
OUTPUT_DIR = build

# Read the list of source files from MakefileList
SRC_FILES = $(shell cat MakefileList)

# Output executable name
OUTPUT = $(OUTPUT_DIR)/server

all: $(OUTPUT_DIR) $(OUTPUT)

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

$(OUTPUT): $(SRC_FILES) | $(OUTPUT_DIR)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SRC_FILES)

clean:
	rm -f $(OUTPUT_DIR)/*
