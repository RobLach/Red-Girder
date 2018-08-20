#ifndef RENDERER_H
#define RENDERER_H

#include "PaperWorld.h"

/** A 2D render that can generate drop shadows. */
class Renderer { //tolua_export
public:
	//tolua_begin
	Renderer();
	~Renderer();

	void beginRender();
	void endRender();

	void setDrawShadows(bool state);

	PaperWorld * getGameWorld();
	PaperWorld * getOverlayWorld();

	Rect2D worldViewport();
	Rect2D overlayViewport();

	Vector2 screenToWorld(const Vector2 &pos);
	Vector2 screenToOverlay(const Vector2 &pos);
	Vector2 worldToOverlay(const Vector2 &pos);

	Vector2 screenToWorld(float x, float y);
	Vector2 screenToOverlay(float x, float y);
	Vector2 worldToOverlay(float x, float y);


	//tolua_end
protected:
	Vector2 map(const Vector2 &pos, const Rect2D &from, const Rect2D &to) const;

	Rect2D worldViewportRect, overlayViewportRect;

	void initRenderDevice();

	RenderDevice *renderDevice;

	PaperWorld overlayWorld;
	PaperWorld renderWorld;

	OrthogonalCameraRef defaultOverlayCamera;
	OrthogonalCameraRef defaultWorldCamera;

}; //tolua_export

#endif // RENDERER_H