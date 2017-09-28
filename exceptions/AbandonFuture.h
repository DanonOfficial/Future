//
// Created by danonofficial on 27.09.17.
//

#ifndef FUTURE_ABANDONFUTURE_H
#define FUTURE_ABANDONFUTURE_H

#include <stdexcept>

namespace error {
    class AbandonFuture : public std::exception {
    public:

        explicit AbandonFuture(std::string msg) noexcept : msg(std::move(msg)) {}

        ~AbandonFuture()  noexcept override = default;

        const char *what() const noexcept override {
            return msg.c_str();
        }

    private:
        std::string msg;
    };
}
#endif //FUTURE_ABANDONFUTURE_H
