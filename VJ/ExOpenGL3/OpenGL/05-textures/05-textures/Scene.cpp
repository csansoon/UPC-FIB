#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"


Scene::Scene()
{
	quad = NULL;
}

Scene::~Scene()
{
	if(quad != NULL)
		delete quad;
	for(int i=0; i<3; i++)
		if(texQuad[i] != NULL)
			delete texQuad[i];
}


void Scene::init()
{
	PosicionChampi[0] = 128.f;
	PosicionChampi[1] = 0.f;
	velocidadChampi = 5.f;

	glm::vec2 geom[2] = {glm::vec2(0.f, 0.f), glm::vec2(128.f, 128.f)};
	glm::vec2 texCoords[2] = {glm::vec2(0.f, 0.f), glm::vec2(1.f, 1.f)};

	initShaders();
	//quad = Quad::createQuad(0.f, 0.f, 128.f, 128.f, simpleProgram);
	//texCoords[0] = glm::vec2(0.f, 0.f); texCoords[1] = glm::vec2(8.f, 2.5f);
	//texQuad[0] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	//texCoords[0] = glm::vec2(0.f, 0.5f); texCoords[1] = glm::vec2(0.5f, 1.f);
	//texQuad[1] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);
	//texCoords[0] = glm::vec2(0.f, 0.5f); texCoords[1] = glm::vec2(0.5f, 1.f);
	//texQuad[2] = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);

	cielo = Quad::createQuad(0.0f, 0.0f, 640.f, 480.f, simpleProgram);

	texCoords[0] = glm::vec2(0.f, 0.f);
	texCoords[1] = glm::vec2(10.f, 2.f);
	geom[0] = glm::vec2(0.f, 0.f);
	geom[1] = glm::vec2(640.f, 128.f);
	suelo = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);

	texCoords[0] = glm::vec2(0.f, 0.5f);
	texCoords[1] = glm::vec2(0.5f, 1.f);
	geom[0] = glm::vec2(0.f, 0.f);
	geom[1] = glm::vec2(128.f, 128.f);
	champi = TexturedQuad::createTexturedQuad(geom, texCoords, texProgram);


	// Load textures
	texs[0].loadFromFile("images/brick.png", TEXTURE_PIXEL_FORMAT_RGB);
	texs[1].loadFromFile("images/varied.png", TEXTURE_PIXEL_FORMAT_RGBA);
	projection = glm::ortho(0.f, float(CAMERA_WIDTH - 1), float(CAMERA_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	float width = 640.f;
	float size = 128.f;

	currentTime += deltaTime;
	PosicionChampi[0] += deltaTime * velocidadChampi;
	velocidadChampi *= 0.9;

	if (PosicionChampi[0] > width + size) {
		PosicionChampi[0] = PosicionChampi[0];
		PosicionChampi[0] = PosicionChampi[0] - (((int)(PosicionChampi[0] / width)) * width);
		PosicionChampi[0] = PosicionChampi[0];
	}

	else if (PosicionChampi[0] < size) {
		PosicionChampi[0] = PosicionChampi[0] - (((int)(PosicionChampi[0] / width)) * width) + width;
	}

	//if (PosicionChampi[0] > 640.f) PosicionChampi[0] = PosicionChampi[0] - 640.f - 128.f;
}

void Scene::render()
{
	glm::mat4 modelview;
	float offset = 32.f;


	simpleProgram.use();
	simpleProgram.setUniformMatrix4f("projection", projection);

	// CIELO
	simpleProgram.setUniform4f("color", 0.0f, 0.8f, 1.0f, 1.0f);
	simpleProgram.setUniformMatrix4f("modelview", modelview);
	cielo->render();

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);

	// SUELO
	modelview = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 480.f - 128.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	suelo->render(texs[0]);

	// CHAMPIÑÓN
	modelview = glm::translate(glm::mat4(1.0f), glm::vec3(PosicionChampi[0], 480.f - 128.f - 128.f + offset, 0.f));
	modelview = glm::translate(modelview, glm::vec3(-64.f, 0.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	champi->render(texs[1]);

	// DOBLE CHAMPIÑÓN
	float width = 640.f;
	float size = 128.f;
	if (PosicionChampi[0] > width - size / 2) {
		modelview = glm::translate(glm::mat4(1.0f), glm::vec3(PosicionChampi[0] - width, 480.f - 128.f - 128.f + offset, 0.f));
		modelview = glm::translate(modelview, glm::vec3(-64.f, 0.f, 0.f));
		texProgram.setUniformMatrix4f("modelview", modelview);
		champi->render(texs[1]);
	}
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/simple.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/simple.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	simpleProgram.init();
	simpleProgram.addShader(vShader);
	simpleProgram.addShader(fShader);
	simpleProgram.link();
	if(!simpleProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << simpleProgram.log() << endl << endl;
	}
	simpleProgram.bindFragmentOutput("outColor");

	vShader.free();
	fShader.free();
	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
}

void Scene::addSpeed(float speed)
{
	velocidadChampi += speed;
}
