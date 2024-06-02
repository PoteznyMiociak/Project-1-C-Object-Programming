#pragma once
#include <string>

class InfoTeller{
	std::string message = "";
public:
	std::string GetMessage();
	void AddToMessages(char firstSymbol, char secondSymbol, char Type);
	void ClearMessages();
	~InfoTeller() {};
};

