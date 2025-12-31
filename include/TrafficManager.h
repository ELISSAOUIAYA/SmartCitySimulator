#ifndef TRAFFIC_MANAGER_H
#define TRAFFIC_MANAGER_H

#include "raylib.h"
#include <vector>

// Énumération pour gérer les états des feux de signalisation
enum LightState { LIGHT_RED, LIGHT_YELLOW, LIGHT_GREEN };

// Structure représentant une instance d'un feu dans le monde 3D
struct TrafficLightInstance {
    Vector3 position;   
    float rotation;     
    LightState state;   
};

class TrafficManager {
public:
    std::vector<TrafficLightInstance> lights; 
    float timer;                             
    float switchTime;                       
    
    // Constructeur : Initialise les paramètres et place les feux
    TrafficManager();

    // Mise à jour de la logique (Gestion du temps et cycle des couleurs)
    void Update(float deltaTime);

    // Affichage des feux dans l'environnement 3D
    void Draw(Model& model); 
};

#endif