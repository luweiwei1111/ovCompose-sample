package com.tencent.compose.sample


import androidx.compose.material.Button
import androidx.compose.material.Text
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.material.Text
import androidx.compose.ui.Alignment
import androidx.compose.runtime.*
import androidx.compose.foundation.background
import androidx.compose.foundation.gestures.Orientation
import androidx.compose.foundation.gestures.scrollable
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.verticalScroll
import androidx.compose.material.Button
import androidx.compose.material.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalDensity
import androidx.compose.ui.unit.dp
import kotlin.system.getTimeMillis

@Composable
internal fun CApiView1500Page() {
    // 创建滚动状态
    val scrollState = rememberScrollState()
    // 存储滚动距离（像素）
    var scrollPosition by remember { mutableStateOf(0) }
    val startTime = remember { getTimeMillis() }

    // 监听滚动状态变化
    LaunchedEffect(scrollState.value) {
        val endTime = getTimeMillis()
        println("lww22 CApiView1500Page  all渲染耗时：${endTime - startTime}ms")
    }
    Column(
        modifier = Modifier
            .fillMaxWidth()
            .fillMaxHeight()
            .verticalScroll(scrollState)  // 启用垂直滚动
    ) {
        ArkUIView(
            name = "cApiStackView1500",
            modifier = Modifier
                .fillMaxWidth()
                .fillMaxHeight()
        )
    }
}