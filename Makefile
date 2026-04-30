CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -O2 $(shell pkg-config --cflags sdl2)
LDFLAGS = $(shell pkg-config --libs sdl2) -lm

TARGET = raytracer.exe
SRCS   = main.c camera.c scene.c trace.c render.c
OBJS   = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)
	cp /ucrt64/bin/SDL2.dll . 2>/dev/null || true

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
