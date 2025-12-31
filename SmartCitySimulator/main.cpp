#include "raylib.h"
#include "CityGraph.h"
#include "Simulation.h"
#include "CityUI.h"     // Contient ta classe d'interface
#include "TrafficManager.h"
int main(void)
{
    // Initialisation de la fenÃªtre
    InitWindow(1280, 800, "SmartCity - Simulation Finale");
    CityUI ui;
    ui.LoadResources(); // IMPORTANT : Charge l'image ici

    // --- CAMERA ---
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 15.0f, 25.0f, 15.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // ==========================================
    // === 1. CHARGEMENT DES MODELES (ASSETS) ===
    // ==========================================
    
    // Routes
    Model RoundAbout = LoadModel("assets/maison/road/road-roundabout.glb");
    Model DoubleRoad = LoadModel("assets/maison/road/road-driveway-double.glb");
    Model RoadSquare = LoadModel("assets/maison/road/road-bend-square.glb");
    Model RoadIntersection = LoadModel("assets/maison/road/road-intersection.glb");
    
    // BÃ¢timents
    Model Hospital = LoadModel("assets/building/bloc/Hospital_building.glb");
    Model Garden = LoadModel("assets/building/bloc/garden.glb");
    Model GasStation = LoadModel("assets/building/bloc/gas_station.glb");
    Model parking = LoadModel("assets/building/bloc/parking.glb");
    Model bank = LoadModel("assets/building/bloc/bank.glb");
    Model shop = LoadModel("assets/building/bloc/shop.glb");
    Model shop2 = LoadModel("assets/building/bloc/classic_shop.glb");
    Model Bakery = LoadModel("assets/building/bloc/bakery.glb");
    Model barber = LoadModel("assets/building/bloc/barber.glb");
    Model pharmacy = LoadModel("assets/building/bloc/pharmacy.glb");
    Model HighSchool = LoadModel("assets/building/bloc/HighSchool.glb");
    Model villa = LoadModel("assets/building/bloc/villa.glb");
    Model Mosque = LoadModel("assets/building/bloc/mosque.glb");
    Model ground = LoadModel("assets/building/bloc/ground.glb");
    Model magnit_shop = LoadModel("assets/building/bloc/magnit_shop.glb");
    Model coffee_shop = LoadModel("assets/building/bloc/coffee_shop.glb");
    Model ground1 = LoadModel("assets/building/bloc/ground1.glb");
    
    // Props & Signalisation
    Model NoEntryModel = LoadModel("assets/feu rouge/no_entry.glb");
    Model RondPointSign = LoadModel("assets/feu rouge/rond_point_sign.glb");
    Model StopModel = LoadModel("assets/feu rouge/stop.glb");
    Model TrafficLight = LoadModel("assets/feu rouge/retro_traffic_light.glb");
    
    // VÃ©hicules
    Model taximodel = LoadModel("assets/cars/taxi.glb");
    Model truck = LoadModel("assets/cars/truck.glb");
    Model van = LoadModel("assets/cars/van.glb");

    // ==========================================
    // === 2. INITIALISATION SIMULATION & UI ===
    // ==========================================
    Simulation sim;
    sim.Init(taximodel, van, truck);

   TrafficManager trafficManager;
    // ==========================================
    // === 3. DEFINITION DES POSITIONS (MAP) ===
    // ==========================================
    
    // --- Routes ---
    Vector3 posRoundAbout1 = {6.0f, 0.03f, -4.0f}; 
    Vector3 posRoundAbout2 = {-7.0f, 0.03f, 7.0f}; 
    Vector3 PosDoubleRoad5 = {-4.0f, 0.03f, 7.0f}; 
    Vector3 PosDoubleRoad6 = {-3.0f, 0.03f, 7.0f}; 
    Vector3 PosRoadIntersection1 = {-7.0f, 0.03f, 1.0f};   
    Vector3 PosDoubleRoad33 = {6.0f, 0.03f, 5.0f};
    Vector3 PosDoubleRoad24 = {-7.0f, 0.03f, 4.0f};
    Vector3 PosDoubleRoad25 = {-7.0f, 0.03f, 3.0f};
    Vector3 PosRoadIntersection2 = {0.0f, 0.03f, 7.0f}; 
    Vector3 PosDoubleRoad30 = {3.0f, 0.03f, 7.0f};
    Vector3 PosDoubleRoad31 = {4.0f, 0.03f, 7.0f};
    Vector3 PosDoubleRoad35 = {6.0f, 0.03f, 4.0f};
    Vector3 PosDoubleRoad36 = {6.0f, 0.03f, 3.0f};
    Vector3 PosDoubleRoad37 = {6.0f, 0.03f, 2.0f};
    Vector3 PosDoubleRoad38 = {6.0f, 0.03f, 1.0f};
    Vector3 PosDoubleRoad39 = {6.0f, 0.03f, 0.0f};
    Vector3 PosDoubleRoad40 = {6.0f, 0.03f, -1.0f};
    Vector3 PosRoadSquare3 = {6.0f, 0.03f, 7.0f};
    Vector3 PosDoubleRoad43 = {-7.0f, 0.03f, -2.0f};
    Vector3 PosRoadSquare4 = {-7.0f, 0.03f, -8.5f};
    Vector3 PosDoubleRoad46 = {-5.0f, 0.03f, -4.0f};
    Vector3 PosDoubleRoad47 = {-4.0f, 0.03f, -4.0f};
    Vector3 PosDoubleRoad48 = {-3.0f, 0.03f, -4.0f};
    Vector3 PosDoubleRoad49 = {-2.0f, 0.03f, -4.0f};
    Vector3 PosDoubleRoad50 = {-1.0f, 0.03f, -4.0f};
    Vector3 PosDoubleRoad51 = {0.0f, 0.03f, -4.0f};
    Vector3 PosDoubleRoad52 = {1.0f, 0.03f, -4.0f};
    Vector3 PosDoubleRoad53 = {2.0f, 0.03f, -4.0f};
    Vector3 PosDoubleRoad58 = {10.0f, 0.03f, -4.0f}; 
    Vector3 PosDoubleRoad62 = {6.0f, 0.03f, -10.0f};
    Vector3 PosRoadIntersection3 = {6.0f, 0.03f, -8.5f};
    Vector3 PosRoadIntersection4 = {-7.0f, 0.03f, -4.0f};
    
    // Grille de routes (DoubleRoad 64 Ã  74)
    Vector3 PosDoubleRoad64 = {4.5f, 0.03f, -8.5f};
    Vector3 PosDoubleRoad65 = {3.5f, 0.03f, -8.5f};
    Vector3 PosDoubleRoad66 = {2.5f, 0.03f, -8.5f};
    Vector3 PosDoubleRoad67 = {1.5f, 0.03f, -8.5f};
    Vector3 PosDoubleRoad68 = {0.5f, 0.03f, -8.5f};
    Vector3 PosDoubleRoad69 = {-0.5f, 0.03f, -8.5f};
    Vector3 PosDoubleRoad70 = {-1.5f, 0.03f, -8.5f};
    Vector3 PosDoubleRoad71 = {-2.5f, 0.03f, -8.5f};
    Vector3 PosDoubleRoad72 = {-3.5f, 0.03f, -8.5f};
    Vector3 PosDoubleRoad73 = {-4.5f, 0.03f, -8.5f};
    Vector3 PosDoubleRoad74 = {-5.5f, 0.03f, -8.5f};

    Vector3 PosDoubleRoad76 = {-7.0f, 0.03f, -6.0f};
    Vector3 PosDoubleRoad77 = {-7.0f, 0.03f, -7.0f};
    Vector3 PosDoubleRoad78 = {6.0f, 0.03f, -7.5f};
    Vector3 PosDoubleRoad7 = {2.0f, 0.03f, 7.0f};
    Vector3 PosDoubleRoad28 = {-2.0f, 0.03f, 7.0f};
    Vector3 PosDoubleRoad80 = {-7.0f, 0.03f, -0.5f};
    Vector3 PosDoubleRoad81 = {0.0f, 0.03f, 5.0f};
    Vector3 PosDoubleRoad82 = {0.0f, 0.03f, 3.0f};
    Vector3 PosRoadSquare5 = {0.0f, 0.03f, 1.0f};
    Vector3 PosDoubleRoad83 = {-3.5f, 0.03f, 1.0f};

    // --- BÃ¢timents ---
    Vector3 PosHospital = {-2.5f, 0.0f, -7.0f};
    Vector3 PosGarden = {3.0f, 0.0f, -6.5f};
    Vector3 Posvilla = {-3.0f, -0.1f, 3.45f};
    Vector3 PosGasStation = {3.0f, 0.0f, 3.1f};
    Vector3 Posparking = {3.3f, 0.0f, -1.5f};
    Vector3 Posbank = {-9.5f, 0.0f, -9.0f};
    Vector3 Posshop = {-9.0f, 0.0f, -1.0f};
    Vector3 PosBakery = {-9.0f, 0.0f, -6.0f};
    Vector3 Posbarber = {-9.0f, 0.0f, -3.0f};
    Vector3 Posshop2 = {-9.5f, 0.0f, 1.5f};
    Vector3 Pospharmacy = {-9.0f, 0.0f, 4.5f};
    Vector3 PosHighSchool = {9.0f, 0.0f, 3.8f};
    Vector3 PosMosque = {9.75f, 0.0f, -8.0f};
    Vector3 Posground = {9.5f, -0.3f, -1.4f};
    Vector3 Posmagnit_shop = {5.3f, 0.0f, 8.2f};
    Vector3 Poscoffee_shop = {-0.9f, 0.0f, 8.7f};
    Vector3 Posground11 = {0.0f, -0.7f, 7.0f};
    Vector3 Posground12 = {1.0f, -0.7f, -7.0f};

    // --- Props ---
    Vector3 PosrondSign1 = {6.0f, 0.0f, -4.0f};
    Vector3 PosrondSign2 = {-7.0f, 0.0f, 7.0f};
    Vector3 PosNoEntry1 = {-8.0f, 0.0f, -4.0f};
    Vector3 PosStop1 = {-6.0f, 0.0f, 0.0f};
    Vector3 PosStop2 = {-1.0f, 0.0f, 6.0f};
    
    // --- Feux ---
    Vector3 PosTrafficLight1 = {5.0f, 0.0f, -6.3f};
    Vector3 PosTrafficLight2 = {7.0f, 0.0f, -2.0f};
    Vector3 PosTrafficLight3 = {4.0f, 0.0f, -3.0f};
    Vector3 PosTrafficLight4 = {8.0f, 0.0f, -5.0f}; 
    Vector3 PosTrafficLight5 = {-5.0f, 0.0f, 6.0f};
    Vector3 PosTrafficLight6 = {-6.0f, 0.0f, 9.0f};
    Vector3 PosTrafficLight7 = {-8.0f, 0.0f, 5.0f};
    Vector3 PosTrafficLight8 = {-9.0f, 0.0f, 8.0f};

    SetTargetFPS(60);

    // ==========================================
    // === 4. BOUCLE PRINCIPALE (GAME LOOP) ===
    // ==========================================
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
            
           
      
        // --- LOGIQUE ---
        if (ui.currentState == STATE_MENU) {
            ui.HandleInput(sim); // L'UI gÃ¨re les inputs du menu
        } else {
            sim.HandleInput(camera); 
            trafficManager.Update(dt);
            // La sim gÃ¨re les inputs du jeu (camÃ©ra, clic, touche S)
            sim.Update(camera);      // Calcul physique
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (ui.currentState == STATE_MENU) {
            ui.DrawMenu(sim); 
        } 
        else {
            BeginMode3D(camera);
            
          
            DrawModelEx(RoundAbout, posRoundAbout1, {0,1,0}, 0.0f, {2,1,2}, GRAY);
            DrawModelEx(RoundAbout, posRoundAbout2, {0,1,0}, 0.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad5, {0,1,0}, 0.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad6, {0,1,0}, 0.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad33, {0,1,0}, 90.0f, {2,1,2}, GRAY);
            DrawModelEx(RoadIntersection, PosRoadIntersection1, {0,1,0}, 90.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad24, {0,1,0}, 90.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad25, {0,1,0}, 90.0f, {2,1,2}, GRAY);
            DrawModelEx(RoadIntersection, PosRoadIntersection2, {0,1,0}, 180.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad30, {0,1,0}, 0.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad31, {0,1,0}, 0.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad35, {0,1,0}, 90.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad36, {0,1,0}, 90.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad37, {0,1,0}, 90.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad38, {0,1,0}, 90.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad39, {0,1,0}, 90.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad40, {0,1,0}, 90.0f, {2,1,2}, GRAY);
            DrawModelEx(RoadSquare, PosRoadSquare3, {0,1,0}, 270.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad43, {0,1,0}, 90.0f, {2,1,2}, GRAY);
            DrawModelEx(RoadSquare, PosRoadSquare4, {0,1,0}, 90.0f, {1,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad46, {0,1,0}, 0.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad47, {0,1,0}, 0.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad48, {0,1,0}, 0.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad49, {0,1,0}, 0.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad50, {0,1,0}, 0.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad51, {0,1,0}, 0.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad52, {0,1,0}, 0.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad53, {0,1,0}, 0.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad58, {0,1,0}, 0.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad62, {0,1,0}, 90.0f, {2,1,2}, GRAY);
            DrawModelEx(RoadIntersection, PosRoadIntersection3, {0,1,0}, 270.0f, {1,1,2}, GRAY);
            DrawModelEx(RoadIntersection, PosRoadIntersection4, {0,1,0}, 90.0f, {2,1,2}, GRAY);
            
            
            DrawModel(DoubleRoad, PosDoubleRoad64, 1.0f, GRAY);
            DrawModel(DoubleRoad, PosDoubleRoad65, 1.0f, GRAY);
            DrawModel(DoubleRoad, PosDoubleRoad66, 1.0f, GRAY);
            DrawModel(DoubleRoad, PosDoubleRoad67, 1.0f, GRAY);
            DrawModel(DoubleRoad, PosDoubleRoad68, 1.0f, GRAY);
            DrawModel(DoubleRoad, PosDoubleRoad69, 1.0f, GRAY);
            DrawModel(DoubleRoad, PosDoubleRoad70, 1.0f, GRAY);
            DrawModel(DoubleRoad, PosDoubleRoad71, 1.0f, GRAY);
            DrawModel(DoubleRoad, PosDoubleRoad72, 1.0f, GRAY);
            DrawModel(DoubleRoad, PosDoubleRoad73, 1.0f, GRAY);
            DrawModel(DoubleRoad, PosDoubleRoad74, 1.0f, GRAY);

            DrawModelEx(DoubleRoad, PosDoubleRoad76, {0,1,0}, 90.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad77, {0,1,0}, 90.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad78, {0,1,0}, 90.0f, {1,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad7, {0,1,0}, 0.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad28, {0,1,0}, 0.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad80, {0,1,0}, 90.0f, {1,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad81, {0,1,0}, 90.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad82, {0,1,0}, 90.0f, {2,1,2}, GRAY);
            DrawModelEx(RoadSquare, PosRoadSquare5, {0,1,0}, 0.0f, {2,1,2}, GRAY);
            DrawModelEx(DoubleRoad, PosDoubleRoad83, {0,1,0}, 0.0f, {5,1,2}, GRAY);

          
            DrawModelEx(GasStation, PosGasStation, {0,1,0}, 360.0f, {0.09f,0.4f,0.15f}, WHITE);
            DrawModelEx(parking, Posparking, {0,1,0}, 90.0f, {3.25f,15.0f,19.5f}, WHITE);
            DrawModelEx(bank, Posbank, {0,1,0}, 90.0f, {0.7f,0.7f,0.7f}, WHITE);
            DrawModelEx(Bakery, PosBakery, {0,1,0}, 90.0f, {0.8f,0.8f,0.8f}, WHITE);
            DrawModelEx(barber, Posbarber, {0,1,0}, 90.0f, {0.4f,0.4f,0.4f}, WHITE);
            DrawModelEx(shop, Posshop, {0,1,0}, 0.0f, {0.5f,0.7f,0.5f}, WHITE);
            DrawModelEx(shop2, Posshop2, {0,1,0}, 90.0f, {0.02f,0.02f,0.02f}, WHITE);
            DrawModelEx(pharmacy, Pospharmacy, {0,1,0}, 0.0f, {0.7f,0.7f,0.7f}, WHITE);
            DrawModelEx(HighSchool, PosHighSchool, {0,1,0}, 90.0f, {0.2f,0.2f,0.2f}, WHITE);
            DrawModelEx(villa, Posvilla, {0,1,0}, 270.0f, {0.18f,0.2f,0.21f}, WHITE);
            DrawModelEx(Hospital, PosHospital, {0,1,0}, 0.0f, {0.37f,0.1f,0.18f}, WHITE);
            DrawModelEx(Garden, PosGarden, {0,1,0}, 90.0f, {0.15f,0.7f,0.2f}, WHITE);
            DrawModelEx(Mosque, PosMosque, {0,1,0}, 0.0f, {0.18f,0.18f,0.18f}, WHITE);
            DrawModelEx(ground, Posground, {0,1,0}, 0.0f, {0.4f,0.4f,0.4f}, WHITE);
            DrawModelEx(magnit_shop, Posmagnit_shop, {0,1,0}, 90.0f, {0.15f,0.15f,0.15f}, WHITE);
            DrawModelEx(coffee_shop, Poscoffee_shop, {0,1,0}, 90.0f, {0.5f,0.5f,0.5f}, WHITE);
            DrawModelEx(ground1, Posground11, {0,1,0}, 90.0f, {2.5f,2.5f,2.6f}, WHITE);
            DrawModelEx(ground1, Posground12, {0,1,0}, 90.0f, {2.5f,2.0f,2.5f}, WHITE);

            DrawModelEx(RondPointSign, PosrondSign1, {0,1,0}, 0.0f, {4,4,4}, WHITE);
            DrawModelEx(RondPointSign, PosrondSign2, {0,1,0}, 90.0f, {4,4,4}, WHITE);
            DrawModelEx(StopModel, PosStop1, {0,1,0}, 270.0f, {0.7f,0.7f,0.7f}, WHITE);
            DrawModelEx(StopModel, PosStop2, {0,1,0}, 315.0f, {0.7f,0.7f,0.7f}, WHITE);
            DrawModelEx(NoEntryModel, PosNoEntry1, {0,1,0}, 0.0f, {0.9f,0.9f,0.9f}, WHITE);

            
            trafficManager.Draw(TrafficLight);
            sim.Draw3D(); 
            DrawGrid(30, 1.0f);
            EndMode3D();

           
            ui.DrawHUD(sim);
        }

        EndDrawing();
    }

    
    UnloadModel(RoundAbout); UnloadModel(DoubleRoad); UnloadModel(RoadSquare); UnloadModel(RoadIntersection);
    UnloadModel(Hospital); UnloadModel(Garden); UnloadModel(GasStation); UnloadModel(parking);
    UnloadModel(bank); UnloadModel(shop); UnloadModel(shop2); UnloadModel(Bakery);
    UnloadModel(barber); UnloadModel(pharmacy); UnloadModel(HighSchool); UnloadModel(villa);
    UnloadModel(Mosque); UnloadModel(ground); UnloadModel(magnit_shop); UnloadModel(coffee_shop);
    UnloadModel(ground1); 
    UnloadModel(truck); UnloadModel(van); UnloadModel(taximodel);
    UnloadModel(RondPointSign); UnloadModel(NoEntryModel); UnloadModel(StopModel); UnloadModel(TrafficLight);

    CloseWindow();
    return 0;
}