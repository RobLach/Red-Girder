#include "stdafx.h"
#include "Renderer.h"

Renderer::Renderer(){
	renderDevice = 0;
	setDrawShadows(true);

	defaultOverlayCamera.reset(new OrthogonalCamera());
	defaultWorldCamera.reset(new OrthogonalCamera());

	defaultOverlayCamera->setRange(0, 800, 0, 600, -1, 1);
	defaultWorldCamera->setRange(0, 1.5, 0, 1.5, -1, 1);

	overlayWorld.setCamera(defaultOverlayCamera);
	renderWorld.setCamera(defaultWorldCamera);

	worldViewportRect = Rect2D::xywh(0, 0, 0, 0);
	overlayViewportRect = Rect2D::xywh(0, 0, 0, 0);

}

Renderer::~Renderer(){
}

PaperWorld * Renderer::getGameWorld() {
	return &renderWorld;
}

PaperWorld * Renderer::getOverlayWorld() {
	return &overlayWorld;
}

void Renderer::setDrawShadows(bool state){
	renderWorld.setDrawShadows(state);
}


void Renderer::initRenderDevice(){
	renderDevice = RenderDevice::lastRenderDeviceCreated;  // HACK

	// Set up the render device in a reasonable manner.
	renderDevice->enableColorWrite();
	renderDevice->enableDepthWrite();
	renderDevice->setAlphaTest(RenderDevice::ALPHA_GREATER, 0.01);
	//renderDevice->setAlphaTest(RenderDevice::ALPHA_ALWAYS_PASS, 0);
	renderDevice->setDepthTest(RenderDevice::DEPTH_LEQUAL);
	renderDevice->setStencilTest(RenderDevice::STENCIL_ALWAYS_PASS);
	renderDevice->setBlendFunc(RenderDevice::BLEND_ONE, RenderDevice::BLEND_ZERO);

	//renderDevice->setColorClearValue(Color4(1, 0, 0, 1));
	//renderDevice->setDepthClearValue(1000);
}

void Renderer::beginRender(){
	if(!renderDevice){
		initRenderDevice();
	}

	renderWorld.clear();
	overlayWorld.clear();

	// Move to finish?
	renderDevice->beginFrame();
	renderDevice->clear();
}

Rect2D Renderer::worldViewport(){
	if(!renderDevice){
		initRenderDevice();
	}

	if(worldViewportRect.width() == 0){
		debugAssertM(renderDevice != 0, "Null render device!");

		int screenWidth = renderDevice->width();
		int screenHeight = renderDevice->height();
		//int screenMinor = min(screenWidth, screenHeight);
		//return Rect2D::xywh((screenWidth-screenMinor)/2, (screenHeight-screenMinor)/2, screenMinor, screenMinor);
		worldViewportRect = Rect2D::xywh(0, 0, screenWidth, screenHeight);
	}

	return worldViewportRect;
}

Rect2D Renderer::overlayViewport(){
	if(!renderDevice){
		initRenderDevice();
	}
	if(overlayViewportRect.width() == 0){
		debugAssertM(renderDevice != 0, "Null render device!");

		int screenWidth = renderDevice->width();
		int screenHeight = renderDevice->height();

		overlayViewportRect = Rect2D::xywh(0, 0, screenWidth, screenHeight);
	}
	return overlayViewportRect;
}

Vector2 Renderer::map(const Vector2 &pos, const Rect2D &from, const Rect2D &to) const {
	Vector2 mapped = pos;
	Vector2 scale = Vector2(to.width()/from.width(), to.height()/from.height());

	mapped -= from.corner(0);
	mapped *= scale;
	mapped += to.corner(0);

	return mapped;
}


Vector2 Renderer::screenToWorld(float x, float y) {
	return screenToWorld(Vector2(x, y));
}


Vector2 Renderer::screenToWorld(const Vector2 &pos) {
	Rect2D viewport = worldViewport();
	Rect2D camera = renderWorld.getCamera()->getRect();

	return map(pos, viewport, camera);
}


Vector2 Renderer::screenToOverlay(float x, float y) {
	return screenToOverlay(Vector2(x, y));
}


Vector2 Renderer::screenToOverlay(const Vector2 &pos) {
	Rect2D viewport = overlayViewport();
	Rect2D camera	= overlayWorld.getCamera()->getRect();

	return map(pos, viewport, camera);
}

Vector2 Renderer::worldToOverlay(float x, float y) {
	return worldToOverlay(Vector2(x, y));
}

Vector2 Renderer::worldToOverlay(const Vector2 &pos) {
	//Vector2 worldPos = pos;

	Rect2D oviewport = overlayViewport();
	Rect2D ocamera	= overlayWorld.getCamera()->getRect();

	Rect2D wviewport = worldViewport();
	Rect2D wcamera = renderWorld.getCamera()->getRect();

	return map(map(pos, wcamera, wviewport), oviewport, ocamera);
}



void Renderer::endRender(){
	// Make sure everything is sorted, etc.
	renderWorld.finalize();
	overlayWorld.finalize();

	renderDevice->push2D();

	// Draw in a square area.
	renderDevice->setViewport(worldViewport());
	renderWorld.draw(renderDevice);

	// Draw in the entire window.
	renderDevice->setViewport(overlayViewport());
	overlayWorld.draw(renderDevice);

	renderDevice->pop2D();

	renderDevice->endFrame();

	// Make sure references get destroyed.
	renderWorld.clear();
	overlayWorld.clear();
}