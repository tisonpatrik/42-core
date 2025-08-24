name:= push_swap_prototype
bin_dir:= bin

tidy:
	@cd src && go mod tidy -v
	@cd src && go fmt ./...

build:
	@cd src && go build -o ../$(bin_dir)/$(name) ./cmd

run:
	@make build
	@./$(bin_dir)/$(name)

clean:
	@rm -f $(bin_dir)/$(name)

test:
	@cd src && go test -count=1 ./...

lab:
	@cd lab && make all

.PHONY: build clean run tidy test lab