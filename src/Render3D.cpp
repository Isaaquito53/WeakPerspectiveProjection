#pragma once
#include <SDL3/SDL.h>
#include <iostream>
#include "Figures.hpp"

// SQUARE:
// p1:
PointD2D pX1(WINDOW_WIDTH / 2 - 10, -8);
PointD2D pY1(WINDOW_HEIGHT / 2 - 10, -8);
// p2:
PointD2D pX2(WINDOW_WIDTH / 2 + 10, -8);
PointD2D pY2(WINDOW_HEIGHT / 2 -10, -8);
// p3:
PointD2D pX3(WINDOW_WIDTH / 2 + 10, -8);
PointD2D pY3(WINDOW_HEIGHT / 2 + 10, -8);
// p4:
PointD2D pX4(WINDOW_WIDTH / 2 - 10, -8);
PointD2D pY4(WINDOW_HEIGHT / 2 + 10, -8);
// p5:
PointD2D pX5(WINDOW_WIDTH / 2 - 10, -7);
PointD2D pY5(WINDOW_HEIGHT / 2 - 10, -7);
// p6:
PointD2D pX6(WINDOW_WIDTH / 2 + 10, -7);
PointD2D pY6(WINDOW_HEIGHT / 2 - 10, -7);
// p7:
PointD2D pX7(WINDOW_WIDTH / 2 + 10, -7);
PointD2D pY7(WINDOW_HEIGHT / 2 + 10, -7);
// p8:
PointD2D pX8(WINDOW_WIDTH / 2 - 10, -7);
PointD2D pY8(WINDOW_HEIGHT / 2 + 10, -7);

// face1:
Face face1({
	{pX1, pY1},
	{ pX2, pY2 },
	{ pX3, pY3 },
	{ pX4, pY4 }
	});

// face2:
Face face2({
	{pX5, pY5},
	{ pX6, pY6 },
	{ pX7, pY7 },
	{ pX8, pY8 }
	});

// fig1:
Figure fig1({ face1, face2 });

int main() {
	bool run = true;
	// F1 and F2 are the two points of the screen cone
	PointD2D F1(0, 0);
	PointD2D F2(WINDOW_WIDTH, 0);
	// FOV is the distance between the camera and the "screen"
	int FOV = 10;
	PointD2D cam(WINDOW_WIDTH / 2, -FOV);

	fig1.UpdateScreenFaces(cam, F1, F2, 0, 0);		// 4th parameter --> axis (0=X, 1=Y)
	fig1.UpdateScreenFaces(cam, F1, F2, 1, 0);

	SDL_Event e;
	static SDL_Window* window = NULL;
	static SDL_Renderer* renderer = NULL;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer("Demo", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);

	while(run){
		// MANAGE EVENTS
		while (SDL_PollEvent(&e)) {
			// MANAGE QUIT
			if (e.type == SDL_EVENT_QUIT) {
				cout << "F";
				run = false;
			}
			if (e.type == SDL_EVENT_KEY_DOWN) {
				// GO RIGHT
				if (e.key.scancode == SDL_SCANCODE_KP_3) {
					fig1.UpdateScreenFaces(cam, F1, F2, 0, -10);
				}
				// GO LEFT
				if (e.key.scancode == SDL_SCANCODE_KP_1) {
					fig1.UpdateScreenFaces(cam, F1, F2, 0, 10);
				}
				// GO DOWN
				if (e.key.scancode == SDL_SCANCODE_KP_4) {
					fig1.UpdateScreenFaces(cam, F1, F2, 1, 10);
				}
				// GO UP
				if (e.key.scancode == SDL_SCANCODE_KP_6) {
					fig1.UpdateScreenFaces(cam, F1, F2, 1, -10);
				}
				// WALK BACKWARDS
				if (e.key.scancode == SDL_SCANCODE_KP_2) {
					if (FOV < 20) {
						FOV++;
						cam.SetXY(cam.GetX(), -FOV);
						fig1.UpdateScreenFaces(cam, F1, F2, 0, 0);
						fig1.UpdateScreenFaces(cam, F1, F2, 1, 0);
					}
				}
				// WALK 
				if (e.key.scancode == SDL_SCANCODE_KP_5) {
					if (FOV > 9) {
						FOV--;
						cam.SetXY(cam.GetX(), -FOV);
						fig1.UpdateScreenFaces(cam, F1, F2, 0, 0);
						fig1.UpdateScreenFaces(cam, F1, F2, 1, 0);
					}
				}
			}
		}
		SDL_SetRenderDrawColorFloat(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColorFloat(renderer, 255,255,255, 255);
		SDL_SetRenderScale(renderer, 4, 4);
		// For each face of the figure
		for (int k = 0; k < fig1.m_nFaces; k++) {
			// Draw a point in for each point of the k-face
			for (int i = 0; i < fig1.m_faces[k].m_nPoints; i++) {
				// Discard z-axis (never ...[i][0/1][1] because this last [1] is the z-axis)
				SDL_RenderPoint(renderer, fig1.m_faces[k].m_screenP[i][0][0] / 4, fig1.m_faces[k].m_screenP[i][1][0] / 4);
			}
		}
		SDL_SetRenderScale(renderer, 1, 1);
		// For each face of the figure
		int i = 0;
		for (int k = 0; k < fig1.m_nFaces; k++) {
			// Draw a line between all the points
			i = 1;
			for (i; i < fig1.m_faces[k].m_nPoints; i++) {
				SDL_RenderLine(renderer,
					fig1.m_faces[k].m_screenP[i - 1][0][0], fig1.m_faces[k].m_screenP[i - 1][1][0],
					fig1.m_faces[k].m_screenP[i][0][0], fig1.m_faces[k].m_screenP[i][1][0]);
			}
			SDL_RenderLine(renderer,
				fig1.m_faces[k].m_screenP[i-1][0][0], fig1.m_faces[k].m_screenP[i-1][1][0],
				fig1.m_faces[k].m_screenP[0][0][0], fig1.m_faces[k].m_screenP[0][1][0]);
		}
		// Draw a line between every point of each face to create the cube
		i = 0;
		for (i; i < fig1.m_faces[0].m_nPoints; i++) {
			SDL_RenderLine(renderer,
				fig1.m_faces[0].m_screenP[i][0][0], fig1.m_faces[0].m_screenP[i][1][0],
				fig1.m_faces[1].m_screenP[i][0][0], fig1.m_faces[1].m_screenP[i][1][0]);
		}
		SDL_RenderPresent(renderer);
	}

	return 0;
}