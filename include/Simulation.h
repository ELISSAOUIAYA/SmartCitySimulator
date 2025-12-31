#ifndef SIMULATION_H
#define SIMULATION_H

#include "CityGraph.h"
#include "Vehicles.h"
#include <iostream>

// Enums et Structures nÃ©cessaires
enum MenuSelection { SEL_TAXI, SEL_VAN, SEL_TRUCK };
struct SpawnOrder { MenuSelection type; std::string startID, endID; int count; };

class Simulation {
public:
    CityGraph graph;
    std::vector<Vehicle*> vehicles;
    std::vector<SpawnOrder> orders;
    
    MenuSelection selectedType = SEL_TAXI;
    std::string startNodeID = "";
    bool isPaused = false;
    int cameraMode = 0; // 0: Free, 1: Map, 2: Drone
    Vehicle* followedVehicle = nullptr;
    
    // ModÃ¨les pour instancier les vÃ©hicules
    Model mTaxi, mVan, mTruck;
    
    int maxVehicles = 50;
    bool configurationMode = true;

    void Init(Model t, Model v, Model tr) {
        mTaxi = t; mVan = v; mTruck = tr;
        InitGraph();
    }

    void AddOrder(MenuSelection type, std::string start, std::string end, int count) {
        orders.push_back({type, start, end, count});
    }

    void ExecuteOrders() {
        for (const auto& o : orders) {
            std::vector<Vector3> p = graph.GetShortestPath(o.startID, o.endID);
            if (p.size() < 2) continue;
            for(int i=0; i<o.count; i++) {
                if (vehicles.size() >= maxVehicles) break;
                if (o.type == SEL_TAXI) vehicles.push_back(new Taxi(p, mTaxi));
                else if (o.type == SEL_VAN) vehicles.push_back(new Van(p, mVan));
                else vehicles.push_back(new Truck(p, mTruck));
            }
        }
    }

