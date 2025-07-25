package com.tencent.compose.sample

import androidx.compose.material.Button
import androidx.compose.material.Text
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxWidth
//import androidx.compose.ui.Modifier
import kotlinx.cinterop.ExperimentalForeignApi
import androidx.compose.material.Text
import androidx.compose.ui.Alignment
import androidx.compose.runtime.*
import platform.resource.com_tencent_kuikly_CurrentTimestamp
import platform.resource.com_compose_LongString
import platform.ffi.callHello
import platform.ffi.printString
import platform.ffi.printStringBegin
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

@OptIn(ExperimentalForeignApi::class)
@Composable
internal fun ComposeToCPage() {
    // 创建滚动状态
    val scrollState = rememberScrollState()
    // 存储滚动距离（像素）
    var scrollPosition by remember { mutableStateOf(0) }
    // 使用dp单位记录滚动距离
    val scrollPositionDp = with(LocalDensity.current) { scrollPosition.toDp() }
    val startTime = remember { getTimeMillis() }
    var count = 0;

    // 监听滚动状态变化
    LaunchedEffect(scrollState.value) {
        if (count == 0) {
            printStringBegin("begin to")
        }
        count = count + 1;
        val endTime = getTimeMillis()
        println("lww33 ComposeToCPage some渲染耗时：${endTime - startTime}ms")
        printString("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789")
        println("lww33 ComposeToCPage  all渲染耗时：${endTime - startTime}ms")
    }

    Column(
        modifier = Modifier
            .fillMaxWidth()
            .fillMaxHeight()
            .verticalScroll(scrollState)  // 启用垂直滚动
    ) {
        // 生成长列表（100个条目）
        repeat(100) { index ->
            Box(
                modifier = Modifier
                    .fillMaxWidth()
                    .height(100.dp)
                    .padding(4.dp)
                    .background(Color.LightGray),
                contentAlignment = Alignment.Center
            ) {
                Text("列表项 #$index")
            }
        }
    }
}