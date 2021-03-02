#include <chrono>
#include <iomanip>
#include <iostream>

int main()
{
    auto now = std::chrono::system_clock::now();

    auto c_now = std::chrono::system_clock::to_time_t(now);

    auto format = "%Y-%m-%d %X";

    auto time = std::put_time(std::localtime(&c_now), format);

    std::cout << time << std::endl;
}