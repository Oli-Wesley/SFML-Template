#include "TitleScene.h"
#include "../Libraries/GameEngine.h"

void TitleScene::load()
{
  PrefabRegistry* pref = PrefabRegistry::get();

  // background
  GameObject* background = scene_root->addChild(std::make_unique<GameObject>("background"));
  background->getTransform()->setLocalPosition(0, 0);
  background->getTransform()->setLocalScale(5, 5);
  background->getTransform()->setLocalZheight(-5);

  background->addComponent<SpriteRenderer>();
  Texture* tex = background->addComponent<Texture>();
  tex->setTexture(AssetDatabase::get()->getTexture("Pixelartimages/Title Screen"));

}
