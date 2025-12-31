#ifndef CITY_UI_H
#define CITY_UI_H

#include "raylib.h"
#include "Simulation.h"
#include <string>

enum UiState { STATE_MENU, STATE_SIMULATION };
enum InputFocus { FOCUS_NONE, FOCUS_LIMIT, FOCUS_START, FOCUS_END, FOCUS_COUNT };

class CityUI {
private:
    // --- NOUVEAU : Texture pour la carte ---
    Texture2D mapTexture; 
    bool textureLoaded = false;

    // Rectangles de l'interface (ajustés pour laisser de la place à l'image)
    Rectangle boxLimit = { 450, 100, 100, 40 };
    Rectangle boxTypeTaxi = { 100, 250, 100, 40 };
    Rectangle boxTypeVan = { 220, 250, 100, 40 };
    Rectangle boxTypeTruck = { 340, 250, 100, 40 };
    Rectangle boxStart = { 100, 350, 100, 40 };
    Rectangle boxEnd = { 250, 350, 100, 40 };
    Rectangle boxCount = { 400, 350, 100, 40 };
    Rectangle btnInsert = { 550, 350, 150, 40 };
    Rectangle btnStart = { 100, 600, 480, 60 }; // Déplacé un peu à gauche

    void DrawTextBox(Rectangle rect, std::string text, bool active, const char* label) {
        DrawText(label, rect.x, rect.y - 20, 20, BLACK);
        DrawRectangleRec(rect, active ? LIGHTGRAY : RAYWHITE);
        DrawRectangleLinesEx(rect, 2, active ? RED : DARKGRAY);
        DrawText(text.c_str(), rect.x + 5, rect.y + 10, 20, BLACK);
        if (active && (int)(GetTime() * 2) % 2 == 0) 
            DrawText("_", rect.x + 8 + MeasureText(text.c_str(), 20), rect.y + 10, 20, RED);
    }

public:
    UiState currentState = STATE_MENU;
    InputFocus currentFocus = FOCUS_NONE;
    
    std::string strLimit = "50";
    std::string strStart = "";
    std::string strEnd = "";
    std::string strCount = "1";
    MenuSelection currentType = SEL_TAXI;

    // --- NOUVEAU : Fonctions de chargement ---
    void LoadResources() {
    mapTexture = LoadTexture("assets/map.png");
    
    if (mapTexture.id == 0) {
        // Cela s'affichera en rouge dans ta console si le fichier est introuvable
        TraceLog(LOG_ERROR, ">>> ALERTE : Le fichier assets/map_nodes.png est INTROUVABLE !");
        textureLoaded = false;
    } else {
        TraceLog(LOG_INFO, ">>> BRAVO : L'image de la carte est bien chargée !");
        textureLoaded = true;
    }
}
    void UnloadResources() {
        if (textureLoaded) UnloadTexture(mapTexture);
    }

