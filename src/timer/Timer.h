//
// Created by nikita on 17.05.17.
//

#ifndef L0SAMPLER_TIMER_H
#define L0SAMPLER_TIMER_H

#include <stack>
#include <chrono>
#include <string>
#include <iostream>

typedef std::chrono::high_resolution_clock Clock;

extern std::stack <Clock::time_point> time_stack;

void start_timer();

double stop_timer();

void stop_timer(std::string msg);

#endif //L0SAMPLER_TIMER_H
