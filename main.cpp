/*- [ ]  **4.1 Слияние массивов.** Напишите программу, которая использует кучу для слияния K отсортированных массивов суммарной длиной N.

**Требования:** время работы O(N * logK). Ограничение на размер кучи O(K).

Формат входных данных: Сначала вводится количество массивов K. Затем по очереди размер каждого массива и элементы массива. Каждый массив упорядочен по возрастанию.

Формат выходных данных: Итоговый отсортированный массив.*/

#include <iostream>
#include <cmath>

template <typename T>
 struct Array
{
     Array(int s = 0)
         : size(s), currentPos(0)
     {
         arr = new T[size];
     }

    ~Array(){
        delete[]arr;
    }
    T getElement() {
        currentPos++;
        return arr[currentPos-1];
    }
    bool isEmpty() {
        return currentPos == size;
    }

    T* arr;
    int size, currentPos;
};

 template <typename T>
 bool defaultLess(const T& l, const T& r)
 {
     return l < r;
 }

 template<typename T>
struct ArrayComparator
{
    bool operator()(const Array<T>* left, const Array<T>* rigth)
    {
        return left->arr[left->currentPos] < rigth->arr[rigth->currentPos];
    }
};

template <class T = int, class Comparator = std::less<T>>
class Heap 
{
public:
    Heap(int s = 2)
        : cmp(), size(s), currentPos(0)
    {
        arr = new T[size];
    }

    ~Heap() {
        delete[] arr;
    }

    void push(const T element) {

        if (currentPos >= size) {
            T* arr2 = new T[size * 2];

            for (int i = 0; i < currentPos; ++i)
            {
                arr2[i] = arr[i];
            }

            delete[] arr;
            arr = arr2;
            size = size * 2;
        }
        if (element->size > 0) {
            arr[currentPos] = element;
        siftUp(currentPos);
        currentPos++;
        }
    }


    T pop() {
        T root = arr[0];
        arr[0] = arr[currentPos - 1];
        currentPos--;
        siftDown(0);
        return root;
    }

private:

    void siftUp(int idx) {

        int parent = (idx - 1) / 2;

        while (idx > 0 && cmp(arr[idx], arr[parent])) {
            if (arr[idx]->size > 0 && arr[parent]->size > 0) {
            std::swap(arr[idx], arr[parent]);
            }
            idx = parent;
            parent = (idx - 1) / 2;
        }
    }


    void siftDown(int idx) {
        while (2 * idx + 1 < currentPos) {
            int j = 2 * idx + 1;
            if ((2*idx+2<currentPos) && (cmp(arr[idx*2+2], arr[idx*2+1])))
                j++;
            if ((cmp(arr[idx], arr[j])) or (arr[idx]==arr[j]))
                break;
            std::swap(arr[idx], arr[j]);
                idx=j;
        }
    }
    Comparator cmp;
    T* arr;
    int currentPos;
    int size;

};

template<typename T>
std::istream& operator>>(std::istream& in, Array<T>* Array)
{
    in >> Array->size;
    delete[]Array->arr;
    Array->arr = new T[Array->size];

    for (int i = 0; i < Array->size; ++i) {
        in >> Array->arr[i];
    }

    return in;
}

void run(std::istream& input, std::ostream& output)
{
    int n, len, s = 0, element;
    input >> n;
    Array<int>** arr = new Array<int>*[n];

    for (int i = 0; i < n; ++i)
    {
        arr[i] = new Array<int>;
        input >> arr[i];
        s += arr[i]->size;
    }


    int* result_array = new int[s];
    Heap<Array<int>*, ArrayComparator<int>> MyHeap;
    Array<int>* temp;

    for (int i = 0; i < n; ++i)
    {
        MyHeap.push(arr[i]);
    }

    for (int i = 0; i < s; ++i)
    {
        temp = MyHeap.pop();
        output << temp->getElement() << " "; 

        if (!temp->isEmpty())
        {
            MyHeap.push(temp);
        }
    }

    delete[] arr;
}


int main() {

    run(std::cin, std::cout);
    return 0;
}
