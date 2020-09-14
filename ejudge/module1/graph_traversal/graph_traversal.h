// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#ifndef MODULE_1_TRAVERSAL_H_
#define MODULE_1_TRAVERSAL_H_

#include <functional>
#include <map>
#include <memory>
#include <queue>
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

#endif // MODULE_1_TRAVERSAL_H_
