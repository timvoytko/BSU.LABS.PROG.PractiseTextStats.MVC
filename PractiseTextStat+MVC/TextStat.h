#pragma once
#include<string>
#include<map>
#include<vector>
#include<fstream>
#include<algorithm>
struct TextStat {
    std::vector<std::string> rows;
    std::vector<std::map<char, int>> letters;
    std::vector<std::map<int, int>> lengths;
    TextStat(std::string filename);
    std::vector<std::pair<char, double>>GetLettersStat(int row_number);
    std::vector<std::pair<int, double>>GetLengthStat(int row_number);
};