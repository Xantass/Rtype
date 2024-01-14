/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main
*/

#include "Main.hpp"
#include "../../ECS/ECSServer.hpp"

int main(int argc, char **argv)
{
    if (argc != 1)
        return 84;
    (void)argv;

    int index = 0;
    std::map<int, std::tuple<std::string, std::string>> spriteData;
    std::string spriteFolderPath = "./assets/sprite/";

    for (const auto &entry : std::filesystem::directory_iterator(spriteFolderPath)) {
        if (entry.is_regular_file()) {
            std::string filepath = entry.path().string();

            if (std::filesystem::exists(filepath)) {
                std::ifstream file(filepath, std::ios::binary);
                if (file) {
                    std::ostringstream fileContent;
                    fileContent << file.rdbuf();
                    // std::cout << "spriteData[" << index << "]: " << filepath << std::endl;
                    spriteData[index] = std::make_tuple(fileContent.str(), filepath);
                } else {
                    std::cerr << "Erreur lors de la lecture du fichier : " << filepath << std::endl;
                }
            } else {
                std::cerr << "Le fichier n'existe pas : " << filepath << std::endl;
            }
        }
        index++;
    }

    Coordinator coordinator;

    coordinator.Init();

    auto networkServerSystem = coordinator.RegisterSystem<NetworkServerSystem>();
    
    Signature signature;

    coordinator.SetSystemSignature<NetworkServerSystem>(signature);

    networkServerSystem->Init(spriteData);
    std::chrono::milliseconds interval(16);
    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::duration elapsedTime;
    while (1) {
        currentTime = std::chrono::steady_clock::now();
        elapsedTime = currentTime - startTime;
        if (elapsedTime >= interval) {
            networkServerSystem->Update(coordinator);
            startTime = currentTime;
        }
    }
    return 0;
}