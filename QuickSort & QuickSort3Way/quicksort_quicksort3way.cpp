
// do not add extra libraries here


/*
    arr       : array to be sorted, in order to get points this array should contain be in sorted state before returning
    size      : size of arr
    ascending : true for ascending, false for descending

    you can use ceil function from cmath

*/
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
int partition(int*& arr, int low, int high,bool order,int &cntr)
{
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if(order){
            if (arr[j] < pivot)
            {
                i++;
                swap(&arr[i], &arr[j]);
            }
        } else{
            if (arr[j] > pivot)
            {
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
        cntr++;
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
void partition3(int*& a, int low, int high, int& i, int& j,bool order,int &cntr)
{
    if (high - low <= 1) {
        if (order){
            if (a[high] < a[low])
            {
                swap(&a[high], &a[low]);
            }

            cntr++;
        } else{
            if (a[high] > a[low])
            {

                swap(&a[high], &a[low]);
            }

            cntr++;
        }
        i = low;
        j = high;
        return;
    }
    int mid = low;
    int pivot = a[high]; // rightmost pivot
    if(order) {
        while (mid <= high) {
            if (a[mid] < pivot) {
                swap(&a[low++], &a[mid++]);
            }
            else if (a[mid] == pivot) {
                mid++;
            }
            else{
                swap(&a[mid], &a[high--]);
            }
            cntr++;
        }
    } else{
        while (mid <= high) {
            if (a[mid] > pivot) {
                swap(&a[low++], &a[mid++]);
            }
            else if (a[mid] == pivot) {
                mid++;
            }
            else{
                swap(&a[mid], &a[high--]);
            }
            cntr++;
        }
    }
    i = low - 1;
    j = mid;
}
void quickSort_1(int*& arr, int low, int high,bool order,int &cntr)
{
    if (low < high)
    {
        int partIndex = partition(arr, low, high,order,cntr);
        quickSort_1(arr, low, partIndex - 1,order,cntr);
        quickSort_1(arr, partIndex + 1, high,order,cntr);
    }
}
void quicksort3(int*& a, int low, int high,bool order,int &cntr)
{
    if (low >= high)
        return;

    int i, j;
    partition3(a, low, high, i, j,order,cntr);
    quicksort3(a, low, i,order,cntr);
    quicksort3(a, j, high,order,cntr);
}
int QuickSort(int*& arr, int size, bool ascending)
{
    int counter=0;
    quickSort_1(arr,0,size-1,ascending,counter);
    return counter;
}

int QuickSort3(int*& arr, int size, bool ascending)
{
    int counter=0;
    quicksort3(arr,0,size-1,ascending,counter);
    return counter;
}
