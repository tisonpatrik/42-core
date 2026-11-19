# make        open the slides in the browser
# make demos  run every benchmark (see demos/Makefile)

OPEN := $(shell command -v xdg-open || command -v open)

show:
	@$(OPEN) index.html >/dev/null 2>&1 &

demos:
	@$(MAKE) --no-print-directory -C demos run

particles hotcold lifetimes beyond division shapes clean:
	@$(MAKE) --no-print-directory -C demos $@

.PHONY: show demos particles hotcold lifetimes beyond division shapes clean
