#include <iostream>

#include "ApplicationContext.h"

int main()
{
	int success = ApplicationContext::Instance()->Initialize();
	if (success == -1)
	{
		std::cout << "Failed to initialize!" << std::endl;
		return -1;
	}

	while (ApplicationContext::Instance()->Update())
	{

	}

	ApplicationContext::Instance()->Dispose();
	return 0;
}
