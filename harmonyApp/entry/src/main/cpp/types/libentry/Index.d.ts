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

import { ArkUIViewController } from "compose/src/main/cpp/types/libcompose_arkui_utils";
import { NodeContent } from "@ohos.arkui.node";

export const add: (a: number, b: number) => number;

export const MainArkUIViewController: () => ArkUIViewController

export const initResourceManager: (resourceManager: resourceManager.ResourceManager) => number;

export const createNativeNode: (nodeContent: NodeContent) => number;

export const createNativeNodeStackView: (nodeContent: NodeContent) => number;

export const createNativeNodeTextView: (nodeContent: NodeContent) => number;

export const createNativeNodeImageView: (nodeContent: NodeContent, imagePath: string) => number;

export const getString: () => string;

export const getLargeString: () => string;
