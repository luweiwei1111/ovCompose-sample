
#include <cstdint>
#include <string>
#include <cstdio>
#include <arkui/native_interface.h>
#include <arkui/native_node.h>
#include <arkui/native_node_napi.h>
#include <hilog/log.h>

#include "manager.h"
#include "HiTraceSystraceSection.h"

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
    for (int i = 0; i < 1500; i++) {
        nodeAPI->addChild(scroll, stack);
    }
    return scroll;
}

ArkUI_NodeHandle createStackViewExample() {
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp createStackExample");
    ArkUI_NodeHandle scroll = nodeAPI->createNode(ARKUI_NODE_SCROLL);

    // 设置Scroll尺寸
    ArkUI_NumberValue value[] = {480};
    ArkUI_AttributeItem item = {value, 1};
    nodeAPI->setAttribute(scroll, NODE_WIDTH, &item);
    value[0].f32 = 1920;
    nodeAPI->setAttribute(scroll, NODE_HEIGHT, &item);

    // 创建纵向布局容器（Column）
    ArkUI_NodeHandle column = nodeAPI->createNode(ARKUI_NODE_COLUMN);

    // 注册滚动事件
    nodeAPI->registerNodeEvent(scroll, NODE_SCROLL_EVENT_ON_SCROLL, 1, nullptr);
    auto onScroll = [](ArkUI_NodeEvent *event) {
        if (OH_ArkUI_NodeEvent_GetTargetId(event) == 1) {
        }
    };
    nodeAPI->registerNodeEventReceiver(onScroll);

    // 创建并添加1500个Stack到Column中
    for (int i = 0; i < 1500; i++) {
        // 创建Stack并设置固定大小
        ArkUI_NodeHandle stack = nodeAPI->createNode(ARKUI_NODE_STACK);

        // 设置Stack宽度和高度
        ArkUI_NumberValue stackWidth[] = {300};
        ArkUI_AttributeItem widthItem = {stackWidth, 1};
        nodeAPI->setAttribute(stack, NODE_WIDTH, &widthItem);

        ArkUI_NumberValue stackHeight[] = {300}; // 固定高度100
        ArkUI_AttributeItem heightItem = {stackHeight, 1};
        nodeAPI->setAttribute(stack, NODE_HEIGHT, &heightItem);

        // +++ 添加红色边框 +++
        // 1. 设置边框宽度（四边统一为2单位）
        ArkUI_NumberValue borderWidthValue[] = {2.0f};
        ArkUI_AttributeItem borderWidthItem = {borderWidthValue, 1};
        nodeAPI->setAttribute(stack, NODE_BORDER_WIDTH, &borderWidthItem);
        
        // 2. 设置边框颜色（红色，ARGB格式：0xFFFF0000）
        ArkUI_NumberValue borderColorValue[] = {0xFFFF0000}; // 红色
        ArkUI_AttributeItem borderColorItem = {borderColorValue, 1};
        nodeAPI->setAttribute(stack, NODE_BORDER_COLOR, &borderColorItem);
        
        // 3. 设置边框样式为实线
        ArkUI_NumberValue borderStyleValue[] = {{.i32 = ARKUI_BORDER_STYLE_SOLID}};
        ArkUI_AttributeItem borderStyleItem = {borderStyleValue, 1};
        nodeAPI->setAttribute(stack, NODE_BORDER_STYLE, &borderStyleItem);

        // 将Stack添加到Column（关键修改）
        nodeAPI->addChild(column, stack);
        HiTraceSystraceSection s("#Compose::createStackViewExample::KeyToCPPList");
    }

    // 将Column添加到Scroll中
    nodeAPI->addChild(scroll, column);

    return scroll;
}


ArkUI_NodeHandle createTextViewExample() {
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp createStackExample");
    ArkUI_NodeHandle scroll = nodeAPI->createNode(ARKUI_NODE_SCROLL);

    // 设置Scroll尺寸
    ArkUI_NumberValue value[] = {480};
    ArkUI_AttributeItem item = {value, 1};
    nodeAPI->setAttribute(scroll, NODE_WIDTH, &item);
    value[0].f32 = 1920;
    nodeAPI->setAttribute(scroll, NODE_HEIGHT, &item);

    // 创建纵向布局容器（Column）
    ArkUI_NodeHandle column = nodeAPI->createNode(ARKUI_NODE_COLUMN);

    // 设置Column填满父容器
//    ArkUI_AttributeItem fillParent = {value, 1};
//    value[0].f32 = 1.0f; // 1.0表示100%比例
//    nodeAPI->setAttribute(column, NODE_WIDTH, &fillParent);
//    nodeAPI->setAttribute(column, NODE_HEIGHT, &fillParent);

    // 注册滚动事件
    nodeAPI->registerNodeEvent(scroll, NODE_SCROLL_EVENT_ON_SCROLL, 1, nullptr);
    auto onScroll = [](ArkUI_NodeEvent *event) {
        if (OH_ArkUI_NodeEvent_GetTargetId(event) == 1) {
        }
    };
    nodeAPI->registerNodeEventReceiver(onScroll);

    // 创建并添加1500个Stack到Column中
    for (int i = 0; i < 1500; i++) {
        // 创建Text并设置内容（唯一区别）
        ArkUI_NodeHandle text = nodeAPI->createNode(ARKUI_NODE_TEXT);
        std::string contentStr = "测试:" + std::to_string(i + 1);
        ArkUI_AttributeItem content = {.string = contentStr.c_str()};
        nodeAPI->setAttribute(text, NODE_TEXT_CONTENT, &content);

        // 将Stack添加到Column（关键修改）
        nodeAPI->addChild(column, text);
    }

    // 将Column添加到Scroll中
    nodeAPI->addChild(scroll, column);

    return scroll;
}


