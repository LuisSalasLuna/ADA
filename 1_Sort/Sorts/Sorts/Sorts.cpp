#include <iostream>
#include <time.h>
#include <vector>

//#include <algorithm>

using namespace std;

long long* GenerarArr(int tam, int dig) {
    srand(time(NULL));
    long long * Arr = new long long[tam];
    for (int i = 0; i < tam; i++) {
        long long val = 0;
        long long mult = 1;
        for (int j = 0; j < dig; j++, mult*=10) {
            val += (rand() % 10)*mult;
        }
        while (val - mult/10 < 0)
            val += (rand() % 10)*mult/10;
        Arr[i] = val;
    }
    return Arr;
}
long long* CopyArr(long long* Origen, int tam) {
    long long* Arr = new long long[tam];
    for (int i = 0; i < tam; i++) {
        Arr[i] = Origen[i];
    }
    return Arr;
}
void Print(long long* Arr, int n) {
    for (int i = 0; i < n; i += 1)
        cout << Arr[i] << " ";
    cout << endl;
}

int particion(long long* Arr, int inicio, int fin) {
    int follower = inicio;                       // c
    int leader = inicio;                         // c
    while (leader < fin) {                       //  n-1
        if (Arr[leader] <= Arr[fin]) {           //    c
            swap(Arr[follower], Arr[leader]);    //    c
            follower += 1;                       //    c
        }
        leader += 1;                             //    c
    }
    swap(Arr[follower], Arr[fin]);               // c
    return follower;
}
void q_sort(long long* Arr, int inicio, int fin) {
    if (inicio >= fin)                          // c
        return;
    int p = particion(Arr, inicio, fin);        // n
    q_sort(Arr, inicio, p - 1);                 // T(n/2)
    q_sort(Arr, p + 1, fin);                    // T(n/2)
}
void Quicksort(long long* Arr, int fin) {
    q_sort(Arr, 0, fin);         //
}

void heap_aux(long long* Arr, int n, int i)
{
    int largest = i;                       // c
    int l = 2 * i + 1;                     // c
    int r = 2 * i + 2;                     // c
    if (l < n && Arr[l] > Arr[largest])    //|> c
        largest = l;                       //|
    if (r < n && Arr[r] > Arr[largest])    //|> c
        largest = r;                       //|
    if (largest != i) {                    //\ /
        swap(Arr[i], Arr[largest]);        // > En el peor caso se entra al if:
        heap_aux(Arr, n, largest);         //|       T(n,i) = T(n,2i+1) + c + c
    }                                      ///
}
 // En el mejor de los casos, el Arr[i] es el mayor del array y nunca entra en un if: c
 // En el peor de los casos siempre entra en almenos uno de los 2 if, por consiguiente entraria en el 3er if tambien
 // haciendo un total de T(n,i) = c + c + T(n,2i+1)
void Heapsort(long long* Arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)  //  > (n/2-1)
        heap_aux(Arr, n, i);              // /  T(n,i)

    for (int i = n - 1; i >= 0; i--) {    // n-1
        swap(Arr[0], Arr[i]);             // > c  
        heap_aux(Arr, i, 0);              //| T(i,0)
    }                                     ///
}
// El mejor de los casos seria con array ordenado descendentemente, ya que el mayor elemento siempre estara al inicio, las comparaciones dentro del
// heap_aux no modificarian al array Tomando un T(n) = n/2-1 + n-1 = 3n/2 -2
// El peor de los casos sria un array ordenado ascendentemente, ya que tendria que buscar en el heap el elemento mayor que se encontraria al final, 
// por consiguiente entraria en el 3er if tambien
// haciendo un total de T(n) = T(n)

void ShellSort(long long arr[], int n){  //O(n^2)                                      //   log2n
    for (int gap = n/2; gap > 0; gap /= 2){                         //   4             2            1              log2n
        for (int i = gap; i < n; i += 1){                           // 4 5 6 7    2 3 4 5 6 7    1 2 3 4 5 6 7     n - log2n
            long long temp = arr[i];                                   // c
            int j;                                                  // c
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)  // 1 1 1 1    1 1 2 2 3 3    1 2 3 4 5 6 7     (n-log2n)/log2n                        
                arr[j] = arr[j - gap];                              //
            arr[j] = temp;                                          // c
        }
    }
}
 // Inicialmente se divide entre 2 el tamaño del array en cada iteracion por lo que el bucle dara log2n ciclos, donde n es el tamaño
 // En el segundo bucle se toma inicialmente a gap y se incrementa hasta llegar al tamaño por lo que lo hara (n -log2n) veces
 // Dentro del segundo for hay operaciones a las que daremos valor constante y un ultimo bucle, este bucle reduce j en base a saltos de tamaño log2n
 // y hara un maximo de (n-log2n)/log2n saltos por elemento

