package moves

import "push_swap_prototype/internal/stack"

func ComputeLISNodes(a *stack.Stack) map[*stack.Node]bool {
    // 1) Zkop�ruj uzly i hodnoty do slice (po\u0159ad�: top -> bottom)
    nodes := make([]*stack.Node, 0, stack.GetSize(a))
    vals  := make([]int, 0, stack.GetSize(a))
    for n := stack.GetHead(a); n != nil; n = n.GetNext() {
        nodes = append(nodes, n)
        vals  = append(vals, n.GetContent()) // uprav podle tvého pole s hodnotou
    }
    n := len(vals)
    if n == 0 {
        return map[*stack.Node]bool{}
    }

    // 2) DP lisLen[i] = d�lka LIS kon\u010d�c� na i; prev[i] = p\u0159edch\u016fdce
    lisLen := make([]int, n)
    prev   := make([]int, n)
    bestLen, bestEnd := 0, 0

    for i := 0; i < n; i++ {
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

    // 3) Rekonstrukce \u2013 projdi prev[] od bestEnd a ozna\u010d uzly
    inLIS := make(map[*stack.Node]bool, bestLen)
    for i := bestEnd; i != -1; i = prev[i] {
        inLIS[nodes[i]] = true
    }
    return inLIS
}