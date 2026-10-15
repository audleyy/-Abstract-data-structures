package singly_linked_list

import (
  "errors"
  "fmt"
)

func nodeAt(head *Node, index int) *Node {
  if index < 0 {
    return nil
  }
  current := head
  for i := 0; i < index && current != nil; i++ {
    current = current.next
  }
  return current
}

func Execute(command string, number int, value string, reverse bool, values []string) ([]string, string, bool, error) {
  var head *Node
  for _, item := range values {
    addToTail(&head, item)
  }
  changed := false
  result := ""
  switch command {
  case "PRINT":
    if reverse {
      printReverse(head)
      fmt.Println()
    } else {
      printRegular(head)
    }
  case "FPUSH":
    addToTail(&head, value)
    changed = true
    result = value
  case "FPUSHHEAD":
    addToHead(&head, value)
    changed = true
    result = value
  case "FSEARCH":
    found := findNode(head, value)
    index := -1
    if found != nil {
      index = 0
      for current := head; current != found; current = current.next {
        index++
      }
    }
    result = fmt.Sprint(index)
  case "FDELHEAD", "FDELTAIL":
    if head == nil {
      return nil, "", false, errors.New("список пуст")
    }
    if command == "FDELHEAD" {
      deleteHead(&head)
    } else {
      deleteTail(&head)
    }
    changed = true
  default:
    nodeFound := nodeAt(head, number)
    if nodeFound == nil {
      return nil, "", false, errors.New("неверный индекс списка")
    }
    switch command {
    case "FGET":
      printIndex(head, number)
    case "FPUSHBEFORE":
      addBefore(&head, nodeFound, value)
      changed = true
      result = value
    case "FPUSHAFTER":
      addAfter(nodeFound, value)
      changed = true
      result = value
    case "FDEL":
      deleteCurrent(&head, nodeFound)
      changed = true
    case "FDELBEFORE":
      if nodeFound == head {
        return nil, "", false, errors.New("перед головой нет элемента")
      }
      deleteBefore(&head, nodeFound)
      changed = true
    case "FDELAFTER":
      if nodeFound.next == nil {
        return nil, "", false, errors.New("после хвоста нет элемента")
      }
      deleteAfter(nodeFound)
      changed = true
    default:
      return nil, "", false, errors.New("неизвестная команда списка")
    }
  }
  saved := []string{}
  for current := head; current != nil; current = current.next {
    saved = append(saved, current.value)
  }
  return saved, result, changed, nil
}
