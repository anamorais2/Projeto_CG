#pragma once

#include "ofMain.h"
#include "cg_extras.h"
#include "cg_drawing_extras.h"
#include "materiais.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void exit();
		
		//floor
		GLint resX, resY;
		GLfloat floorWidth, floorHeight, floorHeightPos;

		//base prédio
		GLfloat baseWidth, baseDepth, baseHeight;
		GLint basePosX, basePosY;
		ofVec3f basePos;


		//view
		int view;

		//Controlo perspetiva
		bool perspectiveView;

		//Rotação segundo as setas
		GLfloat rotationAngleY;
		GLfloat rotationAngleX;
		GLfloat rotationSpeed;
		int prevMouseX, prevMouseY;

		//Angulo de rotaçao para o telhado
		GLfloat rotationAngle;

		//Coordenadas para o primeiro prédio
		GLfloat buildingPosX;
		GLfloat buildingPosY;
		GLfloat buildingPosZ;
		GLfloat buildingWidth;
		GLfloat buildingHeight;
		GLfloat buildingDepth;

		//Variáveis controlo elevador
		GLfloat elevatorSpeed;
		GLfloat elevatorPosX;
		GLfloat elevatorPosY;
		GLfloat elevatorPosZ;
		GLfloat elevatorWidth;
		GLfloat elevatorHeight;
		GLfloat elevatorDepth;

		//Lights
		bool ambientOn;
		bool dirOn;
		bool pointOn;
		bool spotOn;
		bool autoMove;
		bool localViewer;

		GLfloat ambientLight[4];

		GLfloat dirVec[4];
		GLfloat dirAmb[4];
		GLfloat dirDif[4];
		GLfloat dirSpec[4];
		ofVec3f dirVec3f;
		GLfloat dirVecTheta;


		GLfloat pointPos[4];
		GLfloat pointAmb[4];
		GLfloat pointDif[4];
		GLfloat pointSpec[4];
		GLfloat pointZtheta;

		GLfloat spotPos[4];
		GLfloat spotDir[3];
		GLfloat spotAmb[4];
		GLfloat spotDif[4];
		GLfloat spotSpecular[4];
		GLfloat spotExponent;
		GLfloat spotCutoff;
		GLfloat spotTheta;
		GLfloat spotAtC, spotAtL, spotAtQ;

		bool dirAmbientOn;
		bool dirDiffuseOn;
		bool dirSpecularOn;

		bool pointAmbientOn;
		bool pointDiffuseOn;
		bool pointSpecularOn;

		bool spotAmbientOn;
		bool spotDiffuseOn;
		bool spotSpecularOn;

		ofImage img1;
		ofImage img3;
		ofImage img4;

		float phaseX;
		float phaseY;
		float freqs[10];
		float amps[10];

		//skybox
		float rx, ry, rz;

		//procedural texture
		ofImage sky;
		unsigned char* skyPixels = NULL;
		int px, py;

};

		

		

		