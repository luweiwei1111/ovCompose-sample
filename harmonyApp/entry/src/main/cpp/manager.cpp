
#include <cstdint>
#include <string>
#include <cstdio>
#include <arkui/native_interface.h>
#include <arkui/native_node.h>
#include <arkui/native_node_napi.h>
#include <hilog/log.h>

#include "manager.h"

ArkUI_NodeContentHandle nodeContentHandle_ = nullptr;

namespace NativeXComponentSample {
#define TEST_TEXT_NUMBER 20

ArkUI_NodeHandle gTextBuf[TEST_TEXT_NUMBER];
int gBarWidth = 10;

Manager Manager::manager_;
static ArkUI_NativeNodeAPI_1 *nodeAPI;

Manager::~Manager() {
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp ~Manager");
    for (auto iter = nativeXComponentMap_.begin(); iter != nativeXComponentMap_.end(); ++iter) {
        if (iter->second != nullptr) {
            delete iter->second;
            iter->second = nullptr;
        }
    }
    nativeXComponentMap_.clear();
    
    for (auto iter = nativeNodeMap_.begin(); iter != nativeNodeMap_.end(); ++iter) {
        if (iter->second != nullptr) {
            delete iter->second;
            iter->second = nullptr;
        }
    }
    nativeNodeMap_.clear();
    
    for (auto iter = containerMap_.begin(); iter != containerMap_.end(); ++iter) {
        if (iter->second != nullptr) {
            delete iter->second;
            iter->second = nullptr;
        }
    }
    containerMap_.clear();
}

ArkUI_NodeHandle createStackExample() {
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp createStackExample");
    ArkUI_NodeHandle scroll = nodeAPI->createNode(ARKUI_NODE_SCROLL);
    ArkUI_NodeHandle stack = nodeAPI->createNode(ARKUI_NODE_STACK);
    ArkUI_NodeHandle text = nodeAPI->createNode(ARKUI_NODE_TEXT);
    ArkUI_NumberValue value[] = {480};
    ArkUI_AttributeItem item = {value, 1};
    ArkUI_AttributeItem content = {.string = "ContentSlot, this is capi view"};
    nodeAPI->setAttribute(scroll, NODE_WIDTH, &item);
    nodeAPI->setAttribute(stack, NODE_WIDTH, &item);
    value[0].f32 = 300;
    nodeAPI->setAttribute(scroll, NODE_HEIGHT, &item);
    value[0].f32 = 300;
    nodeAPI->setAttribute(stack, NODE_HEIGHT, &item);
    value[0].u32 = 0xFFFFFF00;
    nodeAPI->setAttribute(stack, NODE_BACKGROUND_COLOR, &item);
    nodeAPI->setAttribute(text, NODE_TEXT_CONTENT, &content);
    nodeAPI->registerNodeEvent(scroll, NODE_SCROLL_EVENT_ON_SCROLL, 1, nullptr);
    auto onScroll = [](ArkUI_NodeEvent *event) {
        if (OH_ArkUI_NodeEvent_GetTargetId(event) == 1) {
        }
    };
    nodeAPI->registerNodeEventReceiver(onScroll);
    nodeAPI->addChild(stack, text);
    nodeAPI->addChild(scroll, stack);
    return scroll;
}

napi_value Manager::CreateNativeNode(napi_env env, napi_callback_info info) {
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp CreateNativeNode");
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "CreateNativeNode env or info is null");
        return nullptr;
    }
    
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp CreateNativeNode 1");
    size_t argCnt = 1;
    napi_value args[1] = {nullptr};
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "CreateNativeNode napi_get_cb_info failed");
    }
    
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp CreateNativeNode 2");
    if (argCnt != 1) {
        napi_throw_type_error(env, NULL, "Wrong number of arguments");
        return nullptr;
    }
    
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp CreateNativeNode 3");
    nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1 *>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
    
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp OH_ArkUI_GetBasicNodeAPI after");
    if (nodeAPI != nullptr) {
        if (nodeAPI->createNode != nullptr && nodeAPI->addChild != nullptr) {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp C-API节点挂载到XComponent");
            ArkUI_NodeHandle testNode;
            testNode = createStackExample();
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp 获得第一个参数NodeContent，以供C-API节点挂载");
            OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &nodeContentHandle_);
            
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp OH_ArkUI_NodeContent_AddNode C-API节点挂载到NodeContent");
            OH_ArkUI_NodeContent_AddNode(nodeContentHandle_, testNode);
        }
    }
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp CreateNativeNode 555");
    return nullptr;
    
}

