﻿/*
 * Copyright (c) 2020 Rareș-Nicolaie Ciorbă
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <iostream>
#include <Helltooth.hpp>
#include <random>
#include <time.h>

using namespace ht;
using namespace core;
using namespace maths;
using namespace utils;
using namespace graphics;
using namespace entities;

class Game : public Application {
private:
	Camera* camera;
	std::vector<Entity> entities;
	std::vector<TransformComponent> transforms;
	ModelComponent* model;
	TextureComponent* textureComponent;
	SkyboxComponent* skyboxComponent;
	Entity skyboxEntity;
	UniformBuffer* buffer;
	Texture* texture;
	Texture* skybox;
	Matrix4 proj;
	Renderer* renderer;

public:
	// In here you should initialize stuff that's not depended to the rendering context
	Game() 
		: Application("Window", 1280, 720) {
		srand((u32)time(NULL));
		VFS::Mount("res", "res/shaders/");
		VFS::Mount("res", "res/textures/");
		VFS::Mount("res", "res/models/");

		camera = new FPSCamera(0, 0, -100);
	}

	~Game() {
		delete camera, renderer, buffer, model, texture;
	}

	void Init() {
		proj = Matrix4::CreatePerspective(70, 0.01f, 1000.0f, 1.77f);
		renderer = new Renderer(camera, proj);
		model = Asset::LoadModel("/res/cube.htmodel");
		transforms.resize(10000);
		
		texture = Asset::LoadTexture("/res/cube.httexture");
		textureComponent = new TextureComponent(texture);

		skybox = Asset::LoadTexture("/res/test2.htskybox");
		skyboxComponent = new SkyboxComponent(skybox);
		skyboxEntity.AddComponent(skyboxComponent);
		for (int i = 0; i < 10000; i++) {
			entities.emplace_back();
			entities[i].AddComponent(model);
			transforms[i] = TransformComponent(Vector3((f32)rand() / (f32)RAND_MAX * 200.f - 100.0f, (f32)rand() / (f32)RAND_MAX * 200.f - 100.0f, (f32)rand() / (f32)RAND_MAX * 200.f - 100.0f));
			//transforms[i].Scale(1, 1, 1);
			entities[i].AddComponent(&transforms[i]);
			entities[i].AddComponent(textureComponent);
		}
		entities.push_back(skyboxEntity);

#ifdef HT_OPENGL
		glClearColor(0.3f, 0.4f, 0.7f, 1.0f);
		glEnable(GL_DEPTH_TEST);
#endif
	}

	void Render() {
		for(u32 i=0; i < entities.size(); i++)
			renderer->Submit(entities[i]);
		renderer->Render();
		renderer->End();
	}

	void Update(float delta) {
		camera->Update(delta);
		for (TransformComponent& transform : transforms) {
			transform.Rotate(0, 50.f * delta, 0);
			transform.Update(delta);
		}
	}

	void Tick() {

	}

};

int main() {
	Game game;
	game.Start();

	return 0;
}
