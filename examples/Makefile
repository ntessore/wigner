CFLAGS += -std=c99 -Wall -Wextra -Werror -Wno-unknown-pragmas -pedantic
CFLAGS += -I../src
LDFLAGS += 
LDLIBS += -lm

ifdef DEBUG
CFLAGS += -O0 -g -DDEBUG
else
CFLAGS += -Ofast -march=native -mfpmath=sse
endif

.PHONY: all clean

all: cl_to_xi showdl

clean:
	$(RM) cl_to_xi showdl

cl_to_xi: cl_to_xi.c ../src/wigner_d_l.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) -o $@ $^ $(LDLIBS)

showdl: showdl.c ../src/wigner_d_l.c
	$(CC) $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) -o $@ $^ $(LDLIBS)
