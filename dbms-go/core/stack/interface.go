package stack

import (
  "errors"
)

func Execute(command string, number int, value string, reverse bool, values []string) ([]string, string, bool, error) {
  stack := Stack{}
  initStack(&stack)
  for i := len(values) - 1; i >= 0; i-- {
    push(&stack, values[i])
  }
  changed := false
  result := ""
  switch command {
  case "PRINT":
    print(&stack)
  case "SPUSH":
    push(&stack, value)
    changed = true
    result = value
  case "SINIT":
    initStack(&stack)
    changed = true
  case "SPOP":
    if isEmpty(&stack) {
      return nil, "", false, errors.New("стек пуст")
    }
    result = stack.head.value
    pop(&stack)
    changed = true
  case "SISEMPTY":
    if isEmpty(&stack) {
      result = "TRUE"
    } else {
      result = "FALSE"
    }
  default:
    return nil, "", false, errors.New("неизвестная команда стека")
  }
  saved := []string{}
  for current := stack.head; current != nil; current = current.next {
    saved = append(saved, current.value)
  }
  return saved, result, changed, nil
}
