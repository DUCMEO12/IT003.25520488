#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

const int N = 1000000;
bool TranBoNhoQuickSort = false;

// QuickSort
int partition(vector<double>& a, int low, int high) {
    double pivot = a[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (a[j] <= pivot) {
            i++;
            double temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    double temp = a[i + 1];
    a[i + 1] = a[high];
    a[high] = temp;
    return i + 1;
}

void quickSortRecursive(vector<double>& a, int low, int high, int depth) {
    if (depth > 2000) {
        TranBoNhoQuickSort = true;
        return;
    }

    if (low < high && !TranBoNhoQuickSort) {
        int pi = partition(a, low, high);
        quickSortRecursive(a, low, pi - 1, depth + 1);
        quickSortRecursive(a, pi + 1, high, depth + 1);
    }
}

void quickSort(vector<double>& a, int low, int high) {
    TranBoNhoQuickSort = false;
    quickSortRecursive(a, low, high, 0);
}

// HeapSort
void heapify(vector<double>& a, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && a[l] > a[largest])
        largest = l;

    if (r < n && a[r] > a[largest])
        largest = r;

    if (largest != i) {
        double temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;
        heapify(a, n, largest);
    }
}

void heapSort(vector<double>& a) {
    int n = a.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    for (int i = n - 1; i > 0; i--) {
        double temp = a[0];
        a[0] = a[i];
        a[i] = temp;
        heapify(a, i, 0);
    }
}

// MergeSort
void merge(vector<double>& a, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<double> L(n1);
    vector<double> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = a[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            a[k] = L[i];
            i++;
        } else {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<double>& a, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(a, left, mid);
    mergeSort(a, mid + 1, right);
    merge(a, left, mid, right);
}

int main() {
    vector<vector<double>> dsDayDuLieu(10, vector<double>(N));

    for (int i = 0; i < N; i++) {
        dsDayDuLieu[0][i] = i * 1.0;
    }

    for (int i = 0; i < N; i++) {
        dsDayDuLieu[1][i] = (N - i) * 1.0;
    }

    srand(time(0));
    for (int d = 2; d < 10; d++) {
        for (int i = 0; i < N; i++) {
            dsDayDuLieu[d][i] = (rand() % 2000000) - 1000000;
        }
    }

    cout << "Bat dau chay thu nghiem cac thuat toan:\n" << endl;

    for (int d = 0; d < 10; d++) {
        cout << "Dang chay cho Day " << d + 1 << ":" << endl;

        // QuickSort

        {
            vector<double> DayTam = dsDayDuLieu[d];
            clock_t ThoiGianBatDau = clock();
            quickSort(DayTam, 0, N - 1);
            clock_t ThoiGianKetThuc = clock();
            double ThoiGianChay = (double)(ThoiGianKetThuc - ThoiGianBatDau) / CLOCKS_PER_SEC;

            if (TranBoNhoQuickSort) {
                cout << "  - QuickSort time: Chay khong duoc (Tran bo nho do day da co thu tu)" << endl;
            } else {
                cout << "  - QuickSort time: " << ThoiGianChay * 1000 << " ms" << endl;
            }
        }

        // HeapSort
        {
            vector<double> DayTam = dsDayDuLieu[d];
            clock_t ThoiGianBatDau = clock();
            heapSort(DayTam);
            clock_t ThoiGianKetThuc = clock();
            double ThoiGianChay = (double)(ThoiGianKetThuc - ThoiGianBatDau) / CLOCKS_PER_SEC;
            cout << "  - HeapSort time:  " << ThoiGianChay * 1000 << " ms" << endl;
        }

        // MergeSort
        {
            vector<double> DayTam = dsDayDuLieu[d];
            clock_t ThoiGianBatDau = clock();
            mergeSort(DayTam, 0, N - 1);
            clock_t ThoiGianKetThuc = clock();
            double ThoiGianChay = (double)(ThoiGianKetThuc - ThoiGianBatDau) / CLOCKS_PER_SEC;
            cout << "  - MergeSort time: " << ThoiGianChay * 1000 << " ms" << endl;
        }

        // Ham sort cua C++
        {
            vector<double> DayTam = dsDayDuLieu[d];
            clock_t ThoiGianBatDau = clock();
            sort(DayTam.begin(), DayTam.end());
            clock_t ThoiGianKetThuc = clock();
            double ThoiGianChay = (double)(ThoiGianKetThuc - ThoiGianBatDau) / CLOCKS_PER_SEC;
            cout << "  - C++ sort time:  " << ThoiGianChay * 1000 << " ms" << endl;
        }
        cout << "--------------------------------------------------------" << endl;
    }

    return 0;
}
