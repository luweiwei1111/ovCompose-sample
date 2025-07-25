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

package com.tencent.compose.sample.mainpage

import com.tencent.compose.sample.ArkNativeImage1500Page
import com.tencent.compose.sample.ArkNativeText1500Page
import com.tencent.compose.sample.ArkNativeView1500Page
import com.tencent.compose.sample.CApiImage1500Page
import com.tencent.compose.sample.CApiText1500Page
import com.tencent.compose.sample.CApiView1500Page
import com.tencent.compose.sample.ComposeImage1500Page
import com.tencent.compose.sample.ComposeLongStringPage
import com.tencent.compose.sample.InteropCAPIView
import com.tencent.compose.sample.InteropListNested
import com.tencent.compose.sample.InteropListSimple
import com.tencent.compose.sample.InteropRenderOrder
import com.tencent.compose.sample.InteropTextInput
import com.tencent.compose.sample.InteropVideo
import com.tencent.compose.sample.InteropWebView
import com.tencent.compose.sample.ComposeText1500Page
import com.tencent.compose.sample.ComposeToCPage
import com.tencent.compose.sample.ComposeView1500Page
import com.tencent.compose.sample.data.DisplayItem
import composesample.composeapp.generated.resources.Res
import composesample.composeapp.generated.resources.image_cat
import composesample.composeapp.generated.resources.interop_list
import composesample.composeapp.generated.resources.interop_nested_scroll
import composesample.composeapp.generated.resources.interop_state
import composesample.composeapp.generated.resources.layers
import composesample.composeapp.generated.resources.simple_text
import org.jetbrains.compose.resources.ExperimentalResourceApi

@OptIn(ExperimentalResourceApi::class)
internal actual fun platformSections(): List<DisplayItem> {
    return listOf(
        DisplayItem("混排层级", Res.drawable.layers) { InteropRenderOrder() },
        DisplayItem("混排滑动", Res.drawable.interop_list) { InteropListSimple() },
        DisplayItem("混排嵌滑", Res.drawable.interop_nested_scroll) { InteropListNested() },
        DisplayItem("混排状态", Res.drawable.interop_state) { InteropTextInput() },
        DisplayItem("短视频", Res.drawable.interop_state) { InteropVideo() },
        DisplayItem("WebView", Res.drawable.interop_state) { InteropWebView() },
        DisplayItem("CAPIView", Res.drawable.interop_state) { InteropCAPIView() },
        DisplayItem("compose 1500View", Res.drawable.interop_state) { ComposeView1500Page() },
        DisplayItem("compose 1500Text", Res.drawable.interop_state) { ComposeText1500Page() },
        DisplayItem("compose 1500Image", Res.drawable.interop_state) { ComposeImage1500Page() },
//        DisplayItem("ArkNative 1500View", Res.drawable.interop_state) { ArkNativeView1500Page() },
//        DisplayItem("ArkNative 1500Text", Res.drawable.interop_state) { ArkNativeText1500Page() },
//        DisplayItem("ArkNative 1500Image", Res.drawable.interop_state) { ArkNativeImage1500Page() },
        DisplayItem("CApi 1500View", Res.drawable.interop_state) { CApiView1500Page() },
        DisplayItem("CApi 1500Text", Res.drawable.interop_state) { CApiText1500Page() },
        DisplayItem("CApi 1500Image", Res.drawable.interop_state) { CApiImage1500Page() },
        DisplayItem("long string", Res.drawable.interop_state) { ComposeLongStringPage() },
        DisplayItem("Kotlin to C", Res.drawable.interop_state) { ComposeToCPage() },
        )
}