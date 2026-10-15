package queue

import "fmt"

type Node struct {
  value string
  next  *Node
}

type Queue struct {
  head *Node
  tail *Node
}

func initQueue(queue *Queue) {
  queue.head = nil
  queue.tail = nil
}

func enqueue(queue *Queue, value string) {
  newNode := &Node{value, nil}
  if queue.head == nil {
    newNode.next = queue.head
    queue.head = newNode
    queue.tail = newNode
    return
  }
  queue.tail.next = newNode
  queue.tail = newNode
}

func dequeue(queue *Queue) {
  if queue.head == nil {
    return
  }
  toDelete := queue.head
  queue.head = toDelete.next
  if queue.head == nil {
    queue.tail = nil
  }
}

func print(queue *Queue) {
  current := queue.head
  for current != nil {
    fmt.Printf("%s ", current.value)
    current = current.next
  }
  fmt.Println()
}
