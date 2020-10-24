#include <iostream>
#include <queue>
#include <sstream>
#include <cmath>
#include <regex>

class SplayTree {
public:
    struct SearchResult {
        bool Found;
        int64_t Key;
        std::string Value;
    };

private:
    class Node {
    public:
        int64_t Key;
        std::string Value;

        Node* parent;
        Node* left;
        Node* right;

    public:
        Node(int64_t k, std::string&& v)
          : Key{k}
          , Value{std::move(v)}
          , parent{nullptr}
          , left{nullptr}
          , right{nullptr}
        {}

        void DeleteChildren() {
            if (HasLeft()) {
                left->DeleteChildren();
                delete left;
            }
            if (HasRight()) {
                right->DeleteChildren();
                delete right;
            }
        }

        bool HasParent() const { return parent; }
        bool IsLeftChild() const { return this->parent->left == this; }
        bool HasLeft() const { return left; }
        bool HasRight() const { return right; }
        size_t Depth() const {
            return std::max(
                    (HasLeft()) ? left->Depth() + 1 : 1,
                    (HasRight())? right->Depth() + 1: 1
            );
        }
    };

    struct PrintFiller {
        Node* Exists;
        size_t PlaceholderSize;

        std::ostream& Print(std::ostream& out) const {
            if (!Exists) {
                return out << "_" << RepeatString(" _", PlaceholderSize - 1);
            } else {
                out << "[" << Exists->Key << " " << Exists->Value;
                if (Exists->HasParent()) {
                    out << " " << Exists->parent->Key;
                }
                return out << "]";
            }
        }

    private:
        static std::string RepeatString(const std::string& str, size_t times) {
            std::string nstr;
            nstr.resize(str.size() * times);
            for (size_t i = 0; i < times; ++i) {
                std::copy(str.begin(), str.end(), nstr.begin() + i*str.size());
            }
            return nstr;
        }
    };

private:
    Node* _root;

public:
    SplayTree()
      : _root{nullptr}
    {}

    ~SplayTree() {
        if (!_root) {
            return;
        }
        _root->DeleteChildren();
        delete _root;
        _root = nullptr;
    }

    bool Add(int64_t key, std::string&& value) {
        if (_root == nullptr) {
            _root = new Node(key, std::move(value));
            return true;
        }

        auto parent = _Find(_root, key);
        if (key == parent->Key) {
            _root = parent;
            _Splay(_root);

            return false;
        } else if (key < parent->Key) {
            parent->left = _root = new Node(key, std::move(value));
        } else {
            parent->right = _root = new Node(key, std::move(value));
        }

        _root->parent = parent;
        _Splay(_root);

        return true;
    }
    bool Set(int64_t key, std::string&& value) {
        _root = _Find(_root, key);
        _Splay(_root);
        if (!_root || _root->Key != key) {
            return false;
        }
        _root->Value = std::move(value);
        return true;
    }
    bool Delete(int64_t k) {
        auto toDelete = _Find(_root, k);
        _Splay(toDelete);
        if (!toDelete || toDelete->Key != k) {
            _root = toDelete;
            return false;
        }

        if (!toDelete->HasLeft() && !toDelete->HasRight()) {
            _root = nullptr;
        } else if (!toDelete->HasRight()) {
            _root = toDelete->left;
            _root->parent = nullptr;
        } else if (!toDelete->HasLeft()) {
            _root = toDelete->right;
            _root->parent = nullptr;
        } else {
            auto newRoot = _Max(toDelete->left);
            newRoot->parent = nullptr;
            _Splay(newRoot);

            newRoot->right = toDelete->right;
            if (newRoot->HasRight()) {
                newRoot->right->parent = newRoot;
            }
        }
        delete toDelete;

        return true;
    }

