#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include "Scene.hpp"

int main() {
    Scene scene;

    try {
        scene.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}