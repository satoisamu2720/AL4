#pragma once
#include "Model.h"
#include "ImGuiManager.h"
#include "TextureManager.h"
#include "WorldTransform.h"
#include <cassert>
#include "Input.h"
#include "PlayerBullet.h"
#include <list>


class Player {
public:
	
	///
	///
	///
	///
	///
	void Initialize(Model* model, Vector3 position);

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

	void SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }
	/// <summary>
/// 
/// </summary>
	~Player();
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	Input* input_ = nullptr;
	float inputFloat[3]{0, 0, 0};
	int StopTimer = 0;
	
	
};