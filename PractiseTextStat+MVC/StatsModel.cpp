#pragma once
#include"StatsModel.h"
 int StatsModel::GetStrokeNumber(){
    return stroke_number_;
}
 const TextStat StatsModel::GetTextStat(){
    return text_;
}
 void  StatsModel::SetStrokeNumber(int number) {
    stroke_number_ = number;
}
 const std::vector<std::pair<int, double>> StatsModel::GetLengthStat() {
    return text_.GetLengthStat(stroke_number_);
}
 const std::vector<std::pair<char, double>>  StatsModel::GetLetterStat() {
    return text_.GetLettersStat(stroke_number_);
}
 const std::vector<std::string> StatsModel::GetTextRows() {
     return text_.rows;
 }
 void StatsModel::SetText(const std::string& filename){
     text_ = TextStat(filename);
 }