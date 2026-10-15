package main

import (
  "errors"
  "fmt"
  "os"
  "strconv"
  "strings"

  dynamic_array "dbms-go/core/array"
  singly_linked_list "dbms-go/core/forwardList"
  doubly_linked_list "dbms-go/core/list"
  "dbms-go/core/queue"
  "dbms-go/core/stack"
)

type Query struct {
  command string
  name    string
  number  int
  number2 int
  reverse bool
}

func parseArguments(args []string) (string, string, error) {
  if len(args) != 5 || args[1] != "--file" || args[3] != "--query" {
    return "", "", errors.New("формат: ./dbms --file file.data --query 'COMMAND name [args]'")
  }
  if args[2] == "" || args[4] == "" {
    return "", "", errors.New("укажи файл и запрос")
  }
  return args[2], args[4], nil
}

func argumentCount(command string) int {
  if command == "PRINT" {
    return 0
  }
  if command == "" {
    return -1
  }
  operation := command[1:]
  switch command[0] {
  case 'M':
    switch operation {
    case "PUSH", "DEL", "GET":
      return 1
    case "PUSHINDEX", "SET":
      return 2
    case "LEN":
      return 0
    }
  case 'F', 'L':
    switch operation {
    case "PUSH", "PUSHHEAD", "GET", "DEL", "DELBEFORE", "DELAFTER", "SEARCH":
      return 1
    case "PUSHBEFORE", "PUSHAFTER":
      return 2
    case "DELHEAD", "DELTAIL":
      return 0
    }
  case 'Q':
    if operation == "PUSH" {
      return 1
    }
    if operation == "POP" {
      return 0
    }
  case 'S':
    if operation == "PUSH" {
      return 1
    }
    if operation == "POP" || operation == "ISEMPTY" {
      return 0
    }
  }
  return -1
}

func parseQuery(text string) (Query, error) {
  query := Query{}
  parts := strings.Fields(text)
  if len(parts) < 2 {
    return query, errors.New("укажи команду и имя структуры")
  }
  query.command = parts[0]
  query.name = parts[1]
  count := argumentCount(query.command)
  if count == -1 {
    return query, errors.New("неизвестная команда")
  }
  if query.command == "PRINT" {
    if len(parts) == 3 && parts[2] == "REVERSE" {
      query.reverse = true
    } else if len(parts) != 2 {
      return query, errors.New("формат: PRINT name [REVERSE]")
    }
    return query, nil
  }
  if len(parts) != count+2 {
    return query, errors.New("неверное количество аргументов")
  }
  var err error
  if count >= 1 {
    query.number, err = strconv.Atoi(parts[2])
    if err != nil {
      return query, errors.New("ожидалось целое число")
    }
  }
  if count == 2 {
    query.number2, err = strconv.Atoi(parts[3])
    if err != nil {
      return query, errors.New("ожидалось второе целое число")
    }
  }
  return query, nil
}

func canCreate(command string) bool {
  return command == "MPUSH" || command == "MPUSHINDEX" ||
    command == "FPUSH" || command == "FPUSHHEAD" ||
    command == "LPUSH" || command == "LPUSHHEAD" ||
    command == "QPUSH" || command == "SPUSH"
}

func readFile(filename string, query Query) ([]string, []int, int, byte, error) {
  lines := []string{}
  values := []int{}
  position := -1
  var kind byte
  if query.command != "PRINT" {
    kind = query.command[0]
  }
  data, err := os.ReadFile(filename)
  if err != nil && !os.IsNotExist(err) {
    return nil, nil, position, kind, err
  }
  if len(data) > 0 {
    lines = strings.Split(strings.TrimSuffix(string(data), "\n"), "\n")
  }
  for i, line := range lines {
    parts := strings.Fields(line)
    if len(parts) < 2 || parts[1] != query.name {
      continue
    }
    if position != -1 || len(parts[0]) != 1 {
      return nil, nil, position, kind, errors.New("повторяющееся имя или неверный тип")
    }
    if query.command != "PRINT" && parts[0][0] != kind {
      return nil, nil, position, kind, errors.New("неверный тип структуры")
    }
    kind = parts[0][0]
    position = i
    for _, token := range parts[2:] {
      value, err := strconv.Atoi(token)
      if err != nil {
        return nil, nil, position, kind, errors.New("неверное число в файле")
      }
      values = append(values, value)
    }
  }
  if position == -1 && !canCreate(query.command) {
    return nil, nil, position, kind, errors.New("структура не найдена")
  }
  if !strings.ContainsRune("MFLQS", rune(kind)) {
    return nil, nil, position, kind, errors.New("неизвестный тип структуры")
  }
  if query.reverse && kind != 'F' && kind != 'L' {
    return nil, nil, position, kind, errors.New("REVERSE доступен только для списков")
  }
  return lines, values, position, kind, nil
}

func executeCommand(kind byte, query Query, values []int) ([]int, string, bool, error) {
  switch kind {
  case 'M':
    return dynamic_array.Execute(query.command, query.number, query.number2, query.reverse, values)
  case 'F':
    return singly_linked_list.Execute(query.command, query.number, query.number2, query.reverse, values)
  case 'L':
    return doubly_linked_list.Execute(query.command, query.number, query.number2, query.reverse, values)
  case 'Q':
    return queue.Execute(query.command, query.number, query.number2, query.reverse, values)
  case 'S':
    return stack.Execute(query.command, query.number, query.number2, query.reverse, values)
  }
  return nil, "", false, errors.New("неизвестный тип")
}

func structureToString(kind byte, name string, values []int) string {
  line := string(kind) + " " + name
  for _, value := range values {
    line += " " + strconv.Itoa(value)
  }
  return line
}

func writeFile(filename string, lines []string, position int, kind byte, name string, values []int) error {
  updated := structureToString(kind, name, values)
  if position == -1 {
    lines = append(lines, updated)
  } else {
    lines[position] = updated
  }
  return os.WriteFile(filename, []byte(strings.Join(lines, "\n")+"\n"), 0644)
}

func printResult(result string, changed bool) {
  if result != "" {
    fmt.Println(result)
  } else if changed {
    fmt.Println("OK")
  }
}

func run(args []string) error {
  filename, text, err := parseArguments(args)
  if err != nil {
    return err
  }
  query, err := parseQuery(text)
  if err != nil {
    return err
  }
  lines, values, position, kind, err := readFile(filename, query)
  if err != nil {
    return err
  }
  saved, result, changed, err := executeCommand(kind, query, values)
  if err != nil {
    return err
  }
  if changed {
    if err := writeFile(filename, lines, position, kind, query.name, saved); err != nil {
      return err
    }
  }
  printResult(result, changed)
  return nil
}

func main() {
  if err := run(os.Args); err != nil {
    fmt.Fprintln(os.Stderr, "Ошибка:", err)
    os.Exit(1)
  }
}
