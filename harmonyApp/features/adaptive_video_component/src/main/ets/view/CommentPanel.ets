@Component
export struct CommentPanel {
  build() {
    Column() {
      // 评论列表
      Column() {
        ForEach(commentData, (comment: Comment) => {
          // 主评论容器
          Column() {
            // 第一行：头像、作者、点赞信息
            Row() {
              // 头像
              Image($r('app.media.menu_icon_music_cover'))
                .width(32)
                .height(32)
                .borderRadius(16)
                .margin({ right: 8 })

              // 作者名称
              Text(comment.author)
                .fontSize(16)
                .fontWeight(FontWeight.Bold)
                .margin({ right: 12 })

              // 点赞信息
              Text(`${comment.likeCount}`)
                .fontSize(14)
                .margin({ right: 4 })
              Image($r('app.media.menu_icon_like')) // 假设有点赞图标资源
                .width(16)
                .height(16)
            }
            .width('100%')
            .justifyContent(FlexAlign.Start)
            .padding({ bottom: 8 })

            // 第二行：评论内容
            Text(comment.content)
              .fontSize(14)
              .textAlign(TextAlign.Start)
              .width('100%')
              .margin({ bottom: 8 })

            // 第三行：时间、来源、回复信息
            Row() {
              // 时间和来源
              Text(`${comment.time} 来自:${comment.from}`)
                .fontSize(12)
                .fontColor("#999999")

              // 回复数量和回复按钮（仅当有回复时显示）
              if (comment.replyCount > 0) {
                Text(`  ${comment.replyCount}回复`)
                  .fontSize(12)
                  .fontColor("#999999")
                  .margin({ left: 12 })
              }
            }
            .width('100%')
            .justifyContent(FlexAlign.Start)
            .margin({ bottom: 12 })

            // 回复预览（如果有回复）
            if (comment.replies && comment.replies.length > 0) {
              Column() {
                // 显示第一条回复
                ForEach(comment.replies.slice(0, 1), (reply: Reply) => {
                  Text(`${reply.author}: ${reply.content} //@${reply.replyTo}: ${reply.originalContent}`)
                    .fontSize(13)
                    .fontColor("#666666")
                    .width('100%')
                    .textAlign(TextAlign.Start)
                    .padding(8)
                    .backgroundColor("#f7f7f7")
                    .borderRadius(4)
                })

                // "查看全部回复"提示
                if (comment.replyCount > 1) {
                  Text(`查看全部${comment.replyCount}条回复`)
                    .fontSize(12)
                    .fontColor("#1A8CFF")
                    .width('100%')
                    .textAlign(TextAlign.Start)
                    .margin({ top: 8 })
                }
              }
              .width('100%')
              .margin({ top: 8 })
            }
          }
          .width('100%')
          .padding(12)
          .border({ width: 1, color: "#eeeeee" })
          .margin({ bottom: 8 })
        })
      }
    }
    .width('100%')
    .height('100%')
    .padding(12)
  }
}

// 定义评论数据结构
interface Comment {
  author: string;         // 评论作者
  content: string;        // 评论内容
  likeCount: number;      // 点赞数
  replyCount: number;     // 回复数
  from: string;           // 来自地区
  time: string;           // 评论时间
  replies?: Reply[];      // 回复列表
}

// 定义回复数据结构
interface Reply {
  author: string;        // 回复者名称
  content: string;       // 回复内容
  replyTo: string;       // 回复对象
  originalContent: string; // 原评论内容
}

// 模拟评论数据
const commentData: Comment[] = [
  {
    author: "黄河",
    content: "君不见黄河之水天上来",
    likeCount: 876,
    replyCount: 2,
    from: "北京",
    time: "10-23",
    replies: [
      {
        author: "长江",
        content: "下一句是奔流到海不复回",
        replyTo: "黄河",
        originalContent: "君不见黄河之水天上来"
      },
      {
        author: "森林",
        content: "好诗好诗",
        replyTo: "黄河",
        originalContent: "君不见黄河之水天上来"
      }
    ]
  },
  {
    author: "森林",
    content: "森林，是以木本植物为主体的生物群落",
    likeCount: 323,
    replyCount: 0,
    from: "云南",
    time: "10-23"
  },
  {
    author: "宇宙奥秘",
    content: "无垠的蓝深邃如宇宙",
    likeCount: 666,
    replyCount: 1,
    from: "太空",
    time: "10-22",
    replies: [
      {
        author: "天文爱好者",
        content: "这描述太美了",
        replyTo: "宇宙奥秘",
        originalContent: "无垠的蓝深邃如宇宙"
      }
    ]
  }
];