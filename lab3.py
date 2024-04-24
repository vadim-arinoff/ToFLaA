class Stack:
    def __init__(self):
        # Создаем пустой стек
        self.items = []

    def push(self, item):
        # Добавляем элемент в стек
        self.items.append(item)

    def pop(self):
        # Удаляем и возвращаем верхний элемент стека
        if not self.is_empty():
            return self.items.pop()
        else:
            return None

    def is_empty(self):
        # Проверяем, пуст ли стек
        return len(self.items) == 0

    def peek(self):
        # Возвращаем верхний элемент стека без удаления
        if not self.is_empty():
            return self.items[-1]
        else:
            return None

def check_parentheses_balance(input_string):
    stack = Stack()
  #создаём определение открывающий и закрывающих
    opening_brackets = "({["
    closing_brackets = ")}]"
    for char in input_string:
        if char in opening_brackets:
            stack.push(char)
        elif char in closing_brackets:
            if stack.is_empty():
                return False
            top = stack.pop()
            if opening_brackets.index(top) != closing_brackets.index(char):
                return False

    return stack.is_empty()

# Пример использования:
input_string = "({[()()]})"
if check_parentheses_balance(input_string):
    print("Скобки сбалансированы.")
else:
    print("Скобки не сбалансированы.")
