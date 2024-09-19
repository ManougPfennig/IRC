#include "ircserv.hpp"

std::vector<std::string>	split(std::string str, char delim) {
	std::vector<std::string>	vec;
	std::string					temp;

	for (std::size_t i = 0; i < str.size(); ++i) {
		if (str[i] != delim) {
			temp += str[i];
		}
		else {
			if (!temp.empty()) {
				vec.push_back(temp);
				temp.clear();
			}
		}
	}
	if (!temp.empty()) {
		vec.push_back(temp);
	}
	return vec;
}

void	registerNewClient(t_server &serv, int key) {

	std::string					toParse = serv.buffer;
	std::string					delim = "\r\n";
	std::vector<std::string>	vec;
	std::vector<std::string>	splitted = split(toParse, '\n');
	size_t						found;

	for (std::size_t i = 0; i < splitted.size(); ++i) {
		std::vector<std::string> words = split(splitted[i], ' ');
		if (!words.empty()) {
			if (words[0] == "PASS" && words.size() > 1) {
				vec.push_back(words[1]);
			}
			else if (words[0] == "NICK" && words.size() > 1) {
				vec.push_back(words[1]);
			}
			else if (words[0] == "USER" && words.size() > 1) {
				vec.push_back(words[1]);
				vec.push_back(words[4].erase(0, 1));
				//cette derniere ligne chope le dernier mot et retire le ":" devant
			}
		}
	}

	//debug
	for (std::size_t i = 0; i < splitted.size(); ++i) {
		std::cout << "splitted:" << splitted[i] << std::endl;
	}
	for (std::size_t i = 0; i < vec.size(); ++i) {
		std::cout << "vec:" << vec[i] << std::endl;
	}

	//ceci ne fonctionne pas, a regler demain (surement une histoire de whitespace qui fait qu'il pense que ce ne sont pas les memes)
	// if (vec[0] == serv.password) {
	// 	std::cout << "GOOD PASSWORD" << std::endl;
	// }


	serv.clientMap[key].setNickname(vec[1]);
	serv.clientMap[key].setUsername(vec[2]);
	serv.clientMap[key].setRealname(vec[3]);

	return ;
}
