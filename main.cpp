#include <iostream>
#include "Promise.h"
#include <thread>
#include <future>
int main() {
    Promise<int> out;
    Future<int> a = out.GetFuture();
    try {
        std::thread test([&out] {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            out.Set(10);
            return;
        });
        test.detach();
        if(!a.IsReady()){
            std::cout << "wait for data\n";
        }
        int res = a.Get();
        std::cout << res << std::endl;
    }
    catch (std::exception &sp) {
        std::cerr << sp.what() << std::endl;
    }
    Promise <float&> kek;
    Future <float&> temp;
    temp = kek.GetFuture();
    temp.Get() = 1;
    return 0;
}