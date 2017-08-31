#include "tmx_polyline.h"

namespace core { namespace tmx {

	TmxPolyline::TmxPolyline(XMLElement* polylineElem, int x, int y)
	{
		char *pointsLine = _strdup(polylineElem->Attribute("points"));

		char *next_token;
		char *token = strtok_s(pointsLine, " ", &next_token);
		while (token)
		{
			float px, py;
			sscanf_s(token, "%f,%f", &px, &py);

			int pointX = (int)px + x;
			int pointY = (int)py + y;

			this->m_Points.push_back(TmxPoint({ pointX, pointY }));

			token = strtok_s(0, " ", &next_token);
		}

		free(pointsLine);

		if (this->m_Points.size() < 3) // check if is a poligon
		{
			this->m_Points.clear();
		}
	}

	TmxPolyline::~TmxPolyline()
	{
		this->m_Points.clear();
	}

} }