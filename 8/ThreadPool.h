#ifndef INC_8_THREADPOOL_H
#define INC_8_THREADPOOL_H
#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <functional>
#include <vector>
#include <queue>


class ThreadPool {
    std::queue<std::function<void()>> Tasks;
    std::vector<std::thread> pool;
    std::mutex mutex; //access to tasks
    size_t size;
    std::atomic<bool> is_valid; //If threadpool exists
    std::condition_variable value; //sleeping

    void process_tasks() {
        while(is_valid) {
            std::unique_lock<std::mutex> lock(mutex);
            if(!Tasks.empty()){
                auto current_task = Tasks.front();
                Tasks.pop();
                lock.unlock();
                current_task();
            } else {
                value.wait(lock);
            }
        }
    }

public:
    explicit ThreadPool(size_t poolSize) :size(poolSize), is_valid(true) {
        for(int i = 0; i < poolSize; ++i) {
            pool.emplace_back(std::thread([this](){process_tasks();}));
        }
    }

    ~ThreadPool() {
        is_valid = false; //breaking top cycle in process_tasks
        value.notify_all(); //from sleeping to terminate
        for(int i = 0; i < size; i++) {
            pool[i].join();
        }
    }

    template <class Func, class... Args>
    auto exec(Func func, Args... args){
        auto problem = std::make_shared<std::packaged_task<decltype(func(args...))()>>([func, args...](){
            return func(args...);});
        auto res = problem->get_future();
        std::unique_lock<std::mutex> lock(mutex);
        Tasks.push([problem]() {(*problem)();});
        value.notify_one();
        return res;
    }
};
#endif //INC_8_THREADPOOL_H
