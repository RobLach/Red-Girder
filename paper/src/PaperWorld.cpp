#include "stdafx.h"
#include "PaperWorld.h"

PaperWorld::PaperWorld(){
	setDrawShadows(true);
	//setCamera(Rect2D::xywh(0, 0, 10, 10));
}

PaperWorld::~PaperWorld(){
}

void PaperWorld::setCamera(const OrthogonalCameraRef &c) {
	camera = c;
}


void PaperWorld::setDrawShadows(bool state){
	drawShadows = state;
}


void PaperWorld::clear(){
	opaque.clear();
	transparent.clear();
	debugLines.clear();
}

void PaperWorld::present(PaperRenderable *r){
	if(r->isTransparent()){
		transparent.append(r);
	}else{
		opaque.append(r);
	}
}


bool __cdecl prLT(PaperRenderable * const &elem1, PaperRenderable * const &elem2) {
	return (*elem1) < (*elem2);
}

bool __cdecl prGT(PaperRenderable * const &elem1, PaperRenderable * const &elem2) {
	return (*elem1) > (*elem2);
}

void PaperWorld::finalize(){
	opaque.sort(prGT);

	transparent.sort(prLT);
}

void PaperWorld::loadCamera(RenderDevice *renderDevice){
    //renderDevice->setCameraToWorldMatrix(CoordinateFrame(Matrix3::identity(), Vector3(-0.375*vvp.width()/viewport.width(), -0.375*vvp.height()/viewport.height(), 0.0)));

	if(camera != 0){
		Vector3 low = camera->volume.low();
		Vector3 high = camera->volume.high();
		renderDevice->setProjectionMatrix(Matrix4::orthogonalProjection(low.x, high.x, high.y, low.y, low.z, high.z));
	}else{
		renderDevice->setProjectionMatrix(Matrix4::orthogonalProjection(0, 1024, 768, 0, -1, 1));
	}
}

void PaperWorld::debugLine(const Vector2 &p1, const Vector2 &p2, const Color4 &c1, const Color4 &c2) {
	debugLines.append(DebugLine(p1, p2, c1, c2));
}


void PaperWorld::draw(RenderDevice *renderDevice){
	int i;

	renderDevice->pushState();

	loadCamera(renderDevice);

	//renderDevice->enableColorWrite();
	//renderDevice->enableDepthWrite();
	//renderDevice->setAlphaTest(RenderDevice::ALPHA_GREATER, 0.01);
	renderDevice->setDepthTest(RenderDevice::DEPTH_LEQUAL);
	//renderDevice->setStencilTest(RenderDevice::STENCIL_ALWAYS_PASS);

	// Turn off blending.
	renderDevice->setBlendFunc(RenderDevice::BLEND_ONE, RenderDevice::BLEND_ZERO);

	// Draw opaque tiles.
	for(i=0;i<opaque.length();i++){
		opaque[i]->draw(renderDevice);
	}

	// Turn on blending.
	renderDevice->setBlendFunc(RenderDevice::BLEND_SRC_ALPHA, RenderDevice::BLEND_ONE_MINUS_SRC_ALPHA);

	// Draw shadows.
	if(drawShadows){
		renderDevice->setColor(Color4(0, 0, 0, 0.20));
		for(i=0;i<opaque.length();i++){
			if(opaque[i]->castsShadow()) opaque[i]->drawShadow(renderDevice);
		}

		for(i=0;i<transparent.length();i++){
			if(transparent[i]->castsShadow()) transparent[i]->drawShadow(renderDevice);
		}
	}

	// Draw alpha blended tiles.
	renderDevice->setColor(Color4(1, 1, 1, 1));
	for(i=0;i<transparent.length();i++){
		transparent[i]->draw(renderDevice);
	}


	/*
	// HACK: draw bounds.
	for(i=0;i<opaque.length();i++){
		opaque[i]->drawDebug(renderDevice);
	}

	for(i=0;i<transparent.length();i++){
		transparent[i]->drawDebug(renderDevice);
	}
	*/
	

	// Draw debugging lines.
	if(debugLines.length() > 0){
		renderDevice->setDepthTest(RenderDevice::DEPTH_ALWAYS_PASS);
		renderDevice->setTexture(0, 0);
		renderDevice->setObjectToWorldMatrix(CoordinateFrame());

		renderDevice->beginPrimitive(RenderDevice::LINES);
		for(i=0;i<debugLines.length();i++){
			renderDevice->setColor(debugLines[i].c1);
			renderDevice->sendVertex(debugLines[i].p1);
			renderDevice->setColor(debugLines[i].c2);
			renderDevice->sendVertex(debugLines[i].p2);
		}
		renderDevice->endPrimitive();
	}	

	renderDevice->popState();
}
