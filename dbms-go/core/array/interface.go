package dynamic_array

import (
  "errors"
  "fmt"
)

func Execute(command string, number int, value string, reverse bool, values []string) ([]string, string, bool, error) {
  arr := Array{}
  initArray(&arr)
  for _, item := range values {
    pushBack(&arr, item)
  }
  defer destroy(&arr)
  changed := false
  result := ""
  switch command {
  case "PRINT":
    print(arr)
  case "MPUSH":
    pushBack(&arr, value)
    changed = true
    result = value
  case "MLEN":
    result = fmt.Sprint(length(&arr))
  case "MPUSHINDEX":
    if number < 0 || number >= arr.size {
      return nil, "", false, errors.New("индекс вставки должен быть меньше размера массива")
    }
    pushIndex(&arr, number, value)
    changed = true
    result = value
  default:
    if number < 0 || number >= arr.size {
      return nil, "", false, errors.New("неверный индекс массива")
    }
    switch command {
    case "MGET":
      result = get(&arr, number)
    case "MSET":
      changed = arr.data[number] != value
      replace(&arr, number, value)
      result = value
    case "MDEL":
      remove(&arr, number)
      changed = true
    default:
      return nil, "", false, errors.New("неизвестная команда массива")
    }
  }
  saved := make([]string, arr.size)
  for i := 0; i < arr.size; i++ {
    saved[i] = arr.data[i]
  }
  return saved, result, changed, nil
}
