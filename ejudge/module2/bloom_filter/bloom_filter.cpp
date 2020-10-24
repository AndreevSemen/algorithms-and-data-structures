#include <vector>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <functional>
#include <regex>

const std::runtime_error gError{"error"};

constexpr uint32_t MERSENNE31 = (uint32_t(1) << 31) - 1;

std::vector<size_t> PrimeNumbers(size_t N) {
    std::vector<size_t> primes;
    primes.reserve(N);
    for (size_t i = 2; primes.size() != primes.capacity(); ++i) {
        bool isPrime = true;
        for (auto prime : primes) {
            if (i % prime == 0) {
                isPrime = false;
            }
        }

        if (isPrime) {
            primes.push_back(i);
        }
    }

    return primes;
}

class BloomFilter {
    typedef uint32_t(HashFunc)(uint64_t);

public:
    const size_t StorageSize;
    const size_t HashesNumber;

private:
    // Хранилище битового массива фильтра Блума
    // std::vector<bool> это эффективная по памяти специализация
    // для std::vector, поэтому будем использовать ее
    // для хранинения битового массива
    std::vector<bool> _bits;
    std::vector<std::function<HashFunc>> _hashes;

public:
    BloomFilter(size_t n, double P)
      : StorageSize(std::round(-(n*log2(P)/log(2))))
      , HashesNumber(std::round(-std::log2(P)))
      , _bits(StorageSize)
      , _hashes(HashesNumber)
    {
        if (_bits.empty() || _hashes.empty()) {
            throw gError;
        }
        auto primes = PrimeNumbers(_hashes.size() + 1);
        for (size_t i = 0; i < _hashes.size(); ++i) {
            _hashes[i] = [i1=i, p1=primes[i], m=StorageSize](uint64_t x) -> uint32_t {
                return ((i1+1)*x + p1) % MERSENNE31 % m;
            };
        }
    }

    std::string Print() const {
        std::string result(StorageSize, '0');
        for (size_t i = 0; i < _bits.size(); ++i) {
            if (_bits[i]) {
                result[i] = '1';
            }
        }
        return result;
    }

    void Add(uint64_t K) {
        for (const auto& hash : _hashes) {
            _bits[hash(K)] = true;
        }
    }

    bool Search(uint64_t K) const {
        for (const auto& hash : _hashes) {
            if (!_bits[hash(K)]) {
                return false;
            }
        }
        return true;
    }
};


struct SetParams {
    size_t n;
    double P;
};

struct CommandParams {
    enum CommandEnum {
        Print,
        Add,
        Search,
    };
    CommandEnum Command;
    uint32_t K;
};

SetParams ParseSet(const std::string& command) {
    static std::regex re("^set\\s\\d+\\s[0]*.\\d+$");
    if (std::regex_match(command, re)) {
        auto firstSpaceIndex = command.find(' ');
        auto secondSpaceIndex = command.find(' ', firstSpaceIndex + 1);

        size_t n = std::stoull(command.substr(firstSpaceIndex + 1,
                                              secondSpaceIndex - firstSpaceIndex));
        auto P = std::stod(command.data() + secondSpaceIndex);

        if (!(0. < P && P < 1.)) {
            throw gError;
        }

        return SetParams{
            n,
            P
        };
    }

    throw gError;
}

CommandParams ParseCommand(const std::string& command) {
    if (command == "print") {
        static CommandParams params{
            CommandParams::Print,
            0,
        };
        return params;
    }

    CommandParams params;
    size_t spaceIndex;
    if (command.substr(0, 3) == "add") {
        params.Command = CommandParams::Add;
        spaceIndex = 3;
    } else if (command.substr(0, 6) == "search") {
        params.Command = CommandParams::Search;
        spaceIndex = 6;
    } else {
        throw gError;
    }

    for (size_t i = spaceIndex + 1; i < command.size(); ++i) {
        if (!isdigit(command[i])) {
            throw gError;
        }
    }

    params.K = std::stoull(command.data() + spaceIndex) % MERSENNE31;

    return params;
}

int main() {
    std::stringstream ss;

    std::unique_ptr<BloomFilter> bf;

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }

        try {
            auto params = ParseSet(line);
            bf = std::make_unique<BloomFilter>(params.n, params.P);
            ss << bf->StorageSize << " " << bf->HashesNumber << std::endl;
            break;
        } catch (...) {
            ss << "error" << std::endl;
        }
    }

    CommandParams params;
    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }

        try {
            params = ParseCommand(line);

            switch (params.Command) {
                case CommandParams::Print:
                    ss << bf->Print() << std::endl;
                    break;
                case CommandParams::Add:
                    bf->Add(params.K);
                    break;
                case CommandParams::Search:
                    ss << bf->Search(params.K) << std::endl;
                    break;
                default:
                    throw gError;
            }
        } catch (...) {
            ss << "error" << std::endl;
        }
    }

    std::cout << ss.str();

    return 0;
}
