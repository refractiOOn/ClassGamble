#include "classGamble.h"
#include "classHandleWrapper.h"

Gamble* g_gamble = new Gamble();

DWORD __stdcall Player(LPVOID parameter)
{
	Prediction prediction = *static_cast<Prediction*>(parameter);
	g_gamble->MakePrediction(prediction.name, prediction.number);
	return 0;
}

DWORD __stdcall Bookmaker(LPVOID parameter)
{
	while (true)
	{
		std::cout << "Enter name and number:" << std::endl;
		Prediction prediction;
		std::wcin >> prediction.name >> prediction.number;
		HandleWrapper player = CreateThread(0, 0, Player, &prediction, 0, 0);
		WaitForSingleObject(player.Get(), INFINITE);
	}
}

int main()
{
	HandleWrapper bookmaker = CreateThread(0, 0, Bookmaker, 0, 0, 0);
	WaitForSingleObject(bookmaker.Get(), 30000);
	std::pair<size_t, std::wstring> winner = g_gamble->DetermineWinner();
	std::wcout << winner.second << " wins with number " << winner.first << std::endl;
	std::wcout << "Hidden number was " << g_gamble->GetNumber() << std::endl;
	g_gamble->~Gamble();
}