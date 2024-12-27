#include <iostream>
#include <string>
#include <stdexcept> 
#include <vector>
#include <initializer_list>
#include <cmath>
#include <cstdlib>



template<typename T>
class Matrix 
{


    private:
        int num_dims;
        std::vector<int> dim_vector;
        T* matrix_array;
        int capacity;
        int size;

        void grow()
        {
            int new_capacity = 2 * capacity;
            T* replacement_matrix = (T*)malloc((sizeof(T) * new_capacity));
            for (int i = 0; i < size; i++)
            {
                replacement_matrix[i] = matrix_array[i];
            }

            free(matrix_array);

            matrix_array = replacement_matrix;

            capacity = new_capacity;
        }


        int computeFlatIndex(const std::vector<int>& indices) const 
        {
            if (indices.size() != dim_vector.size())
            {
                throw std::invalid_argument("Number of indices specified must be equal to number of matrix dimension indices");
            }

            int flatIndex = 0;
            int relative_size = capacity;

            for (size_t i = 0; i < indices.size(); i++)
            {
                if (indices[i] < 0 || indices[i] >= dim_vector[i])
                {
                    throw std::out_of_range("Index out of bounds for specified dimension " + std::to_string(i));
                }
                relative_size /= dim_vector[i];
                flatIndex += indices[i] * relative_size;
            }
            return flatIndex;
        }



    public:


        Matrix(std::vector<T> dim_vec) : num_dims(dim_vec.size()), dim_vector(dim_vec), capacity(1000000000), size(0)
        {
            matrix_array = (T*)malloc(sizeof(T) * capacity);
            if (!matrix_array) 
            {
                throw std::bad_alloc();
            }
        }

        // input can be a vector for now
        Matrix(std::vector<T> dim_vec, std::vector<T> input_data) : num_dims(dim_vec.size()), dim_vector(dim_vec), capacity(1000000000), size(input_data.size())
        {
            matrix_array = (T*)malloc(sizeof(T) * capacity);
            if (!matrix_array) 
            {
                throw std::bad_alloc(); 
            }
            for (size_t i = 0; i < input_data.size(); ++i) 
            {
                if (size == capacity) 
                {
                    grow();  // Resize the matrix if needed
                }
                matrix_array[size++] = input_data[i];
            }
        }


        ~Matrix()
        {
            if(matrix_array)
            {
                free(matrix_array);
            }
        }



        // Access elements using N-dimensional indices
        T get (const std::vector<int>& indices) const
        {
            int flatIndex = computeFlatIndex(indices);
            return matrix_array[flatIndex];
        }

        void set(const std::vector<int>& indices, const T& value)
        {
            int flatIndex = computeFlatIndex(indices);
            matrix_array[flatIndex] = value;
        }
    


};


int main()
{
    std::vector<int> dims = {3, 3};
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    Matrix<int> matrix(dims, data);

    // Testing access
    std::vector<int> indices = {1, 1};
    std::cout << "Element at (1, 1): " << matrix.get(indices) << std::endl;

    // Set a value
    indices = {2, 2};
    matrix.set(indices, 42);

    std::cout << "Element at (2, 2): " << matrix.get(indices) << std::endl;

    return 0;
}