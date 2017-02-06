#include "./game.h"
#include "./event.h"
#include <stdio.h>
#include <stdlib.h>

// ゲームの画像
Image blocks[4];
Image junction;
Image bars[2][2];
Image score_board;
Image numbers[10];
Image title;
Image game_messages[2];
Image result_title;
Image result_win;
Image result_lose;
Image result_return;

int map[11][11] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

GameInfo game_info;

// ゲームの状態を初期化
void init_game_info() {
    game_info.state = GAME_TITLE;
    game_info.turn = OWN_TURN;
    game_info.score = 0;
    game_info.npc_score = 0;
}

// ゲームで使う画像をすべて読み込む
void load_images() {
    int i, j;
    char name[30];

    // ブロックの画像を読み込み
    for (i = 0; i < 3; i++) {
        sprintf(name, "assets/image%1d.png", i);
        LoadSprite(&blocks[i], name);
    }
    // 棒の画像を読み込み
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            sprintf(name, "assets/bar%1d%1d.png", i, j);
            LoadSprite(&bars[i][j], name);
        }
    }
    // 数字画像の読み込み
    for (i = 0; i < 10; i++) {
        sprintf(name, "assets/num%1d.png", i);
        LoadSprite(&numbers[i], name);
    }
    // 頂点画像の読み込み
    LoadSprite(&junction, "assets/junction.png");
    // 得点板の読み込み
    LoadSprite(&score_board, "assets/score.png");
    for (i = 0; i < 2; i++) {
        sprintf(name, "assets/game_message%1d.png", i);
        LoadSprite(&game_messages[i], name);
    }
    // タイトル画像
    LoadSprite(&title, "assets/title.png");
    // 結果画面の画像を読み込み
    LoadSprite(&result_title, "assets/result_title.png");
    LoadSprite(&result_win, "assets/result_win.png");
    LoadSprite(&result_lose, "assets/result_lose.png");
    LoadSprite(&result_return, "assets/result_return.png");
}

void draw_game() {
    if (game_info.state == GAME_TITLE) {
        PutSprite(&title, 0, 0);
    } else if (game_info.state == GAME_PLAYING) {
        draw_map();
        if (check_clear()) {
            repair_map();
            game_info.state = GAME_RESULT;
        }
    } else if (game_info.state == GAME_RESULT) {
        draw_result();
    }
}

void draw_map() {
    int i, j;

    // 各ブロックを描画
    for (i = 1; i < 11; i += 2) {
        for (j = 1; j < 11; j += 2) {
            if (map[j][i] == 0) {
                PutSprite(&blocks[0], (i / 2) * 100 + PADDING_WIDTH, (j / 2) * 100 + PADDING_HEIGHT);
            } else if (map[j][i] == 1) {
                PutSprite(&blocks[1], (i / 2) * 100 + PADDING_WIDTH, (j / 2) * 100 + PADDING_HEIGHT);
            } else if (map[j][i] == 2) {
                PutSprite(&blocks[2], (i / 2) * 100 + PADDING_WIDTH, (j / 2) * 100 + PADDING_HEIGHT);
            }
        }
    }

    // 辺を描画
    // 横の辺を描画
    for (i = 1; i < 11; i+= 2) {
        for (j = 0; j < 11; j+= 2) {
            if (map[j][i] == 1) {
                PutSprite(&bars[0][0], (i / 2) * 100 + PADDING_WIDTH, (j / 2) * 100 + PADDING_HEIGHT - 50);
            } else {
                PutSprite(&bars[1][0], (i / 2) * 100 + PADDING_WIDTH, (j / 2) * 100 + PADDING_HEIGHT - 50);
            }
        }
    }
    // 縦の辺を描画
    for (i = 0; i < 11; i += 2) {
        for (j = 1; j < 11; j += 2) {
            if (map[j][i] == 1) {
                PutSprite(&bars[0][1], (i / 2) * 100 + PADDING_WIDTH - 50, (j / 2) * 100 + PADDING_HEIGHT);
            } else {
                PutSprite(&bars[1][1], (i / 2) * 100 + PADDING_WIDTH - 50, (j / 2) * 100 + PADDING_HEIGHT);
            }
        }
    }

    // 頂点の描画
    for (i = 0; i < 11; i+= 2) {
        for (j = 0; j < 11; j += 2) {
            PutSprite(&junction, (i / 2) * 100 + PADDING_WIDTH - 50, (j / 2) * 100 + PADDING_HEIGHT - 50);
        }
    }

    // スコアボードの表示
    PutSprite(&score_board, 0, 500 + PADDING_HEIGHT);
    draw_score(50, 600,  game_info.score);
    draw_score(450, 600, game_info.npc_score);

    // どちらのターンなのかを表示
    if (game_info.turn == OWN_TURN) {
        PutSprite(&game_messages[0], 0, 600);
    } else if (game_info.turn == NPC_TURN) {
        PutSprite(&game_messages[1], 0, 600);
    }
}

void draw_result() {
    // 結果画面を描画する
    PutSprite(&result_title, 0, 0);
    if (game_info.score > game_info.npc_score) {
        PutSprite(&result_win, 0, 180);
    } else {
        PutSprite(&result_lose, 0, 180);
    }
    PutSprite(&result_return, 0, 500);
}

