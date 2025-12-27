#include "../Scene.h"
#include "../GameObject.h"

Scene::Scene()
{
}

Scene::~Scene()
{

}

std::unique_ptr<GameObject> Scene::unload()
{
	onUnload(); // call each scene's onUnload functions.
	scene_root = nullptr; // make scene root go out of scope to destroy it.
	return std::move(dont_destroy);
}


void Scene::load(std::unique_ptr<GameObject> _dont_destroy)
{
	// make or move dont destroy if it exists
	if (_dont_destroy == nullptr) {
		dont_destroy = std::make_unique<GameObject>("Dont_Destroy");
	}
	else {
		dont_destroy = std::move(_dont_destroy);
	}
	scene_root = std::make_unique<GameObject>("SceneRoot"); // create scene_root for the scene to use
	load(); // actually load the scene (create gameobjects and such)
}

// UNUSED CURRENTLY (does work though)
void Scene::onWindowResize(sf::Vector2i new_size)
{
	// Calculate scale 
	float scale_x = float(new_size.x) / target_resolution.x;
	float scale_y = float(new_size.y) / target_resolution.y;
	float uniform_scale = std::min(scale_x, scale_y);

	// apply scale
	scene_root->getTransform()->setLocalScale(uniform_scale, uniform_scale);
	dont_destroy->getTransform()->setLocalScale(uniform_scale, uniform_scale);

	// Calculate position to center the scene
	float offset_x = (new_size.x - target_resolution.x * uniform_scale) / 2.f;
	float offset_y = (new_size.y - target_resolution.y * uniform_scale) / 2.f;

	scene_root->getTransform()->setLocalPosition(offset_x, offset_y);
	dont_destroy->getTransform()->setLocalPosition(offset_x, offset_y);
}

std::vector<Camera::CameraOutput> Scene::render()
{
	// get all renderable objects
	std::vector<IRenderable*> renderables = scene_root->render();
	std::vector<IRenderable*> other = dont_destroy->render();
	renderables.insert(renderables.end(), other.begin(), other.end());

	// sort renderables list
	std::sort(renderables.begin(), renderables.end(), [](IRenderable* a, IRenderable* b)
		{
			return a->getRenderOrder() < b->getRenderOrder();
		});

	// get all cameras then render to them. 
	std::vector<Camera*> cameras = getAllCameras();
	std::vector<Camera::CameraOutput> outputs;
	for (Camera* cam : cameras){
			cam->render(renderables);
			outputs.push_back(cam->getRenderOutput());
	}	
	return outputs;
}

std::vector<Camera*> Scene::getAllCameras()
{
	// get all cameras
	std::vector<GameObject*> objs = scene_root->getAllChilderenWithComponent<Camera>();
	std::vector<GameObject*> objs2 = dont_destroy->getAllChilderenWithComponent<Camera>();
	// merge both into one list
	objs.insert(objs.end(), objs2.begin(), objs2.end());
	// get camera component
	std::vector<Camera*> cameras;
	for (GameObject* game_obj : objs) {
		if (Camera* cam = game_obj->getComponent<Camera>())
			cameras.push_back(cam);
	}
	return cameras;
}
