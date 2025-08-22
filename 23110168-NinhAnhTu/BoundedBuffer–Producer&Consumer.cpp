// producer_consumer.cpp

#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore.h>
#include <vector>   
#include <chrono>
#include <cstdlib>

using namespace std;
vector<int> buffer;
const int BUFFER_SIZE = 5;
mutex mtx;
sem_t empty_slots, filled_slots;

void printBuffer() {
    cout << "[BUFFER] Hiện tại: ";
    for (int val : buffer) cout << val << " ";
    cout << endl;
}

void producer() {
    while (true) {
        int item = rand() % 100;
        sem_wait(&empty_slots);
        {
            lock_guard<mutex> lock(mtx);
            buffer.push_back(item);
            cout << "[PRODUCER] Sản xuất sản phẩm: " << item << endl;
            printBuffer();
        }
        sem_post(&filled_slots);
        this_thread::sleep_for(chrono::milliseconds(500 + rand() % 1000));
    }
}

void consumer() {
    while (true) {
        sem_wait(&filled_slots);
        int item;
        {
            lock_guard<mutex> lock(mtx);
            item = buffer.front();
            buffer.erase(buffer.begin());
            cout << "[CONSUMER] Tiêu thụ sản phẩm: " << item << endl;
            printBuffer();
        }
        sem_post(&empty_slots);
        this_thread::sleep_for(chrono::milliseconds(500 + rand() % 1000));
    }
}

int main() {
    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&filled_slots, 0, 0);

    thread p1(producer), p2(producer);
    thread c1(consumer), c2(consumer);

    p1.join();
    p2.join();
    c1.join();
    c2.join();

    return 0;
}
