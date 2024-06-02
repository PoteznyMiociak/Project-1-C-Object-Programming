#include "InfoTeller.h"
#include <string>
#include <map>

std::map<char, std::string> dictionary = {
	{'W', "wolf"},{'A', "antylope"},{'F', "fox"},
	{'H', "human"},{'S', "sheep"},{'T', "turtle"},
	{'g', "grass"},{'s', "sow"},
	{'u', "guarana"},{'b', "belladona"},
	{'h', "Sosnowsky's hogweed"}
};

void InfoTeller::AddToMessages(char s1, char s2, char type)
{
	std::string info;
	if (type == 'F')		// F for fight
		info += dictionary[s1] + " has killed " + dictionary[s2] + '\n';
	else if (type == 'B')
		info += "We have a new " + dictionary[s1] + "!\n";
	else if (type == 'S')
		info += "The " + dictionary[s1] + " has spreaded." + '\n';
	else if (type == 'E')
		info += "Antylope has escaped!\n";
	else if (type == 'e')
		info += dictionary[s1] + " has eaten " + dictionary[s2] + '\n';
	else if (type == 's')
		info += "Human used super ability, his strenght has improved by 10! \n";
	else if (type == 'c')
		info += "Super ability is avaible.\n";

	size_t found = message.find(info);
	if (found == std::string::npos) {
		message += info;
	}
}


void InfoTeller::ClearMessages() {
	message = "";
}

std::string InfoTeller::GetMessage() {
	return message;
}