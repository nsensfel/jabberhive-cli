################################################################################
################################################################################
CFLAGS += -O3
CFLAGS += -Wall -Wextra -pedantic -Werror
CFLAGS += -D_POSIX_SOURCE
CFLAGS += -D_POSIX_C_SOURCE=200809L
################################################################################
EXECUTABLE ?= jh-cli
BASE_DIR ?= $(CURDIR)
SRC_DIR ?= $(BASE_DIR)/src
COMPILE_DIR ?= $(BASE_DIR)/compilation_data
################################################################################
SRC_FILES ?= $(shell find $(SRC_DIR) -type f -name *.c)
OBJ_FILES ?= $(patsubst $(SRC_DIR)/%.c,$(COMPILE_DIR)/%.o,$(SRC_FILES))
DEP_FILES ?= $(patsubst %.o,%.d,$(OBJ_FILES))
################################################################################

build: $(EXECUTABLE)

$(OBJ_FILES): $(COMPILE_DIR)/%.o : $(SRC_DIR)/%.c $(COMPILE_DIR)/%.d
	$(CC) $(CFLAGS) -c -o $@ $<

$(DEP_FILES): $(COMPILE_DIR)/%.d: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	@set -e; rm -f $@; \
		$(CC) -M $(CFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -fr $(EXECUTABLE) $(COMPILE_DIR)
