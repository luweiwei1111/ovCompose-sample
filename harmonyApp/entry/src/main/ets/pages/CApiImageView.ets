import  nativeNode from 'libentry.so';
import { NodeContent } from "@ohos.arkui.node"
import { image } from '@kit.ImageKit';
import fs from '@ohos.file.fs'
import { common } from '@kit.AbilityKit';

class Params {
  insert: boolean = false;
  nodeContent: NodeContent;

  constructor(insert: boolean, nodeContent: NodeContent) {
    console.debug("TestXXX Params constructor")
    this.insert = insert;
    this.nodeContent = nodeContent;
  }
}

class MyNodeContent extends NodeContent {

}

@Builder
function buildNodeContent(params: Params) {
  Column() {
    ContentSlot(params.nodeContent)
  }
  .height(200)
  .onAppear(() => {
    console.log("TestXXX MyNodeContent.ets ContentSlot onAppear")
  })
}

@Entry
@Component
export struct CApiImageView {
  @State insert: boolean = true;
  private nodeContent = new MyNodeContent();
  @State @Watch('watchContent') controlContent: boolean = true;
  @State imagePixelMap: PixelMap | undefined = undefined;
  @State imagePath: string = '';
  // 获取应用上下文
  private context: common.Context = getContext(this) as common.Context;

  aboutToAppear(): void {

    // nativeNode.createNativeNodeImageView(this.nodeContent);
    this.getImagePath();
  }

  // 获取资源图片并保存到缓存目录
  async getImagePath() {
    try {
      // 1. 获取资源内容
      const resourceData = await this.context.resourceManager.getMediaContent($r("app.media.image_cat"));
      const arrayBuffer = resourceData.buffer.slice(
        resourceData.byteOffset,
        resourceData.byteOffset + resourceData.byteLength
      );

      // 2. 创建缓存文件路径
      const cacheDir = this.context.cacheDir;
      const imageFilePath = `${cacheDir}/image_cat.png`;

      // 3. 将资源写入文件
      const file = await fs.open(imageFilePath, fs.OpenMode.CREATE | fs.OpenMode.READ_WRITE);
      await fs.write(file.fd, arrayBuffer);
      await fs.close(file.fd);

      // 4. 获取图片信息
      const imageSource = image.createImageSource(imageFilePath);
      // const imageInfo = await imageSource.getImageInfo();

      // 5. 更新状态
      this.imagePath = imageFilePath;
      console.log('lww', `图片路径: ${this.imagePath}`);
      nativeNode.createNativeNodeImageView(this.nodeContent, this.imagePath);
    } catch (error) {
      console.error('lww', `获取图片路径失败: ${error.message}`);
    }
  }


  getImagePixelMap() {
    this.getUIContext()?.getHostContext()?.resourceManager.getMediaContent($r("app.media.image_cat")).then((data) => {
      let arrayBuffer = data.buffer.slice(data.byteOffset, data.byteLength + data.byteOffset)
      let imageSource: image.ImageSource = image.createImageSource(arrayBuffer)
      imageSource.getImageInfo((err, value) => {
        if (err) {
          return
        }
        let opts: image.DecodingOptions = {
          editable: true, desiredSize: { height: value.size.height, width: value.size.width }
        }
        imageSource.createPixelMap(opts, (err, pixelMap) => {
          this.imagePixelMap = pixelMap
        })
      })
    })
  }


  watchContent() {
    if (this.getDialogController() == true) {
      nativeNode.createNativeNodeImageView(this.nodeContent, this.imagePath);
    }
  }

  build() {
    Column() {
      Scroll() {
        buildNodeContent(new Params(this.insert, this.nodeContent))
      }
    }
    .height('100%')
    .width('100%')
    .justifyContent(FlexAlign.Start)
    .alignItems(HorizontalAlign.Center)
  }
}