ArkUI_NodeHandle createImageViewExample(const char *imagePath) {
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "lww TestXXX manager.cpp createStackExample %{public}s", imagePath);
    ArkUI_NodeHandle scroll = nodeAPI->createNode(ARKUI_NODE_SCROLL);

    // 设置Scroll尺寸
    ArkUI_NumberValue value[] = {480};
    ArkUI_AttributeItem item = {value, 1};
    nodeAPI->setAttribute(scroll, NODE_WIDTH, &item);
    value[0].f32 = 1920;
    nodeAPI->setAttribute(scroll, NODE_HEIGHT, &item);

    // 创建纵向布局容器（Column）
    ArkUI_NodeHandle column = nodeAPI->createNode(ARKUI_NODE_COLUMN);
    
    // 注册滚动事件
    nodeAPI->registerNodeEvent(scroll, NODE_SCROLL_EVENT_ON_SCROLL, 1, nullptr);
    auto onScroll = [](ArkUI_NodeEvent *event) {
        if (OH_ArkUI_NodeEvent_GetTargetId(event) == 1) {
        }
    };
    nodeAPI->registerNodeEventReceiver(onScroll);

    // 创建并添加1500个Stack到Column中
    // 创建并添加1500个Image到Column中
    for (int i = 0; i < 1500; i++) {
        // 创建Image节点
        ArkUI_NodeHandle imageNode = nodeAPI->createNode(ARKUI_NODE_IMAGE);
        
        // 设置图片源
        ArkUI_AttributeItem srcItem = {.string = imagePath};
        nodeAPI->setAttribute(imageNode, NODE_IMAGE_SRC, &srcItem);
        
        // 设置图片尺寸
        ArkUI_NumberValue widthValue[] = {100.0f};
        ArkUI_AttributeItem widthItem = {widthValue, 1};
        nodeAPI->setAttribute(imageNode, NODE_WIDTH, &widthItem);
        
        ArkUI_NumberValue heightValue[] = {100.0f};
        ArkUI_AttributeItem heightItem = {heightValue, 1};
        nodeAPI->setAttribute(imageNode, NODE_HEIGHT, &heightItem);
        
        // 设置图片边距（使图片之间有间距）
        ArkUI_NumberValue marginValue[] = {5.0f, 5.0f, 5.0f, 5.0f}; // 上、右、下、左
        ArkUI_AttributeItem marginItem = {marginValue, 4};
        nodeAPI->setAttribute(imageNode, NODE_MARGIN, &marginItem);
        
        // 设置圆角效果
        ArkUI_NumberValue radiusValue[] = {10.0f};
        ArkUI_AttributeItem radiusItem = {radiusValue, 1};
        nodeAPI->setAttribute(imageNode, NODE_BORDER_RADIUS, &radiusItem);
        
        // 设置边框
        ArkUI_NumberValue borderWidthValue[] = {1.0f};
        ArkUI_AttributeItem borderWidthItem = {borderWidthValue, 1};
        nodeAPI->setAttribute(imageNode, NODE_BORDER_WIDTH, &borderWidthItem);
        
        ArkUI_NumberValue borderColorValue[] = {0.5f, 0.5f, 0.5f, 1.0f}; // RGBA
        ArkUI_AttributeItem borderColorItem = {borderColorValue, 4};
        nodeAPI->setAttribute(imageNode, NODE_BORDER_COLOR, &borderColorItem);

        // 将Image添加到Column
        nodeAPI->addChild(column, imageNode);
    }

    // 将Column添加到Scroll中
    nodeAPI->addChild(scroll, column);

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

napi_value Manager::CreateNativeNodeStackView(napi_env env, napi_callback_info info) {
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
            testNode = createStackViewExample();
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp 获得第一个参数NodeContent，以供C-API节点挂载");
            OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &nodeContentHandle_);
            
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp OH_ArkUI_NodeContent_AddNode C-API节点挂载到NodeContent");
            OH_ArkUI_NodeContent_AddNode(nodeContentHandle_, testNode);
        }
    }
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp CreateNativeNode 555");
    return nullptr;
    
}


