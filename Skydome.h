#pragma once
#include "WorldTransform.h"
#include "Model.h"
    /// <summary>
/// “V‹…
/// </summary>
class Skydome {
public:
	
	void Initialize();

	void Update();

	void Draw(ViewProjection viewProjection_);

	private:
	WorldTransform worldTransform_;
	    Model* model_ = nullptr;
};
