#pragma once
#include <string>
#include <vector>

struct ValueNode {
	//default property for value, otherwise whatever is in[]e.g ([GAMEOBJECT], [SCRIPT] ect..)
	std::string type = "PROPERTY";
	// Name of the value either {NAME} in NAME(data) or [blockname(NAME)];
	std::string name;
	// data stored inside the '()' within name(data);
	std::string data;
	// array of all child nodes.
	std::vector<ValueNode> children;

	// finds a child with given type and possible name (I dont know if these are actually useful yet,
	// so will probably change in future. when I actually use this new format.
	ValueNode* findChild(const std::string& type, const std::string& name = "");
	bool hasData() const;

	// template function for converting the string stored in data to a specific type.
	template<typename T>
	T getValue(T defaultValue) const;

	template<typename T>
	T getPropetyWithName(std::string name, T defaultValue) {
		const ValueNode* child = findChild("PROPERTY", name);
		if (child == nullptr)
			return defaultValue;
		return child->getValue<T>(defaultValue);
	}
};
