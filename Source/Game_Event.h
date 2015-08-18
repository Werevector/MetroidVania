#pragma once
#include "Event_Type.h"
#include <vector>

template<class T>
class Game_Event{

public:

	Event_Type type;
	vector<T> mCarriageData;


};