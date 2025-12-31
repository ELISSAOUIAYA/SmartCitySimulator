#include "TrafficManager.h"

// Constructeur : Initialisation des feux de signalisation
TrafficManager::TrafficManager() {
    timer = 0;
    switchTime = 4.0f; // Temps avant de changer d'état (4 secondes)

    // Placement des instances de feux avec positions, rotations et états initiaux
    lights.push_back({{5.0f, 0.0f, -6.3f}, 90.0f, LIGHT_RED});
    lights.push_back({{7.0f, 0.0f, -2.0f}, 90.0f, LIGHT_GREEN});
    lights.push_back({{4.0f, 0.0f, -3.0f}, 270.0f, LIGHT_RED});
    lights.push_back({{8.0f, 0.0f, -5.0f}, 180.0f, LIGHT_GREEN});
    lights.push_back({{-5.0f, 0.0f, 6.0f}, 0.0f, LIGHT_RED});
    lights.push_back({{-6.0f, 0.0f, 9.0f}, 90.0f, LIGHT_GREEN});
    lights.push_back({{-8.0f, 0.0f, 5.0f}, 180.0f, LIGHT_RED});
    lights.push_back({{-9.0f, 0.0f, 8.0f}, 270.0f, LIGHT_GREEN});
}

// Mise à jour de la logique des feux (Gestion du cycle de temps)
void TrafficManager::Update(float deltaTime) {
    timer += deltaTime;
    
    // Vérifier si l'intervalle de temps est atteint
    if (timer >= switchTime) {
        timer = 0;
        for (auto& light : lights) {
            // Cycle de transition des couleurs : Rouge -> Vert -> Jaune -> Rouge
            if (light.state == LIGHT_RED) light.state = LIGHT_GREEN;
            else if (light.state == LIGHT_GREEN) light.state = LIGHT_YELLOW;
            else if (light.state == LIGHT_YELLOW) light.state = LIGHT_RED;
        }
    }
}

// Rendu visuel des feux dans la scène 3D
void TrafficManager::Draw(Model& model) {
    for (auto& light : lights) {
        Color lightColor = WHITE;
        
        // Déterminer la couleur de rendu selon l'état du feu
        if (light.state == LIGHT_RED) lightColor = RED;
        else if (light.state == LIGHT_YELLOW) lightColor = YELLOW;
        else if (light.state == LIGHT_GREEN) lightColor = LIME; 

        // Dessiner le modèle 3D avec une échelle de 0.5f
        DrawModelEx(model, light.position, {0, 1, 0}, light.rotation, {0.5f, 0.5f, 0.5f}, lightColor);
    }
}