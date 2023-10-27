#pragma once
#include "Model.h"
#include "ImGuiManager.h"
#include "TextureManager.h"
#include "WorldTransform.h"
#include <cassert>
#include "Input.h"
#include "PlayerBullet.h"
#include <list>
#include "RailCamera.h"
#include "math.h"

class Player {
public:
	
	///
	///
	///
	///
	///
	void Initialize( Model* modelBody, Model* modeHead, Model* modeL_arm, Model* modelR_arm,Vector3 position);

	///
	///
	///
	void Update();

	///
	///
	///
	void Draw(ViewProjection view);
	///
	///
	///
	void OnCollision();
	
	Vector3  GetWorldPosition();

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}
	const WorldTransform& GetWorldTransform() { return worldTransform_; }
	/// <summary>
/// 
/// </summary>
	~Player();

private:
	WorldTransform worldTransform_;
	const ViewProjection* viewProjection_ = nullptr;


	std::unique_ptr<Model> modelFighterBody_;
	std::unique_ptr<Model> modelFighterHead_;
	std::unique_ptr<Model> modelFighterL_arm_;
	std::unique_ptr<Model> modelFighterR_arm_;

	Input* input_ = nullptr;
	float inputFloat[3]{0, 0, 0};
	int StopTimer = 0;
	RailCamera* railCamera_;
	FollowCamera* followCamera_;
	// キャラクターの移動ベクトル
	
	Vector3 velocity_ = {0, 0, 0};
	
};