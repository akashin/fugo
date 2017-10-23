#include <vector>
#include <fstream>
#include <limits>
#include <cmath>
#include <numeric>

namespace fugo {

using Column = std::vector<double>;
using Row = std::vector<double>;
using Matrix = std::vector<Row>;

Matrix ReadMatrix(int rows, int columns)
{
    Matrix matrix(rows, Row(columns));
    for (int row = 0; row < rows; ++row) {
        for (int column = 0; column < columns; ++column) {
            std::cin >> matrix[row][column];
        }
    }
    return matrix;
}

Column ReadColumn(int rows)
{
    Column column(rows);
    for (int row = 0; row < rows; ++row) {
        std::cin >> column[row];
    }
    return column;
}

double innerProduct(const Column& c1, const Column& c2)
{
    return std::inner_product(c1.begin(), c1.end(), c2.begin(), 0.0);
}

namespace {

struct Position
{
    Position(int column, int row)
        : column(column)
        , row(row)
    { }

    int column;
    int row;
};

void SwapLines(Matrix &a, Column &b, std::vector <bool> &used_rows, Position &pivot_element)
{
    std::swap(a[pivot_element.column], a[pivot_element.row]);
    std::swap(b[pivot_element.column], b[pivot_element.row]);
    std::swap(used_rows[pivot_element.column], used_rows[pivot_element.row]);
    pivot_element.row = pivot_element.column;
}

void ProcessPivotElement(Matrix &a, Column &b, const Position &pivot_element)
{
    int size = a.size();

    auto scalingFactor = a[pivot_element.row][pivot_element.column];
    for (int column = 0; column < size; ++column) {
        a[pivot_element.row][column] /= scalingFactor;
    }
    b[pivot_element.row] /= scalingFactor;
    a[pivot_element.row][pivot_element.column] = 1.0;

    for (int row = 0; row < size; ++row) {
        if (row == pivot_element.row) {
            continue;
        }
        scalingFactor = a[row][pivot_element.column];
        for (int column = 0; column < size; ++column) {
            a[row][column] -= scalingFactor * a[pivot_element.row][column];
        }
        b[row] -= scalingFactor * b[pivot_element.row];
        a[row][pivot_element.column] = 0.0;
    }
}

void MarkPivotElementUsed(const Position &pivot_element, std::vector <bool> &used_rows, std::vector <bool> &used_columns)
{
    used_rows[pivot_element.row] = true;
    used_columns[pivot_element.column] = true;
}

Position SelectPivotElement(
    const Matrix &a,
    std::vector <bool> &used_rows,
    std::vector <bool> &used_columns)
{
    int size = a.size();
    Position pivot_element(-1, -1);
    double largestMagnitude = std::numeric_limits<double>::min();

    for (int row = 0; row < size; ++row) {
        if (used_rows[row]) {
            continue;
        }
        for (int column = 0; column < size; ++column) {
            if (used_columns[column]) {
                continue;
            }

            double currentMagnitude = fabs(a[row][column]);
            if (currentMagnitude > largestMagnitude) {
                pivot_element.row = row;
                pivot_element.column = column;
                largestMagnitude = currentMagnitude;
            }
        }
    }
    return pivot_element;
}

} // namespace

struct Equation
{
    Equation()
        : rows(0)
        , columns(0)
    { }

    Equation(const Matrix& a, const Column& b)
        : a(a)
        , b(b)
    {
        rows = a.size();
        columns = a[0].size();
    }

    bool validate(const Column& solution, double EPS = 1e-9) const
    {
        for (int row = 0; row < rows; ++row) {
            double value = 0;
            for (int column = 0; column < columns; ++column) {
                value += a[row][column] * solution[column];
            }
            if (value > b[row] + EPS) {
                return false;
            }
        }
        return true;
    }

    int eliminate()
    {
        std::vector<bool> used_columns(columns, false);
        std::vector<bool> used_rows(rows, false);
        int maxRank = std::min(rows, columns);
        for (int step = 0; step < maxRank; ++step) {
            Position pivot_element = SelectPivotElement(a, used_rows, used_columns);
            if (pivot_element.row == -1 && pivot_element.column == -1) {
                return step;
            }
            SwapLines(a, b, used_rows, pivot_element);
            ProcessPivotElement(a, b, pivot_element);
            MarkPivotElementUsed(pivot_element, used_rows, used_columns);
        }
        return maxRank;
    }

    Matrix a;
    Column b;

    int rows;
    int columns;
};

Equation ReadEquation()
{
    int size;
    std::cin >> size;
    Matrix a(size, std::vector <double> (size, 0.0));
    Column b(size, 0.0);
    for (int row = 0; row < size; ++row) {
        for (int column = 0; column < size; ++column) {
            std::cin >> a[row][column];
        }
        std::cin >> b[row];
    }
    return Equation(a, b);
}

std::ostream& operator << (std::ostream& os, const Column& column) {
    int size = column.size();
    for (int row = 0; row < size; ++row) {
        os << column[row] << " ";
    }
    os << std::endl;
    return os;
}

} // namespace fugo
