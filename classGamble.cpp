#include "classGamble.h"

Gamble::Gamble()
{
    InitializeCriticalSection(&m_criticalSection);
    size_t num;
    srand(time(0));
    num = 2 + rand() % 100;
    m_number = num;
}

Gamble::~Gamble()
{
    DeleteCriticalSection(&m_criticalSection);
}

void Gamble::MakePrediction(const std::wstring& name, const size_t number)
{
    EnterCriticalSection(&m_criticalSection);
    m_map.emplace(number, name);
    LeaveCriticalSection(&m_criticalSection);
}

std::pair<size_t, std::wstring> Gamble::DetermineWinner() const
{
    std::map<size_t, std::wstring>::const_iterator it = m_map.cbegin();
    size_t closestPrediction = it->first;
    size_t closestPredictionDeviation = abs(static_cast<int>(m_number) - static_cast<int>(closestPrediction));
    ++it;
    for (; it != m_map.cend(); ++it)
    {
        size_t currentDeviation = abs(static_cast<int>(m_number) - static_cast<int>(it->first));
        if (currentDeviation < closestPredictionDeviation)
        {
            closestPredictionDeviation = currentDeviation;
            closestPrediction = it->first;
        }
    }
    it = m_map.find(closestPrediction);
    std::pair<size_t, std::wstring> winner = std::make_pair(it->first, it->second);
    return winner;
}

size_t Gamble::GetNumber() const
{
    return m_number;
}