name:= push_swap
generator_name:= generator
bin_dir:= bin
SIZE ?= 500

tidy:
	@cd src && go mod tidy -v
	@cd src && go fmt ./...

build:
	@cd src && go build -o ../$(bin_dir)/$(name) ./cmd
	@cd src && go build -o ../$(bin_dir)/$(generator_name) ./cmd/generator

run:
	@make build
	@ARG="$$(./$(bin_dir)/$(generator_name) $(SIZE))"; \
	./$(bin_dir)/$(name) $$ARG > /tmp/ops.txt; \
	cat /tmp/ops.txt | ./checker_linux $$ARG; \
	rm -f /tmp/ops.txt

clean:
	@rm -f $(bin_dir)/$(name) $(bin_dir)/$(generator_name)

test:
	@cd src && go test -count=1 ./...

.PHONY: build run clean tidy test