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
#include "Sprite.h"

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


	void Collision();

	void Reset();
	/// <summary>
	/// 
	/// </summary>

	void GamePlayInitialize();
	void TitleInitialize();
	void GameOverInitialize();
	void GameClearInitialize();

	void GamePlayUpdate();
	void TitleUpdate();
	void GameOverUpdate();
	void GameClearUpdate();

	enum class Behavior {
		Title,      // 通常状態
		GamePlay, // 攻撃1
		GameOver, // 攻撃2
		GameClear
	};

private: // メンバ変数
	// テクスチャハンドル

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	uint32_t textureHandle_ = 0;
	Sprite* sprite_ = nullptr;

	uint32_t titleTextureHandle_ = 0;
	Sprite* titleSprite_ = nullptr;

	uint32_t titleTwoTextureHandle_ = 0;
	Sprite* titleTwoSprite_ = nullptr;

	uint32_t clearTextureHandle_ = 0;
	Sprite* clearSprite_ = nullptr;

	std::vector<Model*> playerModels;
	std::vector<Model*> enemyModels;

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
	Behavior behavior_ = Behavior::Title;
	std::optional<Behavior> behaviorRequest_ = std::nullopt;
	bool isDebugCameraActive_ = true;
	std::unique_ptr<RailCamera> railCamera_;
	std::unique_ptr<FollowCamera> followCamera_;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
	Sprite* fadeSprrite_ = nullptr;
	Vector4 fadeColor_ = {1.0f, 1.0f, 1.0f, 0.0f};
	 Vector2 titlePos_ = {0.0f, 0.0f};
	 Vector2 titleTwoPos_ = {0.0f, 0.0f};
	bool enemyflag = false;
	bool timeFlag = false;
	float time = 0;
};