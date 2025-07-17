#include "sniffer.h"
#include <gtest/gtest.h>
#include <vector>
#include <string>

// Тест для process_line: проверяем, что счетчик MAC верно наращивается
TEST(SnifferTest, ProcessLineRAandSATrigger) {
    std::vector<std::pair<std::string, int>> counts;

    // Строка с RA
    process_line("RA=AA:BB:CC:DD:EE:FF,Other=xyz", counts);
    ASSERT_EQ(counts.size(), 1u);
    EXPECT_EQ(counts[0].first, "AA:BB:CC:DD:EE:FF");
    EXPECT_EQ(counts[0].second, 1);

    // Строка с SA/TA
    process_line("Some=123,SA/TA=AA:BB:CC:DD:EE:FF", counts);
    ASSERT_EQ(counts.size(), 1u);
    EXPECT_EQ(counts[0].second, 2);

    // Новая TA
    process_line("TA=11:22:33:44:55:66", counts);
    ASSERT_EQ(counts.size(), 2u);
    EXPECT_EQ(counts[1].first, "11:22:33:44:55:66");
    EXPECT_EQ(counts[1].second, 1);
}
