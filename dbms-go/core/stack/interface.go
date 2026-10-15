package stack

import (
  "errors"
  "fmt"
)

func Execute(command string, number int, number2 int, reverse bool, values []int) ([]int, string, bool, error) {
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
    push(&stack, number)
    changed = true
    result = fmt.Sprint(number)
  case "SPOP":
    if isEmpty(&stack) {
      return nil, "", false, errors.New("стек пуст")
    }
    result = fmt.Sprint(stack.head.value)
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
  saved := []int{}
  for current := stack.head; current != nil; current = current.next {
    saved = append(saved, current.value)
  }
  return saved, result, changed, nil
}
