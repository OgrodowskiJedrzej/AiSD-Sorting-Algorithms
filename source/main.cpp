#include <iostream>
#include <algorithm>
#include <vector>

// insertion sort

void insertion_sort(int data[], int size)
{
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

// shell sort

std::vector<long long> generate_sedgewick_gaps(int how_many_gaps, int count)
{
    std::vector<long long> gaps;
    gaps.push_back(1); // added 1 to make correct sequence of gaps
    for (int i = 0; i <= how_many_gaps; i++)
    {
        long long gap = std::pow(4, i + 1) + 3 * std::pow(2, i) + 1;
        if (gap > count)
        {
            break;
        }
        gaps.push_back(gap);
    }
    return gaps;
}

void shell_sort(int data[], int size, const std::vector<long long> &sedgewick_gaps)
{
    for (int gap_index = sedgewick_gaps.size() - 1; gap_index >= 0; --gap_index)
    {
        long long gap = sedgewick_gaps[gap_index];
        for (int i = gap; i < size; ++i)
        {
            int temp = data[i];
            int j;
            for (j = i; j >= gap && data[j - gap] > temp; j -= gap)
            {
                data[j] = data[j - gap];
            }
            data[j] = temp;
        }
    }
}

// selection sort

void selection_sort(int data[], int size)
{
    int min_idx;
    for (int i = 0; i < size - 1; i++)
    {
        min_idx = i;
        for (int j = i + 1; j < size; j++)
        {
            if (data[j] < data[min_idx])
            {
                min_idx = j;
            }
        }
        if (min_idx != i)
        {
            std::swap(data[min_idx], data[i]);
        }
    }
}

// quick sort

int partition_left(int data[], int low, int high)
{
    int pivot = data[low];
    int p = low + 1;
    int q = high;

    while (true)
    {
        while (p <= q && data[p] <= pivot)
            p++;
        while (p <= q && data[q] >= pivot)
            q--;
        if (p <= q)
            std::swap(data[p], data[q]);
        else
            break;
    }

    std::swap(data[low], data[q]);
    return q;
}

void quick_sort_left_pivot(int *data, int low, int high)
{
    if (low < high)
    {
        int pivot = partition_left(data, low, high);
        quick_sort_left_pivot(data, low, pivot - 1);
        quick_sort_left_pivot(data, pivot + 1, high);
    }
}

int partition_random(int data[], int low, int high)
{
    int rand_index = rand() % (high - low + 1) + low;
    std::swap(data[high], data[rand_index]);
    int pivot = data[high];
    int p = low;
    int q = high - 1;

    while (true)
    {
        while (p <= q && data[p] <= pivot)
        {
            p++;
        }
        while (p <= q && data[q] >= pivot)
        {
            q--;
        }
        if (p <= q)
        {
            std::swap(data[p], data[q]);
        }
        else
        {
            break;
        }
    }

    std::swap(data[high], data[p]);
    return p;
}

void quick_sort_random_pivot(int data[], int low, int high)
{
    if (low < high)
    {
        int pivot = partition_random(data, low, high);
        quick_sort_random_pivot(data, low, pivot - 1);
        quick_sort_random_pivot(data, pivot + 1, high);
    }
}

// heap sort

void shift_down(int data[], int i, int upper)
{
    while (true)
    {
        int left = i * 2 + 1;
        int right = i * 2 + 2;

        if (std::max(left, right) < upper)
        {
            if (data[i] >= std::max(data[left], data[right]))
            {
                break;
            }
            else if (data[left] > data[right])
            {
                std::swap(data[i], data[left]);
                i = left;
            }
            else
            {
                std::swap(data[i], data[right]);
                i = right;
            }
        }
        else if (left < upper)
        {
            if (data[left] > data[i])
            {
                std::swap(data[i], data[left]);
                i = left;
            }
            else
            {
                break;
            }
        }
        else if (right < upper)
        {
            if (data[right] > data[i])
            {
                std::swap(data[i], data[right]);
                i = right;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
}

void heap_sort(int data[], int size)
{
    for (int j = (size - 2) / 2; j > -1; j--)
    {
        shift_down(data, j, size);
    }

    for (int end = size - 1; end > 0; end--)
    {
        std::swap(data[0], data[end]);
        shift_down(data, 0, end);
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

    // reading data set size
    int data_set_size;
    if (!(std::cin >> data_set_size))
    {
        std::cerr << "Error reading the maximum integer value\n";
        return 1;
    }

    // reading data set
    int data[data_set_size];
    int count = 0;
    int num;
    while (std::cin >> num && count < data_set_size)
    {
        data[count++] = num;
    }

    // run given algorithm
    switch (algorithm_number)
    {
    case 1:
    {
        insertion_sort(data, count);
        break;
    }
    case 2:
    {
        std::vector<long long> sedgewick_gaps = generate_sedgewick_gaps(30, count);
        shell_sort(data, count, sedgewick_gaps);
        break;
    }
    case 3:
    {
        selection_sort(data, count);
        break;
    }
    case 4:
    {
        heap_sort(data, count);
        break;
    }
    case 5:
    {
        quick_sort_left_pivot(data, 0, count - 1);
        break;
    }
    case 6:
    {
        quick_sort_random_pivot(data, 0, count - 1);
        break;
    }
    default:
    {
        std::cerr << "Wrong algorithm number"
                  << "\n";
        return 1;
    }
    }

    // print the sorted data
    std::cout << "Sorted data: ";
    for (int i = 0; i < std::min(1000, count); ++i)
    {
        std::cout << data[i] << " ";
    }
    std::cout << "\n";

    return 0;
}