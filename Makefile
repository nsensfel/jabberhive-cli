CFLAGS += -O3
CFLAGS += -D_POSIX_SOURCE
CFLAGS += -D_POSIX_C_SOURCE=200809L
################################################################################
EXECUTABLE = jh-cli
SRC_DIR = ./src
################################################################################
export
################################################################################

build: $(EXECUTABLE)

$(EXECUTABLE): $(SRC_DIR)/export.a
	$(CC) -o $@ $<

$(SRC_DIR)/export.a:
	$(MAKE) -C $(SRC_DIR) export.a

clean:
	$(MAKE) -C $(SRC_DIR) clean
	rm -f $(EXECUTABLE)
