//
// Created on 2025/7/21.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#ifndef HARMONYAPP_MANAGER_H
#define HARMONYAPP_MANAGER_H

#include <string>
#include <unordered_map>

#include <js_native_api.h>
#include <js_native_api_types.h>
#include <ace/xcomponent/native_interface_xcomponent.h>
#include <napi/native_api.h>
#include <arkui/native_node.h>

#include "container.h"

namespace NativeXComponentSample {

class Manager {
public:
    ~Manager();
    
    static Manager *GetInstance() {
        return &Manager::manager_;
    }
    
    static napi_value GetContext(napi_env env, napi_callback_info info);
    static napi_value CreateNativeNode(napi_env env, napi_callback_info info);
    static napi_value UpdateNativeNode(napi_env env, napi_callback_info info);
    
    void SetNativeXComponent(std::string &id, OH_NativeXComponent *nativeXComponent);
    OH_NativeXComponent *GetNativeXComponent(const std::string &id);
    
    void SetNativeNode(std::string &id, ArkUI_NodeHandle node);
    ArkUI_NodeHandle GetNativeNode(const std::string &id);
    
    Container *GetContainer(std::string &id);
    
private:
    static Manager manager_;
    
    std:: unordered_map<std::string, OH_NativeXComponent *> nativeXComponentMap_;
    std:: unordered_map<std::string, ArkUI_NodeHandle> nativeNodeMap_;
    std:: unordered_map<std::string, Container *> containerMap_;
};
}

#endif //HARMONYAPP_MANAGER_H
