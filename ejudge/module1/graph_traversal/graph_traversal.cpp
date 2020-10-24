// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#include <graph_traversal.h>

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
