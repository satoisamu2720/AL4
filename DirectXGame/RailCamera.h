#pragma once
#include "ImGuiManager.h"
#include "VectraCalculation.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "FollowCamera.h"
#include <memory>

class RailCamera {

public:
	void Initialize(const Vector3& position, const Vector3& rotation);
	void Update();
	void SetTarget(const WorldTransform* target) { target_ = target; }

	void SetParent(const WorldTransform* parent) { worldTransform_.parent_ = parent; }
	const ViewProjection& GetViewProjection() { return viewProjection_; }
	const WorldTransform& GetWorldTransform() { return worldTransform_; }

private:
	const WorldTransform* target_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
};
