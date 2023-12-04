#pragma once

#include <string>
#include <codecvt>
#include <string>

/// <summary>
/// TODO: Make this work with std::string inputs.
/// </summary>
template <typename T>
const std::wstring GetMessage(T expected, T actual, T context)
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