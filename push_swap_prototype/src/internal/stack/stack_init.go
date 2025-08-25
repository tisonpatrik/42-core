package stack

// New creates a new empty stack
func New() *Stack {
	return &Stack{
		Stack:  []int{},
		Size:   0,
		Top:    0,
		Bottom: 0,
	}
}

// FillStack fills a stack with values from a slice (like C fill_stack)
func FillStack(s *Stack, values []int) {

	CheckDuplication(s, values)
	RandomToRank(values, s.Stack, s.Size)
	s.Bottom = s.Size - 1
}


func	CheckDuplication(s *Stack, values []int) {

	for i := 0; i < len(values); i++ {
		for j := i + 1; j < len(values); j++ {
			if values[i] == values[j] {
				panic("duplicated value")
			}
		}
	}

}

func	RandomToRank(numbers []int, rank []int, size int){
	for i := 0; i < size; i++ {
		countSmaller := 0
		
		for j := 0; j < size; j++ {
			if numbers[j] <= numbers[i] {
				countSmaller++
			}
		}
		
		rank[i] = countSmaller
	}
}