#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>

class MaxHeap {
private:
    std::vector<int> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] > heap[parent]) {
                std::swap(heap[index], heap[parent]);
                index = parent;
            }
            else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int size = heap.size();
        while (index < size) {
            int largest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            if (left < size && heap[left] > heap[largest]) {
                largest = left;
            }
            if (right < size && heap[right] > heap[largest]) {
                largest = right;
            }

            if (largest != index) {
                std::swap(heap[index], heap[largest]);
                index = largest;
            }
            else {
                break;
            }
        }
    }

public:
    void insert(int value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    int extractMax() {
        if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }
        int root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return root;
    }

    void buildHeap(const std::vector<int>& data) {
        heap = data;
        std::cout << '\n';
        for (int i = heap.size() / 2 - 1; i >= 0; --i) {
            heapifyDown(i);
        }
    }

    void update(int index, int newValue) {
        if (index < 0 || index >= heap.size()) {
            throw std::out_of_range("Index out of range");
        }

        int oldValue = heap[index];
        heap[index] = newValue;

        // Если новое значение больше, чем старое — поднимем его вверх.
        if (newValue > oldValue) {
            heapifyUp(index);
        }
        // Если новое значение меньше — опустим его вниз.
        else if (newValue < oldValue) {
            heapifyDown(index);
        }
    }

    void remove(int index) {
        if (index < 0 || index >= heap.size()) {
            throw std::out_of_range("Index out of range");
        }

        // Заменяем элемент на последний в куче
        heap[index] = heap.back();
        heap.pop_back();

        // Восстанавливаем кучу после замены
        if (index < heap.size()) {
            heapifyDown(index);
        }
    }

    const std::vector<int>& getHeap() const {
        return heap;
    }

    bool isHeapPropertyValid() const {
        int size = heap.size();
        for (int i = 0; i < size; ++i) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            // Проверяем, что родитель больше или равен левому потомку
            if (left < size && heap[i] < heap[left]) {
                return false;
            }

            // Проверяем, что родитель больше или равен правому потомку
            if (right < size && heap[i] < heap[right]) {
                return false;
            }
        }
        return true;
    }
};


//Тестирование

// Функция для измерения времени выполнения
template <typename Func>
double measureTime(Func func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

// Тестирование операций с кучей
void testHeap() {
    MaxHeap heap;

    // --- Тест 1: Построение кучи ---
    const int dataSize = 100000;
    std::vector<int> data(dataSize);

    // Генерация случайных данных
    for (int i = 0; i < dataSize; ++i) {
        data[i] = rand() % 100000;
    }

    // Замер времени на построение кучи
    double buildTime = measureTime([&]() {
        heap.buildHeap(data);
        });
    std::cout << "Время построения кучи: " << buildTime << " секунд" << std::endl;

    // Проверка свойства кучи
    if (heap.isHeapPropertyValid())
        std::cout << "Свойство кучи соблюдается после построения.\n";
    else
        std::cout << "Свойство кучи не соблюдается после построения"; // Родитель больше или равен потомкам


    // --- Тест 2: Вставка элемента ---
    int elementToInsert = 50000;
    double insertTime = measureTime([&]() {heap.insert(elementToInsert); });
    std::cout << "Время вставки элемента: " << insertTime << " секунд" << std::endl;

    // Проверка вставленного элемента
    if (heap.isHeapPropertyValid())
        std::cout << "Свойство кучи сохранилось после вставки нового элемента.\n";
    else
        std::cout << "Свойство кучи не сохранено";

    // --- Тест 3: Обновление элемента ---
    int updateIndex = 50000;
    int newValue = 100000;
    double updateTime = measureTime([&]() {heap.update(updateIndex, newValue); });
    std::cout << "Время обновления элемента: " << updateTime << " секунд" << std::endl;

    // Проверка обновления
    if (heap.isHeapPropertyValid())
        std::cout << "Свойство кучи сохранилось после обновления элемента.\n";
    else
        std::cout << "Свойство кучи не сохранено";

    // --- Тест 4: Удаление элемента ---
    int removeIndex = 50000;
    double removeTime = measureTime([&]() {
        heap.remove(removeIndex);
        });
    std::cout << "Время удаления элемента: " << removeTime << " секунд" << std::endl;

    // Проверка свойства кучи после удаления
    if (heap.isHeapPropertyValid())
        std::cout << "Свойство кучи сохранилось после удаления элемента.\n";
    else
        std::cout << "Свойство кучи не сохранено";
}

int main() {
    setlocale(LC_ALL, "Russian");
    try {
        testHeap();
    }
    catch (const std::exception& e) {
        std::cerr << "Тест не пройден: " << e.what() << std::endl;
    }
    return 0;
}
