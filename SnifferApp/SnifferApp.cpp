#include "Sniffer.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

// Конструктор для класса Men
Men::Men(const int& frame, const std::string& macAdr) : frame(frame), macAdr(macAdr) {}

// Функция для вывода информации об объекте Men
void Men::printInfo() const {
    std::cout << macAdr << " " << frame << std::endl;
}

// Функция для валидации пути к файлу
void validateFilePath(int argc, char* argv[]) {
    std::setlocale(LC_ALL, "Russian");

    if (argc < 2) {
        std::cerr << "Использование: " << argv[0] << " <путь_к_файлу>" << std::endl;
        exit(1);
    }

    std::string filePath = argv[1];
    if (!fs::exists(filePath)) {
        std::cerr << "Ошибка: файл не существует: " << filePath << std::endl;
        exit(1);
    }

    if (fs::path(filePath).extension() != ".log") {
        std::cerr << "Ошибка: файл должен иметь расширение .log" << std::endl;
        exit(1);
    }
}

// Функция для парсинга файла
std::vector<Men> parseFile(const std::string& filePath) {
    std::ifstream fileStream(filePath);
    if (!fileStream.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл: " << filePath << std::endl;
        exit(1);
    }

    std::vector<Men> menVector;
    std::string line;
    while (std::getline(fileStream, line)) {
        for (size_t pos = 0; pos < line.length(); ) {
            if ((line[pos] == ',' || line[pos] == '/') &&
                (line.compare(pos + 1, 2, "RA") == 0 ||
                    line.compare(pos + 1, 2, "SA") == 0 ||
                    line.compare(pos + 1, 2, "TA") == 0) &&
                (line[pos + 3] == '/' || line[pos + 3] == '=')) {

                size_t equalPos = line.find('=', pos + 3);
                if (equalPos != std::string::npos) {
                    size_t commaPos = line.find(',', equalPos);
                    std::string macAdr = line.substr(equalPos + 1, commaPos - equalPos - 1);

                    bool found = false;
                    for (auto& men : menVector) {
                        if (men.macAdr == macAdr) {
                            men.frame += 1;
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        menVector.emplace_back(1, macAdr);
                    }

                    pos = commaPos != std::string::npos ? commaPos + 1 : line.length();
                }
                else {
                    pos = line.length();
                }
            }
            else {
                ++pos;
            }
        }
    }

    fileStream.close();
    return menVector;
}

// Функция для сортировки вектора объектов Men
void sortMenVector(std::vector<Men>& menVector) {
    std::sort(menVector.begin(), menVector.end(), [](const Men& a, const Men& b) {
        return b.frame < a.frame;
        });
}

// Функция для печати информации о всех объектах Men
void printMenVector(const std::vector<Men>& menVector) {
    for (const auto& men : menVector) {
        men.printInfo();
    }
}

// Основная функция
int main(int argc, char* argv[]) {
    validateFilePath(argc, argv);

    // Получаем путь к файлу из аргументов командной строки
    std::string file = argv[1];

    // Парсим файл и получаем вектор объектов Men
    std::vector<Men> menVector = parseFile(file);

    // Сортируем вектор по количеству фреймов
    sortMenVector(menVector);

    // Печатаем информацию обо всех объектах Men
    printMenVector(menVector);

    return 0;
}
