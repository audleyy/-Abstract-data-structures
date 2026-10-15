package queue

import (
  "errors"
)

func Execute(command string, number int, value string, reverse bool, values []string) ([]string, string, bool, error) {
  queue := Queue{}
  initQueue(&queue)
  for _, item := range values {
    enqueue(&queue, item)
  }
  changed := false
  result := ""
  switch command {
  case "PRINT":
    print(&queue)
  case "QPUSH":
    enqueue(&queue, value)
    changed = true
    result = value
  case "QINIT":
    initQueue(&queue)
    changed = true
  case "QPOP":
    if queue.head == nil {
      return nil, "", false, errors.New("очередь пуста")
    }
    result = queue.head.value
    dequeue(&queue)
    changed = true
  default:
    return nil, "", false, errors.New("неизвестная команда очереди")
  }
  saved := []string{}
  for current := queue.head; current != nil; current = current.next {
    saved = append(saved, current.value)
  }
  return saved, result, changed, nil
}
