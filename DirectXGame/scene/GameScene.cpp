#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include "VectraCalculation.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	audio_ = Audio::GetInstance();
	input_ = Input::GetInstance();
	textureHandle_ = TextureManager::Load("genshin.png");


	titleTextureHandle_ = TextureManager::Load("title.png");
	titleSprite_ = Sprite::Create(titleTextureHandle_, {0, 0});

	titleTwoTextureHandle_ = TextureManager::Load("title2.png");
	titleTwoSprite_ = Sprite::Create(titleTwoTextureHandle_, {0, 0});

	clearTextureHandle_ = TextureManager::Load("clear.png");
	clearSprite_ = Sprite::Create(clearTextureHandle_, {0, 0});

	uint32_t fadeTexHandle = TextureManager::Load("black.png");
	fadeSprrite_ = Sprite::Create(fadeTexHandle, {0, 0});
	modelFighterBody_.reset(Model::CreateFromOBJ("float_Body", true));
	modelFighterHead_.reset(Model::CreateFromOBJ("float_Head", true));
	modelFighterL_arm_.reset(Model::CreateFromOBJ("float_L_arm", true));
	modelFighterR_arm_.reset(Model::CreateFromOBJ("float_R_arm", true));
	modelEnemyBody_.reset(Model::CreateFromOBJ("enemy", true));
	modelEnemyL_arm_.reset(Model::CreateFromOBJ("needle_L_arm", true));
	modelEnemyR_arm_.reset(Model::CreateFromOBJ("needle_R_arm", true));
	modelHammer_.reset(Model::CreateFromOBJ("hammer", true));

	modelSkydome_ = Model::CreateFromOBJ("sky", true);
	modelGround_ = Model::CreateFromOBJ("ground", true);

	worldTransform_.Initialize();
	viewProjection_.Initialize();
	//自キャラモデル
	 playerModels = {
	    modelFighterBody_.get(), 
		modelFighterHead_.get(), 
		modelFighterL_arm_.get(),
	    modelFighterR_arm_.get(), 
		modelHammer_.get(),
	};

	//敵キャラモデル
	 enemyModels = {
	    modelEnemyBody_.get(),
		modelEnemyL_arm_.get(), 
		modelEnemyR_arm_.get()
	};
	//初期化
	player_ = std::make_unique<Player>();
	player_->Initialize(playerModels);

	enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize(enemyModels);

	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize(modelSkydome_);

	ground_ = std::make_unique<Ground>();
	ground_->Initialize(modelGround_, {1.0f,0.0f,0.0f});
	
	railCamera_ = std::make_unique<RailCamera>();
	railCamera_->Initialize({0.0f, 2.0f, 6.0f}, {0.0f, -3.15f, 0.0f});

	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f});
	


	player_->SetViewProjection(&followCamera_->GetViewProjection());
	enemy_->SetViewProjection(&followCamera_->GetEnemyViewProjection());

	fadeSprrite_->SetColor(fadeColor_);

	debugCamera_ = std::make_unique<DebugCamera>(1280,720);
	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

}
void GameScene::Update() {

	if (behaviorRequest_) {
		// 振るまいを変更する
		behavior_ = behaviorRequest_.value();
		// 各振るまいごとの初期化を実行
		switch (behavior_) {
		case Behavior::Title:
			TitleInitialize();
			break;
		case Behavior::GamePlay:
			GamePlayInitialize();
			break;
		case Behavior::GameOver:
			GameOverInitialize();
			break;
		case Behavior::GameClear:
			GameClearInitialize();
			break;
		}
		// 振るまいリクエストをリセット
		behaviorRequest_ = std::nullopt;
	}

	switch (behavior_) {
	case Behavior::Title:
		TitleUpdate();
		break;
	case Behavior::GamePlay:
		GamePlayUpdate();
		break;
	case Behavior::GameOver:
		GameOverUpdate();
		break;
	case Behavior::GameClear:
		GameClearUpdate();
		break;
	}
}
void GameScene::TitleInitialize() {
	fadeColor_ = {1.0f, 1.0f, 1.0f, 0.0f};
	fadeSprrite_->SetColor(fadeColor_);
	titlePos_ = {0.0f, 0.0f};
	titleSprite_->SetPosition(titlePos_);
	titleTwoPos_ = {0.0f, 0.0f};
	titleTwoSprite_->SetPosition(titleTwoPos_);
}

