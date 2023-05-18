#pragma once
#include "Model.h"
#include "WorldTransform.h"
class PlayerBullet {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name= "model">モデル</param>
	/// <param name= "textureHandle">初期座標</param>
	void Initialize(Model* model,const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Updarte();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name= "viewProjection">ビュープロジェクション）</param>
	void Draw(const ViewProjection& viewProjection);

	private:
		WorldTransform worldTransform_;
		Model* model_;
		uint32_t texturehandle_;
};
