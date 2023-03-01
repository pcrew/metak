
.PHONY: clean cleanall

SOURCES = $(wildcard *.cc)
OBJECTS = $(SOURCES:.cc=.o)
PROGRAM = example

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) -rdynamic $(OBJECTS) -o $@

clean:
	@rm -rf $(PROGRAM)

cleanall: clean
