# make        otevře prezentaci v prohlížeči
# make demos  pustí všechny benchmarky (viz demos/Makefile)

OPEN := $(shell command -v xdg-open || command -v open)

show:
	@$(OPEN) index.html >/dev/null 2>&1 &

demos:
	@$(MAKE) --no-print-directory -C demos run

particles lifetimes shapes clean:
	@$(MAKE) --no-print-directory -C demos $@

.PHONY: show demos particles lifetimes shapes clean
