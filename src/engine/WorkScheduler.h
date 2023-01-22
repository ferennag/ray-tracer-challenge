#ifndef RAY_TRACER_CHALLENGE_WORKSCHEDULER_H
#define RAY_TRACER_CHALLENGE_WORKSCHEDULER_H

#include <vector>
#include <deque>
#include <thread>
#include <mutex>
#include <future>

using namespace std;

template<typename I>
using WorkerFunction = function<void(const I &)>;

template<typename I>
struct Work {
    I data;
    WorkerFunction<I> handler;
};

template<typename I>
class WorkScheduler {
public:
    WorkScheduler();
    explicit WorkScheduler(const int maxThreads);
    ~WorkScheduler() = default;

    WorkScheduler(const WorkScheduler &rhs) = delete;
    WorkScheduler(const WorkScheduler &&rhs) = delete;
    WorkScheduler &operator=(const WorkScheduler &rhs) = delete;
    WorkScheduler &operator=(const WorkScheduler &&rhs) = delete;

    void enqueue(const Work<I> &work);
    void start(promise<void> promise);
    void stop();
private:
    unsigned int m_maxThreads { 1 };
    atomic<bool> m_running { false };
    mutex m_workQueueMutex;
    deque<Work<I>> m_workQueue;

    void executeWork(promise<void> promise);
};

template<typename I>
WorkScheduler<I>::WorkScheduler(): m_maxThreads(thread::hardware_concurrency()) {
}

template<typename I>
WorkScheduler<I>::WorkScheduler(const int maxThreads) {
    m_maxThreads = maxThreads;
}

template<typename I>
void WorkScheduler<I>::stop() {
    m_running = false;
}

template<typename I>
void WorkScheduler<I>::enqueue(const Work<I> &work) {
    m_workQueueMutex.lock();
    m_workQueue.push_back(work);
    m_workQueueMutex.unlock();
}

template<typename I>
void WorkScheduler<I>::start(promise<void> promise) {
    m_running = true;
    vector<future<void>> threads;
    for (int i = 0; i < m_maxThreads; ++i) {
        std::promise<void> threadPromise;
        threads.push_back(threadPromise.get_future());
        std::thread thread(&WorkScheduler::executeWork, this, std::move(threadPromise));
        thread.detach();
    }

    for (auto &future: threads) {
        future.wait();
    }

    m_running = false;
    promise.set_value();
}

template<typename I>
void WorkScheduler<I>::executeWork(promise<void> threadPromise) {
    while (m_running) {
        m_workQueueMutex.lock();
        if (m_workQueue.empty()) {
            m_workQueueMutex.unlock();
            break;
        }
        auto work = m_workQueue.front();
        m_workQueue.pop_front();
        m_workQueueMutex.unlock();

        work.handler(work.data);
    }

    threadPromise.set_value();
}

#endif //RAY_TRACER_CHALLENGE_WORKSCHEDULER_H
