#ifndef SNIFFER_H
#define SNIFFER_H

#include <string>
#include <vector>
#include <utility>

// Парсит одну строку лога в пары <ключ, значение>
std::vector<std::pair<std::string, std::string>> parse_line(const std::string& line);

// Обрабатывает одну строку: при первом триггере RA, SA или TA обновляет двумерный вектор <MAC, count>
void process_line(const std::string& line,
    std::vector<std::pair<std::string, int>>& countsVec);

#endif // SNIFFER_H
