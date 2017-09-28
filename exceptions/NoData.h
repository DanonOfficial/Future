//
// Created by danonofficial on 27.09.17.
//

#ifndef FUTURE_NODATA_H
#define FUTURE_NODATA_H

#include <stdexcept>

namespace error {
    class NoData : public std::exception {
    public:

        explicit NoData(std::string msg) noexcept : msg(std::move(msg)) {}

        ~NoData()  noexcept override = default;

        const char *what() const noexcept override {
            return msg.c_str();
        }

    private:
        std::string msg;
    };
}
#endif //FUTURE_NODATA_H
