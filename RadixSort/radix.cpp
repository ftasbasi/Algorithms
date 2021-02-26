
// do not add extra libraries here


/*
    arr       : array to be sorted, in order to get points this array should contain be in sorted state before returning
    size      : size of arr
    ascending : true for ascending, false for descending

    you can use ceil function from cmath

*/
int countSort(long arr[],bool ascending, int n, int exp,int base)
{
    int counter=0;
    long output[n]; // output array
    long i;
    long countBase=long (pow(10,base));
    long *count=new long[countBase];
    *count={0};

    if (n==0){ return 0;}
    if(ascending){
        for (i = 0; i < n; i++){
            count[(arr[i] / exp) % countBase]++;
            counter++;
        }

        for (i = 1; i < countBase; i++){
            count[i] += count[i - 1];
            counter++;
        }

        for (i = n - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % countBase] - 1] = arr[i];
            count[(arr[i] / exp) % countBase]--;
            counter++;
        }

        for (i = 0; i < n; i++){
            arr[i] = output[i];
            counter++;

        }

    }
    else
    {

        for (i = 0; i < n; i++){
            count[(arr[i] / exp) % countBase]++;
            counter++;
        }

        // Change count[i] so that count[i] now contains actual
        //  position of this digit in output[]
        for (i = countBase-2; i >= 0; i--){
            count[i] += count[i + 1];
            counter++;
        }

        // Build the output array
        for (i = n - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % countBase] - 1] = arr[i];
            count[(arr[i] / exp) % countBase]--;
            counter++;
        }

        // Copy the output array to arr[], so that arr[] now
        // contains sorted numbers according to current digit
        for (i = 0; i < n; i++){
            arr[i] = output[i];
            counter++;

        }
    }

    return counter;

}

// The main function to that sorts arr[] of size n using
// Radix Sort
int radixsort(long arr[],bool ascending, int n,int base)
{
    int result=0;
    // Find the maximum number to know number of digits
    long m = pow(10,11);

    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (long exp = 1; m / exp > 0; exp *= pow(10,base)){

        result+=countSort(arr,ascending, n, exp,base);
    }
    return result;
}
int RadixSort(long arr[], bool ascending, int n, int l ){
    return radixsort(arr,ascending,n,l);

}