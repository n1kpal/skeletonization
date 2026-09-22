#include "algorithm.hpp"
#include <bitset>
#include <vector>
#include <unordered_set>
#include <cmath>
#include "Point.hpp"

#include <iostream>

using namespace std;

const bitset<512> tab("00000000000001010000000001010101000000000000000001010000010101010000000000000000000000000000000000000000000000000101000001010100000000000000010100000000010101010000000000000000010100000101010110000000100000000000000000000000100000001000000011010000110100000010001000100011000000000000001100100010001000100000000000000000000000000000000000000000000000000000000000000000000000000000000010100010101000110000000000000000101000101010001000000000000000001010001010100000000000000000000010100000101000001100000000000000");
const short a[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}};

// Возвращает true если данный пиксель имеет хоть один пиксель фона в окрестности
bool is_board(const vector<vector<bool>>& matrix, const int& line, const int& column) {
    for (short i = 0; i < 8; ++i) {
        if (!matrix[line + a[i][0]][column + a[i][1]]) return true;
    }
    return false;
}

// Преобразует окресность пикселя в индекс шаблона для tab
short pixel_to_index(const vector<vector<bool>>& matrix, const int& line, const int& column) {
    short index = 0;
    for (short i = 0; i < 8; ++i) {
        index += matrix[line + a[i][0]][column + a[i][1]] * pow(2, i);
    }
    return index;
}

/*
Принимает на вход матрицу где 1 - пиксель объекта, 0 - пиксель фона.
Границы входной матрицы должны быть фоном.
*/
void skeletonization(vector<vector<bool>>& matrix) {
    unsigned int height = matrix.size();
    unsigned int width = matrix[0].size();
    unordered_set<Point, PointHash> boarder;
    unordered_set<Point, PointHash> nextBoarder;

    // Первый раз ищем границы
    for (int line = 1; line < height - 1; line++) for (int column = 1; column < width - 1; column++) {
        if (matrix[line][column] && is_board(matrix, line, column)) {
            boarder.emplace(line, column);
        }
    }

    // even == true на четных и false на не четных итерациях
    bool even = false;
    // flag используется для отслеживания последней итерации
    bool flag = true;
    while (flag) {
        if (!even) flag = false;
        // Проходимся по границам
        for (auto it = boarder.begin(); it != boarder.end(); ) {
            Point i = *it;
            // Если шаблону соответствует true в tab (even == 1 на четных и 0 на не четных итерациях)
            if (tab[pixel_to_index(matrix, i.x, i.y) * 2 + even]) {
                // То оставляем этот пиксель в boarder, а всех его соседей едениц помещаем в nextBoarder
                for (short j = 0; j < 8; ++j) {
                    if (matrix[i.x + a[j][0]][i.y + a[j][1]]) {
                        nextBoarder.emplace(i.x + a[j][0], i.y + a[j][1]);
                    }
                }
                it++;
            // Иначе добавляем в nextBoarder сам пиксель и удаляем его из boarder
            } else {
                nextBoarder.emplace(i);
                it = boarder.erase(it);
            }
        }
        // Если на удаление осталась хотя бы одна точка то итерация не последняя
        if (!boarder.empty()) flag = true;
        if (even && !flag) break;

        // Удаляем из matrix все точки оставшиеся в boarder
        for (Point i : boarder) {
            matrix[i.x][i.y] = 0;
        }
        swap(boarder, nextBoarder);
        nextBoarder.clear();
        
        even = !even;
    }
}
