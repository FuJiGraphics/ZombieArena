#pragma once

class Scene;

class SceneMgr : public Singleton<SceneMgr>
{
	friend class Singleton<SceneMgr>;

protected:
	std::vector<Scene*> scenes;

	Scene* currentSceneRaw = nullptr;
	SceneIds startScene = SceneIds::SceneWave1;
	SceneIds currentScene;

	SceneIds nextScene = SceneIds::SceneWave1;

	SceneMgr() = default;
	virtual ~SceneMgr() = default;

	SceneMgr(const SceneMgr&) = delete;
	SceneMgr& operator=(const SceneMgr&) = delete;

	void OnPreDraw();
	void OnPostDraw();

public:
	void Init();
	void Release();

	// Scene* GetCurrentScene() { return scenes[(int)currentScene]; }
	Scene* GetCurrentScene() { return currentSceneRaw; }
	SceneIds GetCurrentSceneId() const { return currentScene; }
	void ChangeScene(SceneIds id, SceneIds currId);

	void Update(float dt);
	void LateUpdate(float dt);

	void Draw(sf::RenderWindow& window);

private:
	float currDt;
};


#define SCENE_MGR (SceneMgr::Instance())

