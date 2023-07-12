#pragma once
#include "Model.h"
#include "ImGuiManager.h"
#include "TextureManager.h"
#include "WorldTransform.h"
#include "EnemyBullet.h"
#include "assert.h"



class Enemy {
public:

	///
	///
	///
	///
	///
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

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

	/// <summary>
	/// 行動フェーズ
	/// </summary>
	enum class Phase {
		Approach, // 接近する
		Leave,    // 離脱する
	};
	~Enemy();
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_;
	Phase phase_ = Phase ::Approach;
	Vector3 velocity_;
	EnemyBullet* bullet_ = nullptr;
	std::list<EnemyBullet*> bullets_;
};
