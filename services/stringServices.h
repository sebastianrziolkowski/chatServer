#ifndef CHATSERVER_STRINGSERVICES_H
#define CHATSERVER_STRINGSERVICES_H

#include <string>
#include <algorithm>
#include <bits/stdc++.h>
#include <sstream>

class stringService {
private:
    static void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
        }));
    }

    static void rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }

public:
    static void trim(std::string &s) {
        ltrim(s);
        rtrim(s);
    }

    static string removeDupWord(const string &str) {
        istringstream ss(str);
        unordered_set <string> hsh;
        string result;
        do {
            string word;
            ss >> word;
            while (hsh.find(word) == hsh.end()) {
                hsh.insert(word);
                result.append(word).append(" ");
            }

        } while (ss);
        return result;
    }
};

#endif //CHATSERVER_STRINGSERVICES_H
