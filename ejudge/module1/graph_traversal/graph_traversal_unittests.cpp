// Copyright 2020 AndreevSemen semen.andreev00@mail.ru

#include <gtest/gtest.h>

#include <graph_traversal.h>

TEST(GraphTraversal, Test) {
    Graph G(Graph::UnDirectional, "01", Graph::Depth);
    G.AddEdge("01", "11");
    G.AddEdge("01", "12");
    G.AddEdge("11", "21");
    G.AddEdge("11", "22");
    G.AddEdge("12", "23");
    G.AddEdge("12", "24");
    G.AddEdge("11", "12");

    std::string expected = "01\n"
                           "11\n"
                           "12\n"
                           "23\n"
                           "24\n"
                           "21\n"
                           "22\n";

    std::string result;
    auto traversal = G.Traversal();
    for (const auto& v : traversal) {
        result += v + '\n';
    }

    EXPECT_EQ(result, expected);
}
