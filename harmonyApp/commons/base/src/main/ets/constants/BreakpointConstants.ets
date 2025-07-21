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

// export const CURRENT_WIDTH_BREAK_POINT = 'currentWidthBreakpoint';
//
// export const CURRENT_HEIGHT_BREAK_POINT = 'currentHeightBreakpoint';

export const TOP_BAR_RECT = 'topBarRect';
//
// export const BOTTOM_BAR_RECT = 'bottomBarRect';
//
export const CUTOUT = 'CUTOUT';

/**
 * Constants for breakpoint.
 */
export class BreakpointConstants {
  /**
   * Breakpoints that represent small device types.
   */
  static readonly BREAKPOINT_SM: string = 'sm';
  /**
   * Breakpoints that represent middle device types.
   */
  static readonly BREAKPOINT_MD: string = 'md';
  /**
   * Breakpoints that represent large device types.
   */
  static readonly BREAKPOINT_LG: string = 'lg';
  /**
   * Grid row column list.
   */
  static readonly GRID_ROW_COLUMNS: number[] = [12, 15, 4];
  /**
   * Grid column span list.
   */
  static readonly GRID_COLUMN_SPANS: number[] = [12, 6, 7, 5, 3, 4, 2];
  /**
   * Breakpoint ranges.
   */
  static readonly BREAKPOINT_RANGES: number[] = [320, 600, 840];
  /**
   * current width breakpoint
   */
  static readonly CURRENT_WIDTH_BREAKPOINT = 'currentWidthBreakpoint'
  /**
   * current height breakpoint
   */
  static readonly CURRENT_HEIGHT_BREAKPOINT = 'currentHeightBreakpoint'
  /**
   * Grid row column list.
   */
  static readonly GRID_ROW_COLUMNS_HOME: number[] = [4, 8, 12];

  /**
   * Grid column span list.
   */
  static readonly GRID_COLUMN_SPANS_HOME: number[] = [0, 1, 4, 7];

  /**
   * Breakpoints ranges.
   */
  static readonly BREAKPOINT_RANGES_HOME: number[] = [320, 600, 840];
}