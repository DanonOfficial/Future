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
#include "SharedState.h"

template<typename T>
class Future {
public:
    Future(Future &&past) : data(std::move(past.data)) {};

    Future(std::shared_ptr<ShareState<T>> data) : data(data) {};

    const T &Get();

    bool IsReady() const;

    void Wait();

    ~Future() = default;

private:

    std::shared_ptr<ShareState<T>> data;
};


template<typename T>
struct Future<T &> {
public:
    Future(Future &&past) : data(std::move(past.data)) {};

    Future(std::shared_ptr<ShareState<T>> data) : data(data) {};

    const T &Get();

    bool IsReady() const;

    void Wait();

    ~Future() = default;

private:

    std::shared_ptr<ShareState<T>> data;
};


template<typename T>
class Promise {
public:
    Promise() : data(new ShareState<T>), futureAlreadyGetted(false) {};

    //Promise(T &smth): data(std::move(smth)),futureAlreadyGetted(false){}

    Promise(Promise<T> &&past) : data(std::move(past.data)), futureAlreadyGetted(false) {};

    Future<T> GetFuture();

    void Set(const T &dataToSet);

    void Set(T &&dataToSet);

    void SetException(const std::exception_ptr &exc);

    ~Promise() = default;

private:
    bool futureAlreadyGetted;
    std::shared_ptr<ShareState<T>> data;
};


#include "FutureImplementation.hpp"


#endif //FUTURE_FUTURE_H
