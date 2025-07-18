#ifndef SNIFFER_H
#define SNIFFER_H

#include <string>
#include <vector>
#include <utility>

// ������ ���� ������ ���� � ���� <����, ��������>
std::vector<std::pair<std::string, std::string>> parse_line(const std::string& line);

// ������������ ���� ������: ��� ������ �������� RA, SA ��� TA ��������� ��������� ������ <MAC, count>
void process_line(const std::string& line,
    std::vector<std::pair<std::string, int>>& countsVec);

/// ��������� pairs<MAC, count> �� �������� count.
void sort_by_count(std::vector<std::pair<std::string, int>>& v);

#endif // SNIFFER_H
