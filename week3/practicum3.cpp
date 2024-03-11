// practicum3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
using std::cout;
using std::cin;
namespace GlobalConstants {
    constexpr size_t ROWS_MAX_COUNT = 100;
    constexpr size_t COLUMNS_MAX_COUNT = 100;
};
namespace Files {
    constexpr char FILE1[] = "text.txt";
    constexpr char FILE2[] = "text1.txt";
    constexpr char FILE3[] = "result.txt";
}

struct Row {
    int fields[GlobalConstants::COLUMNS_MAX_COUNT];
    size_t fields_count = 0;
};
struct Matrix {
    Row rows[GlobalConstants::ROWS_MAX_COUNT];
    size_t rows_count = 0;
    size_t columns_count = 0;
};
int convertToInt(char* str)
{
    int num = 0;
    for (size_t i = 0; str[i] != '\0'; i++)
    {
        num *= 10;
        num += (str[i] - '0');
    }
    return num;
}
size_t readRow(char* str, Row& row)
{
    std::stringstream ss(str);
    size_t columns_count = 0;
    while (!ss.eof())
    {
        char buff[1024];
        ss.getline(buff, 1024, ',');
        row.fields[columns_count++] = convertToInt(buff);
        row.fields_count++;

    }
    return columns_count;
}
Matrix readMatrix(std::ifstream& ifs)
{
    Matrix m;
    size_t index = 0;
    while (true)
    {
        char buff[1024];
        if (ifs.eof())
            break;
        ifs.getline(buff, 1024, '|');
        m.columns_count = readRow(buff, m.rows[index++]);
        m.rows_count++;
    }
    return m;
}
Matrix readMatrixFromFile(const char* file) {
    std::ifstream ifs(file);
    if (!ifs.is_open())
    {
        std::cerr << "Could't open the file" << std::endl;
        return {};
    }
    return readMatrix(ifs);
}
void writeRow(std::ofstream& ofs, const Row& r)
{
    for (size_t i = 0; i < r.fields_count; i++)
    {
        ofs << r.fields[i];
        if (i < r.fields_count - 1)
        {
            ofs << ',';
        }
    }
}
void writeMatrix(std::ofstream& ofs, const Matrix& m)
{
    for (size_t i = 0; i < m.rows_count; i++)
    {
        writeRow(ofs, m.rows[i]);
        if (i < m.rows_count - 1)
        {
            ofs << '|';
        }
        
    }
}
bool writeMatrixInFile(const char* file, const Matrix& m) {
    std::ofstream ofs(file);
    if (!ofs.is_open())
    {
        std::cerr << "Could't open the file" << std::endl;
        return false;
    }
    writeMatrix(ofs, m);
    return true;
}
void printRow(const Row& r)
{
    for (size_t i = 0; i < r.fields_count; i++)
    {
        std::cout << r.fields[i] << " ";
    }
}
void printMatrix(const Matrix& m)
{
    for (size_t i = 0; i < m.rows_count; i++)
    {
        printRow(m.rows[i]);
        std::cout << std::endl;
    }
}
bool areValidMatrices(const Matrix& m1, const Matrix& m2)
{
    return m1.columns_count == m2.rows_count;
}

Matrix multiplyMatrices(const Matrix& m1, const Matrix& m2)
{
    Matrix result;
    if (!areValidMatrices(m1, m2))
    {
        std::cerr << "Matrices can't be multyplied";
        return {};
    }
    for (size_t i = 0; i < m1.rows_count; i++)
    {
        size_t k = 0;
        for (size_t j = 0; j < m2.columns_count; j++)
        {
            result.rows[i].fields[j] = 0;
            
            for (size_t k = 0; k < m2.rows_count; k++)
            {
                result.rows[i].fields[j] += m1.rows[i].fields[k] * m2.rows[k].fields[j];
                
            }
           
        }
        result.rows[i].fields_count = m2.columns_count;
    }
    result.rows_count = m1.rows_count;
    result.columns_count = m2.columns_count;
    return result;

}

int main()
{
    Matrix m1 = readMatrixFromFile(Files::FILE1);
    printMatrix(m1);
    cout << "Rows: " << m1.rows_count << "Columns: "<< m1.columns_count << std::endl;
    Matrix m2 = readMatrixFromFile(Files::FILE2);
    printMatrix(m2);
    cout << "Rows: " << m2.rows_count << "Columns: " << m2.columns_count << std::endl;
    Matrix m = multiplyMatrices(m1, m2);
    printMatrix(m);
    cout << "Rows: " << m.rows_count << "Columns: " << m.columns_count << std::endl;
    writeMatrixInFile(Files::FILE3, m);
    Matrix m100 = readMatrixFromFile(Files::FILE3);
    printMatrix(m100);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
