#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define RD_MIN 0
#define RD_MAX 10000
#define SWPOINT 10
#define or ||
#define and &&

void insertionsort(int *vet, int n);
void selectionsort(int *vet, int n);
void bubblesort(int *vet, int n);
void quicksort(int *vet, int b, int e);
void mergesort(int *vet, int n);
void bucketsort(int *vet, int n, int m);
void shellsort(int *vet, int n);
void testall(int n);
void print_array(int *vet, int n);
void randomize_array(int *vet, int n);
void ascending_array(int *vet, int n);
void descending_array(int *vet, int n);
void recursive_bubblesort(int *vet, int n);
void recursive_selectionsort(int *vet, int b, int e);
void recursive_insertionsort(int *vet, int b, int e);
void modified_quicksort(int *vet, int b, int e, int scanf);
int* selectionsort_indirect(int *vet, int n);

int main(){
    int n;
    char c;
    srand(time(NULL));
    while(true){
        printf("Digite a quantidade de elementos: ");
        scanf("%d", &n);
        getchar();
        testall(n);
        printf("Repetir? [Y/N]: ");
        c = getchar();
        if(c == 'Y' or c == 'y') continue;
        else break;
    }
    return 0;
}

//Function used to test all the implemented 
//sorting algorithms, uncoment to test with
//array in descending, ascending or random.

void testall(int n){
    int i;
    int *vet = malloc(n*sizeof(int));
    time_t ti, tf;

    randomize_array(vet, n);
    //ascending_array(vet, n);
    //descending_array(vet, n);
    ti = time(NULL);
    bubblesort(vet, n);
    tf = time(NULL);
    //print_array(vet, n);
    printf("Tempo de execução (BubbleSort): %.3lf\n", difftime(tf,ti));

    randomize_array(vet, n);
    //ascending_array(vet, n);
    //descending_array(vet, n);
    ti = time(NULL);
    insertionsort(vet, n);
    tf = time(NULL);
    //print_array(vet, n);
    printf("Tempo de execução (InsertionSort): %.3lf\n", difftime(tf,ti));

    randomize_array(vet, n);
    //ascending_array(vet, n);
    //descending_array(vet, n);
    ti = time(NULL);
    selectionsort(vet, n);
    tf = time(NULL);
    //print_array(vet, n);
    printf("Tempo de execução (SelectionSort): %.3lf\n", difftime(tf,ti));

    randomize_array(vet, n);
    //ascending_array(vet, n);
    //descending_array(vet, n);
    ti = time(NULL);
    quicksort(vet, 0, n-1);
    tf = time(NULL);
    //print_array(vet, n);
    printf("Tempo de execução (QuickSort): %.3lf\n", difftime(tf,ti));

    randomize_array(vet, n);
    //ascending_array(vet, n);
    descending_array(vet, n);
    ti = time(NULL);
    mergesort(vet, n);
    tf = time(NULL);
    //print_array(vet, n);
    printf("Tempo de execução (MergeSort): %.3lf\n", difftime(tf,ti));

    randomize_array(vet, n);
    //ascending_array(vet, n);
    //descending_array(vet, n);
    ti = time(NULL);
    bucketsort(vet, n, RD_MAX);
    tf = time(NULL);
    //print_array(vet, n);
    printf("Tempo de execução (BucketSort): %.3lf\n", difftime(tf,ti));

    randomize_array(vet, n);
    //ascending_array(vet, n);
    //descending_array(vet, n);
    ti = time(NULL);
    shellsort(vet, n);
    tf = time(NULL);
    //print_array(vet, n);
    printf("Tempo de execução (ShellSort): %.3lf\n", difftime(tf,ti));


    randomize_array(vet, n);
    //ascending_array(vet, n);
    //descending_array(vet, n);
    ti = time(NULL);
    recursive_bubblesort(vet, n);
    tf = time(NULL);
    //print_array(vet, n);
    printf("Tempo de execução (Recursive BubbleSort): %.3lf\n", difftime(tf,ti));

    randomize_array(vet, n);
    //ascending_array(vet, n);
    //descending_array(vet, n);
    ti = time(NULL);
    recursive_selectionsort(vet, 0, n);
    tf = time(NULL);
    //print_array(vet, n);
    printf("Tempo de execução (Recursive SelectionSort): %.3lf\n", difftime(tf,ti));

    randomize_array(vet, n);
    //ascending_array(vet, n);
    //descending_array(vet, n);
    ti = time(NULL);
    recursive_insertionsort(vet, 1, n);
    tf = time(NULL);
    //print_array(vet, n);
    printf("Tempo de execução (Recursive InsertionSort): %.3lf\n", difftime(tf,ti));

    randomize_array(vet, n);
    //ascending_array(vet, n);
    //descending_array(vet, n);
    ti = time(NULL);
    modified_quicksort(vet, 0, n, SWPOINT);
    tf = time(NULL);
    //print_array(vet, n);
    printf("Tempo de execução (Modified Quicksort): %.3lf\n", difftime(tf,ti));

    randomize_array(vet, n);
    //ascending_array(vet, n);
    //descending_array(vet, n);
    ti = time(NULL);
    int *arr = selectionsort_indirect(vet, n);
    tf = time(NULL);
    //print_array(arr, n);
    printf("Tempo de execução (Inderect Selectionn sort): %.3lf\n", difftime(tf,ti));

    free(vet);
    free(arr);
    return;
}

