//
// Created by nikita on 17.05.17.
//

#include "Timer.h"

std::stack <Clock::time_point> time_stack;

void start_timer()
{
    time_stack.push(Clock::now());
}

double stop_timer()
{
    auto res = std::chrono::duration_cast<std::chrono::duration<double> >(
            Clock::now() - time_stack.top()
    ).count();
    time_stack.pop();
    return res;
}

void stop_timer(std::string msg)
{
    std::cout << "\n" << msg << stop_timer() << "s" << std::endl;
}