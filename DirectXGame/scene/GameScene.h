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
#include "Enemy.h"
#include "Skydome.h"
#include "RailCamera.h"

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
	void CheckAllCollisions();


private: // メンバ変数
	// テクスチャハンドル

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	uint32_t textureHandle_ = 0;
	Sprite* sprite_ = nullptr;

	Model* model_ = nullptr;
	
	
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	uint32_t soundDataHandle_ = 0;
	uint32_t voiceHandle_ = 0;

	float inputFloat3[3] = {0, 0, 0};

	DebugCamera* debugCamera_ = nullptr;
	Player* player_ = nullptr;
	Enemy* enemy_ = nullptr;
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;
	
	PlayerBullet* playerbullet_ = nullptr;
	Vector3 velocity_;
	bool isDebugcameraActive_ = false;
	RailCamera* railCamera_;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};