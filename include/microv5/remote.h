#include "main.h"
#include <vector>

class MRemote {
public: std::vector<int> getRemoteButtonData();
public: void updateAll();
public: void addIndex();
public: void onRelease_wheels();
public: void onPress_forward();
public: void onPress_backward();
public: void onPress_turnLeft();
public: void onPress_turnRight();
public: void onPress_startPuller();
public: void onRelease_puller();
};
