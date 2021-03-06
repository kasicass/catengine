#include "SphereWorld.h"
#include "Tracers/MultiObjects.h"
#include "Utility/Vector3D.h"
#include "Utility/Ray.h"
#include <stdlib.h>
#include <assert.h>

SphereWorld::SphereWorld()
{}

SphereWorld::~SphereWorld()
{}

void SphereWorld::build()
{
	vp_.setHRes(400);
	vp_.setVRes(400);
	vp_.setPixelSize(1.0f);
	vp_.setGamma(1.8f);

	pTracer_ = new MultiObjects(this);

	Sphere *sphere = new Sphere;
	sphere->setCenter(0.0, 0.0, 0.0);
	sphere->setRadius(85.0);
	sphere->setColor(RGBColor::BLUE);
	addObject(sphere);
}

void SphereWorld::renderSceneInternal()
{
	RGBColor pixelColor;
	Ray ray;
	double zw = 100.0;
	double x, y;

	ray.d = Vector3D(0, 0, -1);

	for (int r = 0; r < vp_.vRes; r++)
	{
		for (int c = 0; c < vp_.hRes; c++)
		{
			x = vp_.s * (c - 0.5 * (vp_.hRes - 1.0));
			y = vp_.s * (0.5 * (vp_.vRes - 1.0) - r);
			ray.o = Point3D(x, y, zw);
			pixelColor = pTracer_->traceRay(ray);
			displayPixel(c, r, pixelColor);
		}
	}
}