napi_value Manager::CreateNativeNodeTextView(napi_env env, napi_callback_info info) {
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
            testNode = createTextViewExample();
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp 获得第一个参数NodeContent，以供C-API节点挂载");
            OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &nodeContentHandle_);
            
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp OH_ArkUI_NodeContent_AddNode C-API节点挂载到NodeContent");
            OH_ArkUI_NodeContent_AddNode(nodeContentHandle_, testNode);
        }
    }
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp CreateNativeNode 555");
    return nullptr;
}


//napi_value Manager::CreateNativeNodeImageView(napi_env env, napi_callback_info info) {
//    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp CreateNativeNode");
//    if ((env == nullptr) || (info == nullptr)) {
//        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "CreateNativeNode env or info is null");
//        return nullptr;
//    }
//    
//    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp CreateNativeNode 1");
//    size_t argCnt = 1;
//    napi_value args[1] = {nullptr};
//    if (napi_get_cb_info(env, info, &argCnt, args, nullptr, nullptr) != napi_ok) {
//        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "CreateNativeNode napi_get_cb_info failed");
//    }
//    
//    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp CreateNativeNode 2");
//    if (argCnt != 1) {
//        napi_throw_type_error(env, NULL, "Wrong number of arguments");
//        return nullptr;
//    }
//    
//    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp CreateNativeNode 3");
//    nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1 *>(
//        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));
//    
//    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp OH_ArkUI_GetBasicNodeAPI after");
//    if (nodeAPI != nullptr) {
//        if (nodeAPI->createNode != nullptr && nodeAPI->addChild != nullptr) {
//            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp C-API节点挂载到XComponent");
//            ArkUI_NodeHandle testNode;
//            testNode = createTextViewExample();
//            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp 获得第一个参数NodeContent，以供C-API节点挂载");
//            OH_ArkUI_GetNodeContentFromNapiValue(env, args[0], &nodeContentHandle_);
//            
//            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp OH_ArkUI_NodeContent_AddNode C-API节点挂载到NodeContent");
//            OH_ArkUI_NodeContent_AddNode(nodeContentHandle_, testNode);
//        }
//    }
//    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp CreateNativeNode 555");
//    return nullptr;
//}

napi_value Manager::CreateNativeNodeImageView(napi_env env, napi_callback_info info) {
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp CreateNativeNode");
    
    // 参数检查
    if ((env == nullptr) || (info == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", "CreateNativeNode env or info is null");
        return nullptr;
    }
    
    // 获取参数信息
    size_t argCnt = 2; // 现在需要两个参数
    napi_value args[2] = {nullptr, nullptr};
    napi_value thisArg = nullptr;
    void* data = nullptr;
    
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp CreateNativeNode 1");
    napi_status status = napi_get_cb_info(env, info, &argCnt, args, &thisArg, &data);
    if (status != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", 
                     "CreateNativeNode napi_get_cb_info failed: %{public}d", status);
        return nullptr;
    }
    
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp CreateNativeNode 2");
    if (argCnt < 2) { // 现在需要两个参数
        napi_throw_type_error(env, nullptr, "Wrong number of arguments. Expected 2 arguments.");
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", 
                     "Incorrect argument count: %{public}zu", argCnt);
        return nullptr;
    }
    
    // 解析新的字符串参数
    std::string imagePath;
    napi_valuetype valueType;
    status = napi_typeof(env, args[1], &valueType);
    if (status != napi_ok || valueType != napi_string) {
        napi_throw_type_error(env, nullptr, "Second argument must be a string");
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", 
                     "Second argument is not a string");
        return nullptr;
    }
    
    // 获取字符串长度
    size_t strLength = 0;
    status = napi_get_value_string_utf8(env, args[1], nullptr, 0, &strLength);
    if (status != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", 
                     "Failed to get string length: %{public}d", status);
        return nullptr;
    }
    
    // 分配缓冲区并获取字符串内容
    std::vector<char> buffer(strLength + 1);
    size_t resultLength = 0;
    status = napi_get_value_string_utf8(env, args[1], buffer.data(), buffer.size(), &resultLength);
    if (status != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Manager", 
                     "Failed to get string value: %{public}d", status);
        return nullptr;
    }
    
    imagePath.assign(buffer.data(), resultLength);
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", 
                 "Received image path: %{public}s", imagePath.c_str());
    
    // 原有的节点创建逻辑
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp CreateNativeNode 3");
    nodeAPI = reinterpret_cast<ArkUI_NativeNodeAPI_1 *>(
        OH_ArkUI_QueryModuleInterfaceByName(ARKUI_NATIVE_NODE, "ArkUI_NativeNodeAPI_1"));

    if (nodeAPI != nullptr) {
        if (nodeAPI->createNode != nullptr && nodeAPI->addChild != nullptr) {
            OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Manager", "TestXXX manager.cpp C-API节点挂载到XComponent");
            ArkUI_NodeHandle testNode;
            testNode = createImageViewExample(imagePath.c_str());
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