
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	glEnable(GL_DEPTH_TEST);
	coutModelviewMatrix();
	ofBackground(135, 206, 250);
	ofDisableArbTex();//para utilizar coordenadas de textura normalizadas
	glLineWidth(5);
	glShadeModel(GL_SMOOTH);

	//view
	view = 0;

	//perspectiva Views
	perspectiveView = false;
	
	//floor parameters
	resX = 5;
	resY = 5;
	floorWidth = gw() * 0.5;
	floorHeight = gw() * 0.5;
	floorHeightPos = 0.;//gh() * 0.75;
	
	//floorBasePredio
	baseWidth = floorWidth / GLfloat(resX);
	baseHeight = floorHeight / GLfloat(resY);
	baseDepth = baseWidth;

	basePosX = floor(resX / 2);
	basePosY = floor(resY / 2);
	basePos.z = floorHeightPos + baseDepth * 0.5;

	//Rotação segundo as setas do teclado
	rotationAngleX = 0.0;
	rotationAngleY = 0.0;
	rotationSpeed = 1.0;

	//angulo Rotacao Telhado
	rotationAngle = 0.0;

	//velocidade elevador
	elevatorSpeed = 1;

	//Posição do elevador
	elevatorPosX = 0.0;
	elevatorPosY = 0.0;
	elevatorPosZ = 0.0;
	elevatorWidth = baseWidth / 4;
	elevatorHeight = baseHeight / 4;
	elevatorDepth = baseDepth / 3;

	//luzes
	ambientOn = true;
	dirOn = false;
	pointOn = false;
	spotOn = false;
	autoMove = true;
	localViewer = false;

	pointZtheta = 0;
	dirVecTheta = 0.;

	spotExponent = 0;
	spotCutoff = 1;
	spotTheta = 0;

	pointAmbientOn = true;
	pointDiffuseOn = true;
	pointSpecularOn = true;

	dirAmbientOn = true;
	dirDiffuseOn = true;
	dirSpecularOn = true;

	spotAmbientOn = true;
	spotDiffuseOn = true;
	spotSpecularOn = true;

	//Texturas
	img1.load("UnderGound.png");
	img3.load("Building.png");
	img4.load("Telhado.png");


	//Skybox
	for (int i = 0; i < 10; i++) {
		freqs[i] = 0.25 + 0.25 * i * 5;
		amps[i] = 1. / (i * 0.25 + 1);
		cout << endl << amps[i];
	}

	phaseX = 0.;
	phaseY = 0.;

	px = 128;
	py = 128;
	sky.allocate(px, py, OF_IMAGE_COLOR);
	skyPixels = new unsigned char[px * py * 3];

}

//--------------------------------------------------------------
void ofApp::update(){

	ofSetWindowTitle(ofToString(ofGetFrameRate()) + " My town");

	//Rotação do angulo do telhado rotativo
	rotationAngle += 1.0;


	// Atualiza a posição do elevador
	elevatorPosZ += elevatorSpeed;

	// Verifica se o elevador atingiu os limites superior ou inferior
	if (elevatorPosZ > (baseDepth * 5 - elevatorDepth) || elevatorPosZ <= -(elevatorDepth*0.05)+2) {
		elevatorSpeed *= -1;  // Inverte a direção do movimento
	}

	if (autoMove) {

		//calculo da posicao da luz pontual
		pointPos[0] = gw() * 0.5 * sin(3 * pointZtheta * PI / 180.0);
		pointPos[1] = gh() * 0.5 * cos(pointZtheta * PI / 180.0);
		pointPos[2] = 200 + 199 * cos(8 * pointZtheta * PI / 180.0);
		pointZtheta += 0.25;

		//calculo da direcao da luz direcional
		float z = gh() * 0.25 * (cos(dirVecTheta * PI / 180.) * 0.5 + 0.45);
		float y = gh() * 0.5;
		float x = 0;
		dirVec3f = ofVec3f(x, y, z) - ofVec3f(0, 0, 0);
		dirVecTheta += 0.5;

		//calculo da direcao do spot
		spotDir[0] = cos(spotTheta * PI / 180.);
		spotDir[1] = sin(spotTheta * PI / 180.);
		spotTheta += 0.75;


	}
	else {

		//luz pontual
		//centro acima
		pointPos[0] = 0;
		pointPos[1] = 0;
		pointPos[2] = 90;

		//luz direcional
		//auto max 
		dirVec3f = ofVec3f(0, gh() * 0.5, gh() * 0.25 * 0.95) - ofVec3f(0, 0, 0);

		//spot
		spotDir[0] = 0;
		spotDir[1] = 0;

	}
		
}