void GameScene::TitleUpdate() {

	

	if (input_->TriggerKey(DIK_SPACE)) {
		timeFlag = true;
		
	}
	player_->TitleUpdate();
	ground_->Update();

	railCamera_->Update();
	railCamera_->SetTarget(&player_->GetWorldTransform());
	viewProjection_.matView = railCamera_->GetViewProjection().matView;
	viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
	viewProjection_.TransferMatrix();
	if (timeFlag == true) {
		time++;
		
	}
	if (time >= 60) {
		fadeColor_.w += 0.01f;
		fadeSprrite_->SetColor(fadeColor_);
		titlePos_.x -= 1.0f;
		titlePos_.y -= 1.0f;
		titleSprite_->SetPosition(titlePos_);
		titleTwoPos_.x += 1.0f;
		titleTwoPos_.y -= 1.0f;
		titleTwoSprite_->SetPosition(titleTwoPos_);
	}
	if (time >= 120) {
		time = 0;
		timeFlag = false;
		behaviorRequest_ = Behavior::GamePlay;
	}
}
void GameScene::GamePlayInitialize() {
	fadeColor_ = {1.0f, 1.0f, 1.0f, 1.0f};
	fadeSprrite_->SetColor(fadeColor_);
}



void GameScene::GamePlayUpdate() {
	
	player_->Update(); 
	Collision();

	enemy_->Update();
	skydome_->Update();
	ground_->Update();
	
	
	//debugCamera_->Update();
	//デバックカメラのifdef

	fadeColor_.w -= 0.005f;
	fadeSprrite_->SetColor(fadeColor_);
	
		followCamera_->Update();
		viewProjection_.matView = followCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	    followCamera_->SetTarget(&player_->GetWorldTransform());
		
	
	if (timeFlag == true) {
		time++;
		fadeColor_.w += 0.02f;
		fadeSprrite_->SetColor(fadeColor_);
	}
	if (time >= 120) {
		time = 0;
		timeFlag = false;
		behaviorRequest_ = Behavior::GameClear;
	}
}
void GameScene::Collision() {

	// プレイヤー攻撃と敵の腕判定

	if (player_->GetAttackFlag() == true) {

		// 差を求める
		float dx = abs(player_->GetAttackWorldPosition().x - enemy_->GetWorldPosition().x);
		float dz = abs(player_->GetAttackWorldPosition().z - enemy_->GetWorldPosition().z);
		float dy = abs(player_->GetAttackWorldPosition().y - enemy_->GetWorldPosition().y);
		// 衝突したら
		float dist = dx * dx + dy * dy + dz * dz;
		dist = sqrtf(dist);
		if (dist <= 10) {
			timeFlag = true;
			enemyflag = true;
			enemy_->SetFlag(enemyflag);
		}
	}
}

    void GameScene::Reset() {
	
	
	    player_->Initialize(playerModels);
	    enemy_->Initialize(enemyModels);
	    followCamera_->Initialize({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f});
	    followCamera_->SetTarget(&player_->GetWorldTransform());

	    player_->SetViewProjection(&followCamera_->GetViewProjection());
	    enemy_->SetViewProjection(&followCamera_->GetEnemyViewProjection());

		worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};

	    enemyflag = false;
	    fadeColor_.w = 0.0f;
	    enemy_->SetFlag(enemyflag);
	    time = 0;
	    timeFlag = false;
	    behaviorRequest_ = Behavior::Title;
	
	}

    

    void GameScene::GameOverInitialize() {}

    void GameScene::GameClearInitialize() {}
    
   

    void GameScene::GameOverUpdate() {
	    if (input_->TriggerKey(DIK_SPACE)) {
		Reset();
	    }
    }
    void GameScene::GameClearUpdate() {
	    if (input_->TriggerKey(DIK_SPACE)) {
		Reset();
	    }
    }


	void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();


	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();



	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	if (behavior_ == Behavior::GamePlay) {
		player_->Draw(viewProjection_);
		skydome_->Draw(viewProjection_);
		ground_->Draw(viewProjection_);
		enemy_->Draw(viewProjection_);
	}
	
	if (behavior_ == Behavior::Title) {
		player_->Draw(viewProjection_);
		skydome_->Draw(viewProjection_);
		ground_->Draw(viewProjection_);
		//enemy_->Draw(viewProjection_);
	}
	Model::PostDraw();



	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);
	if (behavior_ == Behavior::GamePlay) {
		fadeSprrite_->Draw();
	}
	if (behavior_ == Behavior::Title) {
		titleSprite_->Draw();
		titleTwoSprite_->Draw();
		fadeSprrite_->Draw();
	}
	if (behavior_ == Behavior::GameOver) {
		titleSprite_->Draw();
	}
	if (behavior_ == Behavior::GameClear) {
		clearSprite_->Draw();
	}
	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる

	/// </summary>
	
	// スプライト描画後処理
	Sprite::PostDraw();


}


	