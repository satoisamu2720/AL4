#pragma once
#define _USE_MATH_DEFINES
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
#include <stdio.h>
#include "BaseCharacter.h"


class Player :public BaseCharacter {
public:
	
	///
	///
	///
	///
	///
	/*void Initialize(
	    Model* modelBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm, Vector3 Position,
	    Vector3 BodyPosition, Vector3 HeadPosition, Vector3 L_armPosition, Vector3 R_armPosition
	  );*/
	void Initialize(
	    const std::vector<Model*>& models);
	///
	///
	///
	void Update();

	///
	///
	///
	void Draw(ViewProjection view) ;
	///
	///
	///
	void InitializeFloatingGimmick(); 

	void UpdateFloatingGimmick(); 

	void DrawFloatingGimmick(); 

	void BehaviorRootUpdate();
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

	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;
	WorldTransform worldTransformHammer_;

	const ViewProjection* viewProjection_ = nullptr;


	/*Model* modelFighterBody_;
	Model* modelFighterHead_;
	Model* modelFighterL_arm_;
	Model* modelFighterR_arm_;*/

	Input* input_ = nullptr;
	float inputFloat[3]{0, 0, 0};
	int StopTimer = 0;
	RailCamera* railCamera_;
	FollowCamera* followCamera_;
	// キャラクターの移動ベクトル
	
	Vector3 velocity_ = {0, 0, 0};
	Vector3 playerPosition = {0, 0, 0};
	Vector3 bodyPosition = {0,0,0};
	Vector3 headPosition = {0, 1.4f, 0};
	Vector3 l_amrPosition = {-0.5f, 1.4f, 0};
	Vector3 r_amrPosition = {0.5f, 1.4f, 0};
	Vector3 hammerPosition = {0.0f, 0.0f, 0.0f};
	//モーション変数
	float floatingParameter_ = 0.0f;
	
};