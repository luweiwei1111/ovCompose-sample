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

export class WidthBreakpointType<T> {
  sm: T;
  md: T;
  lg: T;
  xl: T;

  /**
   * constructor method
   * @param sm sm point value
   * @param md md point value
   * @param lg lg point value
   * @param xl xl point value
   */
  constructor(sm: T, md: T, lg: T, xl: T) {
    this.sm = sm;
    this.md = md;
    this.lg = lg;
    this.xl = xl;
  }

  getValue(currentBp: number): T {
    switch (currentBp) {
      case WidthBreakpoint.WIDTH_SM:
          return this.sm;
      case WidthBreakpoint.WIDTH_MD:
          return this.md;
      case WidthBreakpoint.WIDTH_LG:
        return this.lg;
      case WidthBreakpoint.WIDTH_XL:
        return this.xl;
      default:
        return this.sm
    }
  }
}