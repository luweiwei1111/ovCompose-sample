package com.tencent.compose.sample

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.size
import androidx.compose.runtime.Composable
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import platform.basic.ARKUI_NODE_BUTTON
import platform.basic.ArkUI_NativeNodeAPI_1

@Composable
internal fun CApiView1500Page() {
    Column {
        ArkUIView(
            name = "cApiStackView1500",
            modifier = Modifier
                .fillMaxWidth()
                .fillMaxHeight()
        )
    }
}