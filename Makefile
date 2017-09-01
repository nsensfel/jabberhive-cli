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
	$(CC) $(CFLAGS) -o $@ $<

$(SRC_DIR)/export.a: .JUST_CHECK
	$(MAKE) -C $(SRC_DIR) export.a

clean:
	$(MAKE) -C $(SRC_DIR) clean
	rm -f $(EXECUTABLE)

.JUST_CHECK:
