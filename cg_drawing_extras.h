#pragma once

#include "ofMain.h"
#include "cg_extras.h"
#include "ofApp.h"
#include "materiais.h"



//desenha axis 3D
inline void axis3d() {
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glEnd();
}

//função que desenha quadrado unitário 
//centrado na origem e preenchido
inline void rectFill_unit() {
	glBegin(GL_QUADS);
	glVertex3d(-0.5, -0.5, 0.);
	glVertex3d(-0.5, 0.5, 0.);
	glVertex3d(0.5, 0.5, 0.);
	glVertex3d(0.5, -0.5, 0.);
	glEnd();
}

//função que desenha malha unitária com resolução mxn
inline void malha_unit(GLint m, GLint n) {
	GLfloat x_start = -0.5;
	GLfloat y_start = -0.5;
	GLfloat x_step = 1.0 / GLfloat(m);
	GLfloat y_step = 1.0 / GLfloat(n);

	glBegin(GL_QUADS);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			glVertex2d(i * x_step + x_start, j * y_step + y_start);
			glVertex2d(i * x_step + x_start, (j + 1) * y_step + y_start);
			glVertex2d((i + 1) * x_step + x_start, (j + 1) * y_step + y_start);
			glVertex2d((i + 1) * x_step + x_start, j * y_step + y_start);
		}
	}
	glEnd();
}


inline void cube_unit() {
	GLfloat p = 0.5;
	glBegin(GL_QUADS);

	//frente
	glVertex3f(-p, -p, p);
	glVertex3f(-p, p, p);
	glVertex3f(p, p, p);
	glVertex3f(p, -p, p);

	//tras
	glVertex3f(-p, -p, -p);
	glVertex3f(p, -p, -p);
	glVertex3f(p, p, -p);
	glVertex3f(-p, p, -p);

	//cima
	glVertex3f(-p, -p, -p);
	glVertex3f(-p, -p, p);
	glVertex3f(p, -p, p);
	glVertex3f(p, -p, -p);

	//baixo
	glVertex3f(-p, p, p);
	glVertex3f(-p, p, -p);
	glVertex3f(p, p, -p);
	glVertex3f(p, p, p);

	//esq
	glVertex3f(-p, -p, p);
	glVertex3f(-p, -p, -p);
	glVertex3f(-p, p, -p);
	glVertex3f(-p, p, p);

	//dir
	glVertex3f(p, -p, p);
	glVertex3f(p, p, p);
	glVertex3f(p, p, -p);
	glVertex3f(p, -p, -p);

	glEnd();

}

//Função para desenhar um prédio com o auxilio da função cube_unit()
inline void drawBuilding(float posX, float posY, float posZ, float width, float height, float depth, int material) {

	loadMaterial(material);

	glPushMatrix();
	glTranslatef(posX, posY, posZ);
	glPushMatrix();
	glScalef(width, height, depth);
	cube_unit();
	glPopMatrix();
	glPopMatrix();

}


// Função para desenhar uma pirâmide quadrangular
inline void drawPyramidRoof(float posX, float posY, float posZ, float size) {

	glPushMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Desenhar o prédio
	glColor3f(1, 1, 1); // Cor branca, já que a textura fornecerá as cores

	// Mover para a posição especificada
	glTranslatef(posX, posY, posZ);

	glBegin(GL_TRIANGLES);

	// Definir a base da pirâmide
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-size, 0, -size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, 0, -size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, 0, size);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-size, 0, -size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(size, 0, size);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-size, 0, size);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-size, 0, -size);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0, 2 * size, 0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-size, 0, size);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(size, 0, -size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, 0, size);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0, 2 * size, 0);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(size, 0, -size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-size, 0, -size);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0, 2 * size, 0);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-size, 0, size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(size, 0, size);
	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0, 2 * size, 0);

	glEnd();

	glPopMatrix();
}

inline void malha_unit_yup(GLint m, GLint n) {
	GLfloat x_start = -0.5;
	GLfloat y_start = -0.5;
	GLfloat x_step = 1.0 / GLfloat(m);
	GLfloat y_step = 1.0 / GLfloat(n);

	glNormal3f(0, 0, 1);
	glBegin(GL_QUADS);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			glVertex3f(i * x_step + x_start, j * y_step + y_start, 0);
			glVertex3f((i + 1) * x_step + x_start, j * y_step + y_start, 0);
			glVertex3f((i + 1) * x_step + x_start, (j + 1) * y_step + y_start, 0);
			glVertex3f(i * x_step + x_start, (j + 1) * y_step + y_start, 0);
		}
	}
	glEnd();
}

