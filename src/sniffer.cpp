#include "sniffer.h"
#include <sstream>
#include <vector>
#include <string>

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

// Обрабатывает одну строку: при первом триггере RA, SA или TA обновляет двумерный вектор
void process_line(const std::string& line,
    std::vector<std::pair<std::string, int>>& countsVec) {
    auto kvList = parse_line(line);
    for (const auto& kv : kvList) {
        // разобьём ключ по '/'
        std::istringstream ks(kv.first);
        std::string part;
        while (std::getline(ks, part, '/')) {
            if (part == "RA" || part == "SA" || part == "TA") {
                const std::string& mac = kv.second;
                int idx = find_mac_index(countsVec, mac);
                if (idx >= 0) {
                    countsVec[idx].second++;
                }
                else {
                    countsVec.emplace_back(mac, 1);
                }
                return;  // обработали первый триггер — выходим
            }
        }
    }
}
