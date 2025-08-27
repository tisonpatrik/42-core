package stack

import "fmt"

// Stack represents a doubly-linked list stack
type Stack struct {
	head *Node // pointer to first node
	tail *Node // pointer to last node
	size int   // current size
}

// InitStack creates a new empty stack
func InitStack() *Stack {
	return &Stack{
		head: nil,
		tail: nil,
		size: 0,
	}
}

// GetSize returns the current number of elements in the stack
func GetSize(s *Stack) int {
	return s.size
}

// IsEmpty checks if the stack is empty
func IsEmpty(s *Stack) bool {
	return s.size == 0
}


// GetTop returns the top element of the stack (first element)
func GetTop(s *Stack) *Node {
	return s.head
}

// GetBottom returns the bottom element of the stack (last element)
func GetBottom(s *Stack) *Node {
	return s.tail
}


// ClearStack removes all nodes and frees memory
func ClearStack(s *Stack) {
	current := s.head
	for current != nil {
		next := current.next
		current.prev = nil
		current.next = nil
		current = next
	}
	s.head = nil
	s.tail = nil
	s.size = 0
}

// PrintStack prints the stack contents for debugging
func PrintStack(s *Stack, name string) {
	fmt.Printf("----Printing Stack %s (Top to Down)-------\n", name)
	current := s.head
	for current != nil {
		fmt.Printf("%d ", current.content)
		current = current.next
	}
	fmt.Println()
}