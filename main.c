#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <ntddscsi.h>
#include <stdio.h>


void print_error(DWORD err) {
    LPVOID errorMessage;
    DWORD formatFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
    DWORD languageId = MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT);

    if (FormatMessage(
        formatFlags,
        NULL,
        err,
        languageId,
        (LPWSTR)&errorMessage,
        0,
        NULL
    )) {
        wprintf(L"Error %lu: %s", err, (wchar_t *)errorMessage);    // `\n` already in errorMessage
        LocalFree(errorMessage);
    }
    else {
        wprintf(L"Error formatting message for error code %lu. Error code: %lu", err, GetLastError());
    }
}


void disable_apm(int phydisk_number) {
    char phyname[64] = { 0 };
    sprintf(phyname, "\\\\.\\PhysicalDrive%d", phydisk_number);
    printf("--> disabling for %s\n", phyname);

    HANDLE handle = CreateFileA(phyname, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
    if (handle == INVALID_HANDLE_VALUE) {
        print_error(GetLastError());
        return;
    }

    ATA_PASS_THROUGH_EX aptex = { 0 };
    aptex.Length = sizeof(aptex);
    aptex.TimeOutValue = 5;
    aptex.CurrentTaskFile[6] = 0xef;    // set `command` to `0xef`(setting features)
    aptex.CurrentTaskFile[0] = 0x85;    // set `subcommand` to `0x85`(disabling APM)
    DWORD out_size;
    BOOL ret = DeviceIoControl(handle, IOCTL_ATA_PASS_THROUGH, &aptex, sizeof(aptex), NULL, 0, &out_size, NULL);
    if (ret == 0) {
        print_error(GetLastError());
        goto exit;
    }

exit:
    CloseHandle(handle);
}


const char usage[] = "\
Usage example: \n\
    apmdisable.exe 0 1 3        ; this disables APM function for PhysicalDrive 0, 1 and 3 \n\
    ";

int main(int argc, char ** argv) {
    if (argc == 1) {
        puts(usage);
        exit(1);
    }
    for (int i = 1; i < argc; i++) {
        int num = atoi(argv[i]);
        disable_apm(num);
    }
}
