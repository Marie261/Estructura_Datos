#ifndef COLA_H
#define COLA_H

#include <vector>
#include <stdexcept>

template <typename T>
class Cola {
    private:
        std::vector<T> elementos;

    public:
        Cola() = default;

        int count() const { return static_cast<int>(elementos.size()); }

        bool isEmpty() const { return elementos.empty(); }

        void enqueue(const T& item) {
            elementos.push_back(item);
        }

        T dequeue() {
            if (isEmpty()) {
                throw std::out_of_range("Error: La cola esá vacía.");
            }

            T item = elementos.front();
            elementos.erase(elementos.begin());
            return item;
        }
        
        T peek() const {
            if (isEmpty()) {
                throw std::out_of_range("Error: La cola está vacía.");
            }
            return elementos.front();
        }
};

#endif