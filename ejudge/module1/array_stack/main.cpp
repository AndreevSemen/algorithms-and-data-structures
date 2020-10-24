// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#include <iostream>
#include <memory>
#include <vector>
#include <regex>

template <typename T>
class Stack {
private:
    size_t _capacity;
    size_t _size;
    std::vector<T> _data;

public:
    explicit Stack(size_t cap)
            : _capacity{cap}
            , _size{0}
            , _data{std::vector<T>(cap)}
    {}

    std::string push(T value) {
        if (_size == _capacity) {
            return overflow();
        } else {
            _data[_size++] = value;
        }
        return "";
    }

    std::string pop() {
        if (_size == 0) {
            return underflow();
        } else {
            --_size;
        }
        return std::to_string(_data[_size]) + '\n';
    }

    std::string print() const {
        if (_size == 0) {
            return "empty\n";
        }
        std::string result;
        for (size_t i = 0; i < _size; ++i) {
            result += std::to_string(_data[i]);
            if (i != _size - 1) {
                result += ' ';
            }
        }
        return result + "\n";
    }

    inline static std::string underflow() {
        return "underflow\n";
    }

    inline static std::string overflow() {
        return "overflow\n";
    }
};

std::pair<std::string, std::unique_ptr<int>>
        ParseCommand(const std::string& command) {
    static std::regex withValueRegex{"(set_size|push) [0-9]+"};
    static std::regex noValueRegex{"pop|print"};
    if (std::regex_match(command, withValueRegex)) {
        size_t spaceIndex = command.find(' ');
        return std::make_pair(
                std::string{command.begin(), command.begin() + spaceIndex},
                std::make_unique<int>(
                    std::stoi(
                        std::string{
                            command.begin() + spaceIndex + 1, command.end()
                        }
                    )
                )
        );
    } else if (std::regex_match(command, noValueRegex)) {
        return std::make_pair(command, nullptr);
    } else {
        throw std::invalid_argument{
            "error"
        };
    }
}

int main() {
    std::unique_ptr<Stack<int>> pStack;

    std::string command;
    while (getline(std::cin, command)) {
        if (command.empty()) {
            continue;
        }

        std::pair<std::string, std::unique_ptr<int>> pair;
        try {
            pair = ParseCommand(command);
        } catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            continue;
        }

        if (pStack == nullptr) {
            if (pair.first == "set_size") {
                pStack = std::make_unique<Stack<int>>(*pair.second);
            } else {
                std::cout << "error" << std::endl;
                continue;
            }
        } else if (pair.first == "set_size" && pStack != nullptr) {
            std::cout << "error" << std::endl;
            continue;
        } else if (pair.first == "pop") {
            std::cout << pStack->pop();
        } else if (pair.first == "push") {
            std::cout << pStack->push(*pair.second);
        } else if (pair.first == "print") {
            std::cout << pStack->print();
        }
    }

    return 0;
}
