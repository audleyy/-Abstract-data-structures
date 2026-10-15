package dynamic_array

import (
  "errors"
  "fmt"
)

func Execute(command string, number int, number2 int, reverse bool, values []int) ([]int, string, bool, error) {
  arr := Array{}
  initArray(&arr)
  for _, value := range values {
    pushBack(&arr, value)
  }
  defer destroy(&arr)
  changed := false
  result := ""
  switch command {
  case "PRINT":
    print(arr)
  case "MPUSH":
    pushBack(&arr, number)
    changed = true
    result = fmt.Sprint(number)
  case "MLEN":
    result = fmt.Sprint(length(&arr))
  case "MPUSHINDEX":
    if number < 0 || number >= arr.size {
      return nil, "", false, errors.New("индекс вставки должен быть меньше размера массива")
    }
    pushIndex(&arr, number, number2)
    changed = true
    result = fmt.Sprint(number2)
  default:
    if number < 0 || number >= arr.size {
      return nil, "", false, errors.New("неверный индекс массива")
    }
    switch command {
    case "MGET":
      result = fmt.Sprint(get(&arr, number))
    case "MSET":
      changed = arr.data[number] != number2
      replace(&arr, number, number2)
      result = fmt.Sprint(number2)
    case "MDEL":
      remove(&arr, number)
      changed = true
    default:
      return nil, "", false, errors.New("неизвестная команда массива")
    }
  }
  saved := make([]int, arr.size)
  for i := 0; i < arr.size; i++ {
    saved[i] = arr.data[i]
  }
  return saved, result, changed, nil
}
