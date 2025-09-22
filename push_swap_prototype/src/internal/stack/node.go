package stack

type Node struct {
	content int
	prev    *Node
	next    *Node
}

func CreateNode(content int) *Node {
	return &Node{
		content: content,
		prev:    nil,
		next:    nil,
	}
}

func (n *Node) GetContent() int {
	return n.content
}

func (n *Node) GetNext() *Node {
	return n.next
}

func (n *Node) GetPrev() *Node {
	return n.prev
}