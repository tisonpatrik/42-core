CC      := cc
CFLAGS  := -O2 -Wall -Wextra
BINS    := c/shapes c/particles c/arena c/hotcold

all: $(BINS)

c/%: c/%.c
	$(CC) $(CFLAGS) $< -o $@

shapes: c/shapes
	@echo "--- C" && ./c/shapes
	@echo "--- Python" && python3 python/shapes.py

particles: c/particles
	@echo "--- C (N = 1M)" && ./c/particles
	@echo "--- Python (N = 1M)" && python3 python/particles.py

lifetimes: c/arena
	@echo "--- C" && ./c/arena
	@echo "--- Python" && python3 python/frame_alloc.py

hotcold: c/hotcold
	@echo "--- C (N = 1M)" && ./c/hotcold

run: shapes particles hotcold lifetimes

clean:
	rm -f $(BINS)

.PHONY: all run shapes particles hotcold lifetimes clean
