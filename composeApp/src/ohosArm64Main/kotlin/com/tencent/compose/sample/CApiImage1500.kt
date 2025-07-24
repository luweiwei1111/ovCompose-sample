package com.tencent.compose.sample

import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.napi.js
import kotlinx.cinterop.ExperimentalForeignApi

@OptIn(ExperimentalForeignApi::class)
@Composable
internal fun CApiImage1500Page() {
    Column() {
        ArkUIView(
            name = "cApiImageView1500",
            modifier = Modifier
                .fillMaxWidth()
                .fillMaxHeight()
        )
    }
}