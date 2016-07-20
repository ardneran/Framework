//
//  AbstractWindow.h
//  Framework
//
//  Created by Narendra Umate on 2/21/16.
//
//

#ifndef AbstractWindow_h
#define AbstractWindow_h

#include "Camera.h"
#include "Culler.h"
#include "ObjMeshLoader.h"
#include "Renderer.h"

class Renderer;

struct Parameters {
	Parameters()
	: title("")
	, xOrigin(0)
	, yOrigin(0)
	, xSize(0)
	, ySize(0)
	, renderer(NULL) {
	}
	std::string title;
	int xOrigin;
	int yOrigin;
	int xSize;
	int ySize;
	Renderer* renderer;
};

class AbstractWindow {

public:

	AbstractWindow(Parameters& parameters);
	virtual ~AbstractWindow() = 0;

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

	inline Camera* getCamera() { return m_camera; }

	inline bool isMinimized() const { return m_minimized; }
	inline bool isMaximized() const { return m_maximized; }
	inline bool isActive() const { return m_active; }

	virtual void onMove(const int& x, const int& y);
	virtual bool onResize(const int& xSize, const int& ySize);
	virtual void onMinimize();
	virtual void onMaximize();
	virtual void onRestore();
	virtual void onDisplay();
	virtual void onIdle();
    virtual void onClose();

	virtual void setSwapInterval(const int& syncInterval) = 0;
	virtual void swapWindow() = 0;

protected:
	std::string m_title;
	int m_xOrigin;
	int m_yOrigin;
	int m_xSize;
	int m_ySize;
	Renderer* m_renderer;

	bool m_minimized;
	bool m_maximized;
	bool m_active;

	Camera* m_camera;
	Culler* m_culler;
	Octree* m_octree;
	ObjMeshLoader* m_objMeshLoader;

	// TODO Convert to a list.
	VisualEffect* m_visualEffects[3];
};

#endif /* AbstractWindow_h */
