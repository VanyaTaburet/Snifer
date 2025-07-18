#include "sniffer.h"
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>  // std::sort


// Парсит одну строку лога в пары <ключ, значение>
std::vector<std::pair<std::string, std::string>> parse_line(const std::string& line) {
    std::vector<std::pair<std::string, std::string>> kvList;
    std::string token;
    std::istringstream ss(line);
    while (std::getline(ss, token, ',')) {
        auto pos = token.find('=');
        if (pos == std::string::npos) continue;
        std::string key = token.substr(0, pos);
        std::string value = token.substr(pos + 1);
        kvList.emplace_back(key, value);
    }
    return kvList;
}

// Находит в countsVec пару с первого столбца == mac, возвращает индекс или -1
static int find_mac_index(const std::vector<std::pair<std::string, int>>& countsVec,
    const std::string& mac) {
    for (size_t i = 0; i < countsVec.size(); ++i) {
        if (countsVec[i].first == mac)
            return static_cast<int>(i);
    }
    return -1;
}

// Обрабатывает одну строку: 
void process_line(const std::string& line,
    std::vector<std::pair<std::string, int>>& countsVec) {
    auto kvList = parse_line(line);

    for (const auto& kv : kvList) {
        std::istringstream ks(kv.first);
        std::string part;
        bool isTrigger = false;  // Флаг: найден ли триггер в этом ключе

        // Проверяем все части ключа через слэш
        while (std::getline(ks, part, '/')) {
            if (part == "RA" || part == "SA" || part == "TA") {
                isTrigger = true;  // Триггер найден в этом ключе
                break;             // Выходим из цикла по частям, но обрабатываем ключ
            }
        }

        // Если в ключе был хотя бы один триггер
        if (isTrigger) {
            const std::string& mac = kv.second;
            int idx = find_mac_index(countsVec, mac);
            if (idx >= 0) {
                countsVec[idx].second++;
            }
            else {
                countsVec.emplace_back(mac, 1);
            }
        }
    }
}

void sort_by_count(std::vector<std::pair<std::string, int>>& countsVec)
{
    std::sort(countsVec.begin(), countsVec.end(),
        [](const auto& a, const auto& b)
        {
            if (a.second != b.second)       // большее количество → раньше
                return a.second > b.second;
            return a.first < b.first;       // tie-breaker: MAC по алфавиту
        });
}
