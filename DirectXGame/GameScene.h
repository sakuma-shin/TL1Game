#pragma once
#include"KamataEngine.h"
#include<vector>
#include <map>
#include<string>

class GameScene{

	// レベルデータ
	struct LevelData {
		// オブジェクト1個分のデータ
		struct ObjectData {
			std::string fileName;
			KamataEngine::Vector3 translation;
			KamataEngine::Vector3 rotation;
			KamataEngine::Vector3 scaling;
		};
		// オブジェクトのコンテナ
		std::vector<ObjectData> objects;
	};

public:
	~GameScene();

	void Initialize();
	void Update();
	void Draw();

private:
	KamataEngine::Camera camera_;
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Input* input_ = nullptr;

	// レベルデータ格納用インスタンスを作成
	LevelData* levelData =nullptr;

	// モデルデータコンテナ
	std::map<std::string, KamataEngine::Model*> models;

	// オブジェクトデータコンテナ
	std::vector<KamataEngine::WorldTransform*> worldTransforms;
};
