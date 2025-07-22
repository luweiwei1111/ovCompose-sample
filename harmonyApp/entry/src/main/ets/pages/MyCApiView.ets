import  nativeNode from 'libentry.so';
import { NodeContent } from "@ohos.arkui.node"

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
export struct MyCApiView {
  @State insert: boolean = true;
  private nodeContent = new MyNodeContent();
  @State @Watch('watchContent') controlContent: boolean = true;

  aboutToAppear(): void {
    nativeNode.createNativeNode(this.nodeContent);
  }

  watchContent() {
    if (this.getDialogController() == true) {
      nativeNode.createNativeNode(this.nodeContent);
    }
  }

  build() {
    Column() {
      buildNodeContent(new Params(this.insert, this.nodeContent))
    }
    .height('600px')
    .width('100%')
    .justifyContent(FlexAlign.Start)
    .alignItems(HorizontalAlign.Center)
  }
}
