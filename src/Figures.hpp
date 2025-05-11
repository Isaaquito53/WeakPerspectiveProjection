#include <vector>
#include "Faces.hpp"

class Figure
{
public:
	Figure() { m_nFaces = 0; };
	Figure(vector<Face> faces) { m_faces = faces; m_nFaces = faces.size(); }
	void UpdateScreenFaces(PointD2D cam, PointD2D F1, PointD2D F2, int axis, double offset);

	vector<Face> m_faces;		// faces of the figure
	int m_nFaces;				// number of faces
};