
#include <mvcgame/platform/linux/ApplicationBridge.hpp>
#include <mvcgame/base/Application.hpp>
#include <cassert>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

namespace mvcgame {

    ApplicationBridge::ApplicationBridge() :
    _app(nullptr), _finished(false)
    {
    }

    IRenderBridge& ApplicationBridge::getRender()
    {
        return _renderBridge;
    }

    IFilesystemBridge& ApplicationBridge::getFilesystem()
    {
        return _fsBridge;
    }

    void ApplicationBridge::exit()
    {
        _finished = true;
    }

    void ApplicationBridge::setApplication(Application& app)
    {
        _app = &app;
    }

    void ApplicationBridge::showError(const std::string& error)
    {
        printf("mvcgame error: %s\n", error.c_str());
    }

    void ApplicationBridge::run()
    {
        assert(_app);

        Display                 *dpy;
        Window                  root;
        GLint                   att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
        XVisualInfo             *vi;
        Colormap                cmap;
        XSetWindowAttributes    swa;
        Window                  win;
        GLXContext              glc;
        XWindowAttributes       gwa;
        XEvent                  xev;

        dpy = XOpenDisplay(NULL);
 
        if(dpy == NULL)
        {
            showError("cannot connect to X server");
            return;
        }
        
        root = DefaultRootWindow(dpy);
        vi = glXChooseVisual(dpy, 0, att);

        if(vi == NULL)
        {
            showError("no appropriate visual found");
            return;
        }

        const Size& size = _app->getSize();
        cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
        swa.colormap = cmap;
        swa.event_mask = ExposureMask | KeyPressMask;
        win = XCreateWindow(dpy, root, 0, 0, size.width, size.height, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
        XMapWindow(dpy, win);
        XStoreName(dpy, win, "mvcgame");
        glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
        glXMakeCurrent(dpy, win, glc);
 
        fd_set inFds;
        struct timeval tv;
        tv.tv_usec = 1000000.0f/60;
        tv.tv_sec = 0;
        int x11Fd = ConnectionNumber(dpy);

        while(!_finished)
        {
            FD_ZERO(&inFds);
            FD_SET(x11Fd, &inFds);
            select(x11Fd+1, &inFds, 0, 0, &tv);

            _app->update();

            while(XPending(dpy))
            {
                XNextEvent(dpy, &xev);
            }

            XGetWindowAttributes(dpy, win, &gwa);
            glViewport(0, 0, gwa.width, gwa.height);
            glXSwapBuffers(dpy, win);
        }

        glXMakeCurrent(dpy, None, NULL);
        glXDestroyContext(dpy, glc);
        XDestroyWindow(dpy, win);
        XCloseDisplay(dpy);
    }
}