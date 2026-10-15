package singly_linked_list

import "fmt"

type Node struct {
  value string
  next  *Node
}

func addToHead(head **Node, value string) {
  newNode := &Node{value, nil}
  newNode.next = *head
  *head = newNode
}

func addToTail(head **Node, value string) {
  newNode := &Node{value, nil}
  current := *head
  if *head == nil {
    *head = newNode
    return
  }
  for current.next != nil {
    current = current.next
  }
  current.next = newNode
}

func addAfter(nodeFound *Node, value string) {
  newNode := &Node{value, nil}
  newNode.next = nodeFound.next
  nodeFound.next = newNode
}

func addBefore(head **Node, nodeFound *Node, value string) {
  newNode := &Node{value, nil}
  current := *head
  if nodeFound == *head {
    newNode.next = nodeFound
    *head = newNode
    return
  }
  for current.next != nodeFound {
    current = current.next
  }
  newNode.next = nodeFound
  current.next = newNode
}

func findNode(head *Node, val string) *Node {
  current := head
  for current != nil {
    if current.value == val {
      return current
    }
    current = current.next
  }
  return nil
}

func deleteHead(head **Node) {
  if *head == nil {
    return
  }
  toDelete := *head
  *head = toDelete.next
}

func deleteTail(head **Node) {
  if *head == nil {
    return
  }
  if (*head).next == nil {
    *head = nil
    return
  }
  toDelete := *head
  for toDelete.next.next != nil {
    toDelete = toDelete.next
  }
  toDelete.next = nil
}

func deleteBefore(head **Node, nodeFound *Node) {
  if (*head).next == nodeFound {
    *head = nodeFound
    return
  }
  temp := *head
  for temp.next.next != nodeFound {
    temp = temp.next
  }
  toDelete := temp.next
  temp.next = toDelete.next
}

func deleteAfter(nodeFound *Node) {
  if nodeFound.next == nil {
    return
  }
  nodeFound.next = nodeFound.next.next
}

func deleteCurrent(head **Node, nodeFound *Node) {
  if nodeFound == *head {
    *head = nodeFound.next
    return
  }
  temp := *head
  for temp.next != nodeFound {
    temp = temp.next
  }
  temp.next = nodeFound.next
}

func printRegular(head *Node) {
  current := head
  for current != nil {
    fmt.Printf("%s ", current.value)
    current = current.next
  }
  fmt.Println()
}

func printReverse(head *Node) {
  if head == nil {
    return
  }
  printReverse(head.next)
  fmt.Printf("%s ", head.value)
}

func printIndex(head *Node, index int) {
  current := head
  for i := 0; i < index && current != nil; i++ {
    current = current.next
  }
  if current != nil {
    fmt.Println(current.value)
  }
}


func initForwardList(head **Node) {
  *head = nil
}

