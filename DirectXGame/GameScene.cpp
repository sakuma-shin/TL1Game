#include "GameScene.h"
#include "json.hpp"
#include <fstream>
using namespace KamataEngine;

GameScene::~GameScene() { Model::StaticFinalize(); }

void GameScene::Initialize() {

	Model::StaticInitialize();

	worldTransform_.Initialize();

	camera_.Initialize();

	input_ = Input::GetInstance();

	// レベルデータ
	struct LevelData {
		// オブジェクト1個分のデータ
		struct ObjectData {
			std::string fileName;
			Vector3 translation;
			Vector3 rotation;
			Vector3 scaling;
		};
		// オブジェクトのコンテナ
		std::vector<ObjectData> objects;
	};

	// 連結してフルパスを得る
	const std::string fullpath = std::string("Resources/levels/") + "untitled.json";
	// ファイルストリーム
	std::ifstream file;
	// ファイルを開く
	file.open(fullpath);
	// ファイルオープン失敗をチェック
	if (file.fail()) {
		assert(0);
	}

	// JSON文字列から解凍したデータ
	nlohmann::json deserialized;
	// 解凍
	file >> deserialized;
	// 正しいレベルデータファイルかチェック
	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());
	// "name"を文字列として取得
	std::string name = deserialized["name"].get<std::string>();
	// 正しいレベルデータファイルかチェック
	assert(name.compare("scene") == 0);

	// レベルデータ格納用インスタンスを作成
	LevelData* levelData = new LevelData();

	// "objects"の全オブジェクトを走査
	for (nlohmann::json& object : deserialized["objects"]) {
		assert(object.contains("type"));
		// 種別を取得
		std::string type = object["type"].get<std::string>();
		// 種類ごとの処理
		// 
		
		// 
		//   MESH
		if (type.compare("MESH") == 0) {
			// 要素追加
			levelData->objects.emplace_back(LevelData::ObjectData{});
			// 今追加した要素の参照を得る
			LevelData::ObjectData& objectData = levelData->objects.back();
			if (object.contains("file_name")) {
				// ファイル名
				objectData.fileName = object["file_name"];
			}
			// トランスフォームのパラメータ読み込み
			nlohmann::json& transform = object["transform"];

			objectData.translation.x =(float)transform["translation"][1];
			objectData.translation.y = (float)transform["translation"][2];
			objectData.translation.z = (float)-transform["translation"][0];

			objectData.rotation.x =(float)-transform["rotation"][1];
			objectData.rotation.y =(float)-transform["rotation"][2];
			objectData.rotation.z =(float)transform["rotation"][0];

			objectData.scaling.x = (float)transform["scaling"][1];
			objectData.scaling.y = (float)transform["scaling"][2];
			objectData.scaling.z = (float)transform["scaling"][0];


			//  TODO: コライダーのパラメータ読み込み
		}

		// 再帰処理
		if (object.contains("children")) {
			// 要素追加
			levelData->objects.emplace_back(LevelData::ObjectData{});
			// 今追加した要素の参照を得る
			LevelData::ObjectData& objectData = levelData->objects.back();
			if (object.contains("file_name")) {
				// ファイル名
				objectData.fileName = object["file_name"];
			}
			// トランスフォームのパラメータ読み込み
			nlohmann::json& transform = object["transform"];

			objectData.translation.x = (float)transform["translation"][1];
			objectData.translation.y = (float)transform["translation"][2];
			objectData.translation.z = (float)-transform["translation"][0];

			objectData.rotation.x = (float)-transform["rotation"][1];
			objectData.rotation.y = (float)-transform["rotation"][2];
			objectData.rotation.z = (float)transform["rotation"][0];

			objectData.scaling.x = (float)transform["scaling"][1];
			objectData.scaling.y = (float)transform["scaling"][2];
			objectData.scaling.z = (float)transform["scaling"][0];

		}
	}
}

void GameScene::Update() {}

void GameScene::Draw() {
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();

	dxCommon->ClearDepthBuffer();

	Model::PreDraw(dxCommon->GetCommandList());

	Model::PostDraw();

	Sprite::PreDraw(dxCommon->GetCommandList());

	Sprite::PostDraw();
}
