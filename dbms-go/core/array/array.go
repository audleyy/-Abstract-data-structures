package dynamic_array

import "fmt"

type Array struct {
  data []int
  size int
}

func initArray(arr *Array) {
  arr.data = nil
  arr.size = 0
}

func pushIndex(arr *Array, index int, value int) {
  if index < 0 || index >= arr.size {
    return
  }
  newData := make([]int, arr.size+1)
  for i := 0; i < index; i++ {
    newData[i] = arr.data[i]
  }
  newData[index] = value
  for j := index + 1; j < arr.size+1; j++ {
    newData[j] = arr.data[j-1]
  }
  arr.data = newData
  arr.size++
}

func pushBack(arr *Array, value int) {
  newData := make([]int, arr.size+1)
  for i := 0; i < arr.size; i++ {
    newData[i] = arr.data[i]
  }
  newData[arr.size] = value
  arr.data = newData
  arr.size++
}

func get(arr *Array, index int) int {
  if index < 0 || index >= arr.size {
    return -1
  }
  return arr.data[index]
}

func remove(arr *Array, index int) {
  if index < 0 || index >= arr.size {
    return
  }
  newData := make([]int, arr.size-1)
  j := 0
  for i := 0; i < arr.size; i++ {
    if i != index {
      newData[j] = arr.data[i]
      j++
    }
  }
  arr.data = newData
  arr.size--
}

func replace(arr *Array, index int, value int) {
  if index < 0 || index >= arr.size {
    return
  }
  arr.data[index] = value
}

func length(arr *Array) int {
  return arr.size
}

func destroy(arr *Array) {
  arr.data = nil
  arr.size = 0
}

func print(arr Array) {
  for i := 0; i < arr.size; i++ {
    fmt.Printf("%d ", arr.data[i])
  }
  fmt.Println()
}
