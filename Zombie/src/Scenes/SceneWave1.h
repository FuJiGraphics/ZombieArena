#pragma once
#include "SceneTemplate.h"

class SceneWave1 : public SceneTemplate
{
protected:
	SceneWave1(SceneWave1&) = delete;
	SceneWave1& operator=(const SceneWave1&) = delete;

public:
	SceneWave1();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;

};