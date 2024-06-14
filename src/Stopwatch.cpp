#include "Stopwatch.h"
#include <chrono>

namespace ch = std::chrono;

inline long long GetCurrentTime() {
	return ch::duration_cast<ch::nanoseconds>(
		ch::high_resolution_clock::now().time_since_epoch()).count();
}

Stopwatch::Stopwatch() {
	this->Start();
}
void Stopwatch::Start() {
	this->startTime = GetCurrentTime();
}
long long Stopwatch::Get() {
	return GetCurrentTime() - this->startTime;
}