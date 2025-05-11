#include <vector>
#include "Points.hpp"

class Face {
public:
	Face() { m_nPoints = 0; }
	Face(vector<vector<PointD2D>> points);
	void UpdateScreenPoints(PointD2D cam, PointD2D F1, PointD2D F2, int axis, double offset);

	// each face has a 3D point, each 3D has 2 PointD2D
	// the first Point2D2 has X and Z axis
	// the second one has Y and Z axis
	// the Z axis will be discarded when drawing, but is necessary to move to the 3rd dimension

	vector<vector<PointD2D>> m_points;				// points of the face
	vector<vector<vector<double>>> m_screenP;		// points of the face on the screen
	int m_nPoints;									// number of points
};	