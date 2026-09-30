#include "algorithm.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <bitset>

using namespace std;

int main(int argc, char* argv[]) {
    string inputPath = argv[1];
    string outputPath = argv[2];

    ifstream input(inputPath, ios_base::binary);
    // Для записи в output
    char header[62];
    input.read(header, 62);

    int32_t width = *reinterpret_cast<int32_t*>(header + 18);
    int32_t height = *reinterpret_cast<int32_t*>(header + 22);

    // Реальная ширина с учетом выравнивания
    int32_t realWidth;
    if (width % 32 != 0) {
        realWidth = width + (32 - width % 32);
    } else {
        realWidth = width;
    }

    vector<vector<bool>> matrix(height, vector<bool>(width));

    bitset<8> cur;
    // В этом условии я сделал не очень холрошо потому точ тут по сути почти полностью дублируется код но лучше я не придумал
    if (height > 0) { // Если высота положительная то нулевая строка в файле это самая нижняя
        for (int line = height - 1; line >= 0; line--) {
            for (int column = 0; column < realWidth / 8; column++) {
                cur = input.get();
                for (int i = 0; i < 8; i++) {
                    if (column * 8 + i >= width) break;
                    matrix[line][column * 8 + i] = !cur[7 - i]; // 7 - i из за инвертированной записи в байты
                }
            }
        }
    } else { // Иначе самая верхняя
        height = -height;
        for (int line = 0; line < height; line++) {
            for (int column = 0; column < realWidth / 8; column++) {
                cur = input.get();
                if (column * 8 > width) break;
                for (int i = 0; i < 8; i++) {
                    if (column * 8 + i >= width) break;
                    matrix[line][column * 8 + i] = !cur[7 - i];
                }
            }
        }
    }

    input.close();

    skeletonization(matrix);

    // Для записи высоту делаем положительной
    *reinterpret_cast<int32_t*>(header + 22) = height;
    ofstream output(outputPath, ios_base::binary);
    output.write(header, 62);

    for (int line = height - 1; line >= 0; line--) {
        for (int column = 0; column < realWidth / 8; column++) {
            cur = 0;
            for (int i = 0; i < 8; i++) {
                if (column * 8 + i >= width) break;
                cur[7 - i] = !matrix[line][column * 8 + i];
            }
            output.put(static_cast<char>(cur.to_ulong()));
        }
    }
    output.close();
}