napi_value Manager::UpdateNativeNode(napi_env env, napi_callback_info info) {
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp UpdateNativeNode");
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "UpdateNativeNode env or info is null");
        return nullptr;
    }
    
    size_t argCnt = 1;
    napi_value args[1] = {nullptr};
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "UpdateNativeNode napi_get_cb_info failed");
    }
    
    if (argCnt != 1) {
        napi_throw_type_error(env, NULL, "Wrong number of arguments");
        return nullptr;
    }
    
    napi_valuetype valuetype;
    if (napi_typeof(env, args[0], &valuetype) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_typeof failed");
        return nullptr;
    }
    
    if (valuetype != napi_string) {
        napi_throw_type_error(env, NULL, "Wrong number of arguments");
        return nullptr;
    }
    
    char idStr[OH_XCOMPONENT_ID_LEN_MAX + 1] = {'\0'};
    constexpr uint64_t idSize = OH_XCOMPONENT_ID_LEN_MAX + 1;
    size_t length;
    if (napi_get_value_string_utf8(env, args[0], idStr, idSize, &length) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_get_value_string_utf8 failed");
        return nullptr;
    }
    
    return nullptr;
}

napi_value Manager::GetContext(napi_env env, napi_callback_info info) {
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp GetContext");
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "GetContext env or info is null");
        return nullptr;
    }
    
    size_t argCnt = 1;
    napi_value args[1] = {nullptr};
    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "GetContext napi_get_cb_info failed");
    }
    
    if (argCnt != 1) {
        napi_throw_type_error(env, NULL, "wrong number of arguments");
        return nullptr;
    }
    
    napi_valuetype valuetype;
    if (napi_typeof(env, args[0], &valuetype) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_typeof failed");
        return nullptr;
    }
    
    if (valuetype != napi_number) {
        napi_throw_type_error(env, NULL, "valuetype err");
        return nullptr;
    }
    
    int64_t value;
    if (napi_get_value_int64(env, args[0], &value) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_get_value_int64 failed");
        return nullptr;
    }
    
    napi_value exports;
    if (napi_create_object(env, &exports) != napi_ok) {
        napi_throw_type_error(env, NULL, "napi_create_object failed");
        return nullptr;
    }
    
    return exports;
}

void Manager::SetNativeXComponent(std::string &id, OH_NativeXComponent *nativeXComponent) {
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp SetNativeXComponent");
    if (nativeXComponent == nullptr) {
        return;
    }
    
    if (nativeXComponentMap_.find(id) == nativeXComponentMap_.end()) {
        nativeXComponentMap_[id] = nativeXComponent;
        return;
    }
    
    if (nativeXComponentMap_[id] != nativeXComponent) {
        OH_NativeXComponent *tmp = nativeXComponentMap_[id];
        delete tmp;
        tmp = nullptr;
        nativeXComponentMap_[id] = nativeXComponent;
    }
}

void Manager::SetNativeNode(std::string &id, ArkUI_NodeHandle node) {
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp SetNativeNode");
    if (node == nullptr) {
        return;
    }
    
    if (nativeNodeMap_.find(id) == nativeNodeMap_.end()) {
        nativeNodeMap_[id] = node;
        return;
    }
    
    if (nativeNodeMap_[id] != node) {
        ArkUI_NodeHandle tmp = nativeNodeMap_[id];
        delete tmp;
        tmp = nullptr;
        nativeNodeMap_[id] = node;
    }
}

OH_NativeXComponent *Manager::GetNativeXComponent(const std::string &id) {
    return nativeXComponentMap_[id];
}

ArkUI_NodeHandle Manager::GetNativeNode(const std::string &id) {
    return nativeNodeMap_[id];
}

Container *Manager::GetContainer(std::string &id) {
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp GetContainer");
    if (containerMap_.find(id) == containerMap_.end()) {
        Container *instance = Container::GetInstance(id);
        containerMap_[id] = instance;
        return instance;
    }
    
    return containerMap_[id];
}

}