   void InitGraph() {
        // --- DEFINITION DES NOEUDS ---
        graph.AddNode("A", {-6.6f, 0.0f, 9.5f}, DIRECT); graph.AddNode("B", {-4.5f, 0.0f, 7.3f}, DIRECT);
        graph.AddNode("C", {-9.5f, 0.0f, 7.5f}, DIRECT); graph.AddNode("D", {-6.6f, 0.0f, 4.5f}, DIRECT);
        graph.AddNode("E", {0.5f, 0.0f, 7.3f}, DIRECT);  graph.AddNode("F", {0.4f, 0.0f, 0.7f}, DIRECT);
        graph.AddNode("G", {-6.6f, 0.0f, 1.5f}, DIRECT); graph.AddNode("H", {6.4f, 0.0f, -6.2f}, DIRECT);
        graph.AddNode("I", {6.4f, 0.0f, 7.3f}, DIRECT);  graph.AddNode("J", {6.4f, 0.0f, -1.5f}, DIRECT);
        graph.AddNode("K", {9.0f, 0.0f, -3.6f}, DIRECT); graph.AddNode("L", {3.5f, 0.0f, -3.6f}, DIRECT);
        graph.AddNode("M", {-7.4f, 0.0f, -8.4f}, DIRECT); graph.AddNode("N", {6.4f, 0.0f, -8.5f}, DIRECT);
        graph.AddNode("Y", {-6.5f, 0.0f, -3.6f}, DIRECT); graph.AddNode("G1", {-6.6f, 0.0f, 0.5f}, DIRECT);
        graph.AddNode("Z", {10.5f, 0.0f, -3.6f}, DIRECT); graph.AddNode("Z1", {10.5f , 0.0f, -4.4f}, DIRECT);
        graph.AddNode("N1", {5.7f , 0.0f , -8.5f}, DIRECT); graph.AddNode("N2" , {5.7f , 0.0f , -10.3f}, DIRECT);

        graph.AddNode("1o", {-8.0f, 0.0f, 8.0f}, CIRCULAR); graph.AddNode("2o", {-6.0f, 0.0f, 8.0f}, CIRCULAR);
        graph.AddNode("3o", {-8.0f, 0.0f, 5.5f}, CIRCULAR); graph.AddNode("4o", {-6.0f, 0.0f, 5.5f}, CIRCULAR);
        graph.AddNode("5o", {7.0f, 0.0f, -2.6f}, CIRCULAR); graph.AddNode("6o", {7.0f, 0.0f, -5.0f}, CIRCULAR); 
        graph.AddNode("7o", {5.0f, 0.0f, -2.6f}, CIRCULAR); graph.AddNode("8o", {5.0f, 0.0f, -5.0f}, CIRCULAR); 
        
        graph.AddNode("a", {-7.4f, 0.0f, 9.5f}, INVERSE); graph.AddNode("b", {-4.5f, 0.0f, 6.7f}, INVERSE);
        graph.AddNode("c", {-9.5f, 0.0f, 6.7f}, INVERSE); graph.AddNode("d", {-7.4f, 0.0f, 4.5f}, INVERSE);
        graph.AddNode("f", {-0.4f, 0.0f, 1.3f}, INVERSE);graph.AddNode("e", {-0.5f, 0.0f, 6.5f}, INVERSE);
         graph.AddNode("g", {-7.4f, 0.0f, 0.5f}, INVERSE);
        graph.AddNode("h", {5.7f, 0.0f, -6.2f}, INVERSE); graph.AddNode("i", {5.7f, 0.0f, 6.7f}, INVERSE);
        graph.AddNode("j", {5.7f, 0.0f, -1.5f}, INVERSE); graph.AddNode("k", {9.0f, 0.0f, -4.4f}, INVERSE);
        graph.AddNode("l", {3.5f, 0.0f, -4.4f}, INVERSE); graph.AddNode("n", {6.4f, 0.0f, -10.3f}, INVERSE);
        graph.AddNode("y", {-7.4f, 0.0f, -4.4f}, INVERSE); graph.AddNode("x", {0.4f, 0.0f, 6.7f}, INVERSE);

        // --- CONNEXIONS ---
        graph.Connect("A", "2o"); graph.Connect("2o", "B"); graph.Connect("2o", "4o"); graph.Connect("C", "1o");  
        graph.Connect("1o", "2o"); graph.Connect("B", "E"); graph.Connect("E", "I");  graph.Connect("Z1", "k");
        graph.Connect("E", "F"); graph.Connect("I", "J"); graph.Connect("J", "5o");  graph.Connect("K","Z");
        graph.Connect("7o", "5o"); graph.Connect("5o", "K"); graph.Connect("5o", "6o"); graph.Connect("k", "6o"); 
        graph.Connect("6o", "8o"); graph.Connect("6o", "H"); graph.Connect("H", "N"); graph.Connect("N1", "M");
        graph.Connect("N2", "N1");graph.Connect("N", "n");graph.Connect("N1", "h");graph.Connect("H","N");
        graph.Connect("h","8o");graph.Connect("L","j");graph.Connect("1o","a");
        graph.Connect("N", "N1"); graph.Connect("8o", "7o"); graph.Connect("8o", "l"); graph.Connect("l", "y");
        graph.Connect("M", "y"); graph.Connect("y", "g"); graph.Connect("g", "d"); graph.Connect("d", "3o");  
        graph.Connect("3o", "1o"); graph.Connect("3o", "c"); graph.Connect("4o", "3o"); graph.Connect("7o", "5o");
        graph.Connect("b", "4o"); graph.Connect("e", "b"); graph.Connect("f", "e"); graph.Connect("i", "e"); 
        graph.Connect("4o", "D"); graph.Connect("D", "G"); graph.Connect("G", "Y"); graph.Connect("G", "f"); 
        graph.Connect("Y", "L"); graph.Connect("F", "g"); graph.Connect("j", "i"); graph.Connect("7o", "j"); 
        graph.Connect("L", "o8"); graph.Connect("D", "G1"); graph.Connect("F", "G1"); graph.Connect("G", "G1"); 
        graph.Connect("i", "x"); graph.Connect("x", "F"); graph.Connect("x", "e"); graph.Connect("G1", "Y");
    }
    void HandleInput(Camera3D& camera) {
        if (configurationMode) return;
        if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_KP_1)) selectedType = SEL_TAXI;
        if (IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_KP_2)) selectedType = SEL_VAN;
        if (IsKeyPressed(KEY_THREE) || IsKeyPressed(KEY_KP_3)) selectedType = SEL_TRUCK;
        if (IsKeyPressed(KEY_SPACE)) isPaused = !isPaused;

        // Suppression
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
            Ray ray = GetMouseRay(GetMousePosition(), camera);
            for (int i = 0; i < (int)vehicles.size(); i++) {
                if (vehicles[i]->IsClicked(ray)) {
                    delete vehicles[i]; vehicles.erase(vehicles.begin() + i); break;
                }
            }
        }

        // Ajout manuel
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !IsKeyDown(KEY_X)) {
            Ray ray = GetMouseRay(GetMousePosition(), camera);
            std::string clickedNode = graph.GetNodeClicked(ray);
            if (!clickedNode.empty()) {
                if (startNodeID == "") startNodeID = clickedNode; 
                else {
                    std::vector<Vector3> path = graph.GetShortestPath(startNodeID, clickedNode);
                    if (path.size() > 1) {
                        Vehicle* newV = nullptr;
                        if (selectedType == SEL_TAXI)  newV = new Taxi(path, mTaxi);
                        else if (selectedType == SEL_VAN) newV = new Van(path, mVan);
                        else if (selectedType == SEL_TRUCK) newV = new Truck(path, mTruck);
                        if (newV != nullptr) vehicles.push_back(newV);
                    }
                    startNodeID = ""; 
                }
            }
        }

        // CamÃ©ra Drone (S)
        if (IsKeyPressed(KEY_S)) {
            Ray ray = GetMouseRay(GetMousePosition(), camera);
            for (auto v : vehicles) if (v->IsClicked(ray)) { cameraMode = 2; followedVehicle = v; break; }
        }
        if (IsKeyPressed(KEY_FIVE)) cameraMode = 1; // Map
        if (IsKeyPressed(KEY_SIX)) { cameraMode = 0; followedVehicle = nullptr; } // Free
    }

    void Update(Camera3D& camera) {
        if (configurationMode) { UpdateCamera(&camera, CAMERA_FREE); return; }
        
        for (size_t i = 0; i < vehicles.size(); i++) {
            bool blocked = false;
            float angleRad = vehicles[i]->rotation * DEG2RAD;
            Vector3 forward = { sinf(angleRad), 0, cosf(angleRad) };

            for (size_t j = 0; j < vehicles.size(); j++) {
                if (i == j) continue;
                float dist = Vector3Distance(vehicles[i]->position, vehicles[j]->position);
                
                // --- LOGIQUE ANTI-GHOST (2.0f) ---
                if (dist < 2.0f) { 
                    Vector3 toOther = Vector3Normalize(Vector3Subtract(vehicles[j]->position, vehicles[i]->position));
                    
                    // 1. Est-il devant ?
                    float dotFront = Vector3DotProduct(forward, toOther);
                    // 2. MÃªme direction ?
                    float diffRotation = fabsf(vehicles[i]->rotation - vehicles[j]->rotation);
                    bool sameDirection = (diffRotation < 45.0f || diffRotation > 315.0f);

                    if (dotFront > 0.5f && sameDirection) { blocked = true; break; }
                }
            }
            if (!blocked) vehicles[i]->Update(isPaused);
        }

        if (cameraMode == 2 && followedVehicle) {
            float a = followedVehicle->rotation * DEG2RAD;
            camera.position = Vector3Add(followedVehicle->position, {-sinf(a)*6, 3, -cosf(a)*6});
            camera.target = followedVehicle->position;
        } else if (cameraMode == 1) {
            camera.position = {0, 35, 0}; camera.target = {0,0,0}; camera.up = {0,0,-1};
        } else {
            UpdateCamera(&camera, CAMERA_FREE);
        }
    }

    void Draw3D() {
        graph.DrawDebug();
        for (auto v : vehicles) v->Draw();
        if (startNodeID != "") DrawSphere(graph.nodes[startNodeID].position, 0.6f, YELLOW);
    }

    
    void DrawUI() {
        if (!configurationMode) {
            DrawText("SIMULATION EN COURS", 10, 10, 20, GREEN);
            DrawText(TextFormat("Vehicules: %i", (int)vehicles.size()), 10, 35, 20, BLUE);
        }
    }
};

#endif