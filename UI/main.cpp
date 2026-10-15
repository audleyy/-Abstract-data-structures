#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <exception>
#include <system_error>

#include "../core/array.h"
#include "../core/forwardList.h"
#include "../core/list.h"
#include "../core/queue.h"
#include "../core/stack.h"
#include "../core/BRTree.h"

using namespace std;

dynamic_array::Array currentArray{nullptr, 0};
singly_linked_list::Node* forwardHead = nullptr;
doubly_linked_list::List currentList{nullptr, nullptr};
::queue::Queue currentQueue{nullptr, nullptr};
::stack::Stack currentStack{nullptr};
red_black_tree::Node* treeRoot = nullptr;

struct Query {
  string command;
  string name;
  int number = 0;
  int number2 = 0;
  bool reverse = false;
};

bool parseArguments(int argc, char* argv[], string& filename, string& text) {
  if (argc != 5) return false;
  if (string(argv[1]) != "--file" || string(argv[3]) != "--query") return false;
  filename = argv[2];
  text = argv[4];
  return !filename.empty() && !text.empty();
}

int argumentCount(const string& command) {
  if (command == "PRINT") return 0;
  if (command.empty()) return -1;
  char type = command[0];
  string operation = command.substr(1);

  if (type == 'M') {
    if (operation == "PUSH" || operation == "DEL" || operation == "GET") return 1;
    if (operation == "PUSHINDEX" || operation == "SET") return 2;
    if (operation == "LEN") return 0;
  } else if (type == 'F' || type == 'L') {
    if (operation == "PUSH" || operation == "PUSHHEAD" || operation == "GET" ||
      operation == "DEL" || operation == "DELBEFORE" || operation == "DELAFTER" ||
      operation == "SEARCH") return 1;
    if (operation == "PUSHBEFORE" || operation == "PUSHAFTER") return 2;
    if (operation == "DELHEAD" || operation == "DELTAIL") return 0;
  } else if (type == 'Q') {
    if (operation == "PUSH") return 1;
    if (operation == "POP") return 0;
  } else if (type == 'S') {
    if (operation == "PUSH") return 1;
    if (operation == "POP" || operation == "ISEMPTY") return 0;
  } else if (type == 'T') {
    if (operation == "INSERT" || operation == "DEL" || operation == "GET") return 1;
  }
  return -1;
}

bool readNumber(istream& input, int& number) {
  string token, extra;
  if (!(input >> token)) return false;
  istringstream value(token);
  if (!(value >> number)) return false;
  return !(value >> extra);
}

bool parseQuery(const string& text, Query& query) {
  query = Query{};
  istringstream input(text);
  if (!(input >> query.command >> query.name)) return false;

  int count = argumentCount(query.command);
  if (count == -1) return false;
  if (count >= 1 && !readNumber(input, query.number)) return false;
  if (count == 2 && !readNumber(input, query.number2)) return false;

  string extra;
  if (query.command == "PRINT" && (input >> extra)) {
    if (extra != "REVERSE") return false;
    query.reverse = true;
  }
  return !(input >> extra);
}

bool canCreate(const string& command) {
  return command == "MPUSH" || command == "MPUSHINDEX" ||
       command == "FPUSH" || command == "FPUSHHEAD" ||
       command == "LPUSH" || command == "LPUSHHEAD" ||
       command == "QPUSH" || command == "SPUSH" || command == "TINSERT";
}

bool readFile(const string& filename, const Query& query, vector<string>& lines, vector<int>& values, int& position, char& type, string& treeData) {
  position = -1;
  type = query.command == "PRINT" ? '\0' : query.command[0];
  ifstream input(filename);
  error_code error;
  bool exists = filesystem::exists(filename, error);
  if (!input && (exists || error)) return false;

  string line;
  while (getline(input, line)) {
    istringstream row(line);
    string savedType, savedName;
    if (row >> savedType >> savedName && savedName == query.name) {
      if (position != -1 || savedType.size() != 1) return false;
      if (query.command != "PRINT" && savedType[0] != type) return false;
      type = savedType[0];
      position = static_cast<int>(lines.size());
      if (type == 'T') {
        getline(row, treeData);
      } else {
        while (row >> ws && !row.eof()) {
          int value;
          if (!readNumber(row, value)) return false;
          values.push_back(value);
        }
      }
    }
    lines.push_back(line);
  }

  if (input.bad()) return false;
  if (position == -1 && !canCreate(query.command)) return false;
  if (string("MFLQST").find(type) == string::npos) return false;
  if (query.reverse && type != 'F' && type != 'L') return false;
  return true;
}

