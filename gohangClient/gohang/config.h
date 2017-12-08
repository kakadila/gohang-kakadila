#ifndef CONFIG_H
#define CONFIG_H

//窗口宽高
#define WIN_SIZE_X 600
#define WIN_SIZE_Y 500

//棋盘相对窗口偏移
#define OFFSET_X 30
#define OFFSET_Y 40

//棋盘宽高
#define BOARD_WIDTH 450
#define BOARD_HEIGHT 450

//棋盘纵横向单元格个数
#define LINE_NUM_X 15
#define LINE_NUM_Y 15

//棋子宽高
#define CHESSMAN_WIDTH 25
#define CEHSSMAN_HEIGHT 25

//单元格宽高
const int cell_width = BOARD_WIDTH/(LINE_NUM_X-1);
const int cell_height = BOARD_HEIGHT/(LINE_NUM_Y-1);

//AI思考步数
#define AI_THINK_STEP 2
#define MAX_BRANCH 20

#endif // CONFIG_H
