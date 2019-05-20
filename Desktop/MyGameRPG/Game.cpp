#include <iostream>

int main ( int argv, char *argc[] )
{
	if ( argv == 2 )
		std::cout << argc[1] << std::endl;
	else
		std::cout << "Not enter" << std::endl;
}
