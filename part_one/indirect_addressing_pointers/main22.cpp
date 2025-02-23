#include <iostream>

using std::cout, std::cin, std::endl, std::flush;

constexpr int NUM_OF_ROWS = 5;

int main()
{

    float *twoDimArray[NUM_OF_ROWS] = {};
    int numCols = 0;

    cout << "Enter number of columns\n>>> ";
    cin >> numCols;

    for (int i = 0; i < NUM_OF_ROWS; ++i)
    {
        twoDimArray[i] = new float[numCols];

        for (int j = 0; j < numCols; ++j)
        {
            twoDimArray[i][j] = i + j + 0.5;
            cout << twoDimArray[i][j] << " ";
        }
        cout << "\n";
    }

    for (int i = 0; i < NUM_OF_ROWS; ++i)
    {
        delete[] twoDimArray[i];
    }

    return 0;
}