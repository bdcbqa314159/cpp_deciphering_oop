#include <iostream>

using std::cout, std::cin, std::endl, std::flush;

int main()
{
    int ***threeDimArray = nullptr;

    int dim1{}, dim2{}, dim3{};
    cout << "Enter the 3 dimensions: dim1, dim2, dim3\n>>> ";
    cin >> dim1 >> dim2 >> dim3;

    threeDimArray = new int **[dim1];

    for (int i = 0; i < dim1; ++i)
        threeDimArray[i] = new int *[dim2];

    for (int i = 0; i < dim1; ++i)
    {
        for (int j = 0; j < dim2; ++j)
            threeDimArray[i][j] = new int[dim3];
    }

    for (int i = 0; i < dim1; ++i)
    {
        for (int j = 0; j < dim2; ++j)
        {
            for (int k = 0; k < dim3; ++k)
            {
                threeDimArray[i][j][k] = i + j + k;
                cout << threeDimArray[i][j][k] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

    for (int i = 0; i < dim1; ++i)
    {
        for (int j = 0; j < dim2; ++j)
        {
            delete[] threeDimArray[i][j];
        }
        delete[] threeDimArray[i];
    }
    delete[] threeDimArray;

    return 0;
}