package queue

import (
  "errors"
  "fmt"
)

func Execute(command string, number int, number2 int, reverse bool, values []int) ([]int, string, bool, error) {
  queue := Queue{}
  initQueue(&queue)
  for _, value := range values {
    enqueue(&queue, value)
  }
  changed := false
  result := ""
  switch command {
  case "PRINT":
    print(&queue)
  case "QPUSH":
    enqueue(&queue, number)
    changed = true
    result = fmt.Sprint(number)
  case "QPOP":
    if queue.head == nil {
      return nil, "", false, errors.New("очередь пуста")
    }
    result = fmt.Sprint(queue.head.value)
    dequeue(&queue)
    changed = true
  default:
    return nil, "", false, errors.New("неизвестная команда очереди")
  }
  saved := []int{}
  for current := queue.head; current != nil; current = current.next {
    saved = append(saved, current.value)
  }
  return saved, result, changed, nil
}
