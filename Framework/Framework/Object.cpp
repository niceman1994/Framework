#include "Object.h"

Object::Object() : pBridge(nullptr), strKey(""), TransInfo() { }
Object::Object(Transform _TransInfo) : TransInfo(_TransInfo) { }
Object::~Object() { }