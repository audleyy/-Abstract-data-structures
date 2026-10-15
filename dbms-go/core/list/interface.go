package doubly_linked_list

import (
  "errors"
  "fmt"
)

func nodeAt(list *List, index int) *Node {
  if index < 0 {
    return nil
  }
  current := list.head
  for i := 0; i < index && current != nil; i++ {
    current = current.next
  }
  return current
}

func Execute(command string, number int, value string, reverse bool, values []string) ([]string, string, bool, error) {
  list := List{}
  for _, item := range values {
    addTail(&list, item)
  }
  changed := false
  result := ""
  switch command {
  case "PRINT":
    if reverse {
      printReverse(&list)
      fmt.Println()
    } else {
      printRegular(&list)
    }
  case "LPUSH":
    addTail(&list, value)
    changed = true
    result = value
  case "LPUSHHEAD":
    addHead(&list, value)
    changed = true
    result = value
  case "LSEARCH":
    found := findNode(list.head, value)
    index := -1
    if found != nil {
      index = 0
      for current := list.head; current != found; current = current.next {
        index++
      }
    }
    result = fmt.Sprint(index)
  case "LDELHEAD", "LDELTAIL":
    if list.head == nil {
      return nil, "", false, errors.New("список пуст")
    }
    if command == "LDELHEAD" {
      delHead(&list)
    } else {
      delTail(&list)
    }
    changed = true
  default:
    nodeFound := nodeAt(&list, number)
    if nodeFound == nil {
      return nil, "", false, errors.New("неверный индекс списка")
    }
    switch command {
    case "LGET":
      printIndex(&list, number)
    case "LPUSHBEFORE":
      addBefore(&list, nodeFound, value)
      changed = true
      result = value
    case "LPUSHAFTER":
      addAfter(&list, nodeFound, value)
      changed = true
      result = value
    case "LDEL":
      if nodeFound == list.head {
        delHead(&list)
      } else if nodeFound == list.tail {
        delTail(&list)
      } else {
        delAfter(&list, nodeFound.prev)
      }
      changed = true
    case "LDELBEFORE":
      if nodeFound.prev == nil {
        return nil, "", false, errors.New("перед головой нет элемента")
      }
      delBefore(&list, nodeFound)
      changed = true
    case "LDELAFTER":
      if nodeFound.next == nil {
        return nil, "", false, errors.New("после хвоста нет элемента")
      }
      delAfter(&list, nodeFound)
      changed = true
    default:
      return nil, "", false, errors.New("неизвестная команда списка")
    }
  }
  saved := []string{}
  for current := list.head; current != nil; current = current.next {
    saved = append(saved, current.value)
  }
  return saved, result, changed, nil
}
