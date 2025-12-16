#include "TitleScene.h"
#include "../Libraries/GameEngine.h"

void TitleScene::load()
{
  PrefabRegistry* pref = PrefabRegistry::get();

  // background
  GameObject* background = scene_root->addChild(std::make_unique<GameObject>("background"));
  Transform* background_transform = background->getTransform();
  background_transform->setLocalPosition(0, 0);
  background_transform->setLocalScale(5, 5);
  background_transform->setLocalZheight(-5);

  background->addComponent<SpriteRenderer>();
  background->addComponent<Texture>("Backgrounds/Title_Screen");

  AudioSystem::playSound("FolderTest/Guitar");
}