    SearchResult Search(int64_t k) {
        _root = _Find(_root, k);
        _Splay(_root);

        if (!_root || _root->Key != k) {
            return SearchResult {
                false,
            };
        }
        return SearchResult {
            true,
            _root->Key,
            _root->Value,
        };
    }
    SearchResult Min() {
        _root = _Min(_root);
        _Splay(_root);

        if (!_root) {
            return SearchResult {
                false,
            };
        }
        return SearchResult {
            true,
            _root->Key,
            _root->Value,
        };
    }
    SearchResult Max() {
        _root = _Max(_root);
        _Splay(_root);

        if (!_root) {
            return SearchResult {
                false,
            };
        }
        return SearchResult {
            true,
            _root->Key,
            _root->Value,
        };
    }
    std::ostream& Print(std::ostream& out) const {
        if (!_root) {
            return out << "_" << std::endl;
        }

        size_t depth = _root->Depth();
        std::queue<PrintFiller> q;
        q.push(PrintFiller{_root, 0});
        for (size_t floor = 0; floor < depth; ++floor) {
            size_t width = std::pow(2, floor);
            for (size_t i = 0; i < width;) {
                auto popped = q.front();
                q.pop();

                out << (i ? " " : "");
                popped.Print(out);

                if (!popped.Exists) {
                    i += popped.PlaceholderSize;
                    popped.PlaceholderSize *= 2;
                    q.push(popped);
                } else {
                    ++i;
                    if (popped.Exists->HasLeft()) {
                        q.push(PrintFiller{popped.Exists->left, 0});
                    } else {
                        q.push(PrintFiller{nullptr, 1});
                    }
                    if (popped.Exists->HasRight()) {
                        q.push(PrintFiller{popped.Exists->right, 0});
                    } else {
                        q.push(PrintFiller{nullptr, 1});
                    }
                }
            }
            out << std::endl;
        }

        return out;
    }

private:
    static Node* _Find(Node* tree, int64_t key) {
        if (!tree) {
            return nullptr;
        }
        while (true) {
            if (key == tree->Key) {
                return tree;
            }
            if (key < tree->Key) {
                if (!tree->HasLeft()) {
                    return tree;
                }
                tree = tree->left;
            } else {
                if (!tree->HasRight()) {
                    return tree;
                }
                tree = tree->right;
            }
        }
    }

    static Node* _Min(Node* tree) {
        if (!tree) {
            return nullptr;
        }
        while (tree->HasLeft()) {
            tree = tree->left;
        }
        return tree;
    }

    static Node* _Max(Node* tree) {
        if (!tree) {
            return nullptr;
        }
        while (tree->HasRight()) {
            tree = tree->right;
        }
        return tree;
    }

    static void _Splay(Node* tree) {
        if (!tree) {
            return;
        }
        while (tree->HasParent()) {
            if (tree->IsLeftChild()) {
                if (tree->parent->HasParent()) {
                    if (tree->parent->IsLeftChild()) {
                        _LeftZigZig(tree);
                    } else {
                        _LeftZigZag(tree);
                    }
                } else {
                    _LeftZig(tree);
                }
            } else {
                if (tree->parent->HasParent()) {
                    if (tree->parent->IsLeftChild()) {
                        _RightZigZag(tree);
                    } else {
                        _RightZigZig(tree);
                    }
                } else {
                    _RightZig(tree);
                }
            }
        }
    }

    static inline void _LeftZig(Node* x) {
        auto p = x->parent;
        auto g = p->parent;
        auto B = x->right;

        if (g) {
            if (p->IsLeftChild()) {
                g->left = x;
            } else {
                g->right = x;
            }
        }
        x->right = p;

        x->parent = g;
        p->parent = x;

        p->left = B;
        if (p->HasLeft()) {
            p->left->parent = p;
        }
    }
    static inline void _LeftZigZig(Node* x) {
        _LeftZig(x->parent);
        _LeftZig(x);
    }
    static inline void _LeftZigZag(Node* x) {
        _LeftZig(x);
        _RightZig(x);
    }

    static inline void _RightZig(Node* x) {
        auto p = x->parent;
        auto g = p->parent;
        auto B = x->left;

        if (g) {
            if (p->IsLeftChild()) {
                g->left = x;
            } else {
                g->right = x;
            }
        }
        x->left = p;

        x->parent = g;
        p->parent = x;

        p->right = B;
        if (p->HasRight()) {
            p->right->parent = p;
        }
    }
    static inline void _RightZigZig(Node* x) {
        _RightZig(x->parent);
        _RightZig(x);
    }
    static inline void _RightZigZag(Node* x) {
        _RightZig(x);
        _LeftZig(x);
    }
};

