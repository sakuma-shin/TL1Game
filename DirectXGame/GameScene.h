#pragma once
#include"KamataEngine.h"
#include<vector>

class GameScene{
public:
	~GameScene();

	void Initialize();
	void Update();
	void Draw();

private:
	KamataEngine::Camera camera_;
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Input* input_ = nullptr;

};
