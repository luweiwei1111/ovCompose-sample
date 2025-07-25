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
import { BreakpointConstants2 } from "../constants/BreakpointConstants2";

export class BreakpointType2<T> {
  sm: T;
  md: T;
  lg: T;

  constructor(sm: T, md: T, lg: T) {
    this.sm = sm;
    this.md = md;
    this.lg = lg;
  }

  getValue(currentBreakpoint: string): T {
    if (currentBreakpoint === BreakpointConstants2.BREAKPOINT_MD) {
      return this.md;
    }
    if (currentBreakpoint === BreakpointConstants2.BREAKPOINT_LG) {
      return this.lg;
    } else {
      return this.sm;
    }
  }

  static isSmBreakpoint(currentBreakpoint: string) {
    return currentBreakpoint === BreakpointConstants2.BREAKPOINT_SM;
  }

  static isMdBreakpoint(currentBreakpoint: string) {
    return currentBreakpoint === BreakpointConstants2.BREAKPOINT_MD;
  }

  static isLgBreakpoint(currentBreakpoint: string) {
    return currentBreakpoint === BreakpointConstants2.BREAKPOINT_LG;
  }
}