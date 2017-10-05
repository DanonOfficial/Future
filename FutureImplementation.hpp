//
// Created by danonofficial on 27.09.17.
//

template<typename T>
Future<T &> &Future<T &>::operator=(const Future<T &> &b) {
    *this = std::move(b);
};

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


template<typename T>
void Future<T &>::Wait() {
    if (data == nullptr) {
        throw error::NoData("There is no shared data at adress");
    }
    std::unique_lock<std::mutex> lock(data->mute);
    data->condition.wait(lock, [this] { return data->isReady; });
}

template<typename T>
T &Future<T &>::Get() {
    Wait();
    auto temp = std::move(data);//data == nullptr after it
    if (temp->exception_ptr) {
        std::rethrow_exception(temp->exception_ptr);
    }
    static T res = *temp->value;
    return res;
}

template<typename T>
bool Future<T &>::IsReady() const {
    if (data == nullptr) {
        return false;
    }
    std::unique_lock<std::mutex> lock(data->mute);
    return data->isReady;
}
