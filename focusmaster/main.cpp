#include "features/client/client.hpp"

client cl;

int main() {

    //cl.debugtest();

    std::string command;

    do {
        std::cout << "Focus Master" << std::endl;
        std::cout << "Commands: generate ban rshwid exit" << std::endl;
        std::cout << "Enter command: ";
        std::cin >> command;
        std::cout << "" << std::endl;

        if (command == "generate") {
            int length;

            std::cout << "Enter key length: ";
            std::cin >> length;

            std::cout << cl.generateKey(length) << std::endl;
        }
        else if (command == "ban") {
            std::string identifier;
            std::string id;

            std::cout << "Identifiers: licenseid userid hwid ip" << std::endl;

            std::cout << "Enter Identifier: ";
			std::cin >> identifier;
            std::cout << "" << std::endl;

            std::cout << "Enter ID: ";
            std::cin >> id;
            std::cout << "" << std::endl;

            if (identifier == "licenseid" || identifier == "userid" || identifier == "hwid" || identifier == "ip") {
                std::cout << cl.banID(identifier, id) << std::endl;
            }
            else {
				std::cout << "Invalid identifier." << std::endl << std::endl;
            }
        }
        else if (command == "rshwid") {
            std::string id;

			std::cout << "Enter License ID: ";
            std::cin >> id;
            std::cout << "" << std::endl;

			std::cout << cl.rsHwid(id) << std::endl;
        }
        else {
			std::cout << "Invalid command." << std::endl << std::endl;
        }

    } while (command != "exit");

    return 0;
}