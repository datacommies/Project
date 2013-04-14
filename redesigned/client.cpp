#include "resource.h"
#include "modules/client.h"
#include "modules/server.h"
#include "X11/Xlib.h"
int main()
{
    XInitThreads();
    Client();
    return 0;
}