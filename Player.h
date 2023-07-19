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
	void Initialize(Model* model, uint32_t textureHandle);

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
	void Atack();

	Vector3  GetWorldPosition();

	/// <summary>
/// 
/// </summary>
	~Player();
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	PlayerBullet* bullet_ = nullptr;
	float inputFloat[3]{0, 0, 0};
	std::list<PlayerBullet*> bullets_;
	
};