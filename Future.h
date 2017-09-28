//
// Created by danonofficial on 26.09.17.
//

#ifndef FUTURE_FUTURE_H
#define FUTURE_FUTURE_H

#include <stdexcept>
#include <mutex>
#include <condition_variable>
#include <memory>
#include "exceptions/NoData.h"
#include "exceptions/AbandonFuture.h"

template<typename T>
struct Mailbox {
    T value;
    std::exception_ptr exception_ptr;
    bool isReady = false;
    std::mutex mute;
    std::condition_variable condition;
};

template<typename T>
struct Mailbox<T &> {
    std::reference_wrapper<T> a;
    std::exception_ptr exception_ptr;
    bool isReady = false;
    std::mutex mute;
    std::condition_variable condition;
};


template<typename T>
class Future {
public:
    Future(Future &&past) : data(std::move(past.data)) {};

    Future(std::shared_ptr<Mailbox<T>> data) : data(data) {};

    const T &Get();

    bool IsReady() const;

    void Wait();

    ~Future() = default;

private:

    std::shared_ptr<Mailbox<T>> data;
};


template<typename T>
struct Future<T &> {
public:
    Future(Future &&past) : data(std::move(past.data)) {};

    Future(std::shared_ptr<Mailbox<T>> data) : data(data) {};

    const T &Get();

    bool IsReady() const;

    void Wait();

    ~Future() = default;

private:

    std::shared_ptr<Mailbox<T>> data;
};


template<typename T>
class Promise {
public:
    Promise() : data(new Mailbox<T>), futureAlreadyGetted(false) {};

    //Promise(T &smth): data(std::move(smth)),futureAlreadyGetted(false){}

    Promise(Promise<T> &&past) : data(std::move(past.data)), futureAlreadyGetted(false) {};

    Future<T> GetFuture();

    void Set(const T &dataToSet);

    void Set(T &&dataToSet);

    void SetException(const std::exception_ptr &exc);

    ~Promise() = default;

private:
    bool futureAlreadyGetted;
    std::shared_ptr<Mailbox<T>> data;
};

template<typename T>
struct Promise<T &> {
public:
    Promise() : data(new Mailbox<T>), futureAlreadyGetted(false) {};

    //Promise(T &smth): data(std::move(smth)),futureAlreadyGetted(false){}

    Promise(Promise<T> &&past) : data(std::move(past.data)), futureAlreadyGetted(false) {};

    Future<T &> GetFuture();

    void Set(const T &dataToSet);

    void Set(T &&dataToSet);

    void SetException(const std::exception_ptr &exc);

    ~Promise() = default;

private:
    bool futureAlreadyGetted;
    std::shared_ptr<Mailbox<T>> data;
};

#include "FutureImplementation.hpp"


#endif //FUTURE_FUTURE_H
