package doubly_linked_list

import "fmt"

type Node struct {
  value int
  next  *Node
  prev  *Node
}

type List struct {
  head *Node
  tail *Node
}

func addTail(list *List, value int) {
  newNode := &Node{value, nil, nil}
  if list.head == nil {
    list.head = newNode
    list.tail = newNode
  } else {
    newNode.prev = list.tail
    list.tail.next = newNode
    list.tail = newNode
  }
}

func addHead(list *List, value int) {
  newNode := &Node{value, nil, nil}
  if list.head == nil {
    list.head = newNode
    list.tail = newNode
  } else {
    newNode.next = list.head
    list.head.prev = newNode
    list.head = newNode
  }
}

func findNode(list *Node, val int) *Node {
  current := list
  for current.next != nil {
    if current.value == val {
      return current
    }
    current = current.next
  }
  return nil
}

func addAfter(list *List, nodeFound *Node, value int) {
  newNode := &Node{value, nil, nil}
  if nodeFound.next == nil {
    nodeFound.next = newNode
    newNode.prev = nodeFound
    list.tail = newNode
  } else {
    newNode.next = nodeFound.next
    newNode.prev = nodeFound
    nodeFound.next.prev = newNode
    nodeFound.next = newNode
  }
}

func addBefore(list *List, nodeFound *Node, value int) {
  newNode := &Node{value, nil, nil}
  if nodeFound.prev == nil {
    newNode.next = nodeFound
    nodeFound.prev = newNode
    list.head = newNode
  } else {
    newNode.next = nodeFound
    newNode.prev = nodeFound.prev
    nodeFound.prev.next = newNode
    nodeFound.prev = newNode
  }
}

func delHead(list *List) {
  if list.head == nil {
    return
  }
  toDelete := list.head
  if list.head.next == nil {
    list.head = nil
    list.tail = nil
    return
  }
  list.head = toDelete.next
  list.head.prev = nil
}

func delTail(list *List) {
  if list.tail == nil {
    return
  }
  if list.head == list.tail {
    list.head = nil
    list.tail = nil
    return
  }
  toDelete := list.tail
  list.tail = toDelete.prev
  list.tail.next = nil
}

func delAfter(list *List, nodeFound *Node) {
  if nodeFound.next == nil {
    return
  }
  if nodeFound.next == list.tail {
    delTail(list)
    return
  }
  toDelete := nodeFound.next
  nodeFound.next.prev = nodeFound
  nodeFound.next = toDelete.next
}

func delBefore(list *List, nodeFound *Node) {
  if nodeFound.prev == nil {
    return
  }
  if nodeFound.prev == list.head {
    delHead(list)
    return
  }
  toDelete := nodeFound.prev
  nodeFound.prev.next = nodeFound
  nodeFound.prev = toDelete.prev
}

func printRegular(list *List) {
  current := list.head
  for current != nil {
    fmt.Printf("%d ", current.value)
    current = current.next
  }
  fmt.Println()
}

func printReverse(list *List) {
  if list == nil {
    return
  }
  current := list.tail
  for current != nil {
    fmt.Printf("%d ", current.value)
    current = current.prev
  }
}

func printIndex(list *List, index int) {
  current := list.head
  for i := 0; i < index; i++ {
    current = current.next
  }
  fmt.Println(current.value)
}
