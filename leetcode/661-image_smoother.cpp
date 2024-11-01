#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> imageSmoother(std::vector<std::vector<int>>& img) {
        int limit_y = img.size(), limit_x = img[0].size();
        std::vector<std::vector<int>> smoothed(limit_y, std::vector<int>(limit_x, 0));

        for (int y = 0; y < limit_y; ++y)
            for (int x = 0; x < limit_x; ++x)
                ; // FINISH THIS
    }
};