#include <iostream>
#include <vector>

class PipelineScheduler {
private:
    enum direct { line1, line2 };

public:
    std::pair<int, std::string> MinAssemblyTime(const std::vector<int>& p1, const std::vector<int>& p2,
                                                const std::vector<int>& t1, const std::vector<int>& t2, int e1, int e2,
                                                int x1, int x2) {
        // dp[0] -> p1  dp[1] -> p2
        // dp[0][i] -> minTime before doing step i
        int step = p1.size();
        std::vector<std::vector<int>> dp(2, std::vector<int>(step));
        std::vector<std::vector<direct>> from(2, std::vector<direct>(step));
        dp[0][0] = e1, dp[1][0] = e2;
        from[0][0] = line1, from[1][0] = line2;

        for (int i = 0; i < step - 1; i++) {
            // record path
            if (dp[0][i] + p1[i] < dp[1][i] + p2[i] + t2[i]) {
                dp[0][i + 1]   = dp[0][i] + p1[i];
                from[0][i + 1] = line1;
            } else {
                dp[0][i + 1]   = dp[i][i] + p2[i] + t2[i];
                from[0][i + 1] = line2;
            }

            if (dp[1][i] + p2[i] < dp[0][i] + p1[i] + t1[i]) {
                dp[1][i + 1]   = dp[1][i] + p2[i];
                from[1][i + 1] = line2;
            } else {
                dp[1][i + 1]   = dp[0][i] + p1[i] + t1[i];
                from[1][i + 1] = line1;
            }
        }

        int minTime;
        std::string path;
        direct cur;
        if (dp[0][step - 1] + p1[step - 1] + x1 < dp[1][step - 1] + p2[step - 1] + x2) {
            minTime = dp[0][step - 1] + p1[step - 1] + x1;
            path.insert(0, "x1 -> exit");
            cur = line1;
        } else {
            minTime = dp[1][step - 1] + p2[step - 1] + x2;
            path.insert(0, "x2 -> exit");
            cur = line2;
        }

        for (int i = step; i > 0; --i) {
            switch (cur) {
                case line1:
                    path.insert(0, "S1," + std::to_string(i) + " -> ");
                    cur = from[0][i - 1];
                    break;
                case line2:
                    path.insert(0, "S2," + std::to_string(i) + " -> ");
                    cur = from[1][i - 1];
                    break;
            }
        }

        switch (cur) {
            case line1: path.insert(0, "enter -> e1 -> "); break;
            case line2: path.insert(0, "enter -> e2 -> "); break;
        }

        return {minTime, path};
    }
};

int main(int argc, char* argv[]) {
    PipelineScheduler ps;
    std::vector<int> a1 = {7, 9, 3, 4, 80};
    std::vector<int> a2 = {8, 5, 6, 4, 5};
    std::vector<int> t1 = {2, 3, 1, 3};
    std::vector<int> t2 = {2, 1, 2, 2};

    auto res = ps.MinAssemblyTime(a1, a2, t1, t2, 2, 4, 3, 6);
    std::cout << "minTime: " << res.first << std::endl;
    std::cout << "path: " << res.second << std::endl;
}