// Draws a unit cube made of unit malhas centered in the origin 
inline void cube_malha_unit_yup(GLint m, GLint n) {
	GLfloat p = 0.5;
	// front
	glPushMatrix();
	glTranslated(0., 0., p);
	malha_unit_yup(m, n);
	glPopMatrix();
	// back
	glPushMatrix();
	glTranslated(0., 0., -p);
	glRotated(180, 0, 1, 0);
	malha_unit_yup(m, n);
	glPopMatrix();

	// top
	glPushMatrix();
	glTranslated(0., -p, 0.);
	glRotated(90, 1, 0, 0);
	malha_unit_yup(m, n);
	glPopMatrix();

	// bottom
	glPushMatrix();
	glTranslated(0., p, 0.);
	glRotated(-90, 1, 0, 0);
	malha_unit_yup(m, n);
	glPopMatrix();

	// left
	glPushMatrix();
	glTranslated(-p, 0., 0.);
	glRotated(-90, 0, 1, 0);
	malha_unit_yup(m, n);
	glPopMatrix();

	// right
	glPushMatrix();
	glTranslated(p, 0., 0.);
	glRotated(90, 0, 1, 0);
	malha_unit_yup(m, n);
	glPopMatrix();
}



inline void drawBuildingMalha(float posX, float posY, float posZ, float width, float height, float depth, int material, float m, float n) {



	loadMaterial(material);
	glPushMatrix();
	glTranslatef(posX, posY, posZ);


	// Desenhar o prédio
	glPushMatrix();
	glScalef(width, height, depth);
	cube_malha_unit_yup(m, n);
	glPopMatrix();
	glPopMatrix();

}
// Função para desenhar um elevador com o auxilio da função cube_unit()
inline void drawElevator(float elevatorPosX, float elevatorPosY, float  elevatorPosZ, float  elevatorWidth, float  elevatorHeight, float elevatorDepth, int material) {
	glPushMatrix();
	glTranslatef(elevatorPosX, elevatorPosY, elevatorPosZ);

	loadMaterial(material);
	glScalef(elevatorWidth, elevatorHeight, elevatorDepth);
	cube_unit();
	glPopMatrix();
}

inline void drawBuildingMalhaText(float posX, float posY, float posZ, float width, float height, float depth, float textureRepeatX, float textureRepeatY, int material) {

	loadMaterial(material);
	glPushMatrix();
	glTranslatef(posX, posY, posZ);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Desenhar o prédio
	glColor3f(1, 1, 1); // Cor branca, já que a textura fornecerá as cores
	glPushMatrix();
	glScalef(width, height, depth);

	glBegin(GL_QUADS);

	// Face traseira
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 0.5, -0.5);

	glTexCoord2f(0, textureRepeatY);
	glVertex3f(0.5, -0.5, -0.5);

	glTexCoord2f(textureRepeatX, textureRepeatY);
	glVertex3f(-0.5, -0.5, -0.5);

	glTexCoord2f(textureRepeatX, 0);
	glVertex3f(-0.5, 0.5, -0.5);

	// Face direita
	glTexCoord2f(0, 0);
	glVertex3f(0.5, 0.5, 0.5);

	glTexCoord2f(0, textureRepeatY);
	glVertex3f(0.5, -0.5, 0.5);

	glTexCoord2f(textureRepeatX, textureRepeatY);
	glVertex3f(0.5, -0.5, -0.5);

	glTexCoord2f(textureRepeatX, 0);
	glVertex3f(0.5, 0.5, -0.5);

	// Face esquerda
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0.5, -0.5);

	glTexCoord2f(0, textureRepeatY);
	glVertex3f(-0.5, -0.5, -0.5);

	glTexCoord2f(textureRepeatX, textureRepeatY);
	glVertex3f(-0.5, -0.5, 0.5);

	glTexCoord2f(textureRepeatX, 0);
	glVertex3f(-0.5, 0.5, 0.5);

	// Face superior
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0.5, -0.5);

	glTexCoord2f(0, textureRepeatX);
	glVertex3f(-0.5, 0.5, 0.5);

	glTexCoord2f(textureRepeatY, textureRepeatX);
	glVertex3f(0.5, 0.5, 0.5);

	glTexCoord2f(textureRepeatY, 0);
	glVertex3f(0.5, 0.5, -0.5);

	// Face inferior
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, -0.5, -0.5);

	glTexCoord2f(0, textureRepeatX);
	glVertex3f(-0.5, -0.5, 0.5);

	glTexCoord2f(textureRepeatY, textureRepeatX);
	glVertex3f(0.5, -0.5, 0.5);

	glTexCoord2f(textureRepeatY, 0);
	glVertex3f(0.5, -0.5, -0.5);

	glEnd();

	glPopMatrix();
	glPopMatrix();
}

inline void drawBuildingMalhaTextTelhado(float posX, float posY, float posZ, float width, float height, float depth, float textureRepeatX, float textureRepeatY, int material) {
	glPushMatrix();
	glTranslatef(posX, posY, posZ);

	loadMaterial(material);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Desenhar o prédio
	glColor3f(1, 1, 1); // Cor branca, já que a textura fornecerá as cores
	glPushMatrix();
	glScalef(width, height, depth);

	glBegin(GL_QUADS);

	// Face frontal
	glTexCoord2f(0, 0);
	glVertex3f(-0.5, 0.5, 0.5);

	glTexCoord2f(0, textureRepeatY);
	glVertex3f(-0.5, -0.5, 0.5);

	glTexCoord2f(textureRepeatX, textureRepeatY);
	glVertex3f(0.5, -0.5, 0.5);

	glTexCoord2f(textureRepeatX, 0);
	glVertex3f(0.5, 0.5, 0.5);


	glEnd();

	glPopMatrix();
	glPopMatrix();
}