bool readTree(istream& input, red_black_tree::Node*& root) {
  string token, color;
  if (!(input >> token)) return false;
  if (token == "#") {
    root = nullptr;
    return true;
  }
  istringstream number(token);
  int value;
  if (!readNumber(number, value)) return false;
  if (!(input >> color) || (color != "R" && color != "B")) return false;
  root = new red_black_tree::Node{value, color == "R", nullptr, nullptr};
  return readTree(input, root->left) && readTree(input, root->right);
}

bool loadStructure(char type, const vector<int>& values, const string& treeData) {

  if (type == 'T') {
    istringstream check(treeData);
    string first, second;
    check >> first >> second;

    if (first == "#" || second == "R" || second == "B") {
      istringstream input(treeData);
      string extra;
      if (!readTree(input, treeRoot)) return false;
      return !(input >> extra);
    }

    istringstream oldData(treeData);
    while (oldData >> ws && !oldData.eof()) {
      int value;
      if (!readNumber(oldData, value)) return false;
      red_black_tree::insert(treeRoot, value);
    }
    return true;
  }

  if (type == 'S') {

    for (int i = static_cast<int>(values.size()) - 1; i >= 0; --i)
      ::stack::push(&currentStack, values[i]);
    return true;
  }
  for (int value : values) {
    switch (type) {
      case 'M': dynamic_array::pushBack(currentArray, value); break;
      case 'F': singly_linked_list::addToTail(forwardHead, value); break;
      case 'L': doubly_linked_list::addTail(&currentList, value); break;
      case 'Q': ::queue::enqueue(&currentQueue, value); break;
    }
  }
  return true;
}

singly_linked_list::Node* getForwardNode(int index) {
  if (index < 0) return nullptr;
  auto node = forwardHead;
  for (int i = 0; i < index && node != nullptr; ++i) node = node->next;
  return node;
}

doubly_linked_list::Node* getListNode(int index) {
  if (index < 0) return nullptr;
  auto node = currentList.head;
  for (int i = 0; i < index && node != nullptr; ++i) node = node->next;
  return node;
}

bool executeArray(const Query& query, bool& changed) {
  using namespace dynamic_array;

  const string& command = query.command;
  int index = query.number;
  if (command == "MPUSH") {
    pushBack(currentArray, query.number);
    changed = true;
  } else if (command == "MPUSHINDEX") {
    if (index < 0 || index > currentArray.size) return false;
    pushIndex(currentArray, index, query.number2);
    changed = true;
  } else if (command == "MLEN") {
    cout << length(currentArray) << '\n';
  } else {
    if (index < 0 || index >= currentArray.size) return false;
    if (command == "MGET") cout << get(currentArray, index) << '\n';
    else if (command == "MSET") {
      changed = currentArray.data[index] != query.number2;
      replace(currentArray, index, query.number2);
    } else {
      remove(currentArray, index);
      changed = true;
    }
  }
  return true;
}

bool executeForwardList(const Query& query, bool& changed) {
  using namespace singly_linked_list;

  const string& command = query.command;
  if (command == "FPUSH") addToTail(forwardHead, query.number);
  else if (command == "FPUSHHEAD") addToHead(forwardHead, query.number);
  else if (command == "FSEARCH") {
    auto found = findNode(forwardHead, query.number);
    int index = 0;
    for (auto node = forwardHead; node != found && node != nullptr; node = node->next) ++index;
    cout << (found ? index : -1) << '\n';
    return true;
  } else if (command == "FDELHEAD" || command == "FDELTAIL") {
    if (forwardHead == nullptr) return false;
    if (command == "FDELHEAD") deleteHead(forwardHead);
    else deleteTail(forwardHead);
  } else {
    auto node = getForwardNode(query.number);
    if (node == nullptr) return false;
    if (command == "FGET") {
      printIndex(forwardHead, query.number);
      return true;
    }
    if (command == "FPUSHBEFORE") addBefore(forwardHead, node, query.number2);
    else if (command == "FPUSHAFTER") addAfter(node, query.number2);
    else if (command == "FDELBEFORE") {
      if (node == forwardHead) return false;
      deleteBefore(forwardHead, node);
    } else if (command == "FDELAFTER") {
      if (node->next == nullptr) return false;
      deleteAfter(node);
    } else deleteCurrent(forwardHead, node);
  }

  changed = true;
  return true;
}

