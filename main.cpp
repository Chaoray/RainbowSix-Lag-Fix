#include <windows.h>

#include <iostream>
#include <bitset>

using namespace std;

int main() {
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    int cpuNum = sysinfo.dwNumberOfProcessors;

    HANDLE hProcess;
    HWND hWnd = FindWindowW(NULL, L"Rainbow Six");

    DWORD pid, tid;
    tid = GetWindowThreadProcessId(hWnd, &pid);
    if (!tid) {
        cout << "Rainbow Six Not Found\n";
        return 1;
    }

    hProcess = OpenProcess(PROCESS_SET_INFORMATION, FALSE, pid);
    if (hProcess == INVALID_HANDLE_VALUE) {
        cout << "Rainbow Six Denied Access\n";
        return 1;
    }

    DWORD_PTR dwProcessAffinityMask = 1;
    dwProcessAffinityMask <<= cpuNum - 1;

    BOOL ret = SetProcessAffinityMask(hProcess, dwProcessAffinityMask);
    if (!ret) {
        cout << "Failed to Fix Rainbow Six\n";
        return 1;
    }

    dwProcessAffinityMask <<= 1;
    dwProcessAffinityMask -= 1;

    SetProcessAffinityMask(hProcess, dwProcessAffinityMask);
    if (!ret) {
        cout << "Failed to Fix Rainbow Six\n";
        return 1;
    }

    cout << "Great! Enjoy Non-Laggy Rainbow Six\n";
    return 0;
}
