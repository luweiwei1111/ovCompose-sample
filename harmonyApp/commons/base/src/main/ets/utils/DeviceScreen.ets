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

import { display } from '@kit.ArkUI';


export class DeviceScreen {
  /**
   * Get the screen width in fp.
   *
   * @returns screen width.
   */
  public static getDeviceWidth(): number {
    let displayObject = display.getDefaultDisplaySync();
    let screenPixelWidth = displayObject.width;
    let screenDensityPixels = displayObject.densityPixels;
    return screenPixelWidth / screenDensityPixels;
  }

  /**
   * Get the screen width in px.
   *
   * @returns screen width.
   */
  public static getDeviceWidthPX(): number {
    let displayObject = display.getDefaultDisplaySync();
    let screenPixelWidth = displayObject.width;
    return screenPixelWidth;
  }

  /**
   * Get the screen width in px.
   *
   * @returns screen width.
   */
  public static getDeviceHeightPX(): number {
    let displayObject = display.getDefaultDisplaySync();
    let screenPixelHeight = displayObject.height;
    return screenPixelHeight;
  }

  /**
   * Get the screen height in fp.
   *
   * @returns screen height.
   */
  public static getDeviceHeight(): number {
    let displayObject = display.getDefaultDisplaySync();
    let screenPixelHeight = displayObject.height;
    let screenDensityPixels = displayObject.densityPixels;
    return screenPixelHeight / screenDensityPixels;
  }
}