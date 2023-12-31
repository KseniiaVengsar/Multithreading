// Multithreading.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mtx; 

int client = 0;  // Счетчик клиентов
const int maxClients = 10;  // Макс кол клиентов

void clientTh() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        {
            std::lock_guard<std::mutex> lock(mtx);
            if (client < maxClients) {
                ++client;
                std::cout << "Клиент пришел. Всего клиентов: " << client << std::endl;
            }
        }
    }
}

void operatorTh() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        {
            std::lock_guard<std::mutex> lock(mtx);
            if (client > 0) {
                --client;
                std::cout << "Операционист обслужил клиента. Всего клиентов: " << client << std::endl;
            }
        }
    }
}

int main() {
    std::setlocale(LC_ALL, "RU");

    std::thread clientObj(clientTh);
    std::thread operatorObj(operatorTh);

   
    clientObj.join();
    operatorObj.join();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
