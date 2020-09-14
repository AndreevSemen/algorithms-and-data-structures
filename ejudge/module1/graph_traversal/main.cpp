// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <regex>
#include <set>
#include <vector>

class Graph {
public:
    enum GraphType {
        Directional,
        UnDirectional,
    };

    enum GraphTraversalWay {
        Breadth,
        Depth,
    };

private:
    struct Vertex {
    public:
        std::string ID;
        std::vector<std::weak_ptr<Vertex>> Neighbors;

    public:
        explicit Vertex(std::string id);
    };

private:
    std::map<std::string, std::shared_ptr<Vertex>> _vertexes;
    bool _isDirected;
    bool _isBreadth;
    std::weak_ptr<Vertex> _traversalBeginning;

public:
    Graph(GraphType type, const std::string& beginning, GraphTraversalWay way);
    void AddEdge(const std::string& i, const std::string& j);
    std::vector<std::string> Traversal() const;

private:
    static void SequencedInsert(std::vector<std::weak_ptr<Vertex>>& neighbors,
                                const std::weak_ptr<Vertex>& neighbor);

    std::weak_ptr<Vertex> _GetVertex(const std::string& v);

    std::vector<std::string> _BreadthTraversal(const std::weak_ptr<Vertex>& v) const;
    void _DepthTraversal(const std::weak_ptr<Vertex>& v, std::vector<std::string>& visited) const;
};

Graph::Vertex::Vertex(std::string id)
    : ID{std::move(id)}
{}

Graph::Graph(GraphType type, const std::string& beginning, GraphTraversalWay way) {
    switch (type) {
        case Directional:
            _isDirected = true;
            break;
        case UnDirectional:
            _isDirected = false;
            break;
        default:
            throw std::invalid_argument{
                    "invalid graph type"
            };
    }

    _traversalBeginning = _GetVertex(beginning);

    switch (way) {
        case Breadth:
            _isBreadth = true;
            break;
        case Depth:
            _isBreadth = false;
            break;
        default:
            throw std::invalid_argument{
                    "invalid traversal way"
            };
    }
}

void Graph::AddEdge(const std::string& i, const std::string& j) {
    auto iWeakPtr = _GetVertex(i);
    auto jWeakPtr = _GetVertex(j);

    std::shared_ptr<Vertex> iVertex = iWeakPtr.lock();
    std::shared_ptr<Vertex> jVertex = jWeakPtr.lock();
    if (!iVertex || !jVertex) {
        throw std::runtime_error{
                "vertex has expired"
        };
    }

    SequencedInsert(iVertex->Neighbors, jVertex);
    if (!_isDirected) {
        SequencedInsert(jVertex->Neighbors, iVertex);
    }
}

std::vector<std::string> Graph::Traversal() const {
    if (_isBreadth) {
        return _BreadthTraversal(_traversalBeginning);
    } else {
        std::vector<std::string> visited;
        _DepthTraversal(_traversalBeginning, visited);
        return visited;
    }
}

void Graph::SequencedInsert(std::vector<std::weak_ptr<Vertex>> &neighbors,
                            const std::weak_ptr<Vertex>& neighbor) {
    if (std::find_if(neighbors.begin(), neighbors.end(),
                     [&neighbor](const std::weak_ptr<Vertex>& v){
                         return v.lock()->ID == neighbor.lock()->ID;
                     }) != neighbors.end()) {
        return;
    }
    neighbors.insert(std::lower_bound(neighbors.begin(), neighbors.end(), neighbor,
                                      [](const auto& a, const auto& b) {
                                          return a.lock()->ID < b.lock()->ID;
                                      }),
                     neighbor
    );
}

std::weak_ptr<Graph::Vertex> Graph::_GetVertex(const std::string& v) {
    std::weak_ptr<Vertex> iVertex;
    auto found = _vertexes.find(v);
    if (found != _vertexes.end()) {
        iVertex = found->second;
    }

    auto result = _vertexes.insert(
            std::make_pair(v, std::make_shared<Vertex>(v))
    );

    return result.first->second;
}

std::vector<std::string> Graph::_BreadthTraversal(const std::weak_ptr<Vertex>& v) const {
    std::vector<std::string> visited;

    std::queue<std::weak_ptr<Vertex>> q;
    q.push(_traversalBeginning);
    while (!q.empty()) {
        auto vertexWeakPtr = q.front();
        q.pop();
        auto vertex = vertexWeakPtr.lock();
        if (!vertex) {
            throw std::runtime_error{
                    "vertex has expired"
            };
        }

        if (std::find(visited.begin(), visited.end(), vertex->ID) != visited.end()) {
            continue;
        } else {
            visited.push_back(vertex->ID);
        }

        for (const auto& neighborWeakPtr : vertex->Neighbors) {
            q.push(neighborWeakPtr);
        }
    }

    return visited;
}

void Graph::_DepthTraversal(const std::weak_ptr<Vertex>& v, std::vector<std::string>& visited) const {
    auto vertex = v.lock();
    if (!vertex) {
        throw std::runtime_error{
                "vertex has expired"
        };
    }
    visited.push_back(vertex->ID);

    for (const auto& neighborWeakPtr : vertex->Neighbors) {
        auto neighbor = neighborWeakPtr.lock();
        if (!neighbor) {
            throw std::runtime_error{
                    "vertex has expired"
            };
        }

        if (std::find(visited.begin(), visited.end(), neighbor->ID) != visited.end()) {
            continue;
        }

        _DepthTraversal(neighborWeakPtr, visited);
    }
}

std::tuple<Graph::GraphType, std::string, Graph::GraphTraversalWay>
        ParseInit(const std::string& command) {
    static std::regex regex{"(u|d)\\s\\S+\\s(b|d)"};
    if (!std::regex_match(command, regex)) {
        throw std::invalid_argument{
            "error"
        };
    }

    Graph::GraphType type;
    switch (command[0]) {
        case 'u':
            type = Graph::UnDirectional;
            break;
        case 'd':
            type = Graph::Directional;
            break;
        default:
            throw std::invalid_argument{
                    "error"
            };
    }

    std::string beginning{command.begin() + 2, command.end() - 2};

    Graph::GraphTraversalWay way;
    switch (command[command.size() - 1]) {
        case 'b':
            way = Graph::Breadth;
            break;
        case 'd':
            way = Graph::Depth;
            break;
        default:
            throw std::invalid_argument{
                    "error"
            };
    }

    return {type, beginning, way};
}

std::tuple<std::string, std::string> ParseEdge(const std::string& command) {
    static std::regex regex{"\\S+\\s\\S+"};
    if (!std::regex_match(command, regex)) {
        throw std::invalid_argument{
            "error"
        };
    }

    auto index = command.find(' ');
    return {
        std::string{command.begin(), command.begin() + index},
        std::string{command.begin() + index + 1, command.end()},
    };
}

int main() {
    std::unique_ptr<Graph> G;

    std::string line;
    while (getline(std::cin, line)) {
        try {
            auto t = ParseInit(line);
            G = std::make_unique<Graph>(
                    std::get<0>(t),
                    std::get<1>(t),
                    std::get<2>(t)
            );

            break;
        } catch (...) {
            std::cout << "error" << std::endl;
        }
    }

    while (getline(std::cin, line)) {
        if (line == "EOF") {
            break;
        }
        if (line.empty()) {
            continue;
        }
        try {
            auto edge = ParseEdge(line);
            G->AddEdge(std::get<0>(edge), std::get<1>(edge));
        } catch (...) {
            continue;
        }
    }

    auto t = G->Traversal();
    for (const auto& i : t) {
        std::cout << i << std::endl;
    }

    return 0;
}
