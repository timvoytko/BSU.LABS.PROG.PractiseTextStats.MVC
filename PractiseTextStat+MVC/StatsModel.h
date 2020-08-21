#pragma once
#include"TextStat.h"
class StatsModel {
private:
    TextStat text_;
    int stroke_number_;
public:
    StatsModel(const std::string& filename) :text_(TextStat(filename)) {}
    void SetText(const std::string& filename);
    void SetStrokeNumber(int number);
    const std::vector<std::string> GetTextRows();
    int GetStrokeNumber();
    const TextStat GetTextStat();
    const std::vector<std::pair<int, double>> GetLengthStat();
    const std::vector<std::pair<char, double>> GetLetterStat();
};
