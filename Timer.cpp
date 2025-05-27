#include <iostream>
#include <chrono>
#include <stdexcept>

using namespace std::chrono;

class Timer
{
public:
	~Timer()
	{
		end();
	}
	void start() 
	{
		if (is_running)
			throw std::runtime_error("The timer cannot be repeatedly started when it has already started");

		start_time = high_resolution_clock::now();
		is_running = true;
	}

	void end() 
	{
		if (!is_running)
			throw std::runtime_error("The timing cannot be ended before it starts");

		auto end_time = high_resolution_clock::now();
		total_duration += end_time - start_time;
		is_running = false;
	}

	void print() const 
	{
		auto duration_ms = duration_cast<chrono::milliseconds>(total_duration);
		std::cout << "Total time: " << duration_ms.count() << "ms" << endl;
	}

	void reset() 
	{
		total_duration = nanoseconds::zero();
		is_running = false;
	}
private:
	time_point<high_resolution_clock> start_time;
	nanoseconds total_duration{ 0 };
	bool is_running = false;
};

class ScopedTimer
{
public:
	ScopedTimer()
	{
		timer.start();
	}
	~ScopedTimer()
	{
		timer.end();
		timer.print();
	}
private:
	Timer timer;
};
