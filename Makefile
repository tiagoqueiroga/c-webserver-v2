CFLAGS = -Wall -Wextra -std=c11 -pedantic
OUTPUT_DIR = build

all: $(OUTPUT_DIR) server

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

server: server.c request.c | $(OUTPUT_DIR)
	$(CC) $(CFLAGS) -o $(OUTPUT_DIR)/server server.c request.c

clean:
	rm -f $(OUTPUT_DIR)/*
