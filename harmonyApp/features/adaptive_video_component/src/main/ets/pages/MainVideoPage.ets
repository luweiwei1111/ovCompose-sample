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
import { CommonConstants } from 'base';
import { Recommend } from './Recommend';
import { hilog } from '@kit.PerformanceAnalysisKit';

/**
 * TAB is the index of the picture
 */
const TAB_ICON_INDEX = 2
const LOG_TAG = 'Home'
const DOMAIN = 0x0000;

/**
 * feature page
 */
@Component
export struct MainVideoPage {
  @State selTabIndex: number = 0
  @StorageProp(CommonConstants.NAVIGATION_INDICATOR_HEIGHT) bottomRectHeight: number = 0
  @Provide hideTab: boolean = false
  /**
   * Is bottom tab bar immersive
   */
  @Provide isBottomTabImmersive: boolean = false
  // /**
  //  * Page stack
  //  */
  // @Consume('pathStack') pageStack: NavPathStack;
  /**
   * is 2in1 device
   */
  @Consume is2in1Device: boolean;
  /**
   * Bottom tab data
   */
  private tabData: ResourceStr[] = [$r('app.string.bottom_tab_title_index'), $r('app.string.bottom_tab_title_friend'),
    $r('app.string.bottom_tab_title_friend'), $r('app.string.bottom_tab_title_message'),
    $r('app.string.bottom_tab_title_mine')]
  private controller: TabsController = new TabsController();
  /**
   * Determine which subpage to enter
   */
  private pageIndex: number = 0

  aboutToAppear(): void {
    // this.pageIndex = this.pageStack.getParamByName('Home')[0] as number
    hilog.info(DOMAIN, LOG_TAG, `Home pageIndex = ${this.pageIndex}`)
  }

  // custom tab
  @Builder
  Tab(tabIndex: number, tabTitle: ResourceStr, tabIcon?: ResourceStr) {
    if (tabIcon) {
      Row() {
        Image(tabIcon)
          .width(30)
          .height(30)
      }
      .height(56)
      .layoutWeight(1)
      .justifyContent(FlexAlign.Center)
    } else {
      Text(tabTitle)
        .fontSize(16)
        .lineHeight(24)
        .fontWeight(500)
        .fontColor(this.selTabIndex === tabIndex ? Color.White : $r("app.color.color_white_forty_percent"))
        .layoutWeight(1)
        .textAlign(TextAlign.Center)
        .height(56)
        .onClick(() => {
          this.controller.changeIndex(tabIndex);
          this.selTabIndex = tabIndex;
        })
    }
  }

  build() {
    if (this.is2in1Device) {
      Recommend({ pageIndex: this.pageIndex })
    } else {
      RelativeContainer() {
        Tabs({ barPosition: BarPosition.Start, controller: this.controller }) {
          TabContent() {
            Recommend({ pageIndex: this.pageIndex })
          }
        }
        .barHeight(0)
        .scrollable(false)

        Row() {
          ForEach(this.tabData, (tabTitle: ResourceStr, index: number) => {
            this.Tab(index, tabTitle, index === TAB_ICON_INDEX ? $r('app.media.home_tab_bottom_add') : undefined)
          }, (item: string) => item)
        }
        .width('100%')
        .alignRules({
          bottom: { 'anchor': '__container__', 'align': VerticalAlign.Bottom }
        })
        .onAreaChange((_oldValue: Area, newValue: Area) => {
          try {
            AppStorage.setOrCreate<number>(CommonConstants.BOTTOM_TAB_HEIGHT, newValue.height as number);
          } catch (err) {
            hilog.error(DOMAIN, LOG_TAG, `onAreaChange exception = ${JSON.stringify(err)}`)
          }
        })
        .margin({ bottom: this.bottomRectHeight })
        .visibility(this.hideTab ? Visibility.None : Visibility.Visible)
      }
    }
  }
}