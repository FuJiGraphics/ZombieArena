#pragma once

#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <list>
#include <queue>
#include <unordered_map>
#include <chrono>
#include <sstream>
#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Defines.h"
#include "Utils.h"
#include "Singleton.h"
#include "Framework.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "TextGo.h"
#include "SpriteGo.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "ObjectPool.h"
#include "TileMap.h"
#include "Camera.h"
#include "TextUI.hpp"
#include "Anim.h"

// Scenes
#include "Scenes/SceneGameInfo.h"
#include "Scenes/SceneGameIntro.h"
#include "Scenes/SceneGameOver.h"
#include "Scenes/SceneGameClear.h"
#include "Scenes/SceneGameScores.h"
#include "Scenes/SceneTemplate.h"
#include "Scenes/SceneUpgrade.h"
#include "Scenes/SceneSelect.h"
#include "Scenes/SceneWave1.h"
#include "Scenes/SceneWave2.h"
#include "SceneS/SceneWave3.h"
#include "Scenes/SceneWave4.h"
#include "Scenes/SceneWave5.h"

#include "Items/Item.h"
#include "Items/HealingPotion.h"
#include "Items/Ammo.h"