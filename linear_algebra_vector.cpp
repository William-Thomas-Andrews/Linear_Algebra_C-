#include <iostream>
#include <string>
#include <stdexcept> 
#include <vector>
#include <initializer_list>
#include <cmath>

//implemented flat array style

template<typename T>
class Matrix 
{


    private:
        int dims;
        std::vector<int> dimensions;
        std::vector<T> matrix;


        int calculator(int index, int &relative_size)
        {
            return index * relative_size;
        }

        int computeFlatIndex(const std::vector<int>& indices) const 
        {
            if (indices.size() != dimensions.size())
            {
                throw std::invalid_argument("Number of indices specified must be equal to number of matrix dimension indices");
            }

            // int dim_index = 0;
            int flatIndex = 0;
            int relative_size = matrix.size();

            for (size_t i = 0; i < indices.size(); i++)
            {
                if (indices[i] < 0 || indices[i] >= dimensions[i])
                {
                    throw std::out_of_range("Index out of bounds for specified dimension " + std::to_string(i));
                }
                relative_size /= dimensions[i];
                flatIndex += indices[i] * relative_size;
            }
            return flatIndex;
        }

    public:

        Matrix(const std::vector<int>& dims, T value) : dims(dims.size()), dimensions(dims) 
        {
            int totalSize = 1;
            for (int dim : dimensions)
            {
                totalSize *= dim;
            }
            matrix.resize(totalSize, value);
        }

        // Matrix(const std::vector<int>& dims, std::vector<T> vec) : dims(dims.size()), dimensions(dims) 
        // {
        //     int totalSize = 1;
        //     for (int dim : dimensions)
        //     {
        //         totalSize *= dim;
        //     }
        //     matrix.resize(totalSize, value);
        // }


        // Access elements using N-dimensional indices
        T get (const std::vector<int>& indices) const
        {
            int flatIndex = computeFlatIndex(indices);
            return matrix.at(flatIndex);
        }

        void set(const std::vector<int>& indices, const T& value)
        {
            int flatIndex = computeFlatIndex(indices);
            matrix.at(flatIndex) = value;
        }




        // void createNDMatrix(int dims, T val, int vals_per_vector)
        // {
        //     for (int i = 0; i < dims)
        //     {
        //         for (int j = 0; j < std::pow(vals_per_vector, dims-1); j++)
        //         {
        //             for (int k = 0; k < vals_per_vector; k++)
        //             {
        //                 matrix.push_back(val);
        //             }
        //         }   
        //     }
        // }
};


int main()
{
    // Create a 3x3x3 matrix initialized with value 0
    Matrix<int> mat({3, 3, 3}, 0);

    // Set a value at position (1, 2, 1)
    mat.set({1, 2, 1}, 42);

    // Get the value at position (1, 2, 1)
    std::cout << "Value at (1, 2, 1): " << mat.get({1, 2, 1}) << std::endl;

    // Try accessing out-of-bounds indices
    try 
    {
        mat.get({3, 2, 1}); // Out of bounds
    } catch (const std::out_of_range& e) 
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
