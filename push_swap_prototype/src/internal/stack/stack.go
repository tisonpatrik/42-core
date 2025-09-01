package stack

import "fmt"

type Stack struct {
	head *Node 
	tail *Node 
	size int   // current size
}


func InitStack() *Stack {
	return &Stack{
		head: nil,
		tail: nil,
		size: 0,
	}
}

func GetSize(s *Stack) int {
	return s.size
}

func IsEmpty(s *Stack) bool {
	return s.size == 0
}


func GetHead(s *Stack) *Node {
	return s.head
}


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


func PrintStack(s *Stack, name string) {
	current := s.head
	for current != nil {
		fmt.Printf("%d ", current.content)
		current = current.next
	}
	fmt.Println()
}