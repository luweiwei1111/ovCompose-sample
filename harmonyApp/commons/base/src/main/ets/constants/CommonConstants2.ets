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

export class CommonConstants2 {
  /**
   * the url of h5 service. When using, it needs to be modified to the actual IP and port.
   */
  static readonly H5_URL: string = 'https://consumer.huawei.com/cn/mobileservices/skytone/';
  /**
   * Full percent.
   */
  static readonly FULL_PERCENT: string = '100%';

  /**
   * Font weight 500.
   */
  static readonly FONT_WEIGHT_500: number = 500;

  /**
   * Text opacity.
   */
  static readonly TEXT_OPACITY: number[] = [1, 0.4, 0.6, 0.05];

  /**
   * Lg sidebar width.
   */
  static readonly LG_SIDEBAR_WIDTH: number = 96;

  /**
   * Two.
   */
  static readonly TWO: number = 2;

  /**
   * Three.
   */
  static readonly THREE: number = 3;

  /**
   * Four.
   */
  static readonly FOUR: number = 4;

  /**
   * Five.
   */
  static readonly FIVE: number = 5;

  /**
   * Width unit.
   */
  static readonly WIDTH_UNIT: string = 'vp';

  /**
   * Device types.
   */
  static readonly DEVICE_TYPES: string[] = ['2in1', 'tablet'];

  /**
   * Tab bar height for sm and md.
   */
  static readonly TAB_BAR_HEIGHT: number = 56;

  /**
   * Bottom rect height.
   */
  static readonly BOTTOM_RECT_HEIGHT: number = 24;
}