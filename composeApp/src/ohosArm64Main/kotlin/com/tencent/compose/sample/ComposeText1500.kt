package com.tencent.compose.sample

import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxHeight
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.text.ClickableText
import androidx.compose.material.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.AnnotatedString
import androidx.compose.ui.text.SpanStyle
import androidx.compose.ui.text.buildAnnotatedString
import androidx.compose.ui.text.font.FontStyle
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.withStyle
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp

@Composable
internal fun ComposeText1500Page() {
    val textContent = "Compose Text 文本 1500"
    LazyColumn(modifier = Modifier.fillMaxSize().fillMaxHeight()) {
        // 重复展示1500个Text项
        items(1500) { index ->
            Text(
                text = "[$index] 项目内容 ${index + 1}",
                color = Color.Black,
                fontSize = 16.sp
            )
//            Spacer(modifier = Modifier
//                .fillMaxWidth()
//                .height(10.dp))
        }
    }
}

@Composable
private fun AnnotatedStringTextPage() {
    val annotatedString3 = buildAnnotatedString {
        withStyle(style = SpanStyle(fontWeight = FontWeight.Bold, color = Color.Blue)) {
            append("Compose Text ")
        }
        withStyle(style = SpanStyle()) {
            append("通过")
        }
        withStyle(style = SpanStyle(fontStyle = FontStyle.Italic, color = Color.Red)) {
            append(" AnnotatedString ")
        }
        withStyle(style = SpanStyle()) {
            append("设置富文本效果！")
        }
        withStyle(style = SpanStyle(color = Color.Red)) {
            append("点击 www.qq.com")
        }

        addStringAnnotation(
            tag = "URL",
            annotation = "https://v.qq.com",
            start = 40,
            end = 55
        )
    }
    Column(modifier = Modifier.fillMaxSize()) {
        Text(text = annotatedString3, modifier = Modifier.clickable {
            annotatedString3.getStringAnnotations("URL", 7, 14)
                .firstOrNull()?.let { it ->
                    println("jump to v.qq.com $it")
                }
        })
        ClickableText(
            text = AnnotatedString("ClickableText ") + annotatedString3,
            onClick = { integer ->
                annotatedString3.getStringAnnotations("URL", integer, integer).firstOrNull()?.let {
                    println("jump to v.qq.com $it")
                }
            })
    }

}