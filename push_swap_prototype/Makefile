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
	@echo "🧪 Running all tests..."
	@go test ./... -count=1

test-solver:
	@echo "🎯 Running solver tests (main functionality)..."
	@go test -v ./internal/solver/...

test-verbose:
	@echo "🔍 Running all tests with verbose output..."
	@go test -v ./...

test-coverage:
	@echo "📊 Running tests with coverage..."
	@go test -v -coverprofile=coverage.out ./...
	@go tool cover -html=coverage.out -o coverage.html
	@echo "📈 Coverage report generated: coverage.html"

test-short:
	@echo "⚡ Running tests in short mode..."
	@go test -short ./...

.PHONY: build clean run tidy test test-solver test-verbose test-coverage test-short