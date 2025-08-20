name:= push_swap_prototype
bin_dir:= bin

tidy:
	go mod tidy -v
	go fmt ./...

build:
	@go build -o $(bin_dir)/$(name) ./cmd

run:
	@make build
	@./$(bin_dir)/$(name)

clean:
	@rm -f $(bin_dir)/$(name)

.PHONY: build clean run tidy