#include <cmath>

using namespace std;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 640;

class PointD2D {
public:
	PointD2D() {}
	PointD2D(double x, double y) { m_x = x; m_y = y; }
	double GetX() { return m_x; }
	double GetY() { return m_y; }
	void SetXY(double x, double y) { m_x = x; m_y = y; }
private:
	double m_x;
	double m_y;
};