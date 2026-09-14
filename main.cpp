#include <bitset>
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;


const bitset<512> tab("00000000000001010000000001010101000000000000000001010000010101010000000000000000000000000000000000000000000000000101000001010100000000000000010100000000010101010000000000000000010100000101010110000000100000000000000000000000100000001000000011010000110100000010001000100011000000000000001100100010001000100000000000000000000000000000000000000000000000000000000000000000000000000000000010100010101000110000000000000000101000101010001000000000000000001010001010100000000000000000000010100000101000001100000000000000");


int main() {
    ifstream input("input.bmp", ios_base::binary);
    unsigned int header_size, width;
    int height;

    input.ignore(14);
    input.read(reinterpret_cast<char*>(&header_size), 4);

    if (header_size != 40) {
        cout << "incorrect header";
        return 0;
    }

    input.read(reinterpret_cast<char*>(&width), 4);
    input.read(reinterpret_cast<char*>(&height), 4);
    vector<vector<bool>> matrix(height, vector<bool>(width));

    input.ignore(36);

    bitset<8> cur;
    for (int i = height - 1; i >= 0; i--) for (int j = 0; j < width / 8; j++) {
        cur = input.get();
        for (int k = 0; k < 8; k++) {
            matrix[i][j*8+k] = cur[7 - k];
        }
    }
}