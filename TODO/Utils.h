//#pragma once
//
//#include <iostream>
//#include <thread>
//#include <chrono>
//
//class Utils
//{
//public:
//	Utils() = delete;
//
//	template <typename T>
//	static void Log(const T& message)
//	{
//		std::cout << message << std::endl;
//	}
//
//	static void WaitFor(const float seconds)
//	{
//		std::this_thread::sleep_for(std::chrono::duration<float>(seconds));
//	}
//};