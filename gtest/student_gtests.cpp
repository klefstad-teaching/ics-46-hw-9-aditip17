#include <gtest/gtest.h>

#include "dijkstras.h"
#include "ladder.h"

TEST(Ladder, AdjacentWords) {
    EXPECT_TRUE(is_adjacent("code", "cade"));
    EXPECT_TRUE(is_adjacent("cade", "cate"));
    EXPECT_TRUE(is_adjacent("date", "data"));
    EXPECT_FALSE(is_adjacent("code", "data"));
}

TEST(Ladder, GenerateWordLadder) {
    set<string> word_list = {"code", "cade", "cate", "date", "data"};
    vector<string> ladder = generate_word_ladder("code", "data", word_list);
    
    vector<string> expected = {"code", "cade", "cate", "date", "data"};
    EXPECT_EQ(ladder, expected);
}

TEST(Ladder, NoLadder) {
    set<string> word_list = {"apple", "orange", "banana"};
    vector<string> ladder = generate_word_ladder("start", "end", word_list);
    
    EXPECT_TRUE(ladder.empty());
}

// ------------------- 

Graph create_test_graph() {
    Graph G;
    G.numVertices = 5;
    G.resize(G.numVertices);

    // Adding edges: src -> dst (weight)
    G[0].push_back({0, 1, 2});
    G[0].push_back({0, 3, 6});
    G[1].push_back({1, 2, 3});
    G[1].push_back({1, 3, 8});
    G[2].push_back({2, 4, 5});
    G[3].push_back({3, 4, 9});
    
    return G;
}

// Test Dijkstra's shortest path
TEST(Dijkstra, ShortestPath) {
    Graph G = create_test_graph();
    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    // Expected distances from source (0)
    EXPECT_EQ(distances[0], 0);  // source node
    EXPECT_EQ(distances[1], 2);
    EXPECT_EQ(distances[2], 5);
    EXPECT_EQ(distances[3], 6);
    EXPECT_EQ(distances[4], 10);
}

// Test path extraction
TEST(Dijkstra, ExtractShortestPath) {
    vector<int> v;
    vector<int> previous = {-1, 0, 1, 0, 2}; // backtracking from 4 -> 2 -> 1 -> 0
    vector<int> path = extract_shortest_path(v, previous, 4);

    vector<int> expected = {0, 1, 2, 4};
    EXPECT_EQ(path, expected);
}

// Test disconnected graph (no path)
TEST(Dijkstra, NoPath) {
    Graph G;
    G.numVertices = 3;
    G.resize(G.numVertices);

    // Only one edge, so vertex 2 is disconnected
    G[0].push_back({0, 1, 4});

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    // No path to vertex 2, should be INF
    EXPECT_EQ(distances[2], INF);
    EXPECT_EQ(previous[2], -1);
}

// Test single-node graph
TEST(Dijkstra, SingleNode) {
    Graph G;
    G.numVertices = 1;
    G.resize(G.numVertices);

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);

    EXPECT_EQ(distances[0], 0);
    EXPECT_EQ(previous[0], -1);
}
