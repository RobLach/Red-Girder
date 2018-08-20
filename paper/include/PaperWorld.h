#ifndef NIX_RENDERERWORLD2D_H
#define NIX_RENDERERWORLD2D_H

#include "Tile.h"
#include "OrthogonalCamera.h"

struct DebugLine {
public:
	DebugLine() {
	}

	DebugLine(const Vector2 &p1, const Vector2 &p2, const Color4 &c1 , const Color4 &c2) : p1(p1), p2(p2), c1(c1), c2(c2){
	}

	Vector2 p1, p2;
	Color4 c1, c2;
};

/** A 2D render that can generate fake drop shadows. */
class PaperWorld { //tolua_export
public:
	PaperWorld();
	~PaperWorld();

	/** Sets the area of worldspace that is rendered.  Where and 
	how large this area appears on the screen is controled elsewhere.*/
	void setCamera(const OrthogonalCameraRef &c);

	/** Discards retained renderables.  Does not clear or affect the screen in any way. */
	void clear();

	//tolua_begin

	/** Only stores a reference to the renderable, so do NOT destroy any renderables before clear() is called. */
	void present(PaperRenderable *r);

	//tolua_end

	/** Once all the renderables have been added, sort them. */
	void finalize();

	void draw(RenderDevice *renderDevice);

	void setDrawShadows(bool state);

	OrthogonalCameraRef getCamera() {
		return camera;
	}

	void debugLine(const Vector2 &p1, const Vector2 &p2, const Color4 &c1 = Color4(1, 0, 0, 1), const Color4 &c2 = Color4(1, 0, 0, 1));

protected:
	OrthogonalCameraRef camera;

	void loadCamera(RenderDevice *renderDevice);

	Array<PaperRenderable *> opaque;
	Array<PaperRenderable *> transparent;

	Array<DebugLine> debugLines;

	bool drawShadows;
}; //tolua_export

#endif // RENDERERWORLD2D_H