bool executeDoublyLinkedList(const Query& query, bool& changed) {
  using namespace doubly_linked_list;

  const string& command = query.command;
  if (command == "LPUSH") addTail(&currentList, query.number);
  else if (command == "LPUSHHEAD") addHead(&currentList, query.number);
  else if (command == "LSEARCH") {
    auto found = findNode(currentList.head, query.number);
    int index = 0;
    for (auto node = currentList.head; node != found && node != nullptr; node = node->next) ++index;
    cout << (found ? index : -1) << '\n';
    return true;
  } else if (command == "LDELHEAD" || command == "LDELTAIL") {
    if (currentList.head == nullptr) return false;
    if (command == "LDELHEAD") delHead(&currentList);
    else delTail(&currentList);
  } else {
    auto node = getListNode(query.number);
    if (node == nullptr) return false;
    if (command == "LGET") {
      printIndex(&currentList, query.number);
      return true;
    }
    if (command == "LPUSHBEFORE") addBefore(&currentList, node, query.number2);
    else if (command == "LPUSHAFTER") addAfter(&currentList, node, query.number2);
    else if (command == "LDELBEFORE") {
      if (node->prev == nullptr) return false;
      delBefore(&currentList, node);
    } else if (command == "LDELAFTER") {
      if (node->next == nullptr) return false;
      delAfter(&currentList, node);
    } else {

      if (node == currentList.head) delHead(&currentList);
      else if (node == currentList.tail) delTail(&currentList);
      else delAfter(&currentList, node->prev);
    }
  }

  changed = true;
  return true;
}

bool executeQueue(const Query& query, bool& changed) {
  if (query.command == "QPUSH") ::queue::enqueue(&currentQueue, query.number);
  else {
    if (currentQueue.head == nullptr) return false;

    ::queue::dequeue(&currentQueue);
  }

  changed = true;
  return true;
}

bool executeStack(const Query& query, bool& changed) {
  if (query.command == "SISEMPTY") {
    cout << (::stack::isEmpty(&currentStack) ? "TRUE\n" : "FALSE\n");
    return true;
  }
  if (query.command == "SPUSH") ::stack::push(&currentStack, query.number);
  else {
    if (::stack::isEmpty(&currentStack)) return false;
    ::stack::pop(&currentStack);
  }

  changed = true;
  return true;
}

bool executeTree(const Query& query, bool& changed) {
  using namespace red_black_tree;
  if (query.command == "TGET") cout << (searchElement(treeRoot, query.number) ? "TRUE\n" : "FALSE\n");
  else if (query.command == "TINSERT") {
    changed = searchElement(treeRoot, query.number) == nullptr;
    insert(treeRoot, query.number);
  } else {
    changed = removeElement(treeRoot, query.number);
    return changed;
  }
  return true;
}

void printStructure(char type, bool reverse) {
  switch (type) {
    case 'M': dynamic_array::print(currentArray); break;
    case 'F':
      if (reverse) { singly_linked_list::printReverse(forwardHead); cout << '\n'; }
      else singly_linked_list::printRegular(forwardHead);
      break;
    case 'L':
      if (reverse) doubly_linked_list::printReverse(&currentList);
      else doubly_linked_list::printRegular(&currentList);
      break;
    case 'Q': ::queue::print(&currentQueue); break;
    case 'S': ::stack::print(&currentStack); break;
    case 'T': red_black_tree::printTree(treeRoot); cout << '\n'; break;
  }
}

bool executeCommand(char type, const Query& query, bool& changed) {
  changed = false;
  if (query.command == "PRINT") { printStructure(type, query.reverse); return true; }
  switch (type) {
    case 'M': return executeArray(query, changed);
    case 'F': return executeForwardList(query, changed);
    case 'L': return executeDoublyLinkedList(query, changed);
    case 'Q': return executeQueue(query, changed);
    case 'S': return executeStack(query, changed);
    case 'T': return executeTree(query, changed);
  }
  return false;
}

