#pragma once

#include "Field.hpp"
#include "ShipManager.hpp"
#include "Structs.hpp"

struct AbilityParameters {
	Field& field;
	ShipManager& shipManager;
	Coordinate& coordinate;
	int& currentDamage;

	AbilityParameters(Field& field, ShipManager& sm, Coordinate& coordinate, int& currentDamage)
		: field(field), shipManager(sm), coordinate(coordinate), currentDamage(currentDamage) {};
};
