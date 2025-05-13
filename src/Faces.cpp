#include <iostream>
#include "Faces.hpp"

Face::Face(vector<vector<PointD2D>> points) { 
	m_points = points; 
	m_nPoints = points.size();
	for (int k = 0; k < m_nPoints; k++) {
		vector<vector<double>> pXpY;
		for (int i = 0; i < 2; i++) {
			vector<double> point;
			for (int j = 0; j < 2; j++) {
				point.push_back(0);
			}
			pXpY.push_back(point);
		}
		m_screenP.push_back(pXpY);
	}
}

// Update all the points on the screen from the PointsD2D
void Face::UpdateScreenPoints(PointD2D cam, PointD2D F1, PointD2D F2, int axis, double offset) {
	for (int i = 0; i < m_nPoints; i++) {
		m_points[i][axis].SetXY(m_points[i][axis].GetX() + offset, m_points[i][axis].GetY());

		if (m_points[i][axis].GetX() - cam.GetX() != 0) {
			double mR = (m_points[i][axis].GetY() - cam.GetY()) / (m_points[i][axis].GetX() - cam.GetX());
			double mF = (F2.GetY() - F1.GetY()) / (F2.GetX() - F1.GetX());

			vector<vector<double>> M{
				{-mR, 1},
				{-mF, 1}
			};

			vector<double> N{
				-mR * cam.GetX() + cam.GetY(),
				-mF * F1.GetX() + F1.GetY()
			};

			vector<vector<double>> M2 = {
				{M[1][1] / (-mR + mF), -M[0][1] / (-mR + mF)},
				{-M[1][0] / (-mR + mF), M[0][0] / (-mR + mF)}
			};

			m_screenP[i][axis] = {
				M2[0][0] * N[0] + M2[0][1] * N[1],
				M2[1][0] * N[0] + M2[1][1] * N[1]
			};
			
		}
		else
			m_screenP[i][axis] = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
	}
}