void writeTree(ostream& out, red_black_tree::Node* root) {
  if (root == nullptr) {
    out << "# ";
    return;
  }
  out << root->value << ' ' << (root->isRed ? 'R' : 'B') << ' ';
  writeTree(out, root->left);
  writeTree(out, root->right);
}

string structureToString(char type) {
  ostringstream out;
  switch (type) {
    case 'M':
      for (int i = 0; i < currentArray.size; ++i) out << currentArray.data[i] << ' ';
      break;
    case 'F':
      for (auto node = forwardHead; node != nullptr; node = node->next) out << node->value << ' ';
      break;
    case 'L':
      for (auto node = currentList.head; node != nullptr; node = node->next) out << node->value << ' ';
      break;
    case 'Q':
      for (auto node = currentQueue.head; node != nullptr; node = node->next) out << node->value << ' ';
      break;
    case 'S':
      for (auto node = currentStack.head; node != nullptr; node = node->next) out << node->value << ' ';
      break;
    case 'T': writeTree(out, treeRoot); break;
  }
  return out.str();
}

bool writeFile(const string& filename, vector<string>& lines, int position, char type, const string& name) {
  string updated = string(1, type) + " " + name + " " + structureToString(type);
  if (position == -1) lines.push_back(updated);
  else lines[position] = updated;
  ofstream output(filename);
  if (!output) return false;
  for (const auto& line : lines) output << line << '\n';
  output.close();
  return static_cast<bool>(output);
}

void clearTree(red_black_tree::Node* root) {
  if (root == nullptr) return;
  clearTree(root->left);
  clearTree(root->right);
  delete root;
}

void clearStructures() {
  dynamic_array::destroy(currentArray);
  while (forwardHead != nullptr) singly_linked_list::deleteHead(forwardHead);
  while (currentList.head != nullptr) doubly_linked_list::delHead(&currentList);
  while (currentQueue.head != nullptr) ::queue::dequeue(&currentQueue);
  while (!::stack::isEmpty(&currentStack)) ::stack::pop(&currentStack);
  clearTree(treeRoot);
  treeRoot = nullptr;
}

void printResult(const Query& query, bool changed, int removedValue) {
  string operation = query.command.substr(1);
  if (query.command == "QPOP" || query.command == "SPOP") {
    cout << removedValue << '\n';
  } else if (operation == "PUSH" || operation == "PUSHHEAD" || operation == "INSERT") {
    cout << query.number << '\n';
  } else if (operation == "PUSHINDEX" || operation == "SET" ||
         operation == "PUSHBEFORE" || operation == "PUSHAFTER") {
    cout << query.number2 << '\n';
  } else if (changed) cout << "OK\n";
}

int main(int argc, char* argv[]) {
  string filename, text;
  Query query;
  if (!parseArguments(argc, argv, filename, text)) {
    cerr << "Формат: ./dbms --file file.data --query 'COMMAND name [args]'\n";
    return 1;
  }
  if (!parseQuery(text, query)) {
    cerr << "Неизвестная команда или неверные аргументы\n";
    return 1;
  }
  vector<string> lines;
  vector<int> values;
  int position;
  char type;
  string treeData;
  if (!readFile(filename, query, lines, values, position, type, treeData)) {
    cerr << "Ошибка чтения\n";
    return 1;
  }
  if (!loadStructure(type, values, treeData)) {
    clearStructures();
    cerr << "Некорректные данные структуры в файле\n";
    return 1;
  }

  int removedValue = 0;
  if (query.command == "QPOP" && currentQueue.head != nullptr) removedValue = currentQueue.head->value;
  if (query.command == "SPOP" && currentStack.head != nullptr) removedValue = currentStack.head->value;

  bool changed;

  bool success = executeCommand(type, query, changed);
  if (success && changed) success = writeFile(filename, lines, position, type, query.name);
  clearStructures();

  if (!success) {
    cerr << "Ошибка операции или записи файла\n";
    return 1;
  }
  printResult(query, changed, removedValue);
  return 0;
}
