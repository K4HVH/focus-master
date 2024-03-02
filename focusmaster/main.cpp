#include "features/client/client.hpp"

client cl;

int main() {

    //cl.debugtest();

    std::string command;

    do {
        std::cout << "Focus Master" << std::endl;
        std::cout << "Commands: generate delete ban exit" << std::endl;
        std::cout << "Enter command: ";
        std::cin >> command;
        std::cout << "" << std::endl;

        if (command == "generate") {
            int length;

            std::cout << "Enter key length: ";
            std::cin >> length;

            std::cout << cl.generateKey(length) << std::endl;
        }
        else {
			std::cout << "Invalid command." << std::endl << std::endl;
        }

    } while (command != "exit");

    return 0;
}