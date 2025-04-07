#include "IComponent.h"
#include "../GameObject.h"

void IComponent::setAttatchedTo(GameObject* gameObject)
{
	attatched_to = gameObject;
}
