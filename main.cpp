#include <iostream>
#include "Promise.h"
#include <thread>
#include <future>
int main() {
    /*Promise<int> out;
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
    Promise<int> promise;
    Future<int> f = promise.GetFuture();

    int const x = 10;
    promise.Set(x);*/
    Promise<int &> promise;
    Future<int &> f = promise.GetFuture();

    int const y = 100;
    int x = 10;

    promise.Set(x);
    std::cout <<"kek" << std::endl;
    f.Get() = y;
    std::cout <<"ke1k" << std::endl;
    return 0;
}