#pragma once
#include"TextStat.h"
TextStat::TextStat(std::string filename) {
        
    std::ifstream in(filename);
    if (!in.is_open())abort();
    std::string tmp;
            while (!in.eof()) {
            bool exitflag = 1;
            std::getline(in, tmp);
            rows.push_back(tmp);
            std::sort(tmp.begin(), tmp.end());
            std::map<char, int> tmp_letters_map;
            auto it = std::equal_range(tmp.begin(), tmp.end(), ' ');
            tmp.erase(it.first, it.second);
            if (tmp == "") {
                exitflag = 0;
                tmp_letters_map.insert({ ' ', 1});
            }
            else {
                it = std::equal_range(tmp.begin(), tmp.end(), tmp[0]);
                tmp_letters_map.insert({ tmp[0],it.second - it.first });
                int j = 1;
                while (it.second != tmp.end()) {
                    auto it2 = std::equal_range(it.second, tmp.end(), tmp[j]);
                    tmp_letters_map.insert({ tmp[j],it2.second - it2.first });
                    it = it2;
                    j++;
                }
            }
            letters.push_back(tmp_letters_map);
            std::map<int, int> tmp_length_map;
            tmp = rows.back();
            exitflag = 1;
            std::vector<char> special;
            for (int i = 33; i < 65; i++)special.push_back(i);
            for (int i=91;i<97;i++)special.push_back(i);    
            for (int i = 123; i < 127; i++)special.push_back(i);
            for (int i = 0; i < special.size(); i++) {
                for (int j = 0; j < tmp.length(); j++) {
                    if (tmp[j] == special[i])tmp[j] = ' ';
                }
            }
            while (tmp[0] == ' ') {
                tmp.erase(tmp.begin());
            }
            int size1 = tmp.find(' '), size2;
            if (tmp == "") {
                exitflag = 0;
                size1 = 0;
            }
            if (exitflag&&size1 == std::string::npos) {
                size1 = tmp.length();
                exitflag = 0;
            }
            tmp_length_map.insert({ size1,1 });
            while (exitflag) {
                size2 = tmp.find(' ', size1 + 1);
                if (size2 == std::string::npos) {
                    size2 = tmp.length() ;
                    exitflag = 0;
                }
                if (size2 - size1 - 1 == 0) {
                    size1 = size2;
                    continue;
                }
                tmp_length_map[size2 - size1 - 1]++;
                size1 = size2;
            }
            lengths.push_back(tmp_length_map);
        }
    }

std::vector<std::pair<char, double>> TextStat::GetLettersStat(int row_number){
    int count_of_let = 0;
    for (auto i : letters[row_number]) {
        count_of_let += i.second;
    }
    std::vector<std::pair<char, double>> stats;
    for (auto i : letters[row_number]) {
        stats.push_back({ i.first, (double)i.second / count_of_let });
    }
    return stats;
}
std::vector<std::pair<int, double>> TextStat::GetLengthStat(int row_number){
    int length_sum = 0;
    for (auto i : lengths[row_number]) {
        length_sum += i.second;
    }
    std::vector<std::pair<int, double>> stats;
    for (auto i : lengths[row_number]) {
        stats.push_back({ i.first,(double)i.second / length_sum });
    }
    return stats;
}