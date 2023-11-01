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
	void Initialize(
	    Model* modelBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm,
	    Vector3 BodyPosition, Vector3 HeadPosition, Vector3 L_armPosition, Vector3 R_armPosition);

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
	const WorldTransform& GetWorldTransform() { return worldTransformBody_; }
	/// <summary>
/// 
/// </summary>
	~Player();

private:
	WorldTransform worldTransform_;

	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;

	const ViewProjection* viewProjection_ = nullptr;


	Model* modelFighterBody_;
	Model* modelFighterHead_;
	Model* modelFighterL_arm_;
	Model* modelFighterR_arm_;

	Input* input_ = nullptr;
	float inputFloat[3]{0, 0, 0};
	int StopTimer = 0;
	RailCamera* railCamera_;
	FollowCamera* followCamera_;
	// キャラクターの移動ベクトル
	
	Vector3 velocity_ = {0, 0, 0};
	
};