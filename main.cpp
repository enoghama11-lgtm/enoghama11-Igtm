#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

int main() {
    if (!glfwInit()) {
        std::cout << "glfwInit failed" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGl", NULL, NULL);
    if (!window) {
        std::cout << "glfwCreateWindow failed" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Fel vid GLAD!" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);

bool isPlaying = false;


float camX = 0.0f, camY = 2.0f, camZ = 5.0f;


bool enablePS2Graphics = true;
float colorDepth = 16.0f;


struct Player {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float rotation = 0.0f;
    float swordSwing = 0.0f;
    bool isAttacking = false;
};
Player player1;


IMGUI_CHECKVERSION();
ImGui::CreateContext();
ImGui_ImplGlfw_InitForOpenGL(window, true);
ImGui_ImplOpenGL3_Init("#version 330");

while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();


    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Toolbar / Spelkontroll");
    
    if (ImGui::Button("Play")) {isPlaying = true; }
    ImGui::SameLine();
    if (ImGui::Button("Pause")) {isPlaying = false; }
    ImGui::SameLine();
    if (ImGui::Button("RESET")) {isPlaying = false; player1.x = 0; player1.rotation = 0; camZ = 5.0f;}

    ImGui::Separator();
    ImGui::Text("KAMERA-INSTÃLLNING (TESTA LOD):");
    ImGui::SliderFloat("Kamera Zoom Z", &camZ, 1.0f, 30.0f);

    ImGui::Separator();
    ImGui::Text("KARAKTARS-KONTROLL:");
    ImGui::SliderFloat("Flytta X", &player1.x, -5.0f, 5.0f);
    ImGui::SliderFloat("Rotera gubbe", &player1.rotation, 0.0f, 360.0f);

    if (ImGui::Button("HUGG MED SVARDET")) {
        player1.isAttacking = true;
    }

    ImGui::Separator();
    ImGui::Text("SPARA & LADDA (SAVE SYSTEM):");

    if (ImGui::Button("SPARA SPEL")) {
        std::ofstream utfil("savegame.txt");
        if (utfil.is_open()) {
            utfil << player1.x << "\n" << player1.rotation;
            utfil.close();
        }
    }
    ImGui::SameLine();

    if (ImGui::Button("LADDA SPEL")) {
        std::ifstream inFil("savegame.txt");
        if (inFil.is_open()) {
            inFil >> player1.x >> player1.rotation;
            inFil.close();
        }
    }
        
    ImGui::Separator();
    ImGui::Text("RETRO GRAFIKFILTER");

    ImGui::Checkbox("Aktivera PS2-Grafik", &enablePS2Graphics);
    if (enablePS2Graphics) {
        ImGui::SliderFloat("Farg-crunch", &colorDepth, 4.0f, 32.0f);
    }

    ImGui::Separator();
    if (isPlaying) { ImGui::TextColored(ImVec4(0,1,0,1), "STATUS: SPELET KORS"); }
     else          { ImGui::TextColored(ImVec4(1,0,0,1), "STATUS: PAUSAT"); }

     ImGui::End();


     if (isPlaying) { 
        if (player1.isAttacking) {
            player1.swordSwing += 8.0f;
            if (player1.swordSwing >= 90.0f) { player1.isAttacking = false; }
        } else if (player1.swordSwing > 0.0f) {
            player1.swordSwing -= 4.0f;
        }
    }


    float dx = camX - player1.x;
    float dy = camY - player1.y;
    float dz = camZ - player1.z;
    float avstand = std::sqrt(dx*dx + dy*dy + dz*dz);

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    if (avstand < 6.0f) {

    }
    else if (avstand >= 6.0f && avstand < 15.0f) {

    }
    else {
    }



    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
}


ImGui_ImplOpenGL3_Shutdown();
ImGui_ImplGlfw_Shutdown();
ImGui::DestroyContext();

glfwTerminate();
return 0;
}