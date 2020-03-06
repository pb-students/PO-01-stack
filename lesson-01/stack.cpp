#include <iostream>
#include <vector>

template <typename T>
class Stack {
private:
    std::vector<T> elements;

public:
    void init (std::vector<T> v) {
        elements = v;
    }

    Stack () = default;
    explicit Stack (std::vector<T> v) {
        init(v);
    }

    // NOTE: Destructor is not needed in this case
    void destroy () {
        // noop
    }

    template <typename ...Args>
    int push (Args... args) {
        static_assert((std::is_constructible_v<T, Args&&> && ...));
        (elements.push_back(std::forward<Args>(args)), ...);

        return elements.size();
    }

    T pop () {
        T element = elements.back();
        elements.pop_back();
        return element;
    }

    T top () {
        return elements.back();
    }

    bool empty () {
        return elements.empty();
    }

    bool full () {
        return elements.max_size() == elements.size();
    }
};

void test () {
    Stack<int> intStack;
    Stack<char> charStack({ 'a', 'm', 'e', 'i', 's' });

    // Test char stack
    while (!charStack.empty()) {
        std::cerr << charStack.pop();
    }

    std::cerr << "\n";

    // Test int stack

    std::cerr << "New stack size: " << intStack.push(6, 6, 6, 3) << "\n";
    intStack.push(2);

    std::cerr << "Top element: " << intStack.top() << "\n";

    while (!intStack.empty()) {
        std::cerr << intStack.pop();
    }

    int size = rand() % 100 + 1;
    while (--size) {
        intStack.push(rand() % 10 + 1);
    }

    while (!intStack.empty()) {
        std::cerr << intStack.pop();
    }

}

int main() {
    test();
    return 0;
}
