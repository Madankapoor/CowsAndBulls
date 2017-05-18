#include <windows.h>
#include <stdio.h>


int openqtapplication(char * word)
{
    
    
    char cool[10000];
    TCHAR dir[10000];
    GetCurrentDirectoryA(10000,dir);
    puts(dir);
    sprintf(cool,"\"file:///%s/html/%s.html\"",dir,word);
    
    LONG r = ShellExecute(NULL, "open", cool, NULL, NULL, SW_SHOWNORMAL);
    
    return r;
    }
    
