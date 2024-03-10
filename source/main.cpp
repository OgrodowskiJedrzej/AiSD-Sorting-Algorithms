#include <iostream>
#include <algorithm>

void insertion_sort(int *data, int size)
{
    std::cout << "insertion_sort in use"
              << "\n";
    int key, j;
    for (int i = 1; i < size; i++)
    {
        key = data[i];
        j = i - 1;
        while (j >= 0 && data[j] > key)
        {
            data[j + 1] = data[j];
            j = j - 1;
        }
        data[j + 1] = key;
    }
}

void selection_sort(int *data, int size)
{
    std::cout << "selection_sort in use"
              << "\n";
    int min_idx;
    for (int i = 0; i < size - 1; i++)
    {
        min_idx = i;
        for (int j = i + 1; j < size; j++)
        {
            if (data[j] < data[min_idx])
                min_idx = j;
        }
        if (min_idx != i)
            std::swap(data[min_idx], data[i]);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3 || std::string(argv[1]) != "--algorithm")
    {
        std::cout << "Usage: ./main --algorithm <algorithm_number>\n";
        return 1;
    }

    int algorithm_number = std::stoi(argv[2]);

    // Read the maximum integer value from standard input
    int max_int;
    if (!(std::cin >> max_int))
    {
        std::cerr << "Error reading the maximum integer value\n";
        return 1;
    }

    int data[max_int];

    // Read the remaining integers into the array
    int count = 0;
    int num;
    while (std::cin >> num && count < max_int)
    {
        data[count++] = num;
    }

    // TODO Change to switch case
    if (algorithm_number == 1)
    {
        insertion_sort(data, count);
    }
    else if (algorithm_number == 2)
    {
        selection_sort(data, count);
    }
    else
    {
        std::cerr << "Wrong algorithm number";
        return 1;
    }

    // Print the sorted data
    std::cout << "Sorted data: ";
    for (int i = 0; i < std::min(10, count); ++i)
    {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
