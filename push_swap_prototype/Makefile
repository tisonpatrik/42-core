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
	@echo "🧪 Running all Go tests..."
	@go test ./... 2>&1 | awk '/^ok/ {print "✅ " $$0} /^FAIL/ {print "❌ " $$0} /^=== RUN/ {print "▶️  " $$0} /^--- PASS/ {print "✅ " $$0} /^--- FAIL/ {print "❌ " $$0}'

.PHONY: build clean run tidy test 