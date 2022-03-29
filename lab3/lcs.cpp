#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class LCSOperator {
private:
    enum direct { left, top, leftop };

public:
    std::string LCS(const std::string& str1, const std::string& str2) {
        // dp - start from 1
        std::vector<std::vector<int>> dp(str1.size() + 1, std::vector<int>(str2.size() + 1, 0));
        std::vector<std::vector<direct>> path(str1.size(), std::vector<direct>(str2.size()));
        for (int i = 0; i < str1.size(); ++i) {
            for (int j = 0; j < str2.size(); ++j) {
                if (str1[i] == str2[j]) {
                    dp[i + 1][j + 1] = dp[i][j] + 1;
                    path[i][j]       = leftop;
                } else {
                    if (dp[i + 1][j] > dp[i][j + 1]) {
                        dp[i + 1][j + 1] = dp[i + 1][j];
                        path[i][j]       = left;
                    } else {
                        dp[i + 1][j + 1] = dp[i][j + 1];
                        path[i][j]       = top;
                    }
                }
            }
        }

        std::string lcs;
        int i = str1.size() - 1, j = str2.size() - 1;
        while (i > 0 || j > 0) {
            if (str1[i] == str2[j]) {
                lcs.push_back(str1[i]);
            }
            switch (path[i][j]) {
                case left: --j; break;
                case top: --i; break;
                case leftop: --i, --j; break;
            }
        }
        if (str1[0] == str2[0]) lcs.push_back(str1[0]);
        std::reverse(lcs.begin(), lcs.end());
        return lcs;
    }
};

int main(int argc, char** argv) {
    LCSOperator lcso;
    std::string s1 = "ACCGGTCGAGATGCAG";
    std::string s2 = "ACCGGTCGAGATGCAA";

    auto lcs = lcso.LCS(s1, s2);
    std::cout << lcs << "\t(maxLength: " << lcs.size() << ")" << std::endl;
}