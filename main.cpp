#include "classGamble.h"
#include "classHandleWrapper.h"

DWORD __stdcall Player(LPVOID parameter)
{
	Args args = *static_cast<Args*>(parameter);
	args.gamblePointer->MakePrediction(args.name, args.number);
	return 0;
}

DWORD __stdcall Bookmaker(LPVOID parameter)
{
	Gamble* gamble = static_cast<Gamble*>(parameter);
	while (true)
	{
		std::cout << "Enter player name and his prediction:" << std::endl;
		std::wstring name;
		size_t number;
		std::wcin >> name >> number;
		Args args = { name, number, gamble };
		HandleWrapper player = CreateThread(0, 0, Player, &args, 0, 0);
		WaitForSingleObject(player.Get(), INFINITE);
	}
}

int main()
{
	Gamble gamble;
	HandleWrapper bookmaker = CreateThread(0, 0, Bookmaker, &gamble, 0, 0);
	WaitForSingleObject(bookmaker.Get(), 30000);
	std::pair<size_t, std::wstring> winner = gamble.DetermineWinner();
	std::wcout << winner.second << " wins with number " << winner.first << std::endl;
	std::wcout << "Hidden number was " << gamble.GetNumber() << std::endl;
}