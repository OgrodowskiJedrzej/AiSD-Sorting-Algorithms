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

void swap(int *data, int i, int j) {
    int temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

int partition_left(int *data, int low, int high) {
    int pivot = data[low];
    int p = low + 1;
    int q = high;

    while (true) {
        while (p <= q && data[p] <= pivot) p++;
        while (p <= q && data[q] >= pivot) q--;
        if (p <= q) swap(data, p, q);
        else break;
    }

    swap(data, low, q);
    return q;
}

void quick_sort_left_pivot(int *data, int low, int high) {
    if(low < high) {
        int pivot = partition_left(data, low, high);
        quick_sort_left_pivot(data, low, pivot-1);
        quick_sort_left_pivot(data, pivot+1, high);
    }
}

int partition_right(int *data, int low, int high) {
    int pivot = data[high];
    int p = low;
    int q = high-1;

    while(true) {
        while(p <= q && data[p] <= pivot) p++;
        while(p <= q && data[q] >= pivot) q--;
        if(p <= q) swap(data, p, q);
        else break;
    }

    swap(data, high, p);
    return p;
}

void quick_sort_right_pivot(int *data, int low, int high) {
    if(low < high) {
        int pivot = partition_right(data, low, high);
        quick_sort_right_pivot(data, low, pivot-1);
        quick_sort_right_pivot(data, pivot+1, high);
    }
}

void shift_down(int *data, int i, int upper) {
    while(true) {
        int l = i*2+1;
        int r = i*2+2;

        if(std::max(l, r) < upper) {
            if(data[i] >= std::max(data[l], data[r])) {
                break;
            }
            else if(data[l] > data[r]) {
                swap(data, i, l);
                i = l;
            }
            else {
                swap(data, i, r);
                i = r;
            }
        }
        else if(l < upper) {
            if(data[l] > data[i]) {
                swap(data, i, l);
                i = l;
            }
            else {
                break;
            }
        }
        else if(r < upper) {
            if(data[r] > data[i]) {
                swap(data, i, r);
                i = r;
            }
            else {
                break;
            }
        }
        else {
            break;
        }
    }
}

void heap_sort(int *data, int size) {
    for(int j=(size-2)/2; j>-1; j--) {
        shift_down(data, j, size);
    }

    for(int end=size-1; end>0; -1) {
        swap(data, 0, end);
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
