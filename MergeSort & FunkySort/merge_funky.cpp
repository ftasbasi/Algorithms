
// do not add extra libraries here


/*
    arr       : array to be sorted, in order to get points this array should contain be in sorted state before returning
    size      : size of arr
    ascending : true for ascending, false for descending 
    
    you can use ceil function from cmath
    
*/


void Merge(int*& arr,int l,int m,int r,bool ascending,int &cntr) {

    int p1, r1, s1;
    int n1, n2;
    n1 = m - l + 1;
    n2 = r - m;

    int left_vect[n1];
    int right_vect[n2];

    for (int i = 0; i < n1; i++) {
        left_vect[i] = arr[l + i];
    }

    for (int j = 0; j < n2; j++) {
        right_vect[j] = arr[m + 1 + j];
    }

    p1 = 0; //index of 1st subarray
    r1 = 0; //index of 2nd subarray
    s1 = l;
    if (ascending) {
        while (p1 < n1 && r1 < n2) {

            if (left_vect[p1] <= right_vect[r1]) {
                arr[s1] = left_vect[p1];
                p1++;
            } else {
                arr[s1] = right_vect[r1];
                r1++;
            }
            cntr++;
            s1++;
        }
    } else {
        while (p1 < n1 && r1 < n2) {

            if (left_vect[p1] > right_vect[r1]) {
                arr[s1] = left_vect[p1];
                p1++;
            } else {
                arr[s1] = right_vect[r1];
                r1++;
            }
            cntr++;
            s1++;
        }
    }
    while (p1 < n1) {
        arr[s1] = left_vect[p1];
        p1++;
        s1++;
    }


    while (r1 < n2) {
        arr[s1] = right_vect[r1];
        r1++;
        s1++;
    }


}
int mrgSort (int*& arr,int left,int right, bool ascending,int &cntr)
{

    if (left<right)
    {
        int mid;
        mid = floor(left+right)/2;
        mrgSort(arr,left,mid,ascending,cntr);
        mrgSort(arr,mid+1,right,ascending,cntr);
        Merge(arr,left,mid,right,ascending,cntr);
    }


    return -1;
}
int MergeSort (int*& arr, int size, bool ascending)
{
    int counter=0;
    mrgSort(arr,0,size-1,ascending,counter);

    return counter;

}
int FunkySort (int*& arr, int size, bool ascending)
{   int result=0;
    if(size==1){
        return result;
    }

    if (ascending){
        if (arr[0]>arr[size-1]){
            int tmp=arr[0];
            arr[0]=arr[size-1];
            arr[size-1]=tmp;
        }
    }
    else
    {
        if (arr[0]<arr[size-1]){
            int tmp=arr[0];
            arr[0]=arr[size-1];
            arr[size-1]=tmp;

        }
    }
    result++;
    if(size==2){
        return result;
    }else if(size>2){
        int part_to_sort=ceil(double (size)*2/3);

        result+=FunkySort(arr,part_to_sort,ascending);

        int *tmpPtr;
        tmpPtr=arr+size-part_to_sort;
        result+=FunkySort(tmpPtr,part_to_sort,ascending);


        result+=FunkySort(arr,part_to_sort,ascending);
        return result;
    }
    return result;

}