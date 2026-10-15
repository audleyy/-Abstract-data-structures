# Abstract-data-structures

![alt text](image.png)

# Простой интерфейс структур данных

## Запуск

```bash
./dbms --file file.data --query 'MPUSH numbers 10'
```

- `--file` задаёт путь к файлу данных.
- `--query` задаёт один запрос.
- `numbers` — имя структуры.
- `10` — значение элемента.

Ключи принимаются именно в таком порядке. Весь запрос заключается в кавычки, чтобы оболочка передала его как один аргумент.

```text
argv[0] = ./dbms
argv[1] = --file
argv[2] = file.data
argv[3] = --query
argv[4] = MPUSH numbers 10
argc    = 5
```

## Правила и команды

### Массив

| Команда | Действие |
|---|---|
| `MPUSH name value` | Добавить в конец |
| `MPUSHINDEX name index value` | Вставить по индексу |
| `MGET name index` | Получить элемент |
| `MDEL name index` | Удалить элемент |
| `MSET name index value` | Заменить значение |
| `MLEN name` | Получить длину |

### Односвязный список

| Команда | Действие |
|---|---|
| `FPUSH name value` | Добавить в конец |
| `FPUSHHEAD name value` | Добавить в начало |
| `FPUSHBEFORE name index value` | Добавить перед узлом |
| `FPUSHAFTER name index value` | Добавить после узла |
| `FGET name index` | Прочитать узел |
| `FSEARCH name value` | Найти первое вхождение |
| `FDEL name index` | Удалить узел |
| `FDELHEAD name` | Удалить голову |
| `FDELTAIL name` | Удалить хвост |
| `FDELBEFORE name index` | Удалить узел перед указанным |
| `FDELAFTER name index` | Удалить узел после указанного |

### Двусвязный список

| Команда | Действие |
|---|---|
| `LPUSH name value` | Добавить в конец |
| `LPUSHHEAD name value` | Добавить в начало |
| `LPUSHBEFORE name index value` | Добавить перед узлом |
| `LPUSHAFTER name index value` | Добавить после узла |
| `LGET name index` | Прочитать узел |
| `LSEARCH name value` | Найти первое вхождение |
| `LDEL name index` | Удалить узел |
| `LDELHEAD name` | Удалить голову |
| `LDELTAIL name` | Удалить хвост |
| `LDELBEFORE name index` | Удалить узел перед указанным |
| `LDELAFTER name index` | Удалить узел после указанного |

### Очередь, стек и дерево

| Команда | Действие |
|---|---|
| `QPUSH name value` | Добавить в конец очереди |
| `QPOP name` | Прочитать и удалить первый элемент |
| `SPUSH name value` | Добавить на вершину стека |
| `SPOP name` | Прочитать и удалить вершину |
| `SISEMPTY name` | Проверить пустоту существующего стека |
| `TINSERT name value` | Вставить в дерево |
| `TGET name value` | Проверить наличие значения |
| `TDEL name value` | Удалить значение |

### Печать

```text
PRINT name
PRINT name REVERSE
```