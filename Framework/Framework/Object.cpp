#include "Object.h"

Object::Object() : pBridge(nullptr), strKey(""), Buffer(), HitCount(0), TransInfo() { }
Object::Object(Transform _TransInfo) : TransInfo(_TransInfo), pBridge(nullptr), strKey(""), Buffer(), HitCount(0) { }
Object::~Object() { }