void draw_score(int x, int y, int score) {
    int index;

    // 百の位
    index = (score / 100) % 10;
    PutSprite(&numbers[index], x, y);
    // 十の位
    index = (score / 10)  % 10;
    PutSprite(&numbers[index], x + 30, y);
    // 一の位
    index = score % 10;
    PutSprite(&numbers[index], x + 60, y);
}

void check_surrounded() {
    int i, j;

    for (i = 1; i < 11; i += 2) {
        for (j = 1; j < 11; j += 2) {
            if (map[j][i] == 0 && map[j][i+1] == 2 &&
                map[j][i-1] == 2 && map[j+1][i] == 2 && map[j-1][i] == 2) {
                // 囲まれていればターンに応じて得点
                if (game_info.turn == OWN_TURN) {
                    map[j][i] = 1;
                    game_info.score += 30;
                } else if (game_info.turn == NPC_TURN) {
                    map[j][i] = 2;
                    game_info.npc_score += 30;
                }
            }
        }
    }
}

int check_clear() {
    int status = 1;
    int i, j;

    // すべての四角を確認して0でなければクリア
    for (i = 1; i < 11; i += 2) {
        for (j = 1; j < 11; j += 2) {
            if (map[j][i] == 0) {
                status = 0;
                break;
            }
        }
        if (status == 0) {
            break;
        }
    }
    return status;
}

void click(int x, int y) {
    int i, j;
    int status = 0;

    // 縦の判定
    if (x % 100 > 35 && x % 100 < 65) {
        i = x / 100 * 2;
        j = (y - 20) / 100 * 2 + 1;
        if (i < 11 && j < 11 && map[j][i] == 1) {
            map[j][i] = 2;
            status = 1;
        }
    }
    // 横の判定
    else if (y % 100 > 5 && y % 100 < 35) {
        i = (x - 50) / 100 * 2 + 1;
        j = y / 100 * 2;
        if (i < 11 && j < 11 && map[j][i] == 1) {
            map[j][i] = 2;
            status = 1;
        }
    }
    // 線を引いたら確認
    if (status) {
        // 囲われた四角を確認
        check_surrounded();
        game_info.turn = NPC_TURN;
        // 2秒後にNPCの攻撃
        glutTimerFunc(2000, NpcTimer, 0);
    }
}

void npc_select() {
    int i, j;
    int status = 0;
    int num1, num2;

    for (i = 1; i < 11; i += 2) {
        for (j = 1; j < 11; j += 2) {
            // あと一本線を引けば取れるときは取る
            if (map[j][i] == 0 && (map[j][i+1] + map[j][i-1] + map[j+1][i] + map[j-1][i]) == 7) {
                if (map[j][i+1] == 1) {
                    map[j][i+1] = 2;
                } else if (map[j][i-1] == 1) {
                    map[j][i-1] = 2;
                } else if (map[j+1][i] == 1) {
                    map[j+1][i] = 2;
                } else if (map[j-1][i] == 1) {
                    map[j-1][i] = 2;
                }
                status = 1;
                break;
            }
        }
        if (status) {
            break;
        }
    }
    if (status == 0) {
        // どこも取れない場合は乱数で
        while(1) {
            num1 = random() % 11;
            num2 = random() % 11;
            // 奇数と偶数である場合は，配列内の棒のインデックス
            if (((num1 % 2) + (num2 % 2)) == 1 && map[num1][num2] == 1) {
                map[num1][num2] = 2;
                break;
            }
        }
    }
    // 得点を確認
    check_surrounded();
    // ターンを戻す
    game_info.turn = OWN_TURN;
}
void repair_map() {
    int i, j;

    // 各ブロックをリセット
    for (i = 1; i < 11; i += 2) {
        for (j = 1; j < 11; j += 2) {
            if (map[j][i] != 0) {
                map[j][i] = 0;
            }
        }
    }
    // 辺をリセット
    // 横の辺を元に戻す
    for (i = 1; i < 11; i+= 2) {
        for (j = 0; j < 11; j+= 2) {
            if (map[j][i] != 1) {
                map[j][i] = 1;
            }
        }
    }
    // 縦の辺を元に戻す
    for (i = 0; i < 11; i += 2) {
        for (j = 1; j < 11; j += 2) {
            if (map[j][i] != 1) {
                map[j][i] = 1;
            }
        }
    }
}

void LoadSprite(Image* image, char* name) {
    // 画像の読み込み
    image->img = pngBind(name, PNG_NOMIPMAP, PNG_ALPHA, &image->info, GL_CLAMP, GL_NEAREST, GL_NEAREST);
}

void PutSprite(Image* image, int x, int y) {
    int w, h;  //  テクスチャの幅と高さ
    int tmp_img = image->img;

    w = image->info.Width;   //  テクスチャの幅と高さを取得する
    h = image->info.Height;

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tmp_img);
    glColor4ub(255, 255, 255, 255);

    glBegin(GL_QUADS);  //  幅w, 高さhの四角形

    glTexCoord2i(0, 0);
    glVertex2i(x, y);

    glTexCoord2i(0, 1);
    glVertex2i(x, y + h);

    glTexCoord2i(1, 1);
    glVertex2i(x + w, y + h);

    glTexCoord2i(1, 0);
    glVertex2i(x + w, y);

    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
