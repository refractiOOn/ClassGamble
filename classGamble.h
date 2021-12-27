#pragma once
#include <iostream>
#include <map>
#include <windows.h>

class Gamble
{
public:
	Gamble();
	~Gamble();
	void MakePrediction(const std::wstring& name, const size_t number);
	std::pair<size_t, std::wstring> DetermineWinner() const;
	size_t GetNumber() const;
private:
	std::map<size_t, std::wstring> m_map;
	size_t m_number = 0;
	CRITICAL_SECTION m_criticalSection;
};

struct Args
{
	std::wstring name;
	size_t number = 0;
	Gamble* gamblePointer;
};