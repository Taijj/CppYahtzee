#pragma once

#include <string>


template <typename T, typename U>
const std::wstring GetMessage(T expected, T actual, U context)
{
	std::wstring result = L"Expected {";
	result += std::to_wstring(expected);
	result += L"} but was {";
	result += std::to_wstring(actual);
	result += L"}! ==> {";	
	result += std::to_wstring(context);
	result += L"}";
	return result;
}