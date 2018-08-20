#ifndef NIX_TILE_H
#define NIX_TILE_H

#include "Resource.h"

class PaperWorld;

class PaperRenderable {
public:
	virtual void setXY(float ix, float iy) = 0;
	virtual void center() = 0;
	virtual void setTranslation(float tx, float ty, float ta) = 0;


	virtual void draw(RenderDevice * const r) = 0;
	virtual void drawShadow(RenderDevice * const r) = 0;

	virtual void drawDebug(RenderDevice * const r) = 0;

	virtual bool isTransparent() const = 0;
	virtual bool castsShadow() const = 0;

	virtual void setDepth(float depth) = 0;
	virtual float getDepth() const = 0;

	virtual bool contains(float x, float y) const = 0;

	virtual void present(PaperWorld * const world);

	bool operator>(const PaperRenderable &other) const {
		return getDepth() > other.getDepth();
	};

	bool operator<(const PaperRenderable &other) const {
		return getDepth() < other.getDepth();
	};
};

class Tile : public PaperRenderable { //tolua_export
public:
	//tolua_begin
	Tile();

	void setXY(float ix, float iy);
	void center();

	void setSize(float iw, float ih);

	void setTexture(const NixTextureRef &tex);
	void setColor(float r, float g, float b, float a);

	void setCastsShadow(bool casts);

	bool isTransparent() const;
	bool castsShadow() const;

	void draw(RenderDevice * const r);
	void drawShadow(RenderDevice * const r);
	void drawDebug(RenderDevice * const r);

	void setDepth(float id);
	float getDepth() const;
	void setTranslation(float tx, float ty, float ta);

	bool contains(float x, float y) const;

	//tolua_end

	void setColor(const Color4 &color);

protected:
	void bindTexture(RenderDevice * const r) const;

	CoordinateFrame cframe;
	float x, y, w, h, d;
	NixTextureRef t;
	bool doesCastShadow;
	Color4 color;
}; //tolua_export


class Text : public PaperRenderable { //tolua_export
public:
	//tolua_begin
	Text();

	void setXY(float ix, float iy);
	void center();
	void setDepth(float depth);

	void setTranslation(float tx, float ty, float ta);

	void setColor(float r, float g, float b, float a=1);
	void setOutlineColor(float r, float g, float b, float a=1);

	void setFont(const NixFontRef &f, float s);
	void setText(std::string text);

	void getBounds(float *width = 0, float *height = 0);

	bool contains(float x, float y) const;

	//tolua_end

	void setColors(const Color4 &main, const Color4 &border);
	void setColor(const Color4 &c);
	void setOutlineColor(const Color4 &o);

	bool isTransparent() const;
	bool castsShadow() const;

	void draw(RenderDevice * const r);
	void drawShadow(RenderDevice * const r);
	void drawDebug(RenderDevice * const r);


	float getDepth() const;

protected:
	NixFontRef font;
	Color4 color, outline;
	Vector3 pos;
	float ox, oy;
	float size;
	std::string message;
}; //tolua_export

#endif // TILE_H