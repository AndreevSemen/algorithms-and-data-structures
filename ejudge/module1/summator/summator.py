import sys


def parse_input() -> [int]:
    in_data = ''
    for line in sys.stdin:
        in_data += line

    piece = ''
    numbers = []
    for char in in_data:
        if char == '+' or char == '-':
            if not (piece == '+' or piece == '-') and len(piece) != 0:
                numbers.append(int(piece))
            piece = char
        elif char.isdigit():
            piece += char
        else:
            if len(piece) != 0:
                if piece != '+' and piece != '-':
                    numbers.append(int(piece))
                piece = ''
    if len(piece) != 0:
        numbers.append(int(piece))

    return numbers


if __name__ == '__main__':
    sum = 0
    for num in parse_input():
        sum += num
    print(sum)
