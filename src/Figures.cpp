#pragma once
#include <iostream>
#include "Figures.hpp"

// Update all Faces of the Figure
void Figure::UpdateScreenFaces(PointD2D cam, PointD2D F1, PointD2D F2, int axis, double offset) {
	for (int i = 0; i < m_nFaces; i++) {
		m_faces[i].UpdateScreenPoints(cam, F1, F2, axis, offset);
	}
}