//Function used to randomize the values of an array.

void randomize_array(int *vet, int n){
    int i;
    for(i=0; i<n; ++i){
        vet[i] = (rand()%(RD_MAX-RD_MIN))+RD_MIN;
    }
    return;
}

//Function used to organize the values of an array
//in ascending order.

void ascending_array(int *vet, int n){
    int i;
    randomize_array(vet, n);
    quicksort(vet, 0, n-1);
    return;
}

//Function used to organize the values of an array
//in descending order.

void descending_array(int *vet, int n){
    int i;
    ascending_array(vet, n);
    for(i=0; i<n/2; ++i){
        vet[i] ^= vet[n-1-i];
        vet[n-1-i] ^= vet[i];
        vet[i] ^= vet[n-1-i];
    }
    return;
}

//Function used to print an array.

void print_array(int *vet, int n){
    int i;
    printf("[");
    for(i=0; i<n; ++i){
        printf(" %d", vet[i]);
    }
    printf(" ]\n");
    return;
}

//Implementation of Insertion sort.

void insertionsort(int *vet, int n){
    int i, j, aux;
    for(i=1; i<n; ++i){
        aux = vet[i];
        for(j=i-1; j>=0 and vet[j]>aux; --j){
            vet[j+1] = vet[j];
        }
        vet[j+1] = aux;
    }
    return;
}

//Implementation of Selection sort.

void selectionsort(int *vet, int n){
    int i, j, m;
    for(i=0; i<n-1; ++i){
        m = i;
        for(j=i+1; j<n; ++j){
            if(vet[j] < vet[m]){
                m = j;
            }
        }
        if(i != m){
            vet[i] ^= vet[m];
            vet[m] ^= vet[i];
            vet[i] ^= vet[m];
        }
    }
    return;
}

//Implementation of Bubble sort.

void bubblesort(int *vet, int n){
    int i, j;
    bool t;
    for(i=n-1; i>0; i--){
        t = false;
        for(j=0; j<i; ++j){
            if(vet[j] > vet[j+1]){
                vet[j] ^= vet[j+1];
                vet[j+1] ^= vet[j];
                vet[j] ^= vet[j+1];
                t = true;
            }
        }
        if(!t) break;
    }
    return;
}

//Implementation of Quick sort.

void quicksort(int *vet, int b, int e){
    int i, j, p;
    p = vet[b];
    i = b+1;
    j = e;

    while(i <= j){
        if(vet[i] <= p) ++i;
        else if(vet[j] > p) --j;
        else{
            vet[i] ^= vet[j];
            vet[j] ^= vet[i];
            vet[i] ^= vet[j];
            i++; j--;
        }
    }

    vet[b] = vet[j];
    vet[j] = p;
    if(j-1 > b) quicksort(vet,b,j-1);
    if(j+1 < e) quicksort(vet,j+1,e);
    
    return;
}

//Implementation of Merge sort.

