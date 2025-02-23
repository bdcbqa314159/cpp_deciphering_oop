#include <iostream>

using std::cout, std::cin, std::endl, std::flush;

int main()
{
    int numRows{}, numCols{};
    double **twoDimArray = nullptr;

    cout << "Enter number of rows\n>>> ";
    cin >> numRows;
    cout << "\nEnter number of columns\n>>> ";
    cin >> numCols;

    twoDimArray = new double *[numRows];
    for (int i = 0; i < numRows; ++i)
        twoDimArray[i] = new double[numCols];

    for (int i = 0; i < numRows; ++i)
    {
        for (int j = 0; j < numCols; ++j)
        {
            twoDimArray[i][j] = i + j + 0.5;
            cout << twoDimArray[i][j] << " ";
        }
        cout << "\n";
    }

    for (int i = 0; i < numRows; ++i)
    {
        delete[] twoDimArray[i];
    }

    delete[] twoDimArray;

    return 0;
}