package separator

import (
	"fmt"
	"os"
	"push_swap_prototype/internal/stack"
)


func ComputeLISNodes(a *stack.Stack) map[*stack.Node]bool {
    logInput(a)

    nodes := make([]*stack.Node, 0, stack.GetSize(a))
    vals  := make([]int, 0, stack.GetSize(a))
    for n := stack.GetHead(a); n != nil; n = n.GetNext() {
        nodes = append(nodes, n)
        vals  = append(vals, n.GetContent())
    }
    n := len(vals)
    if n == 0 {
        return map[*stack.Node]bool{}
    }

    
    lisLen := make([]int, n)
    prev   := make([]int, n)
    bestLen, bestEnd := 0, 0

    for i := range n {
        lisLen[i] = 1
        prev[i]   = -1
        for j := 0; j < i; j++ {
            if vals[j] < vals[i] && lisLen[j]+1 > lisLen[i] {
                lisLen[i] = lisLen[j] + 1
                prev[i]   = j
            }
        }
        if lisLen[i] > bestLen {
            bestLen, bestEnd = lisLen[i], i
        }
    }

    inLIS := make(map[*stack.Node]bool, bestLen)
    for i := bestEnd; i != -1; i = prev[i] {
        inLIS[nodes[i]] = true
    }
    
    logOutput(vals, prev, bestEnd)
    
    return inLIS
}

func logInput(a *stack.Stack) {
	numbers := stack.ToArray(a)
	file, err := os.OpenFile("LIS.txt", os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0644)
	if err != nil {
		fmt.Printf("Error opening file: %v\n", err)
		return
	}
	defer file.Close()
	
	fmt.Fprintf(file, "input: %v\n", numbers)
}

func logOutput(vals []int, prev []int, bestEnd int) {
	// rekonstruuj posloupnost od konce
	order := make([]int, 0)
	for i := bestEnd; i != -1; i = prev[i] {
		order = append(order, vals[i])
	}
	// oto\u010d slice, proto\u017ee je pozp�tku
	for l, r := 0, len(order)-1; l < r; l, r = l+1, r-1 {
		order[l], order[r] = order[r], order[l]
	}

	file, err := os.OpenFile("LIS.txt", os.O_CREATE|os.O_WRONLY|os.O_APPEND, 0644)
	if err != nil {
		fmt.Printf("Error opening file: %v\n", err)
		return
	}
	defer file.Close()

	fmt.Fprintf(file, "output: %v\n", order)
}
