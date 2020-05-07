CFLAGS += -std=c99 -Wall -Wextra -Werror -Wno-unknown-pragmas -pedantic
LDFLAGS += 
LDLIBS += -lm

ifdef DEBUG
CFLAGS += -O0 -g -DDEBUG
else
CFLAGS += -Ofast -march=native -mfpmath=sse
endif

.PHONY: all clean

all: wigner_d.so

clean:
	$(RM) wigner_d.so

wigner_d.so: wigner_d.c
	$(CC) -shared $(CFLAGS) $(LDFLAGS) $(CPPFLAGS) -o $@ $^ $(LDLIBS)
