################################################################################
SRC_FILES = $(wildcard ./*.c)
OBJ_FILES = $(SRC_FILES:.c=.o)
DEP_FILES = $(SRC_FILES:.c=.d)
################################################################################

build: export.a

export.a: $(OBJ_FILES)
	ar cr $@ $^

clean:
	rm -f $(OBJ_FILES)
	rm -f $(DEP_FILES)
	rm -f export.a

%.d: %.c
	@set -e; rm -f $@; \
		$(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

include $(DEP_FILES)
