#include "Object.h"

Object::Object() : pBridge(nullptr), strKey(""), Buffer(), TransInfo() { }
Object::Object(Transform _TransInfo) : TransInfo(_TransInfo), pBridge(nullptr), strKey(""), Buffer() { }
Object::~Object() { }