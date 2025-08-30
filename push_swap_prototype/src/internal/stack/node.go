package stack

type Node struct {
	content int
	prev    *Node
	next    *Node
}

// CreateNode creates a new node with given content
func CreateNode(content int) *Node {
	return &Node{
		content: content,
		prev:    nil,
		next:    nil,
	}
}

// GetContent returns the content value of the node
func (n *Node) GetContent() int {
	return n.content
}

// GetNext returns the next node pointer
func (n *Node) GetNext() *Node {
	return n.next
}

// GetPrev returns the previous node pointer
func (n *Node) GetPrev() *Node {
	return n.prev
}