#include "DesktopMascot.h"

#include <iostream>

int main() {
	DesktopMascot::Initialize();

	cout << "Now" << endl;
	DesktopMascot::Execute();
	DesktopMascot::End();

	return 1;
}