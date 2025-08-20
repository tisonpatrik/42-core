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


test:
	@echo "🧪 Running tests..."
	@go test ./internal/... -count=1

test-verbose:
	@go test -v ./internal/...

.PHONY: build clean run tidy test test-verbose