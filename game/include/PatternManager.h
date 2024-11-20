//===========================================================
//========== Touch & Brush - Final Degree Project ===========
//======== Carla Maciá Díez - University of Alicante ========
//===========================================================

#include "Vector2D.h"
#include <vector>
#include <math.h>

#define M(a,b)  Vector2D((a), (b))
#define ANCHOR_POINTS 6

//Ideal patterns
const Vector2D h_line[ANCHOR_POINTS] {M(0, 96),
										M(50, 96),
										M(100, 96),
										M(151, 96),
										M(202, 96),
										M(254, 96)};

const Vector2D v_line[ANCHOR_POINTS] {M(128, 0),
										M(128, 38),
										M(128, 76),
										M(128, 115),
										M(128, 153),
										M(128, 192)};

const Vector2D triangle[ANCHOR_POINTS] {M(125, 56),
										M(180, 103),
										M(179, 115),
										M(83, 116),
										M(100, 75),
										M(115, 50)};

const Vector2D heart[ANCHOR_POINTS] {M(109, 150),
										M(48, 101),
										M(91, 64),
										M(83, 58),
										M(151, 99),
										M(114, 156)};

const Vector2D cm_shapes[3] {M(128,95),
							 M(126,96),
							 M(130,85)};

class PatternManager{
	public:
		PatternManager();
		PatternManager(const PatternManager&);
		virtual ~PatternManager();
		float checkPattern(const Vector2D[]); //comprueba un patron especifico
		int checkPattern(); //comprueba todos los patrones y devuelve un entero al mas parecido
		void insertPoint(int, int);
		void clearPattern();
		void calculateCenterOfMass();
		int findNearest(int, int, const Vector2D[]);

	private:

		//center of mass of the user stroke
		int x_cm;
		int y_cm;
		//center of mass of the ideal stroke
		int x_cm_s;
		int y_cm_s;
		//user stroke
		std::vector<Vector2D*> user_pattern;
};