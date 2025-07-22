//
// Created on 2025/7/21.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONYAPP_CONTAINER_H
#define HARMONYAPP_CONTAINER_H

#include <string>
#include <unordered_map>
#include <ace/xcomponent/native_interface_xcomponent.h>

const unsigned int LOG_PRINT_DOMAIN = 0xFF00;

namespace NativeXComponentSample {

class Container {
public:
    explicit Container(const std::string &id);
    ~Container() = default;
    static Container *GetInstance(const std::string &id);
    static void Release(const std::string &id);
    void RegisterCallback(OH_NativeXComponent *nativeXComponent);
    
public:
    static std::unordered_map<std::string, Container *> instance_;
    std::string id_;
    
private:
    OH_NativeXComponent_Callback containerCallback_;
    OH_NativeXComponent_MouseEvent_Callback mouseCallback_;
};
}
#endif //HARMONYAPP_CONTAINER_H
