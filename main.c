#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//Author: Ethan Holland

typedef struct coordinate
{
    int x;
    int y;
    double distance;

}coordinate;
void insertionSortModified(coordinate** coordsList, int l, int r);
void mergeInsertionSort(coordinate** coordsList, int l, int r, int t);
void merge(coordinate** coordsList, int l, int m, int r);
coordinate** readData(int n);
void wrapper(coordinate** coordsList, int n, int t);
int compareTo(coordinate* ptrPt1, coordinate* ptrPt2, coordinate* myStore);
double calcDistance(coordinate* ptPtr, coordinate* myStore);
coordinate* myStore; 
int binarySearch(coordinate** searchList, coordinate item, int len);




int main(void)
{
    int n, s, t;
    myStore = malloc(sizeof(coordinate));
    scanf("%d %d %d %d %d", &myStore->x, &myStore->y, &n, &s, &t);
    coordinate** coordsList = readData(n);
    coordinate** searchList = malloc(s * sizeof(coordinate*));
    for (int i = 0; i < s; i++)
    {
        searchList[i] = malloc(sizeof(coordinate));
        scanf("%d %d", &searchList[i]->x, &searchList[i]->y);
    }
    wrapper(coordsList, n, t);
    for (int i = 0; i < n; i++)
    {
        printf("%d %d\n", coordsList[i]->x, coordsList[i]->y);
    }
    for (int i=0; i<s; i++)
    {
        int search = binarySearch(coordsList, *searchList[i], n);
        if (search==-1)
        {
            printf("%d %d not found\n", searchList[i]->x, searchList[i]->y);
        }
        else
        {
            printf("%d %d found at rank %d\n", searchList[i]->x, searchList[i]->y, search + 1);
        }
    }

    for (int i = 0; i < n; i ++)
        free(coordsList[i]);
    for (int i = 0; i < s; i ++)
        free(searchList[i]);
    free(coordsList);
    free(searchList);
    free(myStore);
    return 0;





}






coordinate** readData(int n)
{
    //x and y are our location, n is the number of neighboring buildings, s is the number of points
    //to search for, and t is the threshold to be used for determining if we run merge or
    //insertion sort.


    coordinate** coordsList = malloc(n * sizeof(coordinate*));
    for (int i = 0; i < n; i++)
    {
        coordsList[i] = malloc(sizeof(coordinate));
        scanf("%d %d", &coordsList[i]->x, &coordsList[i]->y);
        coordsList[i]->distance = calcDistance(coordsList[i], myStore);
    }
    return coordsList;

}
void insertionSortModified(coordinate** coordsList, int l, int r)
{
    int j;
    for (int i = l+1; i <= r; i++)
    {
        coordinate* hand = coordsList[i];
        for (j = i-1; j >= l; j--)
        {
            if (compareTo(coordsList[j], hand, myStore) > 0)
                coordsList[j+1] = coordsList[j];
            else 
                break;

        }
       
        coordsList[j+1] = hand;

    }
}
void mergeInsertionSort(coordinate** coordsList, int l, int r, int t)
{
    int size = r - l + 1;
    //calc size using r-l+1
    //if size <= threshold (t), then call insertion
    //otherwise (else statement) do merge sort normally
    if (size <= t)
    {
        insertionSortModified(coordsList, l, r);
    }
    else
        if (l < r)
        {
            //get the mid point
            int m = (l+r)/2;

            //sort first and second halves
            mergeInsertionSort(coordsList, l, m, t);
            mergeInsertionSort(coordsList, m+1, r, t);
            merge(coordsList, l , m , r);

        }
}

void merge(coordinate** coordsList, int l, int m, int r)
{
    int k;
    int n1 = m - l + 1;
    int n2 = r-m;

    //create temp arrays:
    coordinate** L =  malloc(n1*sizeof(coordinate*));
    coordinate** R =  malloc(n2*sizeof(coordinate*));

    //Next, copy data to temp arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = coordsList[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = coordsList[m + 1 + j];
    //merge the temp arrays back into arr[l..r]
    int i = 0; //Initial index of the first subarray
    int j = 0; //Initial index of the second subarray
    k = l; //Initial value of the merged subarray
    while (i < n1 && j < n2)
    {
        if(compareTo(L[i], R[j], myStore) <= 0)
        {
            coordsList[k] = L[i];
            i++;
        }
        else
        {
            coordsList[k] = R[j];
            j++;

        }
        k++;
    }
    //copy the remaining elements of L, if there are any
    while (i < n1)
    {
        coordsList[k] = L[i];
        i++;
        k++;
    }
    //copy the remaining elements of R if there are any
    while (j < n2)
    {
        coordsList[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
    //L is for left index and R is the right index of the subarray to be sorted

}

int compareTo(coordinate* ptrPt1, coordinate* ptrPt2, coordinate* myStore)
{
    if (calcDistance(ptrPt1, myStore) < calcDistance(ptrPt2, myStore))
    {
        return -1;

    }
    else if(calcDistance(ptrPt1, myStore) > calcDistance(ptrPt2, myStore))
    {
        return 1;
    }

    else if (calcDistance(ptrPt1, myStore) == calcDistance(ptrPt2, myStore))
        {
            if (ptrPt1->x < ptrPt2->x)
                return -1;
            else if(ptrPt1->x > ptrPt2->x)
                return 1;
            else
            {
                if (ptrPt1->y < ptrPt2->y)
                    return -1;
                else if (ptrPt1->y > ptrPt2->y)
                    return 1;
                else
                    return 0;
            }
        }


}

double calcDistance(coordinate* ptPtr, coordinate* myStore)
{
    double distance = sqrt((ptPtr->x - myStore->x)*(ptPtr->x - myStore->x) + (ptPtr->y - myStore->y)*(ptPtr->y - myStore->y));
    return distance;

}

int binarySearch(coordinate** searchList, coordinate item, int len)
{
    int l = 0, h = len - 1;
    int mid;

    while (l <= h)
    {
        mid = (l + h) / 2;
        // Check if item is present at mid
        if (compareTo(searchList[mid], &item, myStore) == 0)
            return mid;
        // If item greater, ignore left half
        if (compareTo(searchList[mid], &item, myStore) < 0)
            l = mid + 1;

        // If item is smaller, ignore right half
        else
            h = mid - 1;
    }

    // if we reach here, then element was
    // not present
    return -1;
}

void wrapper(coordinate** coordsList, int n, int t)
{
    mergeInsertionSort(coordsList, 0, n - 1, t);
}
