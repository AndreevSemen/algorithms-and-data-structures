import sys
import re


class Stack:
    def __init__(self, capacity: int):
        self._capacity = capacity
        self._size = 0
        self._data = [0 for i in range(0, capacity)]

    def push(self, value: int) -> str:
        if self._size == self._capacity:
            return 'overflow'
        else:
            self._data[self._size] = value
            self._size += 1
            return ''

    def pop(self) -> str:
        if self._size == 0:
            return 'underflow'
        else:
            self._size -= 1
            return str(self._data[self._size])

    def print(self) -> str:
        if self._size == 0:
            return 'empty'
        else:
            return str.join(' ', map(str, self._data[:self._size]))


def parse_command(cmd: str) -> (str, str):
    with_value_re = re.compile("(set_size\s\d+$)|(push\s\S+$)")
    no_value_re = re.compile("pop|print")

    if re.match(with_value_re, cmd):
        val = cmd[cmd.find(' ') + 1:]
        cmd = cmd[:cmd.find(' ')]
        return cmd, val
    elif re.match(no_value_re, cmd):
        return cmd, None

    return None, None


if __name__ == '__main__':
    stack = None
    for line in sys.stdin:
        line = line[:-1]
        if len(line) == 0:
            continue

        command, value = parse_command(line)
        if command is None:
            print("error")
            continue

        if stack is None:
            if command == 'set_size':
                stack = Stack(int(value))
            else:
                print('error')
        elif command == 'set_size':
            print('error')
        elif command == 'push':
            s = stack.push(value)
            if s != '':
                print(stack.push(value))
        elif command == 'pop':
            print(stack.pop())
        elif command == 'print':
            print(stack.print())
        else:
            print('error')
