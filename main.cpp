#include "Client.h"

// using namespace std;

void main()
{
	Client mcc("0.0.0.0", 54000);
	if (mcc.init() != 0)
		return;

	mcc.run();

	system("pause");
}