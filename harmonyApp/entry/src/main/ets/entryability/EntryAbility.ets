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

import { AbilityConstant, ConfigurationConstant, UIAbility, Want } from '@kit.AbilityKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
import { KeyboardAvoidMode, window } from '@kit.ArkUI';
import { initResourceManager } from 'libentry.so';
import { deviceInfo } from '@kit.BasicServicesKit';
import { BreakpointConstants, CommonConstants } from 'base';

const DOMAIN = 0x0000;

export default class EntryAbility extends UIAbility {
  private uiContext?: UIContext;
  private windowClass?: window.Window;

  onCreate(want: Want, launchParam: AbilityConstant.LaunchParam): void {
    this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_NOT_SET);
    initResourceManager(this.context.resourceManager)
    hilog.info(DOMAIN, 'testTag', '%{public}s', 'Ability onCreate');
  }

  onDestroy(): void {
    hilog.info(DOMAIN, 'testTag', '%{public}s', 'Ability onDestroy');
  }

  onWindowStageCreate(windowStage: window.WindowStage): void {
    // Main window is created, set main page for this ability
    hilog.info(DOMAIN, 'testTag', '%{public}s', 'Ability onWindowStageCreate');

    // windowStage.loadContent('pages/Index', (err) => {
    //   if (err.code) {
    //     hilog.error(DOMAIN, 'testTag', 'Failed to load the content. Cause: %{public}s', JSON.stringify(err));
    //     return;
    //   }
    //   hilog.info(DOMAIN, 'testTag', 'Succeeded in loading the content.');
    // });
    windowStage.loadContent('pages/Index', (err) => {
      if (err.code) {
        hilog.error(DOMAIN, 'testTag', 'Failed to load the content. Cause: %{public}s', JSON.stringify(err));
        return;
      }
      try {
        AppStorage.setOrCreate(CommonConstants.WINDOW_STAGE, windowStage);
        windowStage.getMainWindow().then((data: window.Window) => {
          // [Start fullscreen]
          // Set full screen
          data.setWindowLayoutFullScreen(true).then(() => {
            hilog.info(DOMAIN, 'testTag', 'Succeeded in setting the window layout to full-screen mode.');
          })
          let deviceTypeInfo: string = deviceInfo.deviceType;

          if (deviceTypeInfo === '2in1') {
            if (canIUse('SystemCapability.Window.SessionManager')) {
              // 2in1 device settings hide title bar and title bar height
              data.setWindowDecorVisible(false);
              // [StartExclude fullscreen]
              data.setWindowDecorHeight(56)
              // [EndExclude fullscreen]
            }
          }
          // [End fullscreen]


          this.windowClass = data
          this.uiContext = data.getUIContext();
          // 设置虚拟键盘抬起时压缩页面大小为减去键盘的高度
          this.uiContext.setKeyboardAvoidMode(KeyboardAvoidMode.RESIZE)
          let widthBp: WidthBreakpoint = this.uiContext.getWindowWidthBreakpoint();
          let heightBp: HeightBreakpoint = this.uiContext.getWindowHeightBreakpoint();
          AppStorage.setOrCreate(BreakpointConstants.CURRENT_WIDTH_BREAKPOINT, widthBp);
          AppStorage.setOrCreate(BreakpointConstants.CURRENT_HEIGHT_BREAKPOINT, heightBp);

          const windowRect = data.getWindowProperties().windowRect
          AppStorage.setOrCreate(CommonConstants.WINDOW_SIZE, {
            width: px2vp(windowRect.width), height: px2vp(windowRect.height)
          } as window.Size);
          data.on('windowSizeChange', this.onWindowSizeChange);

          //set bar height
          const voidArea = data.getWindowAvoidArea(window.AvoidAreaType.TYPE_SYSTEM)
          this.onAvoidAreaChange({ type: window.AvoidAreaType.TYPE_SYSTEM, area: voidArea });
          let avoidArea: window.AvoidArea = data.getWindowAvoidArea(window.AvoidAreaType.TYPE_CUTOUT);
          this.onAvoidAreaChange({ type: window.AvoidAreaType.TYPE_CUTOUT, area: avoidArea });
          const avoidAreaNavigation =
            this.windowClass.getWindowAvoidArea(window.AvoidAreaType.TYPE_NAVIGATION_INDICATOR)
          this.onAvoidAreaChange({ type: window.AvoidAreaType.TYPE_NAVIGATION_INDICATOR, area: avoidAreaNavigation })
          data.on('avoidAreaChange', this.onAvoidAreaChange);

          data.setSpecificSystemBarEnabled('navigationIndicator', false);
          data.setWindowLayoutFullScreen(true);

          this.updateBreakPoint(data.getWindowProperties().windowRect.width);
          data.on('windowSizeChange', (windowSize: window.Size) => {
            this.updateBreakPoint(windowSize.width);
          })
        })
      } catch (err) {
        hilog.info(DOMAIN, 'testTag', 'fail in setCurrentBreakpoint.');
      }
      hilog.info(DOMAIN, 'testTag', 'Succeeded in loading the content.');
    });
  }

  onWindowStageDestroy(): void {
    // Main window is destroyed, release UI related resources
    hilog.info(DOMAIN, 'testTag', '%{public}s', 'Ability onWindowStageDestroy');
  }

  onForeground(): void {
    // Ability has brought to foreground
    hilog.info(DOMAIN, 'testTag', '%{public}s', 'Ability onForeground');
  }

  onBackground(): void {
    // Ability has back to background
    hilog.info(DOMAIN, 'testTag', '%{public}s', 'Ability onBackground');
  }

  private onWindowSizeChange = (_windowSize: window.Size) => {
    let widthBp: WidthBreakpoint = this.uiContext!.getWindowWidthBreakpoint();
    AppStorage.setOrCreate(BreakpointConstants.CURRENT_WIDTH_BREAKPOINT, widthBp);
    let heightBp: HeightBreakpoint = this.uiContext!.getWindowHeightBreakpoint();
    AppStorage.setOrCreate(BreakpointConstants.CURRENT_HEIGHT_BREAKPOINT, heightBp);
    const currentWindowSize: window.Size = {
      width: px2vp(_windowSize.width), height: px2vp(_windowSize.height)
    };
    AppStorage.setOrCreate(CommonConstants.WINDOW_SIZE, currentWindowSize);
  };

  private onAvoidAreaChange = (avoidArea: window.AvoidAreaOptions) => {
    if (avoidArea.type === window.AvoidAreaType.TYPE_CUTOUT) {
      AppStorage.setOrCreate(CommonConstants.CUTOUT, avoidArea.area);
    } else if (avoidArea.type === window.AvoidAreaType.TYPE_SYSTEM) {
      AppStorage.setOrCreate(CommonConstants.SYSTEM_HEIGHT, this.uiContext?.px2vp(avoidArea.area.topRect.height))
    } else if (avoidArea.type === window.AvoidAreaType.TYPE_NAVIGATION_INDICATOR) {
      AppStorage.setOrCreate(CommonConstants.NAVIGATION_INDICATOR_HEIGHT, this.uiContext?.px2vp(avoidArea.area.bottomRect.height))
    }
  }

  updateBreakPoint(windowWidth: number): void {
    let windowWidthVp = px2vp(windowWidth);
    let curBp: string = '';
    if (windowWidthVp < BreakpointConstants.BREAKPOINT_RANGES[1]) {
      curBp = BreakpointConstants.BREAKPOINT_SM;
    } else if (windowWidthVp < BreakpointConstants.BREAKPOINT_RANGES[2]) {
      curBp = BreakpointConstants.BREAKPOINT_MD;
    } else {
      curBp = BreakpointConstants.BREAKPOINT_LG;
    }
    AppStorage.setOrCreate('currentBreakpoint', curBp);
  }
}