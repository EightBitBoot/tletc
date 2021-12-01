#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>

typedef struct XData_s {
    Display *display;
    int      screen;
    int      blackPixel;
    int      whitePixel;
    Window   window;
    // WM_DELETE_WINDOW, WM_TAKE_FOCUS
    Atom     wmProtocols_a[2];
} XData;

// Global X11 Data
XData xdata = {0};

int main(int argc, char **argv) {
    // Get the basic information about the server
    xdata.display = XOpenDisplay(NULL);
    xdata.screen  = XDefaultScreen(xdata.display);

    // Get the basic colors for the screen
    xdata.blackPixel = BlackPixel(xdata.display, xdata.screen);
    xdata.whitePixel = WhitePixel(xdata.display, xdata.screen);

    // TODO(Adin): Switch to XCreateWindow when necessary
    // Create the window
    xdata.window  = XCreateSimpleWindow(xdata.display, XDefaultRootWindow(xdata.display), 0, 0, 600, 400, 0, 0, xdata.blackPixel);

    // Choose events to recieve
    XSelectInput(xdata.display, xdata.window, KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | ExposureMask);

    // Tell the window manager which protocols the client participates in
    xdata.wmProtocols_a[0] = XInternAtom(xdata.display, "WM_DELETE_WINDOW", false); 
    xdata.wmProtocols_a[1] = XInternAtom(xdata.display, "WM_TAKE_FOCUS", false); 
    XSetWMProtocols(xdata.display, xdata.window, xdata.wmProtocols_a, 2);

    // Set the window name and other properties used by the window manager
    const char *windowName = "TLETC";
    XTextProperty nameProperty = {0};
    XmbTextListToTextProperty(xdata.display, (char **) &windowName, 1, XStringStyle, &nameProperty);
    XSetWMProperties(xdata.display, xdata.window, &nameProperty, NULL, argv, argc, NULL, NULL, NULL);

    // Queue the window for display when outbound buffer is flushed
    XMapWindow(xdata.display, xdata.window);

    bool running = true;
    XEvent event; // The event being processed
    while(running) {
        // Grab the next event in the queue or block
        XNextEvent(xdata.display, &event); 

        switch(event.type) {
            case ClientMessage: {
                // Client Message Event
                char *typeName = XGetAtomName(xdata.display, event.xclient.type);
                printf("ClientMessageType: %lu, ClientMessageTypeName: %s\n", event.xclient.type, typeName);
                XFree(typeName);

                if(event.xclient.format == 32 ) {
                    // long data in event: currently assuming data is atom
                    char *dataAtomName = XGetAtomName(xdata.display, event.xclient.data.l[0]);
                    printf("ClientMessageData: %lu, ClientMessageDataName: %s\n", event.xclient.data.l[0], dataAtomName);
                    XFree(dataAtomName);

                    if(event.xclient.data.l[0] == xdata.wmProtocols_a[0]) {
                        // WM_DESTROY_WINDOW message (x button was pressed or equivalent)
                        running = false;
                    }
                }

                // Seperate per-message groups of output with newlines
                printf("\n");
                break;
            }

            default:
                break;
        }
    }

    // Destroy the window and close the display
    XDestroyWindow(xdata.display, xdata.window);
    XCloseDisplay(xdata.display);

    // Goodbye world
    return 0;
}
