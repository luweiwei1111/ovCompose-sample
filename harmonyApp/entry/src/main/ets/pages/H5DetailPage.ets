/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { webview } from "@kit.ArkWeb";
import { window } from "@kit.ArkUI";
import { BreakpointConstants2, BreakpointType2, CommonConstants2 } from "base";

/**
 * 提供给h5页面的arkTS接口定义类。
 */
class WebClassProxy {
  close() {
    this.destroySubWindow();
  }

  private destroySubWindow() {
    window.findWindow("h5DetailPage").destroyWindow((err) => {
      const errCode: number = err.code;
      if (errCode) {
        console.error("Failed to destroy the window. Cause:", JSON.stringify(err));
        return;
      }
      console.info('Succeeded to destroy subWindow.');
    });
  }
}

@Component
export struct H5DetailPage {
  @StorageLink('currentBreakpoint') currentBreakpoint: string = BreakpointConstants2.BREAKPOINT_LG;
  webController: webview.WebviewController = new webview.WebviewController();
  webClassProxy: WebClassProxy = new WebClassProxy();

  async aboutToAppear(): Promise<void> {
    const windowClass = await (AppStorage.get('windowStage') as window.WindowStage).getMainWindow();
    windowClass.on('windowRectChange', (data: window.RectChangeOptions) => {
      try {
        const subWindow = window.findWindow("h5DetailPage");
        subWindow.moveWindowTo(data.rect.left, data.rect.top);
        subWindow.resize(data.rect.width, data.rect.height);
      } catch (err) {
        console.error("This window state is abnormal", err);
      }
    })
  }

  onBackPress(): boolean | void {
    this.webClassProxy.close();
  }

  build() {
    Row() {
      Stack({ alignContent: Alignment.End }) {
        // 这里创建一个空的框框填满屏幕,实现窗口左边点击回退功能。
        Column() {}
        .width('100%')
        .height('100%')
        .onClick(() => {
          this.webClassProxy.close();
        })

        Column() {
          Web({ src: CommonConstants2.H5_URL, controller: this.webController })
            .enableNativeEmbedMode(true)
            .clip(true)
            .borderRadius(BreakpointType2.isSmBreakpoint(this.currentBreakpoint) ? 0 : 20)
            .domStorageAccess(true)
            .multiWindowAccess(true)
            .javaScriptAccess(true)
            .geolocationAccess(false)
            .imageAccess(true)
            .onlineImageAccess(true)
            .fileAccess(true)
            .mediaPlayGestureAccess(true)
            .mixedMode(MixedMode.Compatible)
            .onControllerAttached(() => {
              this.webController.registerJavaScriptProxy(this.webClassProxy, "webClass", ["close"]);
              this.webController.refresh();
            })
        }
        .height(BreakpointType2.isSmBreakpoint(this.currentBreakpoint) ? '100%' :
          BreakpointType2.isMdBreakpoint(this.currentBreakpoint) ? '98%' : '95%')
        .width(BreakpointType2.isSmBreakpoint(this.currentBreakpoint) ? '100%' :
          BreakpointType2.isMdBreakpoint(this.currentBreakpoint) ? '50%' : 480)
        .margin(BreakpointType2.isSmBreakpoint(this.currentBreakpoint) ? 0 : 10)
      }
    }
    .height('100%')
    .width('100%')
  }
}