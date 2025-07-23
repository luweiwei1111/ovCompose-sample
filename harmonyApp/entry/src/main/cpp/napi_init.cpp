/*
 * Tencent is pleased to support the open source community by making ovCompose available.
 * Copyright (C) 2025 THL A29 Limited, a Tencent company. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "libkn_api.h"
#include "napi/native_api.h"
#include <rawfile/raw_file_manager.h>
#include <hilog/log.h>
#include "manager.h"

namespace NativeXComponentSample {

static napi_value Add(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    napi_value args[2] = {nullptr};

    napi_get_cb_info(env, info, &argc, args , nullptr, nullptr);

    napi_valuetype valuetype0;
    napi_typeof(env, args[0], &valuetype0);

    napi_valuetype valuetype1;
    napi_typeof(env, args[1], &valuetype1);

    double value0;
    napi_get_value_double(env, args[0], &value0);

    double value1;
    napi_get_value_double(env, args[1], &value1);

    napi_value sum;
    napi_create_double(env, value0 + value1, &sum);

    return sum;

}

static napi_value MainArkUIViewController(napi_env env, napi_callback_info info) {
    return reinterpret_cast<napi_value>(MainArkUIViewController(env));
}

static napi_value InitResourceManager(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1] = {nullptr};
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    auto manager = OH_ResourceManager_InitNativeResourceManager(env, args[0]);
    auto kt = libkn_symbols();
    kt->kotlin.root.com.tencent.compose.initResourceManager(manager);

    napi_value result;
    napi_create_int32(env, 0, &result);
    return result;
}

static napi_value GetNativeString(napi_env env, napi_callback_info info) {
    // 1.创建C++字符串
    std::string cppStr = "Hello from Native!";
    
    //2.转为NAPI字符串(自动处理内存)
    napi_value jsString;
    napi_create_string_utf8(env, cppStr.c_str(), NAPI_AUTO_LENGTH, &jsString);
    
    return jsString;
}

std::string generate_random_string(size_t length) {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(nullptr)));
        seeded = true;
    }
    static const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const size_t charset_size = sizeof(charset) - 1;
    
    std::string result;
    result.reserve(length);
    for (size_t i = 0; i < length; i++) {
        result += charset[random() % charset_size];
    }
    return result;
}

// 返回1500字节字符串
static napi_value GetLargeString(napi_env env, napi_callback_info info) {
    const size_t length = 1500;
    std::string largeStr = generate_random_string(length);
    
    // 验证长度
    if (largeStr.size() != length) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Init", "largeStr size err");
        return nullptr;
    }
    
    napi_value result;
    napi_status status = napi_create_string_utf8(env, largeStr.c_str(), largeStr.size(), &result);
    if (status != napi_ok) {
        OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "Init", "napi_create_string_utf8 err");
        return nullptr;
    }
    
    return result;
}


EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports) {
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Init", "TextXXX init.cpp Init begins");
    if ((env == nullptr) || (exports == nullptr)) {
        OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Init", "env or exports is null");
        return nullptr;
    }
    
    androidx_compose_ui_arkui_init(env, exports);
    napi_property_descriptor desc[] = {
        {"add", nullptr, Add, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"initResourceManager", nullptr, InitResourceManager, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"MainArkUIViewController", nullptr, MainArkUIViewController, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getContext", nullptr, Manager::GetContext, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"createNativeNode", nullptr, Manager::CreateNativeNode, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"updateNativeNode", nullptr, Manager::UpdateNativeNode, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getString", nullptr, GetNativeString, nullptr, nullptr, nullptr, napi_default, nullptr},
        {"getLargeString", nullptr, GetLargeString, nullptr, nullptr, nullptr, napi_default, nullptr},
    };
    napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    return exports;
}
EXTERN_C_END

static napi_module demoModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "entry",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterEntryModule(void)
{
    napi_module_register(&demoModule);
}

}