long long GetMax(long long array[], int size) {
    long long max = array[1];              //c
    for (int i = 2; i < size; i++) {   //n-1
        if (array[i] > max)             //   c  
            max = array[i];             //   c
    }
    return max;                         //c
}
void CountingSort(long long* array, int size) {
    vector<long long> output(size);               //  c
    long long max = GetMax(array, size);          //  n
    vector<long long> count(max+1);               //  c
    //long long* count = new long long[max+1];
    for (long long i = 0; i < count.size(); i++)     //  max
        count[i] = 0;                          //    c
    for (long long i = 0; i < size; i++)             //  n 
        count[array[i]]++;                     //    c
    for (long long i = 1; i < count.size(); i++)     //  max-1
        count[i] += count[i - 1];              //    c
    for (long long i = size-1; i >= 0; i--) {        //  n
        output[count[array[i]]-1] = array[i];  //    c
        count[array[i]] -= 1;                  //    c
    }
    for (long long i = 0; i < size; i++) {           //  n
        array[i] = output[i];                  //    c
    }
}

void Sort(vector<long long> &vec) {
    for (int i = 0; i < vec.size(); i++) {      // n
        long long actual = vec[i];                    //   c
        int j = i - 1;                          //   c
        while (j >= 0 && vec[j] > actual) {     //   n-1
            vec[j + 1] = vec[j];                //     c
            j--;                                //     c
        }                                          
        vec[j + 1] = actual;                    //  c
    }
}
void BucketSort(long  long* array, int size) {
    long long max = GetMax(array, size);                         // n
    long long place = 1;                                         // c
    while (max / place > 10)                                // log10max
        place *= 10;                                        //     c    
    vector<vector<long long>>  bucket(10);                       // c
    for (int i = 0; i < size; i++) {                        // n
        bucket[(int(array[i]/place))].push_back(array[i]);  // c
    }
    for (int i = 0; i < bucket.size(); i++) {               // 10
        Sort(bucket[i]);                                    //     c
    }
    int index = 0;                                          // c
    for (int i = 0; i < 10; i++) {                        // n
        while (!bucket[i].empty()) {                        //    bucket[i].size()
            array[index++] = *(bucket[i].begin());          //           c
            bucket[i].erase(bucket[i].begin());             //           c
        }
    }
}

void Merge(long long* A, int i, int m, int f) {
    int p = i;                         // c
    int q = m + 1;                     // c
    int k = 0;                         // c
    int tam = f - i + 1;               // c
    vector<long long> C(tam);             // c

    while (p <= m && q <= f) {         // \           //
        if (A[p] < A[q]) {             // |
            C[k] = A[p];               // |
            p++;                       //  > Peor caso: Todos en la segunda mitad:
        }                              // |             n/2
        else {                         // |
            C[k] = A[q];               // |
            q++;                       // |
        }                              // |
        k++;                           // /
    }
    while (q <= f) {                   // \           //
        C[k] = A[q];                   // |
        q++;                           //  > No hay elementos en la segunda mitad
        k++;                           // |              
    }                                  // /

    while (p <= m) {                   // \           //
        C[k] = A[p];                   // |
        p++;                           //  > Toma todos los elementos de la primera mitad:
        k++;                           // |              n/2
    }                                  // /

    for (p = 0; p < tam ;p++) {        // \           //
        A[i] = C[p];                   //  > reemplazar elementos en A por su forma ordenada,
        i= i+1;                        // |   costo ignorado:  c
    }                                  // /
}
void MergeSort(long long* A, int i, int f) {
    if (f > i) {
        int m = (i + f) / 2;           // c
        MergeSort(A, i, m);            // T(n/2)
        MergeSort(A, m + 1, f);        // T(n/2)
        Merge(A, i, m, f);             // n
    }
}
 // T(n) = 2T(n/2) + n + c

