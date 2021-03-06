#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <map>

using namespace std;


template<typename T>
class MaxHeap {
    vector<T> heap;

    int getLeftChild(int parent) {
        return 2 * parent + 1;
    }

    int getRightChild(int parent) {
        return 2 * parent + 2;
    }

    int getParent(int child) {
        if (child % 2 == 0) {
            return child / 2 - 1;
        } else {
            return child / 2;
        }
    }

    void siftDown(int node) {
        int left = getLeftChild(node);
        int right = getRightChild(node);

        int biggest = [](const vector<pair<int, int> > &v) {
            return max_element(v.begin(), v.end())->second;
        }({
            {heap[node], node},
            {left < size() ? heap[left]: INT_MIN, left},
            {right < size() ? heap[right]: INT_MIN, right}
        });

        if (biggest != node) {
            swap(heap[node], heap[biggest]);
            siftDown(biggest);
        }
    }

    void siftUp(int node) {
        int parent = getParent(node);

        if (node && heap[parent] < heap[node]) {
            swap(heap[node], heap[parent]);
            siftUp(parent);
        }
    }
public:
    MaxHeap() {}

    MaxHeap(vector<T> input) {
        heap = input;
        for (int i = heap.size() / 2; i >= 0; --i)
            siftDown(i);
    }

    unsigned int size() {
        return heap.size();
    }

    bool empty() {
        return size() == 0;
    }

    void push(T value) {
        heap.push_back(value);
        siftUp(size() - 1);
    }

    void pop() {
        try {
            if (empty()) {
                throw out_of_range("Bad index");
            }

            heap[0] = heap.back();
            heap.pop_back();
            siftDown(0);
        } catch (const out_of_range& e) {
            cout << e.what() << endl;
            throw;
        }
    }

    int top() {
        try {
            if (empty()) {
                throw out_of_range("Bad index");
            }
            return heap[0];
        } catch (const out_of_range& e) {
            cout << e.what() << endl;
            throw;
        }
    }

    void print() {
        for (size_t i = 0; i < size(); ++i) {
            cout << heap[i] << ' ';
        }
        cout << endl;
    }
};


int main() {
    vector<int> input{6, 3, 2, 4, 1, 5};

    MaxHeap<int> h{input};

    h.print();

    for (int i = 0; i < input.size(); ++i) {
        cout << h.top() << endl;
        h.pop();
    }

    return 0;
}
