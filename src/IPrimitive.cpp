#include "IPrimitive.h"

IPrimitive::IPrimitive(void)
{
	iRegistry = 0;
}

IPrimitive::~IPrimitive(void)
{
	vecLines.empty();
	vecPoints.empty();
	vecTriangles.empty();
}

void IPrimitive::DrawEverything()
{
	DrawLines();
	DrawPoints();
	DrawTriangles();
}

void IPrimitive::DrawLines()
{
	if (vecLines.size() > 0)
	{
		glPushMatrix();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_ALPHA_TEST);
			glTranslatef(0.0f, 0.0f, 0.0f);

				glBegin(GL_LINES);	
					std::vector<ILine>::iterator iter;
					for (iter = vecLines.begin(); iter != vecLines.end(); iter++)
					{
						glColor3f(iter->r, iter->g, iter->b);
						glVertex2d(iter->x1, iter->y1);
						glVertex2d(iter->x2, iter->y2);
					}
				glEnd();

			glEnable(GL_TEXTURE_2D);
			glEnable(GL_ALPHA_TEST);
		glPopMatrix();
	}
}

int IPrimitive::CreateLine(double x1, double y1, double x2, double y2, float r, float g, float b)
{
	iRegistry++;

	ILine tmpLine;
	tmpLine.x1 = x1;
	tmpLine.x2 = x2;
	tmpLine.y1 = y1;
	tmpLine.y2 = y2;
	tmpLine.r = r;
	tmpLine.g = g;
	tmpLine.b = b;
	tmpLine.no = iRegistry;

	vecLines.push_back(tmpLine);

	return iRegistry;
}

int IPrimitive::CreateLine(ILine *line)
{
	return CreateLine(line->x1, line->y1, line->x2, line->y2, line->r, line->g, line->b);
}

ILine * IPrimitive::GetLine(int iNo)
{
	std::vector<ILine>::iterator iter;
	for (iter = vecLines.begin(); iter != vecLines.end(); iter++)
	{
		if (iter->no == iNo)
		{
			return &*iter;
		}
	}
	return NULL;
}


void IPrimitive::DeleteLine(int iNo)
{
	std::vector<ILine>::iterator iter;
	iter = vecLines.begin();
	while ( iter != vecLines.end())
	{
		if (iter->no == iNo)
		{
			iter = vecLines.erase(iter);   
		}
		else iter++ ;
	}
}




void IPrimitive::DrawPoints()
{
	if (vecPoints.size() > 0)
	{
		glPushMatrix();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_ALPHA_TEST);
			glTranslatef(0.0f, 0.0f, 0.0f);

				glBegin(GL_POINTS);	
					std::vector<IPoint>::iterator iter;
					for (iter = vecPoints.begin(); iter != vecPoints.end(); iter++)
					{
						glColor3f(iter->r, iter->g, iter->b);
						glVertex2d(iter->x, iter->y);
					}
				glEnd();

			glEnable(GL_TEXTURE_2D);
			glEnable(GL_ALPHA_TEST);
		glPopMatrix();
	}
}

int IPrimitive::CreatePoint(float x, float y, float r, float g, float b)
{
	iRegistry++;

	IPoint tmpPoint;
	tmpPoint.x = x;
	tmpPoint.y = y;
	tmpPoint.r = r;
	tmpPoint.g = g;
	tmpPoint.b = b;
	tmpPoint.no = iRegistry;

	vecPoints.push_back(tmpPoint);

	return iRegistry;
}

int IPrimitive::CreatePoint(IPoint *point)
{
	return CreatePoint(point->x, point->y, point->r, point->g, point->b);
}

void IPrimitive::DeletePoint(int iNo)
{
	std::vector<IPoint>::iterator iter;
	iter = vecPoints.begin();
	while ( iter != vecPoints.end())
	{
		if (iter->no == iNo)
		{
			iter = vecPoints.erase(iter);   
		}
		else iter++ ;
	}
}

IPoint *IPrimitive::GetPoint (int iNo)
{
	std::vector<IPoint>::iterator iter;
	for (iter = vecPoints.begin(); iter != vecPoints.end(); iter++)
	{
		if (iter->no == iNo)
		{
			return &*iter;
		}
	}
	return NULL;
}









void IPrimitive::DrawTriangles()
{
	if (vecTriangles.size() > 0)
	{
		glPushMatrix();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_ALPHA_TEST);
			glTranslatef(0.0f, 0.0f, 0.0f);
				glBegin(GL_TRIANGLES);	
					std::vector<ITriangle>::iterator iter;
					for (iter = vecTriangles.begin(); iter != vecTriangles.end(); iter++)
					{
						glColor3f(iter->r, iter->g, iter->b);
						glVertex2d(iter->x1, iter->y1);
						glVertex2d(iter->x2, iter->y2);
						glVertex2d(iter->x3, iter->y3);
					}
				glEnd();
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_ALPHA_TEST);
		glPopMatrix();
	}
}

int IPrimitive::CreateTriangle(double x1, double y1, double x2, double y2, double x3, double y3, float r, float g, float b, bool wire)
{
	iRegistry++;

	ITriangle tmpTriangle;
	tmpTriangle.x1 = x1;
	tmpTriangle.y1 = y1;
	tmpTriangle.x2 = x2;
	tmpTriangle.y2 = y2;
	tmpTriangle.x3 = x3;
	tmpTriangle.y3 = y3;
	tmpTriangle.r = r;
	tmpTriangle.g = g;
	tmpTriangle.b = b;
	tmpTriangle.wireframe = wire;
	tmpTriangle.no = iRegistry;

	vecTriangles.push_back(tmpTriangle);

	return iRegistry;
}

int IPrimitive::CreateTriangle(ITriangle *triangle)
{
	return CreateTriangle(triangle->x1, triangle->y1, triangle->x2, triangle->y2, triangle->x3, triangle->y3, triangle->r, triangle->g, triangle->b, triangle->wireframe);
}

void IPrimitive::DeleteTriangle(int iNo)
{
	std::vector<ITriangle>::iterator iter;
	iter = vecTriangles.begin();
	while ( iter != vecTriangles.end())
	{
		if (iter->no == iNo)
		{
			iter = vecTriangles.erase(iter);   
		}
		else iter++ ;
	}
}

ITriangle *IPrimitive::GetTriangle (int iNo)
{
	std::vector<ITriangle>::iterator iter;
	for (iter = vecTriangles.begin(); iter != vecTriangles.end(); iter++)
	{
		if (iter->no == iNo)
		{
			return &*iter;
		}
	}
	return NULL;
}
