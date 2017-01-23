#include <iostream>
#include <string>

int main() {
	std::string s0 = "Hallo";
	std::string s1 = "Hallo";
	std::string s2 = "Tschau";

	std::cout << "==" << std::endl;
	if (s0 == s1) {
		std::cout << "s0 == s1" << std::endl;
	}
	else {
		std::cout << "s0 != s1" << std::endl;
	}
	if (s0 == s2) {
		std::cout << "s0 == s2" << std::endl;
	}
	else {
		std::cout << "s0 != s2" << std::endl;
	}

	std::cout << "Compare" << std::endl;
	if (s0.compare(s1) == 0) {
		std::cout << "s0 == s1" << std::endl;
	}
	else {
		std::cout << "s0 != s1" << std::endl;
	}
	if (s0.compare(s2) == 0) {
		std::cout << "s0 == s2" << std::endl;
	}
	else {
		std::cout << "s0 != s2" << std::endl;
	}

	system("PAUSE");
}