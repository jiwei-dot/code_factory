#include <vector>
#include <cstdint>
#include <string>
#include <tuple>

// "4, 2, 4(2, 1, 8, 4(1, 2, 1)), 1, 8"
// 00 01 02 03 00 01 xx xx xx 00 00 01 02 03 04 05 06 07

std::tuple<int, int, bool> get_next_size(
    const std::string &pattern,
    int start, int end)
{
    if (start >= end)
        return std::make_tuple(-1, -1, false);

    int p = start;
    while ((p < end) && ((pattern[p] < '0') || (pattern[p] > '9')))
        ++p;

    int q = p;
    while ((q < end) && ((pattern[q] >= '0') && (pattern[q] <= '9')))
        ++q;

    int size = std::stoi(std::string(pattern.begin() + p, pattern.begin() + q));

    bool is_array = (q < end) && (pattern[q] == '(');

    return std::make_tuple(size, q, is_array);
}

// 4(2, 1, 2, 4(1, 2, 1))
bool check_array(
    const std::vector<std::uint8_t> &data,
    int data_begin, int data_end,
    const std::string &pattern,
    int pattern_begin, int pattern_end)
{
    // 当data解析完但是pattern有余，则出错

    auto next_size = get_next_size(pattern, pattern_begin, pattern_end);
    if (std::get<2>(next_size))
    {
        // read std::get<0>(next_size) bytes, convert to int
        int len = 0;
        int temp = 0;
        bool res = check_array(data,
                    data_begin + std::get<0>(next_size),
                    data_begin + std::get<0>(next_size) + len,
                    pattern,
                    std::get<1>(next_size),
                    temp);
        return res && false;
    }
    else if (std::get<0>(next_size) == -1)
    {

    }
}

bool check(
    const std::vector<std::uint8_t> &data,
    int data_begin, int data_end,
    const std::string &pattern,
    int pattern_begin, int pattern_end)
{
    if ((data_begin >= data_end) && (pattern_begin >= pattern_end))
        return true;
}