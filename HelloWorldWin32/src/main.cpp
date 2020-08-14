#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>

// have to change Subsystem in Properties to 'Windows (/SUBSYSTEM:WINDOWS)'
// https://docs.microsoft.com/en-us/windows/win32/learnwin32/your-first-windows-program

// defines the behavior of the window (appearance, how it interacts with the user, etc.) 
// WindowProc is not called explicitly, Windows communicates with the program by passing it a series of messages
// each time the DispatchMessage is called, it indirectly causes the Windows to invoke WindowProc
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc = WindowProc;  // pointer to window procedure ('WindowProc')
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;  // string that identifies the window class

    RegisterClass(&wc);

    // Create a top-level window.
    // returns a HWND (handle), used by a program to reference a window
    // to perform an operation on a window, typically have to call a function that takes a HWND value as a paramater 
    HWND hwnd = CreateWindowEx(
        0,  // Optional window styles.
        CLASS_NAME,  // Window class
        L"Hello World Windows",  // Window text
        WS_OVERLAPPEDWINDOW,  // Window style
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,  // Size and position
        NULL,  // Parent window    
        NULL,  // Menu
        hInstance,  // Instance handle
        NULL  // Additional application data can be passed to window
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.
    MSG msg = { };

    // GetMessage polls from the message queue (created by OS) 
    // the message queue holds the messages for all the windows created on that thread 
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);  // related to keyboard input, translates keystrokes (key down, key up) into characters
        DispatchMessage(&msg);  // tells the operating system to call the window procedure of the window that is the target of the message
    }

    /*
    - "Posting a message" means the message goes on the message queue, and is dispatched through the message loop (GetMessage and DispatchMessage)
    - "Sending a message" means the message skips the queue, and the operating system calls the window procedure directly
    */

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    /*
    - hwnd is a handle to the window
    - uMsg is the message code; for example, the WM_SIZE message indicates the window was resized
    - wParam and lParam contain additional data that pertains to the message, the exact meaning depends on the message code
    - LRESULT is an integer value that your program returns to Windows, it contains your program's response to a particular message, 
      the meaning of this value depends on the message code 
    - CALLBACK is the calling convention for the function
    */

    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        
        // All painting occurs here, between BeginPaint and EndPaint.

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hwnd, &ps);
    }
    return 0;
    }

    // function performs the default action for the message
    // pass message parameters to this function when you do not want to handle a particular message in the window procedure
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
