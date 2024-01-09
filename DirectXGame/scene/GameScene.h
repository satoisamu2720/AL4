#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "DebugCamera.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Skydome.h"
#include "RailCamera.h"
#include "FollowCamera.h"
#include "Ground.h"
#include "Enemy.h"
#include <memory>

    /// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

	

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ

	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 
	/// </summary>
	

private: // メンバ変数
	// テクスチャハンドル

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	uint32_t textureHandle_ = 0;
	Sprite* sprite_ = nullptr;

	std::unique_ptr<Model> modelFighterBody_;
	std::unique_ptr<Model> modelFighterHead_;
	std::unique_ptr<Model> modelFighterL_arm_;
	std::unique_ptr<Model> modelFighterR_arm_;
	std::unique_ptr<Model> modelEnemyBody_;
	std::unique_ptr<Model> modelEnemyL_arm_;
	std::unique_ptr<Model> modelEnemyR_arm_;
	std::unique_ptr<Model> modelHammer_;
	
	
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	uint32_t soundDataHandle_ = 0;
	uint32_t voiceHandle_ = 0;

	float inputFloat3[3] = {0, 0, 0};

	std::unique_ptr<DebugCamera> debugCamera_;
	std::unique_ptr<Player> player_;
	std::unique_ptr<Skydome>skydome_;
	Model* modelSkydome_ = nullptr;
	std::unique_ptr<Ground> ground_;
	Model* modelGround_ = nullptr;
	std::unique_ptr<Enemy> enemy_;
	
	Vector3 velocity_;

	//const WorldTransform& GetWorldTransform() { return matProjection; }

	bool isDebugCameraActive_ = false;
	std::unique_ptr<RailCamera> railCamera_;
	std::unique_ptr<FollowCamera> followCamera_;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};