long getMax(long long array[], int n) {
    long long max = array[0];              // c
    for (int i = 1; i < n; i++)       // n-1
        if (array[i] > max)           //   c
            max = array[i];           //   c
    return max;
}
void CountingSortR(long long* array, int size, int place) {
    const int max = 10;                                          // c
    vector<long long> output(size);                                   // c
    vector<long long> count(max);                                     // c
    for (long long i = 0; i < max; ++i)                                //  10
        count[i] = 0;                                            //    c
    for (long long i = 0; i < size; i++)                               //  n
        count[(array[i]/place) % 10]++;                          //    c
    for (long long i = 1; i < max; i++)                                //  10
        count[i] += count[i - 1];                                //    c
    for (long long i = size - 1; i >= 0; i--) {                        //  n 
        output[count[(array[i] / place) % 10] - 1] = array[i];   //    c
        count[(array[i] / place) % 10]--;                        //    c
    }
    for (int i = 0; i < size; i++)                               //  n
        array[i] = output[i];                                    //    c
}
void RadixSort(long long array[], int size) {
    long long max = getMax(array, size);                        // n-1
    for (long long place = 1; max / place > 0; place *= 10)      // log10max
        CountingSortR(array, size, place);                 //    n           
}

void GnomeSort(long long arr[], int n){
    int indice = 0;
    while (indice < n) {
        if (indice == 0) { indice++; }
        if (arr[indice] >= arr[indice - 1]) {
            indice++;
        }
        else {
            swap(arr[indice], arr[indice - 1]);
            indice--;
        }
    }
}

int main()
{
    long long i = 0;
    cout << i;
    //long long max = 9855257608;
    //vector<long long> count(max + 1);
    //long long* count = new long long[max + 1];
    int n;
    cout << " Ingrese cantidad de datos: ";
    cin >> n;
    cout << endl;
    long long* Arr = GenerarArr(n, 5);
    long long* Arr2 = CopyArr(Arr, n);
    long long* Arr3 = CopyArr(Arr, n);
    long long* Arr4 = CopyArr(Arr, n);
    long long* Arr5 = CopyArr(Arr, n);
    long long* Arr6 = CopyArr(Arr, n);
    long long* Arr7 = CopyArr(Arr, n);
    long long* Arr8 = CopyArr(Arr, n);
    unsigned t0, t1;
    double time;

    //Medir Quicksort
    //Print(Arr, n);
    t0 = clock();
    Quicksort(Arr, n - 1);
    t1 = clock();
    //Print(Arr, n);
    time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << " Execution Time Quicksort: " << time << endl << endl;
    //-------------------

    //Medir Heapsort
    //Print(Arr2, n);
    t0 = clock();
    Heapsort(Arr2, n);
    t1 = clock();
    //Print(Arr2, n);
    time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << " Execution Time Heapsort: " << time << endl << endl;
    //-------------------

    //Medir ShellSort
    //Print(Arr3, n);
    t0 = clock();
    ShellSort(Arr3, n);
    t1 = clock();
    //Print(Arr3, n);
    time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << " Execution Time ShellSort: " << time << endl << endl;
    //-------------------

    //Medir CountingSort
    /*//Print(Arr4, n);
    t0 = clock();
    CountingSort(Arr4, n);
    t1 = clock();
    //Print(Arr4, n);
    time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << " Execution Time CountingSort: " << time << endl << endl;
    //-------------------*/

    //Medir BucketSort
    //Print(Arr5, n);
    t0 = clock();
    BucketSort(Arr5, n);
    t1 = clock();
    //Print(Arr5, n);
    time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << " Execution Time BucketSort: " << time << endl << endl;
    //-------------------

    //Medir MergeSort
    //Print(Arr6, n);
    t0 = clock();
    MergeSort(Arr6, 0, n-1);
    t1 = clock();
    //Print(Arr6, n);
    time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << " Execution Time MergeSort: " << time << endl << endl;
    //-------------------

    //Medir RadixSort
    //Print(Arr7, n);
    t0 = clock();
    RadixSort(Arr7, n);
    t1 = clock();
    //Print(Arr7, n);
    time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << " Execution Time RadixSort: " << time << endl << endl;
    //-------------------

    //Medir GnomeSort
    /*//Print(Arr8, n);
    t0 = clock();
    GnomeSort(Arr8, n);
    t1 = clock();
    //Print(Arr8, n);
    time = (double(t1 - t0) / CLOCKS_PER_SEC);
    cout << " Execution Time GnomeSort: " << time << endl << endl;
    //-------------------*/

}

//Suba en un archivo pdf una comparativa de tiempos dada una misma entrada
// de tamaño n = {10, 100, 1 000, 10 000, 100 000, 500 000, 1 000 000}, números 
//tipo double, número aleatórios pero el mismo conjunto para cada algoritmo. 