#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

int shared_data = 0;
std::mutex mtx;

void writer_thread() {
    for (int i = 0; i < 100; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        shared_data = i;
        std::cout << "Writer: " << shared_data << std::endl;

        // Добавление задержки на 2 секунды
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void reader_thread() {
    for (int i = 0; i < 100; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        int value = shared_data;
        std::cout << "Reader: " << value << std::endl;

        // Добавление задержки на 2 секунды
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int main() {
    std::thread writer(writer_thread);
    std::thread reader(reader_thread);

    writer.join();
    reader.join();

    return 0;
}
