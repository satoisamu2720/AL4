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
	std::vector<Model*> playerModels = {
	    modelFighterBody_.get(), 
		modelFighterHead_.get(), 
		modelFighterL_arm_.get(),
	    modelFighterR_arm_.get(), 
		modelHammer_.get(),
	};

	//敵キャラモデル
	std::vector<Model*> enemyModels = {
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
	railCamera_->Initialize({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f});

	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f});
	followCamera_->SetTarget(&player_->GetWorldTransform());


	player_->SetViewProjection(&followCamera_->GetViewProjection());
	enemy_->SetViewProjection(&followCamera_->GetEnemyViewProjection());

	

	debugCamera_ = std::make_unique<DebugCamera>(1280,720);
	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

}
void GameScene::Update() {

	switch (sceneMode_) {
	case 0:
		GamePlayUpdate();
		break;
	case 1:
		TitleUpdate();
		break;
	case 2:
		GameOverUpdate();
		break;
	case 3:
		GameClearUpdate();
		break;
	}
}

void GameScene::GamePlayUpdate() {
	player_->Update(); 
	skydome_->Update();
	enemy_->Update();
	ground_->Update();
	
	Collision();
	
	debugCamera_->Update();
	//デバックカメラのifdef

	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_LSHIFT) && isDebugCameraActive_ == false) {
		isDebugCameraActive_ = true;
	} else if (input_->TriggerKey(DIK_LSHIFT) && isDebugCameraActive_ == true) {
		isDebugCameraActive_ = false;
		
	}
    #endif
	fadeColor_.w -= 0.005f;
	fadeSprrite_->SetColor(fadeColor_);
	
	//カメラ処理
	if (isDebugCameraActive_ == true) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		//ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		followCamera_->Update();
		//railCamera_->Update();

		viewProjection_.matView = followCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;

		/*viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;*/
		viewProjection_.TransferMatrix();

		if (timeFlag == true) {
			time++;
			fadeColor_.w += 0.01f;
			fadeSprrite_->SetColor(fadeColor_);
		}
			if (time >= 60) {
				timeFlag = false;
				time = 0;
			    sceneMode_ = 3;
			}
		  
	}
	
}
    void GameScene::Collision() {
	
	// プレイヤー攻撃と敵の腕判定
	

		// 差を求める
	float dx = abs(player_->GetAttackWorldPosition().x - enemy_->GetWorldPosition().x);
	float dz = abs(player_->GetAttackWorldPosition().z - enemy_->GetWorldPosition().z);
	float dy = abs(player_->GetAttackWorldPosition().y - enemy_->GetWorldPosition().y);
		// 衝突したら
		float dist = dx * dx + dy * dy + dz * dz;
		dist = sqrtf(dist);
		if (dist <= 10) {
		timeFlag = true;
		enemy_->SetFlag(enemyflag);
		}
	}
    
    void GameScene::TitleUpdate() {

	    if (input_->TriggerKey(DIK_SPACE)) {
		// リセット
		sceneMode_ = 0;
	    }
    }

    void GameScene::GameOverUpdate() {
	    if (input_->TriggerKey(DIK_SPACE)) {
		Initialize();
		enemyflag = false;
		sceneMode_ = 1;
	    }
    }
    void GameScene::GameClearUpdate() {
	    if (input_->TriggerKey(DIK_SPACE)) {
		Initialize();
		enemyflag = false;
		sceneMode_ = 1;
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
	player_->Draw(viewProjection_);
	skydome_->Draw(viewProjection_);
	ground_->Draw(viewProjection_);
	enemy_->Draw(viewProjection_);
	Model::PostDraw();



	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);
	if (sceneMode_ == 0) {
		fadeSprrite_->Draw();
	}
	if (sceneMode_ == 1) {
		titleSprite_->Draw();
	}
	if (sceneMode_ == 2) {
		titleSprite_->Draw();
	}
	if (sceneMode_ == 3) {
		titleSprite_->Draw();
	}
	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる

	/// </summary>
	
	// スプライト描画後処理
	Sprite::PostDraw();


}


	