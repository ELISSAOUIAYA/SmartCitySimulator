#ifndef CITY_GRAPH_H
#define CITY_GRAPH_H

#include "Node.h"
#include "raymath.h"
#include <map>
#include <queue>
#include <algorithm>

class CityGraph {
public:
    std::map<std::string, Node> nodes;

    void AddNode(std::string id, Vector3 pos, NodeType type) {
        nodes[id] = Node(id, pos, type);
    }

    void Connect(std::string idA, std::string idB) {
        if (nodes.count(idA) && nodes.count(idB)) {
            nodes[idA].neighbors.push_back(idB);
        }
    }

    std::vector<Vector3> GetShortestPath(std::string startID, std::string endID) {
        std::map<std::string, float> distances;
        std::map<std::string, std::string> previous;
        auto cmp = [](std::pair<float, std::string> a, std::pair<float, std::string> b) { return a.first > b.first; };
        std::priority_queue<std::pair<float, std::string>, std::vector<std::pair<float, std::string>>, decltype(cmp)> pq(cmp);

        for (auto const& [id, node] : nodes) distances[id] = 1e6;
        distances[startID] = 0;
        pq.push({0, startID});

        while (!pq.empty()) {
            std::string current = pq.top().second;
            pq.pop();
            if (current == endID) break;

            for (const std::string& neighbor : nodes[current].neighbors) {
                float dist = Vector3Distance(nodes[current].position, nodes[neighbor].position);
                if (distances[current] + dist < distances[neighbor]) {
                    distances[neighbor] = distances[current] + dist;
                    previous[neighbor] = current;
                    pq.push({distances[neighbor], neighbor});
                }
            }
        }

        std::vector<Vector3> path;
        std::string curr = endID;
        if (previous.find(curr) == previous.end() && startID != endID) return path;
        while (curr != startID) {
            path.push_back(nodes[curr].position);
            curr = previous[curr];
        }
        path.push_back(nodes[startID].position);
        std::reverse(path.begin(), path.end());
        return path;
    }

    void DrawDebug() {
        for (auto const& [id, node] : nodes) {
            Color c = (node.type == INVERSE) ? RED : (node.type == CIRCULAR ? BLUE : GREEN);
            DrawSphere(node.position, 0.08f, c);
        }
    }

    std::string GetNodeClicked(Ray ray) {
        for (auto const& [id, node] : nodes) {
            if (GetRayCollisionSphere(ray, node.position, 0.6f).hit) return id;
        }
        return "";
    }
};

#endif