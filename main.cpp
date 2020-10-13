#include <Windows.h>
#include <iostream>
#include <chrono>

using namespace std;

#define DWM_COMPOSED_EVENT "DwmComposedEvent_1"

int main() {
	HANDLE hDwmComposedEvent = OpenEventA(SYNCHRONIZE, FALSE, DWM_COMPOSED_EVENT);
	cout << "GetLastError() = " << GetLastError() << endl;

	// Performance measurements
	std::chrono::milliseconds startMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	SHORT f12 = 0;
	int f = 0;

	while (true) {
		WaitForSingleObject(hDwmComposedEvent, INFINITE); // Waits for DWM to compose next frame
		f++;
		// Press F12 to show FPS
		f12 = GetAsyncKeyState(VK_F12);
		if (f12 & 1) {
			std::chrono::milliseconds nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
			long long diffMs = nowMs.count() - startMs.count();
			float diffSec = diffMs / 1000;
			float fps = f / diffSec;
			cout << fps << endl;
		}
	}

	system("pause");
	return EXIT_SUCCESS;
}
