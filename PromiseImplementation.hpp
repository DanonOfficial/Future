//
// Created by danonofficial on 30.09.17.
//

#ifndef FUTURE_PROMISEIMPLEMENTATION_HPP
#define FUTURE_PROMISEIMPLEMENTATION_HPP

template<typename T>
void Promise<T>::Set(const T &dataToSet) {
    if (data == nullptr) {
        throw error::NoData("There is no shared data at adress");
    }
    std::lock_guard <std::mutex> lock(data->mute);
    if (data->isReady) {
        throw error::AbandonFuture("You will broke future after this, sorry, but i cann't allow you to do it");
    }
    data->value = dataToSet;
    data->isReady = true;
    data->condition.notify_all();
}

template<typename T>
void Promise<T>::Set(T &&dataToSet) {
    if (data == nullptr) {
        throw error::NoData("There is no shared data at adress");
    }
    std::lock_guard <std::mutex> lock(data->mute);
    if (data->isReady) {
        throw error::AbandonFuture("You will broke future after this, sorry, but i cann't allow you to do it");
    }
    data->value = dataToSet;
    data->isReady = true;
    data->condition.notify_all();
}

template<typename T>
void Promise<T>::SetException(const std::exception_ptr &exc) {
    if (data == nullptr) {
        throw error::NoData("There is no shared data at adress");
    }
    std::lock_guard <std::mutex> lock(data->mute);
    if (data->isReady) {
        throw error::AbandonFuture("You will broke future after this, sorry, So i cann't allow you to do it");
    }
    data->exception_ptr = std::move(exc);
    data->isReady = true;
    data->condition.notify_all();
}

template<typename T>
Future <T> Promise<T>::GetFuture() {
    if (data == nullptr) {
        throw error::NoData("There is no shared data at adress");
    }
    if (futureAlreadyGetted == true) {
        throw error::AbandonFuture("You are trying to get already getted value");
    }
    futureAlreadyGetted = true;
    return Future<T>(data);
}

#endif //FUTURE_PROMISEIMPLEMENTATION_HPP
