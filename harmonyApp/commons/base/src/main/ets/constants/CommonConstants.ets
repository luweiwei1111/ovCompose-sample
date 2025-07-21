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
 */

import { Permissions } from '@kit.AbilityKit';
import { geoLocationManager } from '@kit.LocationKit';

export class CommonConstants {
  /**
   * Permissions.
   */
  static readonly PERMISSIONS: Array<Permissions> = ['ohos.permission.APPROXIMATELY_LOCATION',
    'ohos.permission.LOCATION'];
  static readonly locationRequest: geoLocationManager.CurrentLocationRequest = {
    'priority': geoLocationManager.LocationRequestPriority.ACCURACY,
    'scenario': geoLocationManager.LocationRequestScenario.UNSET,
    'maxAccuracy': 20
  };
  /**
   * Constant for screen dpi.
   */
  static readonly SCREEN_DPI_CONSTANT: number = 160;
  /**
   * Full width.
   */
  static readonly FULL_WIDTH: string = '100%';
  /**
   * Full height.
   */
  static readonly FULL_HEIGHT: string = '100%';
  /**
   * Slide up judging distance.
   */
  static readonly UP_SLIDE: number = -20;
  /**
   * Slide down judging distance.
   */
  static readonly DOWN_SLIDE: number = 20;
  /**
   * Column margin left of md.
   */
  static readonly LEFT_MD: number = 24;
  /**
   * Change position line.
   */
  static readonly CHANGE: number = 200;
  /**
   * Column margin right of md.
   */
  static readonly RIGHT_MD: number = 350;
  /**
   * Route avoidance feature array.
   */
  static readonly AVOIDS: Array<number> = [0, 4, 32];
  /**
   * Camera duration.
   */
  static readonly DURATION: number = 200;
  /**
   * LatLng zoom.
   */
  static readonly ZOOM: number = 15;
  /**
   * Languages.
   */
  static readonly languageMap: ReadonlyMap<string, string> = new Map([
    ['en-Latn-US', 'en'],
    ['zh-Hant', 'zh'],
    ['zh-Hans', 'zh_CN']
  ]);
  /**
   * Component opacity value: 1.
   */
  static readonly FULL_OPACITY: number = 1;
  /**
   * Component opacity value: 0.6.
   */
  static readonly SIXTY_OPACITY: number = 0.6;
  static readonly FONT_WEIGHT_FIVE: number = 500;
  static readonly FLEX_BASIS_AUTO = 'auto';
  static readonly NAV_PATH_STACK: string = 'NavPathStack';

  /**
   * Initialized state of avPlayer
   */
  public static readonly AV_PLAYER_INITIALIZED_STATE: string = 'initialized';
  /**
   * Prepared state of avPlayer
   */
  public static readonly AV_PLAYER_PREPARED_STATE: string = 'prepared';
  /**
   * Playing state of avPlayer
   */
  public static readonly AV_PLAYER_PLAYING_STATE: string = 'playing';
  /**
   * Pause state of avPlayer
   */
  public static readonly AV_PLAYER_PAUSED_STATE: string = 'paused';
  /**
   * Completed state of avPlayer
   */
  public static readonly AV_PLAYER_COMPLETED_STATE: string = 'completed';
  /**
   * Error state of avPlayer
   */
  public static readonly AV_PLAYER_ERROR_STATE: string = 'error';
  /**
   * second to millisecond
   */
  public static readonly PROGRESS_THOUSAND: number = 1000;
  /**
   * Seconds in one hour
   */
  public static readonly SECOND_IN_HOUR: number = 3600;
  /**
   * Seconds in one minute
   */
  public static readonly SECOND_IN_MINUTE: number = 60;
  /**
   * Time display separator
   */
  public static readonly COLON: string = ':';
  /**
   * zero
   */
  public static readonly ZERO: number = 0;
  /**
   * one
   */
  public static readonly ONE: number = 1;
  /**
   * ten
   */
  public static readonly TEN: number = 10;
  /**
   * Time compensation 0
   */
  public static readonly TIME_PREFIX: string = '0';
  /**
   * empty avplayer time
   */
  public static readonly EMPTY_TIME: string = '00'
  /**
   * Bottom tab height
   */
  public static readonly BOTTOM_TAB_HEIGHT: string = 'bottom_tab_height';
  /**
   * Bottom navigationBar height
   */
  public static readonly NAVIGATION_INDICATOR_HEIGHT: string = 'bottomRectHeight';
  // type -> window.AvoidAreaType.TYPE_NAVIGATION_INDICATOR
  /**
   * statusBar height
   */
  public static readonly SYSTEM_HEIGHT: string = 'topRectHeight';
  // type -> window.AvoidAreaType.TYPE_SYSTEM
  /**
   * statusBar height
   */
  public static readonly CUTOUT: string = 'CUTOUT';
  // type -> window.AvoidAreaType.TYPE_SYSTEM
  /**
   * window size
   */
  public static readonly WINDOW_SIZE: string = 'windowSize';
  /**
   * avplayer play source array
   */
  public static readonly VIDEO_SOURCE: string[] = [
    '9_16_1.mp4',
    '9_16_2.mp4',
    '1_1.mp4',
    '3_4.mp4',
    '4_3.mp4',
    '16_9.mp4',
    'https://v-cdn.zjol.com.cn/280443.mp4',
    'https://v-cdn.zjol.com.cn/276982.mp4',
    'https://v-cdn.zjol.com.cn/276984.mp4',
    'https://v-cdn.zjol.com.cn/276985.mp4',
    'https://v-cdn.zjol.com.cn/276986.mp4',
    'https://v-cdn.zjol.com.cn/276987.mp4',
    'https://v-cdn.zjol.com.cn/276988.mp4',
  ];
  /**
   * windowStage
   */
  public static readonly WINDOW_STAGE: string = 'windowStage'
}