    void HandleInput(Simulation& sim) {
        if (currentState == STATE_MENU) {
            Vector2 mouse = GetMousePosition();
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (CheckCollisionPointRec(mouse, boxLimit)) currentFocus = FOCUS_LIMIT;
                else if (CheckCollisionPointRec(mouse, boxStart)) currentFocus = FOCUS_START;
                else if (CheckCollisionPointRec(mouse, boxEnd)) currentFocus = FOCUS_END;
                else if (CheckCollisionPointRec(mouse, boxCount)) currentFocus = FOCUS_COUNT;
                else currentFocus = FOCUS_NONE;

                if (CheckCollisionPointRec(mouse, boxTypeTaxi)) currentType = SEL_TAXI;
                if (CheckCollisionPointRec(mouse, boxTypeVan)) currentType = SEL_VAN;
                if (CheckCollisionPointRec(mouse, boxTypeTruck)) currentType = SEL_TRUCK;

                if (CheckCollisionPointRec(mouse, btnInsert)) {
                    try {
                        sim.AddOrder(currentType, strStart, strEnd, std::stoi(strCount));
                        strStart = ""; strEnd = ""; strCount = "1";
                    } catch (...) {}
                }

                if (CheckCollisionPointRec(mouse, btnStart)) {
                    try { sim.maxVehicles = std::stoi(strLimit); } catch(...) { sim.maxVehicles = 50; }
                    sim.ExecuteOrders();
                    sim.configurationMode = false;
                    currentState = STATE_SIMULATION;
                }
            }

            // Gestion clavier ... (inchangé)
            if (currentFocus != FOCUS_NONE) {
                int key = GetCharPressed();
                while (key > 0) {
                    if ((key >= 32) && (key <= 125)) {
                        if (currentFocus == FOCUS_LIMIT && strLimit.length() < 3) strLimit += (char)key;
                        if (currentFocus == FOCUS_START && strStart.length() < 3) strStart += (char)key;
                        if (currentFocus == FOCUS_END && strEnd.length() < 3) strEnd += (char)key;
                        if (currentFocus == FOCUS_COUNT && strCount.length() < 3) strCount += (char)key;
                    }
                    key = GetCharPressed();
                }
                if (IsKeyPressed(KEY_BACKSPACE)) {
                    if (currentFocus == FOCUS_LIMIT && !strLimit.empty()) strLimit.pop_back();
                    if (currentFocus == FOCUS_START && !strStart.empty()) strStart.pop_back();
                    if (currentFocus == FOCUS_END && !strEnd.empty()) strEnd.pop_back();
                    if (currentFocus == FOCUS_COUNT && !strCount.empty()) strCount.pop_back();
                }
            }
        }
    }

    void DrawMenu(Simulation& sim) {
        DrawText("CONFIGURATION DE LA VILLE", 100, 20, 30, DARKBLUE);
        
        // --- AFFICHAGE DE LA PHOTO À DROITE ---
        if (textureLoaded) {
            // Position x=720 pour la mettre à droite, échelle 0.5f (à ajuster selon la taille)
            DrawTextureEx(mapTexture, { 720, 80 }, 0.0f, 0.45f,WHITE);
            DrawRectangleLinesEx({ 720, 80, mapTexture.width * 0.45f, mapTexture.height * 0.45f }, 2, DARKGRAY);
            DrawText("REFERENCE DES NOEUDS (ID)", 750, 50, 20, GRAY);
        }

        DrawTextBox(boxLimit, strLimit, currentFocus == FOCUS_LIMIT, "Limite Max:");

        DrawText("Type de Vehicule:", 100, 220, 20, BLACK);
        DrawRectangleRec(boxTypeTaxi, (currentType == SEL_TAXI) ? ORANGE : LIGHTGRAY);
        DrawRectangleLinesEx(boxTypeTaxi, 2, BLACK); DrawText("TAXI", boxTypeTaxi.x+25, boxTypeTaxi.y+10, 20, BLACK);
        
        DrawRectangleRec(boxTypeVan, (currentType == SEL_VAN) ? ORANGE : LIGHTGRAY);
        DrawRectangleLinesEx(boxTypeVan, 2, BLACK); DrawText("VAN", boxTypeVan.x+30, boxTypeVan.y+10, 20, BLACK);
        
        DrawRectangleRec(boxTypeTruck, (currentType == SEL_TRUCK) ? ORANGE : LIGHTGRAY);
        DrawRectangleLinesEx(boxTypeTruck, 2, BLACK); DrawText("TRUCK", boxTypeTruck.x+15, boxTypeTruck.y+10, 20, BLACK);

        DrawTextBox(boxStart, strStart, currentFocus == FOCUS_START, "Depart (ID):");
        DrawTextBox(boxEnd, strEnd, currentFocus == FOCUS_END, "Arrivee (ID):");
        DrawTextBox(boxCount, strCount, currentFocus == FOCUS_COUNT, "Qte:");

        DrawRectangleRec(btnInsert, SKYBLUE);
        DrawRectangleLinesEx(btnInsert, 2, DARKBLUE);
        DrawText("INSERER", btnInsert.x+35, btnInsert.y+10, 20, DARKBLUE);

        // Liste des commandes (déplacée en bas à droite ou sous l'image)
       
        int yPos = 580;
        int count = 0;
        for(const auto& order : sim.orders) {
            if (count > 5) break; // Limite l'affichage pour ne pas déborder
            std::string t = (order.type == SEL_TAXI) ? "Taxi" : (order.type == SEL_VAN ? "Van" : "Truck");
            DrawText(TextFormat("- %i %s: %s -> %s", order.count, t.c_str(), order.startID.c_str(), order.endID.c_str()), 720, yPos, 18, BLACK);
            yPos += 22;
            count++;
        }

        DrawRectangleRec(btnStart, GREEN);
        DrawRectangleLinesEx(btnStart, 3, DARKGREEN);
        DrawText("DEMARRER LA SIMULATION", btnStart.x + 80, btnStart.y + 15, 25, WHITE);
    }

    void DrawHUD(Simulation& sim) {
        DrawText("SIMULATION EN COURS", 10, 10, 20, GREEN);
        DrawText(TextFormat("Vehicules: %i / %i", (int)sim.vehicles.size(), sim.maxVehicles), 10,35 , 20, BLUE );
        DrawText("[1] Taxi  [2] Van  [3] Truck", 10, 60, 20, DARKGRAY);
        DrawText("Camera: ZQSD + Souris ", 10, 85, 20, DARKGRAY);
        DrawText("[5]: Map [6]: Libre [s]: Drone", 10, 110, 20, DARKGRAY);
        DrawText("Ajout Manuel: ND-Click", 10, 135, 20, BROWN);
        DrawText("Suppression : R-Click", 10, 160, 20, BROWN);
        DrawText("Pause        : Espace", 10, 185, 20, BROWN);


    }
};

#endif