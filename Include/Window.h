//
//  Window.h
//  
//
//  Created by Narendra Umate on 8/17/15.
//
//

#ifndef ____Window__
#define ____Window__

#include <string>
#include <SDL.h>

class Window {
public:
	struct Parameters {
		Parameters()
		:	title("")
		,	xOrigin(0)
		,	yOrigin(0)
		,	xSize(0)
		,	ySize(0) {
		}
		std::string title;
		int xOrigin, yOrigin, xSize, ySize;
	};

	virtual ~Window();

	inline void setTitle(const std::string& title) { m_title = title; }
	inline std::string getTitle() { return m_title; }
	inline void setXOrigin(const int& xOrigin) { m_xOrigin = xOrigin; }
	inline int getXOrigin() { return m_xOrigin; }
	inline void setYOrigin(const int& yOrigin) { m_yOrigin = yOrigin; }
	inline int getYOrigin() { return m_yOrigin; }
	inline void setXSize(const int& xSize) { m_xSize = xSize; }
	inline int getXSize() { return m_xSize; }
	inline void setYSize(const int& ySize) { m_ySize = ySize; }
	inline int getYSize() { return m_ySize; }
	inline bool isMinimized() const { return m_minimized; }
	inline bool isMaximized() const { return m_maximized; }
	inline bool isActive() const { return m_active; }

	// Display callbacks
	virtual void onMove(const int& x, const int& y);
	virtual bool onResize(const int& xSize, const int& ySize);
	virtual void onMinimize();
	virtual void onMaximize();
	virtual void onRestore();
	virtual void onDisplay();
	virtual void onIdle();

protected:
	// Abstract base class
	Window(Parameters& parameters);

	std::string m_title;
	int m_xOrigin, m_yOrigin, m_xSize, m_ySize;
	bool m_minimized, m_maximized, m_active;

private:
	void handleEvent(const SDL_Event& event);
	void handleWindowEvent(const SDL_Event& event);
	void handleKeyUpEvent(const SDL_Event& event);
	void handleKeyDownEvent(const SDL_Event& event);

	SDL_Window* sdlWindow;
};

#endif /* defined(____Window__) */