struct Command {
    enum CommandType {
        Add,
        Set,
        Delete,
        Search,
        Min,
        Max,
        Print
    };

    bool OK;
    CommandType Type;
    int64_t Key;
    std::string Value;
};

bool IsFragmentEquals(const char* fbeg, const char* fend, const char* rhs) {
    while (fbeg != fend && *rhs != '\0') {
        if (*(fbeg++) != *(rhs++)) {
            return false;
        }
    }
    return true;
}

inline Command ParseCommand(const std::string& command) {
    Command cmd;

    auto firstSpace = command.find(' ');
    auto typeBeg = command.data();
    auto typeEnd = command.data() + firstSpace;
    if (IsFragmentEquals(typeBeg, typeEnd,"add")) {
        cmd.Type = Command::Add;
    } else if (IsFragmentEquals(typeBeg, typeEnd, "set")) {
        cmd.Type = Command::Set;
    } else if (IsFragmentEquals(typeBeg, typeEnd, "delete")) {
        cmd.Type = Command::Delete;
    } else if (IsFragmentEquals(typeBeg, typeEnd, "search")) {
        cmd.Type = Command::Search;
    } else if (IsFragmentEquals(typeBeg, typeEnd, "min")) {
        cmd.Type = Command::Min;
    } else if (IsFragmentEquals(typeBeg, typeEnd, "max")) {
        cmd.Type = Command::Max;
    } else if (IsFragmentEquals(typeBeg, typeEnd, "print")) {
        cmd.Type = Command::Print;
    } else {
        cmd.OK = false;
        return cmd;
    }

    auto secondSpace = command.find(' ', firstSpace + 1);
    switch (cmd.Type) {
        case Command::Add:
        case Command::Set:
            if (secondSpace == std::string::npos) {
                cmd.OK = false;
            } else {
                cmd.Key = std::strtoll(command.data() + firstSpace + 1, nullptr, 10);
                cmd.Value = command.substr(secondSpace + 1, command.size() - secondSpace - 1);
                cmd.OK = true;
            }
            break;
        case Command::Delete:
        case Command::Search:
            cmd.Key = std::strtoll(command.data() + firstSpace + 1, nullptr, 10);
            cmd.OK = true;
            break;
        case Command::Min:
        case Command::Max:
        case Command::Print:
            cmd.OK = true;
            break;
        default:
            cmd.OK = false;
            break;
    }

    return cmd;
}

bool inline ErrorOccurred(bool result) {
    if (!result) {
        std::cout << "error" << std::endl;
    }
    return !result;
}

int main() {
    SplayTree tree;

    std::string line;
    
    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }


        auto cmd = ParseCommand(line);
        if (ErrorOccurred(cmd.OK)) {
            continue;
        }
        if (cmd.Type == Command::Add) {
            ErrorOccurred(tree.Add(cmd.Key, std::move(cmd.Value)));
        } else if (cmd.Type == Command::Set) {
            ErrorOccurred(tree.Set(cmd.Key, std::move(cmd.Value)));
        } else if (cmd.Type == Command::Delete) {
            ErrorOccurred(tree.Delete(cmd.Key));
        } else if (cmd.Type == Command::Search) {
            auto found = tree.Search(cmd.Key);
            if (found.Found) {
                std::cout << "1 " << found.Value << std::endl;
            } else {
                std::cout << "0" << std::endl;
            }
        } else if (cmd.Type == Command::Min) {
            auto result = tree.Min();
            if (!ErrorOccurred(result.Found)) {
                std::cout << result.Key << " " << result.Value << std::endl;
            }
        } else if (cmd.Type == Command::Max) {
            auto result = tree.Max();
            if (!ErrorOccurred(result.Found)) {
                std::cout << result.Key << " " << result.Value << std::endl;
            }
        } else if (cmd.Type == Command::Print) {
            tree.Print(std::cout);
        }
    }

    return 0;
}
