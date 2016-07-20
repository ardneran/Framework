//
//  NativeWindow.h
//  Framework
//
//  Created by Narendra Umate on 7/17/16.
//
//

#ifndef NativeWindow_h
#define NativeWindow_h

#include <cassert>

#include "AbstractWindow.h"

#include "Native.h"

struct Parameters;

class NativeWindow : public AbstractWindow {
    
public:
    NativeWindow(Parameters& parameters);
    virtual ~NativeWindow() = 0;
    
    void handlePollEvent();
    
    virtual void setSwapInterval(const int& syncInterval);
    virtual void swapWindow();
    
    static std::map<Nativewindow*, NativeWindow*> s_windowMap;
    
private:
    void initializeNative();
    void initializeMetal();
    void deinitializeNative();
    void deinitializeMetal();
    
    Nativewindow* m_nativeWindow;
};

#endif /* NativeWindow_h */