void mergesort(int *vet, int n){
    if(n==1) return;
    
    int m, i, j, k;
    m = n/2;
    int v1[m], v2[n-m];

    for(i=0; i<m; ++i) v1[i] = vet[i];
    for(j=m; j<n; ++j) v2[j-m] = vet[j];

    mergesort(v1,m);
    mergesort(v2,n-m);

    i = j = 0;
    for(k=0; k<n; ++k){
        if(i>=m) vet[k] = v2[j++];
        else if(j>=n-m) vet[k] = v1[i++];
        else if(v1[i] > v2[j]) vet[k] = v1[i++];
        else vet[k] = v2[j++];
    }

    return;
}

//Implementation of Bucket sort.

void bucketsort(int *vet, int n, int m){
    int i, j;
    int *aux = (int *) calloc(m,sizeof(int));

    for(i=0; i<n; ++i){
        aux[vet[i]]++;
    }

    for(i=j=0; i<m; ++i){
        while(aux[i]--){
            vet[j++] = i;
        }
    }

    free(aux);
    return;
}

//Implementation of Shell sort.

void shellsort(int *vet, int n){
    int i, g, j, m;
    
    for(g=n/2; g>0; g /= 2){
        for(i=g; i<n; ++i){
            m = vet[i];
            for(j=i; j>=g and vet[j-g] > m; j-=g){
                vet[j] = vet[j-g];
            }
            vet[j] = m;
        }
    }
    return;
}

//Implementation of a recursive Bubble sort.

void recursive_bubblesort(int *vet, int n){
    int i;
    bool t = false;

    for(i=0; i<n-1; ++i){
        if(vet[i] > vet[i+1]){
            vet[i] ^= vet[i+1];
            vet[i+1] ^= vet[i];
            vet[i] ^= vet[i+1];
            t = true;
        }
    }
    
    if(t) recursive_bubblesort(vet, n-1);
    return;
}

//Implementation of a recursive Selection sort.

void recursive_selectionsort(int *vet, int b, int e){
    int i, m;
    if(b == e) return;
    else{
        m = b;
        for(i=b; i<e; ++i){
            if(vet[i] < vet[m]){
                m = i;
            }
        }
        if(m != b){
            vet[b] ^= vet[m];
            vet[m] ^= vet[b];
            vet[b] ^= vet[m];
        }
        recursive_selectionsort(vet, b+1, e);
    }
}

//Implementation of a recursive Insertion sort.

void recursive_insertionsort(int *vet, int b, int e){
    int i, aux;
    if(b == e) return;
    aux = vet[b];
    for(i=b-1; i>=0 and vet[i]>aux; --i){
        vet[i+1] = vet[i];
    }
    vet[i+1] = aux;
    recursive_insertionsort(vet,b+1,e);
}

//Implementation of a hybrid quicksort-insertionsort.

void modified_quicksort(int *vet, int b, int e, int s){
    if(e-b <= s){
        int i, j, aux;
        for(i=b+1; i<=e; ++i){
            aux = vet[i];
            for(j=i-1; j>=0 and vet[j]>aux; --j){
                vet[j+1] = vet[j];
            }
            vet[j+1] = aux;
        }
        return;
    }
    else{
        int i, j, p;
        p = vet[b];
        i = b+1;
        j = e;
    
        while(i <= j){
            if(vet[i] <= p) ++i;
            else if(vet[j] > p) --j;
            else{
                vet[i] ^= vet[j];
                vet[j] ^= vet[i];
                vet[i] ^= vet[j];
                i++; j--;
            }
        }
    
        vet[b] = vet[j];
        vet[j] = p;
        quicksort(vet,b,j-1);
        quicksort(vet,j+1,e);
    }
}

//Implementation of indirect Selection sort.

int* selectionsort_indirect(int *vet, int n){
    int i, j, m;
    int *aux = (int *) malloc(n*sizeof(int));
    for(i=0; i<n; ++i) aux[i] = i;

    for(i=0; i<n-1; ++i){
        m = i;
        for(j=i+1; j<n; ++j){
            if(vet[aux[j]] < vet[aux[m]]){
                m = j;
            }
        }
        if(i != m){
            aux[i] ^= aux[m];
            aux[m] ^= aux[i];
            aux[i] ^= aux[m];
        }
        
    }
    return aux;
}
