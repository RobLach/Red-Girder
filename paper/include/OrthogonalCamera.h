#ifndef ORTHOGONALCAMERA_H
#define ORTHOGONALCAMERA_H

#include "SmartPtr.h"

typedef SmartPointerRef<class OrthogonalCamera> OrthogonalCameraRef;

class OrthogonalCamera : public SmartPointerBase {
public:

	void centerOn(float x, float y, float z, float width, float height, float depth);

	void setRange(float x0, float x1, float y0, float y1, float z0, float z1);

	void setHorisontalRange(float minR, float maxR);

	void setVerticalRange(float minR, float maxR);

	void setDepthRange(float minR, float maxR);

	Rect2D getRect() const;

	AABox volume;
};

#endif
