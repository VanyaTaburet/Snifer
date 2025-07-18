#include "sniffer.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: sniffer <log-file>\n";
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Cannot open file: " << filename << "\n";
        return 1;
    }

    std::vector<std::pair<std::string, int>> countsVec;
    std::string line;
    while (std::getline(in, line)) {
        process_line(line, countsVec);
    }

    sort_by_count(countsVec);          // вызываем сортировку

    // Выводим в консоль, отсортировав по убыванию (можно добавить сортировку позже)
    for (auto& p : countsVec) {
        std::cout << p.first << " " << p.second << "\n";
    }

    return 0;
}
