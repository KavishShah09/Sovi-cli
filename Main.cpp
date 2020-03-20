#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
using namespace std;

// struct Timer
// {
//     chrono::time_point<chrono::steady_clock> start, end;
//     chrono::duration<float> duration;

//     Timer()
//     {
//         start = chrono::high_resolution_clock::now();
//     }

//     ~Timer()
//     {
//         end = chrono::high_resolution_clock::now();
//         duration = end - start;

//         float ms = duration.count() * 1000.0f;
//         cout << "\nTime taken: " << ms << "ms" << endl;
//     }
// };

void PrintArray(vector<int> &data)
{
    for (int i = 0; i < (int)(data.size()); i++)
    {
        cout << data[i] << " ";
    }
}

void GenerateArray(int n, vector<int> &data)
{
    int element;
    for (int i = 0; i < n; i++)
    {
        element = rand() % 100;
        data.emplace_back(element);
    }
    cout << "\nRandom Elements: ";
    PrintArray(data);
    cout << "\n";
}

void SelectionSort(vector<int> &data)
{
    for (int i = 0; i < (int)(data.size()) - 1; i++)
    {
        int iMin = i;
        for (int j = i + 1; j < (int)data.size(); j++)
        {
            if (data[j] < data[iMin])
                iMin = j;
        }
        if (i != iMin)
        {
            swap(data[i], data[iMin]);
            cout << "Sorting: ";
            PrintArray(data);
            cout << "\n";
        }
    }
}

void BubbleSort(vector<int> &data)
{
    for (int i = 0; i < (int)data.size() - 1; i++)
    {
        int flag = 0;
        for (int j = 0; j < ((int)data.size() - i - 1); j++)
        {
            if (data[j] > data[j + 1])
            {
                swap(data[j], data[j + 1]);
                cout << "Sorting: ";
                PrintArray(data);
                cout << "\n";
                flag = 1;
            }
        }
        if (flag == 0)
            break;
    }
}

void InsertionSort(vector<int> &data)
{
    for (int i = 1; i < (int)data.size(); i++)
    {
        int value = data[i];
        int hole = i;
        while (hole > 0 && data[hole - 1] > value)
        {
            data[hole] = data[hole - 1];
            hole -= 1;
        }
        data[hole] = value;
        cout << "Sorting: ";
        PrintArray(data);
        cout << "\n";
    }
}

void Merge(vector<int> &left, vector<int> &right, vector<int> &data)
{
    int sizeLeft = (int)left.size(), sizeRight = (int)right.size();
    int i = 0, j = 0, k = 0;
    while (i < sizeLeft && j < sizeRight)
    {
        if (left[i] <= right[j])
        {
            data[k] = left[i];
            i++;
        }
        else
        {
            data[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < sizeLeft)
    {
        data[k] = left[i];
        i++;
        k++;
    }
    while (j < sizeRight)
    {
        data[k] = right[j];
        j++;
        k++;
    }
}

void MergeSort(vector<int> &data)
{
    int size = (int)data.size();
    if (size < 2)
        return;
    int mid = size / 2;
    vector<int> left(mid);
    vector<int> right(size - mid);
    for (int i = 0; i < mid; i++)
        left[i] = data[i];
    for (int i = mid; i < size; i++)
        right[i - mid] = data[i];
    MergeSort(left);
    MergeSort(right);
    Merge(left, right, data);
    cout << "Sorting: ";
    PrintArray(data);
    cout << "\n";
}

int Partition(vector<int> &data, int start, int end)
{
    int pivot = data[end];
    int partitionIndex = start;
    for (int i = start; i < end; i++)
    {
        if (data[i] <= pivot)
        {
            swap(data[i], data[partitionIndex]);
            partitionIndex++;
        }
    }
    swap(data[partitionIndex], data[end]);
    return partitionIndex;
}

int RandomizedPartition(vector<int> &data, int start, int end)
{
    int PivotIndex = start + rand() % (end - start);
    swap(data[PivotIndex], data[end]);
    return Partition(data, start, end);
}

void QuickSort(vector<int> &data, int start, int end)
{
    if (start < end)
    {
        cout << "Sorting: ";
        PrintArray(data);
        cout << "\n";
        int partitionIndex = RandomizedPartition(data, start, end);
        QuickSort(data, start, partitionIndex - 1);
        QuickSort(data, partitionIndex + 1, end);
    }
}

void heapify(vector<int> &data, int len, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < len && data[left] > data[largest])
        largest = left;

    if (right < len && data[right] > data[largest])
        largest = right;

    if (largest != i)
    {
        swap(data[i], data[largest]);

        heapify(data, len, largest);
    }
}

void HeapSort(vector<int> &data)
{
    for (int i = (int)data.size() / 2 - 1; i >= 0; i--)
        heapify(data, (int)data.size(), i);

    for (int i = (int)data.size() - 1; i >= 0; i--)
    {
        swap(data[0], data[i]);
        heapify(data, i, 0);
        cout << "Sorting: ";
        PrintArray(data);
        cout << "\n";
    }
}

int main()
{
    srand((unsigned int)time(NULL));
    int n, element, choice;
    cout << "Press 1 to generate random elements or press 2 to enter your elements: ";
    cin >> choice;
    cout << "Enter the number of elements you would like to sort: ";
    cin >> n;
    vector<int> data;
    data.reserve(n);
    if (choice == 1)
    {
        GenerateArray(n, data);
    }
    else
    {
        cout << "Enter the elements: ";
        for (int i = 0; i < n; i++)
        {
            cin >> element;
            data.emplace_back(element);
        }
    }
    cout << "\n";
    int algoChoice;
    cout << "Choose the algorithm 1)Selection Sort 2)Bubble Sort 3)Insertion Sort 4)Merge Sort 5)Quick Sort 6)Heap Sort: ";
    cin >> algoChoice;
    cout << "\n";
    //Timer timer;
    switch (algoChoice)
    {
    case 1:
        SelectionSort(data);
        break;
    case 2:
        BubbleSort(data);
        break;
    case 3:
        InsertionSort(data);
        break;
    case 4:
        MergeSort(data);
        break;
    case 5:
        QuickSort(data, 0, data.size() - 1);
        break;
    case 6:
        HeapSort(data);
        break;
    default:
        cout << "Invalid Input!";
        break;
    }
    cout << "\nSorted Elements: ";
    PrintArray(data);
    cout << "\n";
    system("PAUSE");
    return 0;
}