//
// Created by danonofficial on 30.09.17.
//

#ifndef FUTURE_PROMISE_HPP
#define FUTURE_PROMISE_HPP
#include "Future.h"
#include "SharedState.h"
template<typename T>
struct Promise {
public:
    Promise() : data(new ShareState<T>), futureAlreadyGetted(false) {};


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
 template<typename T>
struct Promise<T &> {
public:
    Promise() : data(new ShareState<T>), futureAlreadyGetted(false) {};

    //Promise(T &smth): data(std::move(smth)),futureAlreadyGetted(false){}

    Promise(Promise<T> &&past) : data(std::move(past.data)), futureAlreadyGetted(false) {};

    Future<T&> GetFuture();

    void Set(const T &dataToSet);

    void Set(T &&dataToSet);

    void SetException(const std::exception_ptr &exc);

    ~Promise() = default;

private:
    bool futureAlreadyGetted;
    std::shared_ptr<ShareState<T>> data;
};

#include "PromiseImplementation.hpp"

#endif //FUTURE_PROMISE_HPP
