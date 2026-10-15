package queue

import "fmt"

type Node struct {
  value int
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

func enqueue(queue *Queue, value int) {
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
    fmt.Printf("%d ", current.value)
    current = current.next
  }
  fmt.Println()
}
