#ifndef __GAME_H__
#define __GAME_H__

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <glpng/glpng.h>
#else
#include <GL/glut.h>
#include <GL/glpng.h>
#endif

#define PADDING_WIDTH  (50)
#define PADDING_HEIGHT (20)

#define GAME_TITLE    (0)
#define GAME_PLAYING  (1)
#define GAME_RESULT   (2)

#define OWN_TURN  (0)
#define NPC_TURN  (1)

// 画像のための構造体
struct _image {
    GLuint img;
    pngInfo info;
};
typedef struct _image Image;

// ゲームの情報のための構造体
struct _game_info {
    int state;
    int turn;
    int score;
    int npc_score;
};
typedef struct _game_info GameInfo;

// マップに何があるかの情報
extern int map[11][11];
// ゲームの情報
extern GameInfo game_info;

// ゲームの状態を初期化
void init_game_info();
// ゲームで使う画像のすべてを読み込み
void load_images();
// ゲームを描画
void draw_game();
// ゲームのプレイ中の画面を描画
void draw_map();
// ゲームの結果画面を描画
void draw_result();
// ゲームのスコアを描画
void draw_score(int x, int y, int score);

// 囲われているかを確認
void check_surrounded();
// クリアしたかを確認
int check_clear();

// クリックしたときに呼ばれる関数
void click(int x, int y);

// NPCが手を選択する関数
void npc_select();
// マップを修復する関数
void repair_map();

// PNG画像を読み込み
void LoadSprite(Image* image, char* name);
// PNG画像を表示
void PutSprite(Image* image, int x, int y);

#endif /* __GAME_H__ */
