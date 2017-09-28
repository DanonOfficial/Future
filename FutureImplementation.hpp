//
// Created by danonofficial on 27.09.17.
//

template<typename T>
void Promise<T>::Set(const T &dataToSet) {
    if (data == nullptr) {
        throw error::NoData("There is no shared data at adress");
    }
    std::lock_guard<std::mutex> lock(data->mute);
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
    std::lock_guard<std::mutex> lock(data->mute);
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
    std::lock_guard<std::mutex> lock(data->mute);
    if (data->isReady) {
        throw error::AbandonFuture("You will broke future after this, sorry, So i cann't allow you to do it");
    }
    data->exception_ptr = std::move(exc);
    data->isReady = true;
    data->condition.notify_all();
}

template<typename T>
Future<T> Promise<T>::GetFuture() {
    if (data == nullptr) {
        throw error::NoData("There is no shared data at adress");
    }
    if (futureAlreadyGetted == true) {
        throw error::AbandonFuture("You are trying to get already getted value");
    }
    futureAlreadyGetted = true;
    return Future<T>(data);
}

template<typename T>
void Future<T>::Wait() {
    if (data == nullptr) {
        throw error::NoData("There is no shared data at adress");
    }
    std::unique_lock<std::mutex> lock(data->mute);
    data->condition.wait(lock, [this] { return data->isReady; });
}

template<typename T>
const T &Future<T>::Get() {
    Wait();
    auto temp = std::move(data);//data == nullptr after it
    if (temp->exception_ptr) {
        std::rethrow_exception(temp->exception_ptr);
    }
    return std::move(temp->value);
}

template<typename T>
bool Future<T>::IsReady() const {
    if (data == nullptr) {
        return false;
    }
    std::unique_lock<std::mutex> lock(data->mute);
    return data->isReady;
}
