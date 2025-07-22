
#include <string>
#include <hilog/log.h>
#include "container.h"

namespace NativeXComponentSample {

std::unordered_map<std::string, Container *> Container::instance_;

Container::Container(const std::string &id) {
    this->id_ = id;
}

Container *Container::GetInstance(const std::string &id) {
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "TextXXX container.cpp GetInstance");
    if (instance_.find(id) == instance_.end()) {
        Container *instance = new Container(id);
        instance_[id] = instance;
        return instance;
    } else {
        return instance_[id];
    }
}

void Container::Release(const std::string &id) {
    Container *render = Container::GetInstance(id);
    if (render != nullptr) {
        free(render);
    }
}

void Container::RegisterCallback(OH_NativeXComponent *nativeXComponent) {
    OH_LOG_Print(LOG_APP, LOG_INFO, LOG_PRINT_DOMAIN, "Callback", "TextXXX container.cpp RegisterCallback");
}
}