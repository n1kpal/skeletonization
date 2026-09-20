#include "algorithm.cpp"
#include "Bmp.hpp"
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

int main() {
    vector<vector<bool>> matrix(1024, vector<bool>(1024));
    ifstream input("input.bmp", ios_base::binary);
    input.ignore(62);

    bitset<8> cur;
    for (int i = 1023; i >= 0; i--) for (int j = 0; j < 1024 / 8; j++) {
        cur = input.get();
        for (int k = 0; k < 8; k++) {
            matrix[i][j*8+k] = cur[k];
        }
    }

    input.close();

    skeletonization(matrix);

    Bmp bmp;
    bmp.biWidth = 1024;
    bmp.biHeight = 1024;
    bmp.biSizeImage = 131072;
    bmp.bfSize = 131134;
    ofstream output("output.bmp", ios_base::binary);
    output.write(reinterpret_cast<char*>(&bmp), sizeof(bmp));
}