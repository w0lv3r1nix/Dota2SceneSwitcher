#include <windows.h>
#include <fstream>
#include <iostream>

using namespace std;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
char szClassName[ ] = "Dota2 Scene Switcher";
HANDLE thread;
HANDLE timer;
HANDLE stopReq;
DWORD timeToSleep;
bool bKillThread;
string filename;

static DWORD WINAPI ThreadProc(LPVOID pParam){
	LARGE_INTEGER dueTime;

	if((timer = CreateWaitableTimer(NULL, FALSE, NULL)) == NULL)
		return 999;
	dueTime.QuadPart=0;
	SetWaitableTimer(timer, &dueTime, timeToSleep, NULL, NULL, FALSE);
	HANDLE handles[] = { timer, stopReq };

	while(!bKillThread)
	{
		ifstream ifs(filename.c_str(), fstream::in);
		if (ifs.is_open()) {
	        string game_state;
	        for (string line; getline(ifs, line);) {
	            std::size_t found = line.find("C:Gamerules: entering state");
	            if (found != std::string::npos) {
	                std::size_t begin = line.find("'") + 1;
	                std::size_t end = line.find("'", begin);
	                game_state = line.substr(begin, end - begin);
	            }
	        }
	        string title = "Dota2 Scene Switcher - ";
	        title.append( game_state );
	        SetWindowText((HWND)pParam, title.c_str());
	        std::cout << game_state << std::endl;
	        ifs.close();
	    } else {
	        std::cout << "Was unable to open the file!" << std::endl;
	    }

		WaitForMultipleObjects(2, handles, FALSE, INFINITE);
	}

	CloseHandle(timer);
	return 0;
}

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)

{
                    
    filename = lpszArgument;
    if( filename.empty() ) {
        MessageBox( NULL, 
                   "Logfile not specified, using default:\n\nC:\\Program Files (x86)\\Steam\\steamapps\\common\\dota 2 beta\\dota\\dota2_console.txt",
                   "Dota 2 Scene Switcher",
                MB_ICONWARNING );
        filename = "C:\\Program Files (x86)\\Steam\\steamapps\\common\\dota 2 beta\\dota\\dota2_console.txt";
    }
    int result;
    do {
        ifstream ifs(filename.c_str(), fstream::in);
        if (!ifs.is_open()) {
             result = MessageBox( NULL, 
                   "Unable to locate the console logfile\nPlease make sure you have set con_logfile variable into your autoexec.cfg inside dota2 folder\nIf you already did it, just open dota2 one time to make sure that dota create the logfile!",
                   "Dota 2 Scene Switcher",
                MB_ICONERROR | MB_RETRYCANCEL );
        } else {
            break;
        }
        if( result == IDCANCEL ) {
            return 99;
        }
    } while( result == IDRETRY );
    
    
                    
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           "Dota2 Scene Switcher",       /* Title Text */
           WS_OVERLAPPED | WS_SYSMENU, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           175,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nFunsterStil);
    HWND hwndLabel1;
    HWND hwndLabel2;
    HWND hwndLabel3;
    

 

    //code inside WINAPI WinMain() function
    hwndLabel1 = CreateWindow("STATIC","www.facebook.com/w0lv3r1nix", WS_VISIBLE | WS_CHILD | SS_RIGHT,10,100,500,35,hwnd,NULL,hThisInstance,NULL);
    hwndLabel2 = CreateWindow("STATIC","www.youtube.com/w0lv3r1nix", WS_VISIBLE | WS_CHILD | SS_RIGHT,10,60,500,35,hwnd,NULL,hThisInstance,NULL);
    hwndLabel3 = CreateWindow("STATIC","www.twitch.tv/w0lv3r1nix", WS_VISIBLE | WS_CHILD | SS_RIGHT,10,20,500,35,hwnd,NULL,hThisInstance,NULL);
    HFONT hFont, hNewFont;
    LOGFONT lf;
    HDC hDC;
    hFont = (HFONT)SendMessage(hwndLabel1, WM_GETFONT, 0, 0);
    if(hDC = GetDC(hwndLabel1))
    {
        if (hFont == NULL)
        {
            hFont = (HFONT) GetStockObject(SYSTEM_FONT);
            GetObject(hFont, sizeof(LOGFONT),&lf);
            lf.lfQuality = DEFAULT_QUALITY;
            lf.lfWidth = 0;
        }
        else
           GetObject(hFont, sizeof(LOGFONT),&lf);

        int dpi = GetDeviceCaps(hDC, LOGPIXELSY);
        lf.lfHeight = -MulDiv(30, dpi, dpi);
        hNewFont = CreateFontIndirect(&lf);

        SendMessage(hwndLabel1, WM_SETFONT, (WPARAM)hNewFont, MAKELPARAM(TRUE,0));
        SendMessage(hwndLabel2, WM_SETFONT, (WPARAM)hNewFont, MAKELPARAM(TRUE,0));
        SendMessage(hwndLabel3, WM_SETFONT, (WPARAM)hNewFont, MAKELPARAM(TRUE,0));
        ReleaseDC(hwndLabel1, hDC);
     }
    
    
    timeToSleep = 300;
	thread = 0;
	timer = 0;
	bKillThread = true;
    if(!thread) {
        bKillThread = false;
		thread = CreateThread(NULL, 0, ThreadProc, (LPVOID)hwnd, 0, NULL);
    }

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            if(thread) {
                bKillThread = true;
        		DWORD retv;
        		MSG msg;
        		HANDLE handles[] = {thread};
        		SetEvent(stopReq);
        		//process messages while waiting for the thread to complete, otherwise the thread will be locked forever
        		while((retv = MsgWaitForMultipleObjects(1, handles, FALSE, INFINITE, QS_ALLINPUT)) != WAIT_FAILED)
        		{
        			if(retv == WAIT_OBJECT_0)
        				break;
        			else if(retv == WAIT_OBJECT_0+1)
        				while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        				{
        					TranslateMessage(&msg);
        					DispatchMessage(&msg);
        				}
        		}
        		ResetEvent(stopReq);

        		if(thread)
        		{
        			CloseHandle(thread);
        			thread = 0;
        		}
        	}
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
