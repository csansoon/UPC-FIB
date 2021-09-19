#include <iostream>
#include <cmath>
#include "Scene.h"


Scene::Scene()
{
	for(int i = 0; i < 4; i++)
		quads[i] = NULL;
}

Scene::~Scene()
{
	for(int i = 0; i < 4; i++)
		if(quads[i] != NULL)
			delete quads[i];
}


void Scene::init()
{
	initShaders();
	for(int i = 0; i < 4; i++)
		quads[i] = Quad::createQuad(-0.75f + (i % 2), -0.75f + (i / 2), 0.5f, 0.5f, program);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
}

void Scene::render()
{
	// Change quad colors using elapsed time
	float value = (sin(currentTime / 1000.f) + 1.0f) / 2.0f;

	program.use();
	program.setUniform4f("color", value, value, value, 1.0f);
	quads[0]->render();
	program.setUniform4f("color", value, 0, 0, 1.0f);
	quads[1]->render();
	program.setUniform4f("color", 0, value, 0, 1.0f);
	quads[2]->render();
	program.setUniform4f("color", 0, 0, value, 1.0f);
	quads[3]->render();
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
	program.init();
	program.addShader(vShader);
	program.addShader(fShader);
	program.link();
	if(!program.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << program.log() << endl << endl;
	}
	program.bindFragmentOutput("outColor");
}

