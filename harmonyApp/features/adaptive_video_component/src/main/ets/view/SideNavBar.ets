// import { HomeConstants } from "../constants/HomeConstants"

/**
 * Text of tabs.
 */
const tab: Array<string> = ['首页', '朋友', '发布', '消息', '我'];
const TWENTY_SIZE: string = '20%';
const SIXTY_SIZE: string = '60%';
const FULL_SIZE: string = '100%';

/*
 * 侧边导航栏
 */
@Component
export struct SideNavBar {
  @State arr: Array<string> = tab;

  build() {
    SideBarContainer(SideBarContainerType.Overlay) {
      Column() {
        Column()
          .height(TWENTY_SIZE)
        Column() {
          ForEach(this.arr, (item: string) => {
            Column() {
              if (item === this.arr[2]) {
                Image($r('app.media.home_tab_bottom_add'))
                  .width($r('app.float.width_middle'))
              } else {
                Text(item)
                  .fontSize($r('app.float.font_size_middle'))
                  .fontColor(Color.White)
              }
            }
            .height('15%')
            .justifyContent(FlexAlign.Center)
          }, (item: string) => JSON.stringify(item))
        }
        .width(FULL_SIZE)
        .height(SIXTY_SIZE)
        .justifyContent(FlexAlign.Center)
        Column()
          .height(TWENTY_SIZE)
      }
      .width(FULL_SIZE)
      .height(FULL_SIZE)
    }
    .sideBarWidth(FULL_SIZE)
  }
}