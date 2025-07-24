package com.tencent.compose.sample

import androidx.compose.foundation.Image
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.foundation.verticalScroll
import androidx.compose.material.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.RectangleShape
import androidx.compose.ui.graphics.graphicsLayer
import androidx.compose.ui.graphics.painter.Painter
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.unit.dp
import com.tencent.compose.sample.rememberLocalImage
import composesample.composeapp.generated.resources.Res
import composesample.composeapp.generated.resources.image_cat
import org.jetbrains.compose.resources.ExperimentalResourceApi
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.border

@OptIn(ExperimentalResourceApi::class)
@Composable
internal fun ComposeView1500Page() {
    val imageBitmap = rememberLocalImage(Res.drawable.image_cat)

    Column(
        modifier = Modifier
            .verticalScroll(rememberScrollState())
            .fillMaxWidth()
    ) {
        repeat(1500) { index ->
            Box(
                modifier = Modifier
                    .size(100.dp)
                    .border(2.dp, Color.Red)
            )
        }
    }
}
