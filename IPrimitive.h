#ifndef IPRIMITIVE_H
#define IPRIMITIVE_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>
#include <vector>
#include <algorithm>

struct ILine
{
	int no;
	double x1;
	double x2;
	double y1;
	double y2;
	float r;
	float g;
	float b;
};

struct IPoint
{
	int no;
	float x;
	float y;
	float r;
	float g;
	float b;
};

struct ITriangle
{
	int no;
	double x1;
	double y1;
	double x2;
	double y2;
	double x3;
	double y3;
	float r;
	float g;
	float b;
	bool wireframe;
};

class IPrimitive
{
public:
	IPrimitive(void);
	virtual ~IPrimitive(void);

	void   DrawEverything();

	void   DrawLines();
	int    CreateLine(double x1, double y1, double x2, double y2, float r, float g, float b);
	int    CreateLine(ILine *line);
	void   DeleteLine(int iNo);
	ILine  *GetLine(int iNo);

	void   DrawPoints ();
	int    CreatePoint(float x, float y, float r, float g, float b);
	int    CreatePoint(IPoint *point);
	void   DeletePoint(int iNo);
	IPoint *GetPoint (int iNo); 

	void   DrawTriangles ();
	int    CreateTriangle(double x1, double y1, double x2, double y2, double x3, double y3, float r, float g, float b, bool wire);
	int    CreateTriangle(ITriangle *triangle);
	void   DeleteTriangle(int iNo);
	ITriangle *GetTriangle (int iNo); 

private:
	std::vector<ILine>     vecLines;
	std::vector<IPoint>    vecPoints;
	std::vector<ITriangle> vecTriangles;

	int iRegistry;

};


#endif
