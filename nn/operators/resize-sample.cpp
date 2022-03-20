#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// TODO: upsample_float
//       downsample_int, downsample_float
//       cout -> ostream, stringstream
//       lambda:
/*
    upsample: (integer multiplier)
    input:
    [[1,2]
     [3,4]]
    output: h/w, h*2, w*3
    [[1,2,1,2,1,2],
     [1,2,1,2,1,2],
     [3,4,3,4,3,4],
     [3,4,3,4,4,4]]
*/

void upsample_int(const vector<int>& src,
                  vector<int>& dst,
                  int h_in,
                  int w_in,
                  int h_scale,
                  int w_scale)
{
    map<int, vector<int>> item;
    for (int k = 0; k < h_in; ++k)
    {
        for (int i = 0; i < w_scale; ++i)
        {
            for (int j = 0; j < w_in; ++j)
            {
                item[k].push_back(src[k * w_in + j]);
            }
        }
    }

    for (int k = 0; k < h_in; ++k)
    {
        for (int i = 0; i < h_scale; ++i)
        {
            dst.insert(dst.end(), item[k].begin(), item[k].end());
        }
    }
}

int main()
{
    vector<int> src = {1, 2, 3, 4};
    vector<int> dst;
    upsample_int(src, dst, 2, 2, 2, 3);
    cout << "result: ";
    for_each(dst.begin(), dst.end(), [](int i){ cout << i << " "; });
    return 0;
}