#include "MainGame.h"

#include <SDLEngine/Errors.h>
#include <SDLEngine/SDLEngine.h>
#include <SDLEngine/ResourceManager.h>

#include <iostream>
#include <string>

MainGame::MainGame() :
	m_screenWidth(1024), 
	m_screenHeight(720), 
	m_gameState(GameState::PLAY), 
	m_time(0.0f),
	m_maxFPS(60.0f)
{
	m_camera2D.Init(m_screenWidth, m_screenHeight);
}

MainGame::~MainGame()
{
}

void MainGame::Run()
{
	InitSystems();

	GameLoop();
}

void MainGame::InitSystems()
{
	SDLEngine::init();

	m_window.Create("Game Engine", m_screenWidth, m_screenHeight, 0, SDLEngine::Color(0,0,255,255));

	InitShaders();

	m_spriteBatch.Init();
	m_fpsLimiter.Init(m_maxFPS);
}

void MainGame::InitShaders()
{
	m_colorProgram.CompileShaders("Shaders/ColorShading.vert", "Shaders/ColorShading.frag");
	m_colorProgram.AddAttribute("vertexPosition");
	m_colorProgram.AddAttribute("vertexColor");
	m_colorProgram.AddAttribute("vertexUV");
	m_colorProgram.LinkShaders();
}

void MainGame::GameLoop()
{
	while (m_gameState != GameState::EXIT)
	{
		m_fpsLimiter.Begin();

		ProcessInput();
		m_time += 0.01f;

		m_camera2D.Update();

		for (int i = 0; i < _bullets.size();)
		{
			if (_bullets[i].Update())
			{
				_bullets[i] = _bullets.back();
				_bullets.pop_back();
			}
			else
			{
				i++;
			}
		}

		DrawGame();

		m_fps = m_fpsLimiter.End();

		static int frameCounter = 0;
		frameCounter++;
		if (frameCounter == 10000)
		{
			std::cout << m_fps << std::endl;
			frameCounter = 0;
		}
	}
}

void MainGame::ProcessInput()
{
	SDL_Event ev;

	const float CAMERA_SPEED = 2.0f;
	const float SCALE_SPEED = 0.1f;

	while (SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{
			case SDL_QUIT:
				m_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				m_inputManager.SetMouseCoords(ev.motion.x, ev.motion.y);
				break;
			case SDL_KEYDOWN:
				m_inputManager.PressKey(ev.key.keysym.sym);
				break;
			case SDL_KEYUP:
				m_inputManager.ReleaseKey(ev.key.keysym.sym);
				break;
			case SDL_MOUSEBUTTONDOWN:
				m_inputManager.PressKey(ev.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				m_inputManager.ReleaseKey(ev.button.button);
				break;
			default:
				break;
		}
	}

	if (m_inputManager.IsKeyPressed(SDLK_w))
	{
		m_camera2D.SetPosition(m_camera2D.GetPosition() + glm::vec2(0.0f, CAMERA_SPEED));
	}
		
	if (m_inputManager.IsKeyPressed(SDLK_s))
	{
		m_camera2D.SetPosition(m_camera2D.GetPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
	}
		
	if (m_inputManager.IsKeyPressed(SDLK_a))
	{
		m_camera2D.SetPosition(m_camera2D.GetPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
	}
		
	if (m_inputManager.IsKeyPressed(SDLK_d))
	{
		m_camera2D.SetPosition(m_camera2D.GetPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
	}
		
	if (m_inputManager.IsKeyPressed(SDLK_q))
	{
		m_camera2D.SetScale(m_camera2D.GetScale() + SCALE_SPEED);
	}
		
	if (m_inputManager.IsKeyPressed(SDLK_e))
	{
		m_camera2D.SetScale(m_camera2D.GetScale() - SCALE_SPEED);
	}

	if (m_inputManager.IsKeyPressed(SDL_BUTTON_LEFT))
	{
		glm::vec2 mouseCoords = m_inputManager.GetMouseCoords();
		mouseCoords = m_camera2D.ConvertScreenToWorld(mouseCoords);
		
		glm::vec2 playerPosition(0.0f);
		glm::vec2 direction = mouseCoords - playerPosition;
		direction = glm::normalize(direction);

		_bullets.emplace_back(mouseCoords, direction, 0.01f, 1000);
	}		
}

void MainGame::DrawGame()
{
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_colorProgram.Use();
	glActiveTexture(GL_TEXTURE0);
	GLint textureLocation = m_colorProgram.GetUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	GLint pLocation = m_colorProgram.GetUniformLocation("P");
	glm::mat4 cameraMatrix = m_camera2D.GetCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	m_spriteBatch.Begin();

	glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
	static SDLEngine::GLTexture texture = SDLEngine::ResourceManager::GetTexture("Textures/character/idle/i1.png");
	SDLEngine::Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;

	m_spriteBatch.Draw(pos, uv, texture.id, 0.0f, color);

	for (int i = 0; i < _bullets.size(); i++)
	{
		_bullets[i].Draw(m_spriteBatch);
	}

	m_spriteBatch.End();
	m_spriteBatch.RenderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	m_colorProgram.Unuse();

	m_window.SwapBuffer();
}
