#pragma once
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "VectraCalculation.h"
#include "ImGuiManager.h"
#include <memory>

class FollowCamera {

public:
	void Initialize(const Vector3& position, const Vector3& rotation);
	void Update();

	const ViewProjection& GetViewProjection() { return viewProjection_; }
	const WorldTransform& GetWorldTransform() { return worldTransform_; }

private:
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;
};
