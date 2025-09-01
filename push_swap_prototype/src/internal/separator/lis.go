package separator

import "push_swap_prototype/internal/stack"

// ComputeLISNodes computes the Longest Increasing Subsequence (LIS) of the given stack.
// Returns a map indicating which nodes are part of the LIS.
func ComputeLISNodes(a *stack.Stack) map[*stack.Node]bool {
    // 1) Zkopruj uzly i hodnoty do slice (pořad�: top -> bottom)
    nodes := make([]*stack.Node, 0, stack.GetSize(a))
    vals  := make([]int, 0, stack.GetSize(a))
    for n := stack.GetHead(a); n != nil; n = n.GetNext() {
        nodes = append(nodes, n)
        vals  = append(vals, n.GetContent()) // adjust according to your value field
    }
    n := len(vals)
    if n == 0 {
        return map[*stack.Node]bool{}
    }

    // 2) DP lisLen[i] = length of LIS ending at i; prev[i] = predecessor
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

    // 3) Reconstruction - go through prev[] from bestEnd and mark nodes
    inLIS := make(map[*stack.Node]bool, bestLen)
    for i := bestEnd; i != -1; i = prev[i] {
        inLIS[nodes[i]] = true
    }
    return inLIS
}