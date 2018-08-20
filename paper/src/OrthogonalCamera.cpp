#include "stdafx.h"
#include "OrthogonalCamera.h"

void OrthogonalCamera::centerOn(float x, float y, float z, float width, float height, float depth){
	
	Vector3 low = Vector3(x-width*0.5, y-height*0.5, z-depth*0.5);
	Vector3 high = Vector3(x+width*0.5, y+height*0.5, z+depth*0.5);
	
	volume.set(low, high);
	
}

void OrthogonalCamera::setRange(float x0, float x1, float y0, float y1, float z0, float z1){
	//Vector3 low = Vector3(x0, y0, z0);
	//Vector3 high = Vector3(x1, y1, z1);
	Vector3 low = Vector3(x0, y0, z0);
	Vector3 high = Vector3(x1, y1, z1);
	volume.set(low, high);
}

void OrthogonalCamera::setHorisontalRange(float minR, float maxR){
	Vector3 low = volume.low();
	Vector3 high = volume.high();
	low.x = minR;
	high.x = maxR;
	volume.set(low, high);
}

void OrthogonalCamera::setVerticalRange(float minR, float maxR){
	Vector3 low = volume.low();
	Vector3 high = volume.high();
	low.y = minR;
	high.y = maxR;
	volume.set(low, high);
}

void OrthogonalCamera::setDepthRange(float minR, float maxR){
	Vector3 low = volume.low();
	Vector3 high = volume.high();
	low.z = minR;
	high.z = maxR;
	volume.set(low, high);
}

Rect2D OrthogonalCamera::getRect() const {
	Vector3 low = volume.low();
	Vector3 high = volume.high();
	return Rect2D::xyxy(low.xy(), high.xy());
}
