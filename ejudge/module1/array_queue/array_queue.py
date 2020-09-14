import sys
import re


class Queue:
    def __init__(self, capacity: int):
        self._capacity = capacity
        self._size = 0
        self._head = 0
        self._data = [0 for i in range(0, capacity)]

    def push(self, value) -> str:
        if self._size == self._capacity:
            return 'overflow'
        else:
            index = (self._head + self._size) % self._capacity
            self._data[index] = value
            self._size += 1
            return ''

    def pop(self) -> str:
        if self._size == 0:
            return 'underflow'
        else:
            poped = self._data[self._head]
            self._head = (self._head + 1) % self._capacity
            self._size -= 1
            return str(poped)

    def print(self) -> str:
        if self._size == 0:
            return 'empty'
        else:
            result = ''
            for i in range(0, self._size):
                index = (self._head + i) % self._capacity
                result += self._data[index]
                if i != self._size - 1:
                    result += ' '
            return result


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
    with open(sys.argv[1], 'r') as ifile:
        with open(sys.argv[2], 'w') as ofile:
            printter = lambda s: print(s, file=ofile)

            for line in ifile:
                if line[-1] == '\n':
                    line = line[:-1]

                if len(line) == 0:
                    continue

                command, value = parse_command(line)
                if command is None:
                    printter("error")
                    continue

                if stack is None:
                    if command == 'set_size':
                        stack = Queue(int(value))
                    else:
                        printter('error')
                elif command == 'set_size':
                    printter('error')
                elif command == 'push':
                    s = stack.push(value)
                    if s != '':
                        printter(stack.push(value))
                elif command == 'pop':
                    printter(stack.pop())
                elif command == 'print':
                    printter(stack.print())
                else:
                    printter('error')