//--------------------------------------------------------------
void ofApp::draw() {

	
	if (!perspectiveView) {

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		perspective(60,100,1000, false, true);
	}
	else {

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		glOrtho(-gw() / 2, gw() / 2, gh() / 2, -gh() / 2, -10000, 10000);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	switch (view) {
	case 0:
		//vista de cima
		glTranslatef(gw() * 0.5, gh() * 0.5, 0);
		lookat(0,0,800,0,0,1,
			0, 1, 0);
		break;
	case 1:
		//vista de frente, da altura do chão
		lookat(0, gh(), 10,
			0, 0, 10,
			0, 0, -1);
		glTranslatef(0, 10, -100);
		break;
	case 2:
		//vista de lado esquerdo
		lookat(-gw(), 0, 0,
			0, 0, gw()/3,
			0, 0, -1);
		break;
	case 3:
		//vista de lado direito
		lookat(gw(), 0, 0,
			0, 0, gw() / 3,
			0, 0, -1);
		break;
	case 4:
		//vista de trás
		lookat(0, -gh(), 10,
			0, 0, 10,
			0, 0, -1);
		glTranslatef(0, 100, -100);
		break;
	}
	
	//define luzes
	glEnable(GL_LIGHTING);//habilita o uso de iluminação
	glEnable(GL_NORMALIZE);//utiliza versores para normais (normais normalizadas)
	glEnable(GL_COLOR_MATERIAL);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, localViewer);

	//luz ambiente
	if (ambientOn) {
		ambientLight[0] = 1;
		ambientLight[1] = 1;
		ambientLight[2] = 1;
		ambientLight[3] = 1;
	}
	else {
		ambientLight[0] = 0.;
		ambientLight[1] = 0.;
		ambientLight[2] = 0.;
		ambientLight[3] = 1;
	}
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

	
	//luz direcional
	dirVec[0] = dirVec3f.x;//x
	dirVec[1] = dirVec3f.y;//y
	dirVec[2] = dirVec3f.z;//z
	dirVec[3] = 0;//vetor - direção!

	if (dirAmbientOn) {
		dirAmb[0] = 0.25;//R
		dirAmb[1] = 0.25;//G
		dirAmb[2] = 0.25;//B
		dirAmb[3] = 1.;//constante
	}
	else {
		dirAmb[0] = 0.;//R
		dirAmb[1] = 0.;//G
		dirAmb[2] = 0.;//B
		dirAmb[3] = 1.;//constante
	}
	
	if (dirDiffuseOn) {
		dirDif[0] = 0.5;//R
		dirDif[1] = 0.;//G
		dirDif[2] = 0.5;//B
		dirDif[3] = 1.;//constante
	}
	else {
		dirDif[0] = 0;//R
		dirDif[1] = 0.;//G
		dirDif[2] = 0.;//B
		dirDif[3] = 1.;//constante
	}

	if (dirSpecularOn) {
		dirSpec[0] = 0.;//R
		dirSpec[1] = 0.;//G
		dirSpec[2] = 0.;//B
		dirSpec[3] = 1.;//constante
	}
	else {
		dirSpec[0] = 0.;//R
		dirSpec[1] = 0.;//G
		dirSpec[2] = 0.;//B
		dirSpec[3] = 1.;//constante
	
	}

	glLightfv(GL_LIGHT0, GL_POSITION, dirVec);
	glLightfv(GL_LIGHT0, GL_AMBIENT, dirAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, dirDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, dirSpec);

	if (dirOn) {
		glEnable(GL_LIGHT0);
	}
	else {
		glDisable(GL_LIGHT0);
	}

	//luz pontual
	pointPos[3] = 1;

	if (pointAmbientOn) {
		pointAmb[0] = 0.25;//R
		pointAmb[1] = 0.25;//G
		pointAmb[2] = 0.25;//B
		pointAmb[3] = 1.;//constante
	}
	else {
		pointAmb[0] = 0.;//R
		pointAmb[1] = 0.;//G
		pointAmb[2] = 0.;//B
		pointAmb[3] = 1.;//constante
	}

	if (pointDiffuseOn) {

		pointDif[0] = 0.5;//R
		pointDif[1] = 0.5;//G
		pointDif[2] = 0.5;//B
		pointDif[3] = 1.;//constante
	}
	else {
		pointDif[0] = 0.;//R
		pointDif[1] = 0.;//G
		pointDif[2] = 0;//B
		pointDif[3] = 1.;//constante
	}

	if (pointSpecularOn) {

		pointSpec[0] = 0.;//R
		pointSpec[1] = 0.;//G
		pointSpec[2] = 0.;//B
		pointSpec[3] = 1.;//constante
	}
	else {

		pointSpec[0] = 0.;//R
		pointSpec[1] = 0.;//G
		pointSpec[2] = 0.;//B
		pointSpec[3] = 1.;//constante
	
	}

	glLightfv(GL_LIGHT1, GL_POSITION, pointPos);
	glLightfv(GL_LIGHT1, GL_AMBIENT, pointAmb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, pointDif);
	glLightfv(GL_LIGHT1, GL_SPECULAR, pointSpec);

	if (pointOn) {
		glEnable(GL_LIGHT1);
	}
	else {
		glDisable(GL_LIGHT1);
	}

	//luz foco
	spotPos[0] = -gw() * 0.0004;
	spotPos[1] = 0.;
	spotPos[2] = 330.;
	spotPos[3] = 1.;


	if (spotAmbientOn) {

		spotAmb[0] = 0.2;//R
		spotAmb[1] = 0.2;//G
		spotAmb[2] = 0.2;//B
		spotAmb[3] = 0.;//constante
	}
	else {
		spotAmb[0] = 0.;//R
		spotAmb[1] = 0.;//G
		spotAmb[2] = 0.;//B
		spotAmb[3] = 0.;//constante
	}

	//direcao
	spotDir[0] = 0.;
	spotDir[1] = 0.;
	spotDir[2] = -1.;
	//spotDir[3] = 0.;Não tem a 4 coordenada, é sempre vetor


	if (spotDiffuseOn) {

		spotDif[0] = 1.;//R
		spotDif[1] = 1.;//G
		spotDif[2] = 1.;//B
		spotDif[3] = 1.;//constante
	}
	else {
		spotDif[0] = 0.;//R
		spotDif[1] = 0.;//G
		spotDif[2] = 0.;//B
		spotDif[3] = 1.;//constante
	}


	if (spotSpecularOn) {

		spotSpecular[0] = 1.;//R
		spotSpecular[1] = 1.;//G
		spotSpecular[2] = 1.;//B
		spotSpecular[3] = 1.;//constante
	}
	else {
		spotSpecular[0] = 0.;//R
		spotSpecular[1] = 0.;//G
		spotSpecular[2] = 0.;//B
		spotSpecular[3] = 1.;//constante
	}
	

	//concentracao
	spotExponent = 25;//0 - 128

	//angulo
	spotCutoff = 100;//0 - 180

	glLightfv(GL_LIGHT2, GL_POSITION, spotPos);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDir);

	glLightfv(GL_LIGHT2, GL_AMBIENT, spotAmb);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, spotDif);
	glLightfv(GL_LIGHT2, GL_SPECULAR, spotSpecular);

	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, spotExponent);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spotCutoff);

	//atenuação
	spotAtC = 1.;
	spotAtL = 0.;
	spotAtQ = 0.;
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, spotAtC);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, spotAtL);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, spotAtQ);

	if (spotOn) {
		glEnable(GL_LIGHT2);
	}
	else {
		glDisable(GL_LIGHT2);
	}

	//Skybox
	phaseX += 0.0005 * cos(dirVecTheta * 0.001);
	phaseY -= 0.0006 * cos(dirVecTheta * 0.0001);


	skyPixels = sky.getPixels().getData();

	ofColor A(0, 30, 180);
	ofColor B(255, 255, 255);

	for (int j = 0; j < py; j++) {
		for (int i = 0; i < px; i++) {
			int index = 3 * (j * px + i);
			float noise = getMultiNoise(0.008 * (i)+phaseX, 0.008 * (j)+phaseY, freqs, amps, 10);
			ofColor auxColor = A.getLerped(B, noise);
			skyPixels[index] = auxColor.r;
			skyPixels[index + 1] = auxColor.g;
			skyPixels[index + 2] = auxColor.b;
		}
	}
	sky.setFromPixels(skyPixels, px, py, OF_IMAGE_COLOR);
	sky.update();

	glEnable(GL_TEXTURE);
	sky.bind();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glColor3f(1, 1, 1);
	glPushMatrix();
	glRotatef(0, 1, 0, 0);
	glRotatef(0, 0, 1, 0);
	glRotatef(0, 0, 0, 1);
	glScalef(gw() * 50, gw() * 50., gw() * 50.);
	ofDrawSphere(1);
	glPopMatrix();


	sky.unbind();
	glDisable(GL_TEXTURE);
	
	glPushMatrix();//master push

	glDisable(GL_COLOR_MATERIAL);

	// Aplicar rotações com as setas
	glRotatef(rotationAngleX, 1, 0, 0);
	glRotatef(rotationAngleY, 0, 1, 0);

	glEnable(GL_TEXTURE);

	img1.bind();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// floor
	glPushMatrix(); // floor push
	loadMaterial(8);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-floorWidth / 2, -floorHeight / 2, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-floorWidth / 2, floorHeight / 2, 0);
	glTexCoord2f(1, 1);
	glVertex3f(floorWidth / 2, floorHeight / 2, 0);
	glTexCoord2f(1, 0);
	glVertex3f(floorWidth / 2, -floorHeight / 2, 0);
	glEnd();
	glPopMatrix(); // floor pop
	img1.unbind();
	glDisable(GL_TEXTURE);

	glLineWidth(2);


	// Desenhar o primeiro prédio
	buildingPosX = basePos.x; // Coordenadas X do prédio
	buildingPosY = basePos.y + 1; // Coordenadas Y do prédio (acima do floor)
	buildingPosZ = basePos.z; // Coordenadas Z do prédio 
	buildingWidth = baseWidth; // Largura do prédio
	buildingHeight = baseHeight; // Altura do prédio 
	buildingDepth = baseDepth * 2; // Profundidade do prédio

	
	glEnable(GL_TEXTURE);
	img3.bind();
	glPushMatrix(); 
	glTranslatef(0, 0, baseDepth / 2 + 1); // Mover 1 unidade acima no eixo Z
	drawBuildingMalhaText(buildingPosX, buildingPosY, buildingPosZ, buildingWidth, buildingHeight, buildingDepth,6, 5,16);
	glPopMatrix(); 
	img3.unbind();
	glDisable(GL_TEXTURE);

	//Para colocar uma textura no telhado 
	glEnable(GL_TEXTURE);
	img4.bind();
	glPushMatrix();
	glTranslatef(0, 0, baseDepth / 2 + 1); // Mover 1 unidade acima no eixo Z
	drawBuildingMalhaTextTelhado(buildingPosX, buildingPosY, buildingPosZ, buildingWidth, buildingHeight, buildingDepth, 6, 5,16);
	glPopMatrix();
	img4.unbind();
	glDisable(GL_TEXTURE);


	// Desenhar o segundo prédio
	glPushMatrix(); 
	glTranslatef(0, 0, 21);
	drawBuilding(basePos.x + baseWidth + 1, basePos.y + 1, basePos.z, baseWidth, baseHeight, baseDepth + 40, 6);
	glPopMatrix(); 

	// Desenhar o terceiro prédio
	glPushMatrix(); 
	glTranslatef(0, 0, baseDepth * 0.01);
	drawBuilding(basePos.x + 2 * baseWidth + 2, basePos.y + 1, basePos.z, baseWidth, baseHeight, baseDepth, 5);
	glPopMatrix(); 

	// Desenhar o quarto prédio
	glPushMatrix();
	glTranslatef(0, 0, 21);
	drawBuilding(-(basePos.x + baseWidth + 1), basePos.y + 1, basePos.z, baseWidth, baseHeight, baseDepth + 40, 6);
	glPopMatrix();

	// Desenhar o quinto prédio
	glPushMatrix(); 
	glTranslatef(0, 0, baseDepth * 0.01);
	drawBuilding(-(basePos.x + 2 * baseWidth + 2), basePos.y + 1, basePos.z, baseWidth, baseHeight, baseDepth, 5);
	glPopMatrix(); 
	
	// Desenhar o telhado (pirâmide quadrangular) em cima do primeiro prédio
	float roofSize = buildingWidth / 2; //Tamanho do telhado conforme a largura do primeiro prédio
	float roofPosX = buildingPosX; // Posição X do telhado (alinhado com o prédio)
	float roofPosY = buildingPosY ; // Posição Y do telhado (acima do prédio)
	float roofPosZ = buildingPosZ + buildingHeight + roofSize + 1; // Posição Z do telhado (mesmo nível do prédio)

	glEnable(GL_TEXTURE);
	img4.bind();
	glPushMatrix(); 
	glTranslatef(roofPosX, roofPosY, roofPosZ);

	// Ajustar a rotação para que o pico da pirâmide esteja orientado corretamente
	glRotatef(-90,1,0,0); 
	glRotatef(180, 0, 0, 1); 
	//Rotação constante do telhado
	glRotatef(rotationAngle, 0, 1, 0);
	loadMaterial(10);
	drawPyramidRoof(0, 0, 0, roofSize); 
	glPopMatrix(); 
	img4.unbind();
	glDisable(GL_TEXTURE);

	
	// Desenhar sexto prédio
	glPushMatrix(); 
	glTranslatef(0, 0, 1);
	drawBuilding(basePos.x + baseWidth + 1, basePos.y + baseWidth, basePos.z , baseWidth / 2, baseHeight / 2, baseDepth, 5);
	glPopMatrix(); 

	// Desenhar setimo prédio
	glPushMatrix();
	glTranslatef(0, 0, 1);
	drawBuilding(-(basePos.x + baseWidth + 1), basePos.y + baseWidth, basePos.z, baseWidth / 2, baseHeight / 2, baseDepth, 5);
	glPopMatrix(); 

	// Desenhar o oitavo prédio
	glEnable(GL_TEXTURE);
	img3.bind();
	glPushMatrix();
	glTranslatef(0, 0, baseDepth * 0.01);
	drawBuildingMalhaText(basePos.x + 2 * baseWidth + 2, basePos.y + 2 * baseWidth, basePos.z / 2 + 1, baseWidth / 3, baseHeight/3, baseDepth/2,4,4,16);
	glPopMatrix(); 
	img3.unbind();
	glDisable(GL_TEXTURE);

	//Para colocar uma textura no telhado 
	glEnable(GL_TEXTURE);
	img4.bind();
	glPushMatrix();
	glTranslatef(0, 0, baseDepth * 0.01);
	drawBuildingMalhaTextTelhado(basePos.x + 2 * baseWidth + 2, basePos.y + 2 * baseWidth, basePos.z / 2 + 1, baseWidth / 3, baseHeight / 3, baseDepth / 2, 4, 4,16);
	glPopMatrix();
	img4.unbind();
	glDisable(GL_TEXTURE);


	// Desenhar o nono prédio
	glPushMatrix();
	glTranslatef(0, 0, baseDepth / 2 + 1); 
	drawBuildingMalha(basePos.x - (baseWidth + baseWidth/2) , basePos.y + 1 - 2* baseWidth, basePos.z, baseWidth * 2, baseHeight, baseDepth * 2,13,7,7);
	glPopMatrix(); 
	
	// Desenhar o decimo prédio
	glPushMatrix(); 
	glTranslatef(0, 0, 21);
	drawBuilding(basePos.x, basePos.y + 1 - baseWidth, basePos.z, baseWidth, baseHeight, baseDepth + 40, 5);
	glPopMatrix();

	// Desenhar o decimo primeiro prédio
	glPushMatrix(); 
	glTranslatef(0, 0, baseDepth * 0.01);
	drawBuilding(basePos.x, basePos.y + 1 - 2 * baseWidth, basePos.z, baseWidth, baseHeight, baseDepth, 6);
	glPopMatrix(); 

	// Desenhar o decimo segundo prédio
	glEnable(GL_TEXTURE);
	img3.bind();
	glPushMatrix();
	glTranslatef(0, 0, baseDepth * 0.01);
	drawBuildingMalhaText(-(basePos.x + 2 * baseWidth + 2), basePos.y + 2 * baseWidth, basePos.z / 2 + 1, baseWidth / 3, baseHeight / 3, baseDepth / 2,4, 4,16);
	glPopMatrix();
	img3.unbind();
	glDisable(GL_TEXTURE);

	//Para colocar uma textura no telhado 
	glEnable(GL_TEXTURE);
	img4.bind();
	glPushMatrix();
	glTranslatef(0, 0, baseDepth * 0.01);
	drawBuildingMalhaTextTelhado(-(basePos.x + 2 * baseWidth + 2), basePos.y + 2 * baseWidth, basePos.z / 2 + 1, baseWidth / 3, baseHeight / 3, baseDepth / 2, 4, 4,16);
	glPopMatrix();
	img4.unbind();
	glDisable(GL_TEXTURE);

	// Desenhar o decimo terceiro prédio
	glPushMatrix();
	glTranslatef(0, 0, baseDepth /2 + 1);
	drawBuildingMalha(basePos.x + (baseWidth + baseWidth / 2), basePos.y + 1 - 2 * baseWidth, basePos.z, baseWidth * 2, baseHeight, baseDepth * 2, 13,7,7);
	glPopMatrix();

	// Desenhar decimo quarto prédio

	glPushMatrix();
	glTranslatef(0, 0, baseDepth*2 + 1);
	drawBuildingMalha(-(basePos.x + baseWidth + 1),  -(basePos.y + baseWidth), basePos.z, baseWidth/2 , baseHeight , baseDepth * 5, 1,5,5);
	glPopMatrix();


	// Desenhar torre decimo terceiro prédio
	glPushMatrix();
	glTranslatef(0, 0, baseDepth*2 + 2);
	drawBuildingMalha(basePos.x + (baseWidth + baseWidth / 2), basePos.y + 1 - 2 * baseWidth, basePos.z, baseWidth , baseHeight*1/2, baseDepth , 1, 7, 7);
	glPopMatrix();

	// Desenhar 2  torre decimo terceiro prédio
	glPushMatrix();
	glTranslatef(0, 0, baseDepth * 3 + 5);
	drawBuildingMalha(basePos.x + (baseWidth + baseWidth / 2), basePos.y + 1 - 2 * baseWidth, basePos.z, baseWidth/2, baseHeight * 1 / 5, baseDepth, 3, 7, 7);
	glPopMatrix();


	// Elevador no prédio mais alto
	
	glPushMatrix();
	glTranslated(-(basePos.x + baseWidth +1), -(basePos.y + baseWidth), basePos.z - elevatorDepth);
	drawElevator(elevatorPosX,elevatorPosY, elevatorPosZ, elevatorWidth, elevatorHeight, elevatorDepth,0);
	glPopMatrix();

	glPopMatrix(); // master pop

	rx += 0.1;
	ry += 0.2;
	rz += 0.15;

	//desenha representação das luzes e vetores utilizados
	//sem iluminação
	glDisable(GL_LIGHTING);//desabilita iluminação
	//representação da posição da Light1
	if (pointOn) {
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(pointPos[0], pointPos[1], pointPos[2]);
		glScalef(30, 30, 30);
		cube_unit();
		glPopMatrix();
	}

	//representação da posição da Light0
	if (dirOn) { 
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(dirVec3f.x, dirVec3f.y, dirVec3f.z); 
		glScalef(30, 30, 30); 
		cube_unit();
		glPopMatrix();

	}

	//representação da posição da luz spot
	if (spotOn) {
		glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(spotPos[0], spotPos[1], spotPos[2]);
		glScalef(30, 30, 30);
		cube_unit();
		glPopMatrix();
	}

}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case '1':
		glDisable(GL_CULL_FACE);
		break;
	case '2':
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		break;
	case '3':
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		break;
	case '4':
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT_AND_BACK);
		break;
	case 'f':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'g':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 'a':
		ambientOn = !ambientOn;
		break;
	case 'd':
		dirOn = !dirOn;
		break;
	case 'o':
		pointOn = !pointOn;
		break;
	case 'z':
		dirAmbientOn = !dirAmbientOn;
		break;
	case 'x':
		dirDiffuseOn = !dirDiffuseOn;
		break;
	case 'c':
		dirSpecularOn = !dirSpecularOn;
		break;
	case 'y':
		pointAmbientOn = !pointAmbientOn;
		break;
	case 'u':
		pointDiffuseOn = !pointDiffuseOn;
		break;
	case 'i':
		pointSpecularOn = !pointSpecularOn;
		break;
	case 'w':
		spotAmbientOn = !spotAmbientOn;
		break;
	case 'e':
		spotDiffuseOn = !spotDiffuseOn;
		break;
	case 'r':
		spotSpecularOn = !spotSpecularOn;
		break;
	case 'm':
		glShadeModel(GL_FLAT);
		break;
	case 'n':
		glShadeModel(GL_SMOOTH);
		break;
	case 'p':
		perspectiveView = !perspectiveView;
		break;
	case 'v':
		view++;
		if (view > 4) {
			view = 0;
		}
		break;

	case 'q':
		autoMove = !autoMove;
		break;

	case 's':
		spotOn = !spotOn;
		break;
	case '+':
		spotExponent++;
		if (spotExponent > 128) {
			spotExponent = 128;
		}
		break;
	case '-':
		spotExponent--;
		if (spotExponent < 0) {
			spotExponent = 0;
		}
		break;
	case 'l':
		spotCutoff++;
		if (spotCutoff > 180) {
			spotCutoff = 180;
		}
		break;
	case 'k':
		spotCutoff--;
		if (spotCutoff < 1) {
			spotCutoff = 1;
		}
		break;
	case '9':
		localViewer = !localViewer; 
		break;
	case OF_KEY_UP:
		rotationAngleX += rotationSpeed;
		break;
	case OF_KEY_DOWN:
		rotationAngleX -= rotationSpeed;
		break;
	case OF_KEY_LEFT:
		rotationAngleY += rotationSpeed;
		break;
	case OF_KEY_RIGHT:
		rotationAngleY -= rotationSpeed;
		break;
	}
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	int deltaX = x - prevMouseX;
	int deltaY = y - prevMouseY;

	rotationAngleX += deltaY * rotationSpeed;
	rotationAngleY += deltaX * rotationSpeed;

	prevMouseX = x;
	prevMouseY = y;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	prevMouseX = -x;
	prevMouseY = -y;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	setup();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::exit() {

	sky.clear();
	img4.clear();
	img3.clear();
	img1.clear();
}

