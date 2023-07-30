#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
#include "VectraCalculation.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete player_;
	delete enemy_;
	delete modelSkydome_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	audio_ = Audio::GetInstance();
	input_ = Input::GetInstance();
	textureHandle_ = TextureManager::Load("genshin.png");

	model_ = Model::Create();
	modelSkydome_ = Model::CreateFromOBJ("sky", true);

	
	
	viewProjection_.Initialize();

	player_ = new Player();
	playerbullet_ = new PlayerBullet();
	player_->Initialize(model_, textureHandle_);

	enemy_ = new Enemy();
	enemy_->SetPlayer(player_);
	Vector3 position = {0, 3, 30};
	enemy_->Initialize(model_, position, velocity_);

	
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_);
	

	debugCamera_ = new DebugCamera(1280, 720);
	
	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

}

void GameScene::Update() {
	player_->Update(); 
	enemy_->Update();
	skydome_->Update();
	CheckAllCollisions();

	debugCamera_->Update();
	//デバックカメラのifdef

	#ifdef _DEBUG
	if (input_->TriggerKey(DIK_LSHIFT) && isDebugcameraActive_ == false) {
		isDebugcameraActive_ = true;
	} else if (input_->TriggerKey(DIK_LSHIFT) && isDebugcameraActive_ == true) {
		isDebugcameraActive_ = false;
		
	}
    #endif
	

	
	//カメラ処理
	if (isDebugcameraActive_ ==true) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		//ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		//ビュープロジェクション行列の更新と転送
		viewProjection_.UpdateMatrix();
	}
	CheckAllCollisions();
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
	enemy_->Draw(viewProjection_);
	skydome_->Draw(viewProjection_);
	Model::PostDraw();



	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる

	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();


}

	void GameScene::CheckAllCollisions() {
	Vector3 posA, posB;
	float enemyBulletRadius = 0.5f;
	float playerBulletRadius = 0.5f;
	float playerRadius = 1.0f;
	float enemyRadius = 1.0f;

	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();

	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullets();
#pragma region
	posA = player_->GetWorldPosition();
	for (EnemyBullet* bullet : enemyBullets) {
		posB = bullet->GetWorldPosition();
		float collide = {
		    (posB.x - posA.x) * (posB.x - posA.x)+ (posB.y - posA.y) * (posB.y - posA.y)+
		    (posB.z - posA.z) * (posB.z - posA.z)};
		if (collide <= (playerRadius+enemyBulletRadius)*( enemyRadius+playerBulletRadius)){
			player_->OnCollision();
			bullet->OnCollision();
		}
	}
#pragma endregion
#pragma region
	posA = enemy_->GetWorldPosition();
	for (PlayerBullet* bullet : playerBullets) {
		posB = bullet->GetWorldPosition();

		float collide = {
		    (posB.x - posA.x) * (posB.x - posA.x)+ (posB.y - posA.y) * (posB.y - posA.y)+
		    (posB.z - posA.z) * (posB.z - posA.z)};
		if (collide <=
		    (enemyRadius + playerBulletRadius) * (enemyRadius + playerBulletRadius)) {
			enemy_->OnCollision();
			bullet->OnCollision();
		}
	}
#pragma endregion
#pragma region
	for (EnemyBullet* eBullet : enemyBullets) {

		posA = eBullet->GetWorldPosition();
		for (PlayerBullet* pbullet : playerBullets) {
			posB = pbullet->GetWorldPosition();
			float collide = {
			    (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) +
			    (posB.z - posA.z) * (posB.z - posA.z)};
			if (collide <=(enemyRadius + playerBulletRadius) * (enemyRadius + playerBulletRadius)) {
				eBullet->OnCollision();
				pbullet->OnCollision();
			}
		}
	}
#pragma endregion
 }