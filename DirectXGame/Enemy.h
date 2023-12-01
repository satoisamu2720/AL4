#pragma once
#include "EnemyBullet.h"
#include "ImGuiManager.h"
#include "Model.h"
#include "TextureManager.h"
#include "WorldTransform.h"
#include "assert.h"
#include <list>
#include "BaseCharacter.h"
class Player;

class Enemy : public BaseCharacter {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name= "model">モデル</param>
	/// <param name= "textureHandle">初期座標</param>
	void Initialize(const std::vector<Model*>& models);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name= "viewProjection">ビュープロジェクション）</param>
	void Draw(ViewProjection view);

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	void OnCollision();

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

	Vector3 GetWorldPosition();

	//const std::list<EnemyBullet*>& GetBullets() const { return bullets_; }
	/// <summary>
	/// 行動フェーズ
	/// </summary>
	enum class Phase {
		Approach, // 接近する
		Attack,   // 攻撃する
		Leave,    // 離脱する
	};
	~Enemy();

public:
	WorldTransform worldTransform_;
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;

	Model* model_ = nullptr;
	uint32_t textureHandle_;
	float enemyInputFloat[3]{0, 0, 0};
	Phase phase_ = Phase ::Approach;
	Vector3 velocity_;
	EnemyBullet* bullet_ = nullptr;
	std::list<EnemyBullet*> bullets_;
	static const int kFreInterval = 60;
	Player* player_ = nullptr;
	//Vector3 Normalise;
	
	const ViewProjection* viewProjection_ = nullptr;

	Vector3 enemyPosition = {0, 0, 0};
	Vector3 bodyPosition = {0, 0, 0};
	Vector3 l_amrPosition = {-0.8f, 1, 0};
	Vector3 r_amrPosition = {0.8f, 1, 0};

private:
	//int32_t startTimer = 0;
};