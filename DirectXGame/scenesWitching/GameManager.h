#pragma once
#include <memory>
#include "scenesWitching/IScene.h"
#include "scenesWitching/TitleScene.h"
#include "scenesWitching/GameStageScene.h"
#include "scenesWitching/ClearScene.h"
class GameManager {
private:
	std::unique_ptr<IScene> sceneArr_[3];
	int currentSceneNo_;
	int preSceneNo_;


public:
	GameManager();
	~GameManager();
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	// 汎用機能
	Input* input = nullptr;
	Audio* audio = nullptr;
	AxisIndicator* axisIndicator = nullptr;
	PrimitiveDrawer* primitiveDrawer = nullptr;
	GameScene* gameScene = nullptr;
	int Run();
};
