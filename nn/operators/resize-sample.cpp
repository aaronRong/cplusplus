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

void upsample_int(/*const*/ int* src,
                  int* dst,
                  int h_in,
                  int w_in,
                  int h_scale,
                  int w_scale)
{
    int* psrc = src;
    int* pdst = dst;
    for (int _h_in = 0; _h_in < h_in; ++_h_in)
    {
        for (int _w_scale = 0; _w_scale < w_scale; ++_w_scale)
        {
            memcpy(pdst, psrc, sizeof(int) * w_in);
            pdst += w_in;
        }
        for (int _h_scale = 0; _h_scale < h_scale - 1; ++_h_scale)
        {
            memcpy(pdst, pdst - w_scale * w_in, sizeof(int) * w_in * w_scale);
        }
        pdst += (h_scale - 1) * w_scale * w_in;
        psrc += w_in;
    }
}

int main()
{
    // vector<int> src = {1, 2, 3, 4};
    // vector<int> dst;
    // upsample_int(src, dst, 2, 2, 2, 3);
    // cout << "result: ";
    // for_each(dst.begin(), dst.end(), [](int i){ cout << i << " "; });

    int src[] = {1, 2, 3, 4};
    int dst[4 * 2 * 3];
    upsample_int(src, dst, 2, 2, 2, 3);
    for (int i = 0; i < 4 * 2 * 3; ++i)
    {
        cout << dst[i] << " ";
    }
    return 0;
}