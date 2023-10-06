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

	model_.reset(Model::CreateFromOBJ("float_Body", true));
	modelSkydome_ = Model::CreateFromOBJ("sky", true);
	modelGround_ = Model::CreateFromOBJ("ground", true);
	worldTransform_.Initialize();
	
	
	viewProjection_.Initialize();

	player_ = std::make_unique<Player>();
	Vector3 playerPosition(0, -0.5, 6);
	// 自キャラの初期化
	player_->Initialize(model_.get(), playerPosition);

	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize(modelSkydome_);
	ground_ = std::make_unique<Ground>();
	ground_->Initialize(modelGround_, {1.0f,-2.0f,0.0f});
	
	railCamera_ = std::make_unique<RailCamera>();
	railCamera_->Initialize({0.0f, 0.0f, -30.0f}, {0.0f, 0.0f, 0.0f});

	player_->SetParent(&railCamera_->GetWorldTransform());

	debugCamera_ = std::make_unique<DebugCamera>(1280,720);
	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

}

void GameScene::Update() {
	player_->Update(); 
	skydome_->Update();
	ground_->Update();
	
	

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
		railCamera_->Update();
		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
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
	Model::PostDraw();



	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる

	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();


}

	