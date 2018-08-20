#include "stdafx.h"

#include "Tile.h"

#include "PaperWorld.h"

void PaperRenderable::present(PaperWorld * const world) {
	world->present(this);
}


Tile::Tile(){
	t = NixTextureRef();
	setColor(1, 1, 1, 1);
	setTranslation(0, 0, 0);
	setDepth(0);
}

void Tile::setXY(float ix, float iy){
	x = ix;
	y = iy;
}

void Tile::setSize(float iw, float ih){
	w = iw;
	h = ih;
}

void Tile::setDepth(float id){
	d = id;
}

float Tile::getDepth() const {
	return d;
}


void Tile::setTranslation(float tx, float ty, float ta) {
	cframe = CoordinateFrame(Matrix3::fromEulerAnglesXYZ(0, 0, ta), Vector3(tx, ty, 0));
}

void Tile::setTexture(const NixTextureRef &tex){
	t = tex;
}

void Tile::setColor(const Color4 &c){
	color = c;
}


void Tile::setColor(float r, float g, float b, float a){
	setColor(Color4(r, g, b, a));
}

bool Tile::isTransparent() const{
	if(t != 0){
		return !t->texture->opaque() || color.a < 0.999;
	}else{
		return color.a < 0.999;
	}
}


void Tile::setCastsShadow(bool casts){
	doesCastShadow = casts;
}

void Tile::bindTexture(RenderDevice * const r) const {
	if(t == 0){
		r->setTexture(0, 0);
	}else{
		r->setTexture(0, t->texture);
	}
}


void Tile::draw(RenderDevice * const r){
	bindTexture(r);

	r->setColor(color);
	r->setObjectToWorldMatrix(cframe);
	r->beginPrimitive(RenderDevice::QUADS);

	r->setTexCoord(0, Vector2(0, 0));
	r->sendVertex(Vector3(x, y, d));

	r->setTexCoord(0, Vector2(1, 0));
	r->sendVertex(Vector3(x+w, y, d));

	r->setTexCoord(0, Vector2(1, 1));
	r->sendVertex(Vector3(x+w, y+h, d));

	r->setTexCoord(0, Vector2(0, 1));
	r->sendVertex(Vector3(x, y+h, d));
	r->endPrimitive();
}

void Tile::drawDebug(RenderDevice * const r) {
	r->setTexture(0, 0);

	r->setColor(color);
	r->setObjectToWorldMatrix(cframe);
	r->beginPrimitive(RenderDevice::LINE_STRIP);

	r->sendVertex(Vector3(x, y, d));
	r->sendVertex(Vector3(x+w, y, d));
	r->sendVertex(Vector3(x+w, y+h, d));
	r->sendVertex(Vector3(x, y+h, d));
	r->sendVertex(Vector3(x, y, d));

	r->endPrimitive();
}

void Tile::drawShadow(RenderDevice * const r){
	if(!doesCastShadow) return;

	bindTexture(r);

	r->setObjectToWorldMatrix(cframe);
	r->beginPrimitive(RenderDevice::QUADS);

	int iterations = 5;

	Vector3 off = cframe.normalToObjectSpace(Vector3(0.05, 0.05, -0.2)*3.0/iterations);

	float zProj = -0.8f;

	for(int i=1;i<iterations;i++){
		float xOff = off.x*i;
		float yOff = off.y*i;
		float zOff = off.z*i;

		r->setTexCoord(0, Vector2(0, 0));
		r->sendVertex(Vector3(x+xOff,	y+yOff,		zProj));

		r->setTexCoord(0, Vector2(1, 0));
		r->sendVertex(Vector3(x+w+xOff, y+yOff,		zProj));

		r->setTexCoord(0, Vector2(1, 1));
		r->sendVertex(Vector3(x+w+xOff, y+h+yOff,	zProj));

		r->setTexCoord(0, Vector2(0, 1));
		r->sendVertex(Vector3(x+xOff,	y+h+yOff,	zProj));
	}
	
	r->endPrimitive();
}

bool Tile::castsShadow() const{
	return doesCastShadow;
}

void Tile::center() {
	setXY(-w*0.5, -h*0.5);
}

/** @todo Make take rotation into account. */
bool Tile::contains(float px, float py) const {

	Vector3 localP = cframe.pointToObjectSpace(Vector3(px, py, 0));
	
	return localP.x >= x && localP.y >= y && localP.x < x+w && localP.y < y+h;

	//return min(px-x, py-y) >= 0 && min(x+w-px, y+h-py) > 0;
}


Text::Text(){
	setTranslation(0, 0, 0);
	setDepth(0.9999);
	setColor(1, 1, 1, 1);
	setOutlineColor(0, 0, 0, 1);
	setXY(0, 0);
}

void Text::draw(RenderDevice * const r){
	
	if(font != 0){
		r->pushState();
		//CoordinateFrame cframe = r->getObjectToWorldMatrix();
		CoordinateFrame cframe = CoordinateFrame();

		cframe.translation.z = pos.z;
		r->setObjectToWorldMatrix(cframe);

		font->font->draw2D(r, message, pos.xy()+Vector2(ox, oy), size, color, outline);

		r->popState();
	}

	// Hack
	//font->draw3D(r, message, Vector3(x, y, 0.999), 12, Color3::white(), Color3::black());
}

void Text::drawShadow(RenderDevice * const r) {
}

void Text::drawDebug(RenderDevice * const r) {
}

bool Text::isTransparent() const {
	return true;
}

bool Text::castsShadow() const {
	return false;
}

void Text::setXY(float ix, float iy){
	ox = ix;
	oy = iy;
}

void Text::center(){
	float w, h;
	getBounds(&w, &h);
	setXY(-w*0.5, -h*0.5);
}


float Text::getDepth() const {
	return pos.z;
}

void Text::setDepth(float depth) {
	pos.z = depth;
}

void Text::setTranslation(float tx, float ty, float ta) {
	pos.x = tx;
	pos.y = ty;
	/** Angle is currently ignored. */
}

void Text::setFont(const NixFontRef &f, float s){
	font = f;
	size = s;
}

void Text::setColors(const Color4 &main, const Color4 &border) {
	color = main;
	outline = border;
}


void Text::setColor(float r, float g, float b, float a){
	setColor(Color4(r, g, b, a));
}

void Text::setOutlineColor(float r, float g, float b, float a){
	setOutlineColor(Color4(r, g, b, a));
}

void Text::setColor(const Color4 &c){
	color = c;
}

void Text::setOutlineColor(const Color4 &o){
	outline = o;
}


void Text::getBounds(float *width, float *height){
	if(font != 0){
		Vector2 b = font->font->get2DStringBounds(message, size);
		*width	= b.x;
		*height	= b.y;
	}else{
		width = 0;
		height = 0;
	}
}

void Text::setText(std::string text) {
	message = text;
}

/** @todo Make return somthing other than false. */
bool Text::contains(float x, float y) const {
	return false;
}