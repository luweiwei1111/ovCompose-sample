/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 *
 */
import { BreakpointConstants, CommonConstants } from 'base';
import { deviceInfo } from '@kit.BasicServicesKit';
import { window } from '@kit.ArkUI';
import { ConfigurationConstant } from '@kit.AbilityKit';
import { MainVideoPage } from './MainVideoPage';
import { SideNavBar } from '../view/SideNavBar';
import { CommentPanel } from '../view/CommentPanel';

/**
 * Home page
 */
@Component
export struct HomePage {
  /**
   * is 2in1 device
   */
  @Provide is2in1Device: boolean = false
  windowStage: window.WindowStage = AppStorage.get(CommonConstants.WINDOW_STAGE) as window.WindowStage;
  mainWin: window.Window = this.windowStage.getMainWindowSync();
  @StorageProp(BreakpointConstants.CURRENT_WIDTH_BREAKPOINT) currentWidthBreakpoint: WidthBreakpoint =
    WidthBreakpoint.WIDTH_XS;
  // pageInfos: NavPathStack = new NavPathStack();

  aboutToAppear(): void {
    this.is2in1Device = deviceInfo.deviceType === '2in1'
    this.setWindowSystemBarProperties('#FFFFFF', ConfigurationConstant.ColorMode.COLOR_MODE_DARK)
  }

  build() {
    NavDestination() {
      GridRow({
        columns: {
          sm: BreakpointConstants.GRID_ROW_COLUMNS_HOME[0], // 小屏：4列
          md: BreakpointConstants.GRID_ROW_COLUMNS_HOME[1], // 中屏幕：8列
          lg: BreakpointConstants.GRID_ROW_COLUMNS_HOME[2]  // 大屏：12列
        }
      }) {
        if (this.currentWidthBreakpoint === WidthBreakpoint.WIDTH_LG ||
          this.currentWidthBreakpoint === WidthBreakpoint.WIDTH_XL) {
          // 左侧导航栏Sidebar
          GridCol({
            span: {
              sm: BreakpointConstants.GRID_COLUMN_SPANS_HOME[0], // 小屏：0列
              md: BreakpointConstants.GRID_COLUMN_SPANS_HOME[0], // 中屏：0列
              lg: BreakpointConstants.GRID_COLUMN_SPANS_HOME[1]  // 大屏：1列
            }
          }) {
            SideNavBar()
          }
        }

        // 中间
        GridCol({
          span: {
            sm: BreakpointConstants.GRID_COLUMN_SPANS_HOME[2], // 小屏：4列
            md: BreakpointConstants.GRID_COLUMN_SPANS_HOME[3], // 中屏：4列
            lg: BreakpointConstants.GRID_COLUMN_SPANS_HOME[3]  // 大屏：7列
          }
        }) {
          // 主页视频区域
          MainVideoPage()
        }

        if (this.currentWidthBreakpoint === WidthBreakpoint.WIDTH_LG ||
          this.currentWidthBreakpoint === WidthBreakpoint.WIDTH_XL) {
          GridCol({
            span: {
              sm: BreakpointConstants.GRID_COLUMN_SPANS_HOME[0], // 小屏：0列
              md: BreakpointConstants.GRID_COLUMN_SPANS_HOME[0], // 中屏：0列
              lg: BreakpointConstants.GRID_COLUMN_SPANS_HOME[2]  // 大屏：4列
            }
          }) {
            // 评论区
            CommentPanel()
          }
        }
      }
    }
    .hideTitleBar(true)
    .backgroundColor(Color.Black)
    .onWillHide(() => {
      this.setWindowSystemBarProperties('#000000', ConfigurationConstant.ColorMode.COLOR_MODE_LIGHT)
    })
  }

  private setWindowSystemBarProperties(statusBarContentColor?: string,
    colorMode?: ConfigurationConstant.ColorMode) {
    let sysBarProps: window.SystemBarProperties = {
      statusBarContentColor: statusBarContentColor
    };
    this.mainWin?.setWindowSystemBarProperties(sysBarProps);
    if (canIUse('SystemCapability.Window.SessionManager')) {
      if (this.is2in1Device) {
        this.mainWin?.setDecorButtonStyle({ colorMode: colorMode })
      }
    }
  }
}