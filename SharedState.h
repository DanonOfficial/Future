//
// Created by danonofficial on 30.09.17.
//

#ifndef FUTURE_SHAREDSTATE_HPP
#define FUTURE_SHAREDSTATE_HPP

template<typename T>
struct ShareState {
    T value;
    std::exception_ptr exception_ptr;
    bool isReady = false;
    std::mutex mute;
    std::condition_variable condition;
};

template<typename T>
struct ShareState <T&>{
    T& value;
    std::exception_ptr exception_ptr;
    bool isReady = false;
    std::mutex mute;
    std::condition_variable condition;
};

#endif //FUTURE_SHAREDSTATE_HPP
