#include "IComponent.h"
#include "../GameObject.h"

void IComponent::setAttatchedTo(GameObject* gameObject)
{
	attached_to = gameObject;
}
