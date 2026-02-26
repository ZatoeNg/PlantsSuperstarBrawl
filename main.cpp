#include "graphics.h" // 引用图形库头文件
#include "./Basic/sceneManager.h"
#include "./Basic/platform.h"
#include "./Basic/player.h"
#include "./Basic/atlas.h"
#include "./Basic/menuScene.h"
#include "./Basic/gameScene.h"
#include "./Basic/selectorScene.h"

//使用了mciSendString，因此需要添加该库
#pragma comment(lib,"Winmm.lib")

SceneTemplate* menuScene = nullptr;
SceneTemplate* gameScene = nullptr;
SceneTemplate* selectorScene = nullptr;
SceneManager sceneManager;
Camera mainCamera;

std::vector<Platform> platformList;
std::vector<Bullet*> bulletList;

Player* player1 = nullptr;
Player* player2 = nullptr;

IMAGE* imgPlayer1Avatar=nullptr;
IMAGE* imgPlayer2Avatar=nullptr;

bool isDebug = false; //是否处于调试模式

IMAGE imgMenuBackground;						//主菜单背景图片

IMAGE imgVS;									//VS艺术字体图片
IMAGE img1P;									//1P 艺术字体
IMAGE img2P;									//2P 艺术字体
IMAGE img1PDesc;							//1P 键位描述图片
IMAGE img2PDesc;							//2P 键位描述图片
IMAGE imgGravestoneLeft;						//朝向左的墓碑图片
IMAGE imgGravestoneRight;						//朝向右的墓碑图片
IMAGE imgSelectorTip;							//选角界面的提示信息文本图片
IMAGE imgSelectorBackground;					//选角界面的背景
IMAGE img1PSelectorBtnIdleLeft;			//1P 向左选择按钮默认状态图片
IMAGE img1PSelectorBtnIdleRight;			//1P 向右选择按钮默认状态图片
IMAGE img1PSelectorBtnDownLeft;			//1P 向左选择按钮按下状态图片
IMAGE img1PSelectorBtnDownRight;			//1P 向右选择按钮按下状态图片
IMAGE img2PSelectorBtnIdleLeft;			//2P 向左选择按钮默认状态图片
IMAGE img2PSelectorBtnIdleRight;			//2P 向右选择按钮默认状态图片
IMAGE img2PSelectorBtnDownLeft;			//2P 向左选择按钮按下状态图片
IMAGE img2PSelectorBtnDownRight;			//2P 向右选择按钮按下状态图片
IMAGE imgPeashooterSelectorBackgroundLeft;	//选角界面朝向左的豌豆射手背景图片
IMAGE imgPeashooterSelectorBackgroundRight;	//选角界面朝向右的豌豆射手背景图片
IMAGE imgSunflowerSelectorBackgroundLeft;	//选角界面朝向左的龙日葵背景图片
IMAGE imgSunflowerSelectorBackgroundRight;	//选角界面朝向右的龙日葵背景图片

IMAGE imgSky;									//天空
IMAGE imgHills;								//山脉
IMAGE imgPlatformLarge;						//大型平台
IMAGE imgPlatformSmall;						//小型平台

IMAGE img1PCursor;							//1P 指示光标图片
IMAGE img2PCursor;							//2P 指示光标图片

Atlas atlasPeashooterIdleLeft;				//豌豆射手朝向左的默认动画图集
Atlas atlasPeashooterIdleRight;				//豌豆射手朝向右的默认动画图集
Atlas atlasPeashooterRunLeft;				//豌豆射手朝向左的奔跑动画图集
Atlas atlasPeashooterRunRight;				//豌豆射手朝向右的奔跑动画图集
Atlas atlasPeashooterAttackExLeft;			//豌豆射手朝向左的特殊攻击动画图集
Atlas atlasPeashooterAttackExRight;			//豌豆射手朝向右的特殊攻击动画图集
Atlas atlasPeashooterDieLeft;				//豌豆射手朝向左的死亡动画图集
Atlas atlasPeashooterDieRight;				//豌豆射手朝向右的死亡动画图集

Atlas atlasSunflowerIdleLeft;				//龙日葵朝向左的默认动画图集
Atlas atlasSunflowerIdleRight;				//龙日葵朝向右的默认动画图集
Atlas atlasSunflowerRunLeft;				//龙日葵朝向左的奔跑动画图集
Atlas atlasSunflowerRunRight;				//龙日葵朝向右的奔跑动画图集
Atlas atlasSunflowerAttackExLeft;			//龙日葵朝向左的特殊攻击动画图集
Atlas atlasSunflowerAttackExRight;			//龙日葵朝向右的特殊攻击动画图集
Atlas atlasSunflowerDieLeft;				//龙日葵朝向左的死亡动画图集
Atlas atlasSunflowerDieRight;				//龙日葵朝向右的死亡动画图集

IMAGE imgPea;									//豌豆图片
Atlas atlasPeaBreak;							//豌豆破碎动画图集
Atlas atlasSun;								    //阳光动画图集
Atlas atlasSunExplode;						    //阳光爆炸动画图集
Atlas atlasSunEx;								//特殊阳光动画图集
Atlas atlasSunExExplode;						//特殊阳光爆炸动画图集
Atlas atlasSunText;							//"阳光"文本动画图集

Atlas atlasRunEffect;						//奔跑特效动画图集
Atlas atlasJumpEffect;						//跳跃动画图集
Atlas atlasLandEffect;						//落地动画图集

IMAGE img1PWinner;							//1P 获胜文本图片
IMAGE img2PWinner;							//2P 获胜文本图片
IMAGE imgWinnerBar;							//获胜玩家文本背景图片

IMAGE imgAvatarPeashooter;					//豌豆射手头像图片
IMAGE imgAvatarSunflower;						//龙日葵头像图片



/*图片翻转
 * */
void flipAtlas(Atlas& src, Atlas& dst)
{
    dst.clear();

    for (int i = 0; i < src.getSize(); i++)
    {
        IMAGE imgFlipped;
        flipImage(src.getImage(i), &imgFlipped);
        dst.addImage(imgFlipped);
    }
}



/*封装资源加载时繁杂的代码*/
void loadGameResources() {		//将整个游戏程序中使用的素材都加载进来, 方便后续开发过程中直接使用,而不是在使用时才跳转回来添加新的资源加载逻辑

    //        加载字体
    AddFontResourceEx(_T("resources/IPix.ttf"), FR_PRIVATE, NULL);

    //    加载背景
    loadimage(&imgMenuBackground, _T("resources/menu_background.png"));

    //   加载游戏图集
    loadimage(&imgVS, _T("resources/VS.png"));
    loadimage(&img1P, _T("resources/1P.png"));
    loadimage(&img2P, _T("resources/2P.png"));
    loadimage(&img1PDesc, _T("resources/1P_desc.png"));
    loadimage(&img2PDesc, _T("resources/2P_desc.png"));
    loadimage(&imgGravestoneRight, _T("resources/gravestone.png"));
    flipImage(&imgGravestoneRight, &imgGravestoneLeft);
    loadimage(&imgSelectorTip, _T("resources/selector_tip.png"));
    loadimage(&imgSelectorBackground, _T("resources/selector_background.png"));
    loadimage(&img1PSelectorBtnIdleRight, _T("resources/1P_selector_btn_idle.png"));
    flipImage(&img1PSelectorBtnIdleRight, &img1PSelectorBtnIdleLeft);
    loadimage(&img1PSelectorBtnDownRight, _T("resources/1P_selector_btn_down.png"));
    flipImage(&img1PSelectorBtnDownRight, &img1PSelectorBtnDownLeft);
    loadimage(&img2PSelectorBtnIdleRight, _T("resources/2P_selector_btn_idle.png"));
    flipImage(&img2PSelectorBtnIdleRight, &img2PSelectorBtnIdleLeft);
    loadimage(&img2PSelectorBtnDownRight, _T("resources/2P_selector_btn_down.png"));
    flipImage(&img2PSelectorBtnDownRight, &img2PSelectorBtnDownLeft);
    loadimage(&imgPeashooterSelectorBackgroundRight, _T("resources/peashooter_selector_background.png"));
    flipImage(&imgPeashooterSelectorBackgroundRight, &imgPeashooterSelectorBackgroundLeft);
    loadimage(&imgSunflowerSelectorBackgroundRight, _T("resources/sunflower_selector_background.png"));
    flipImage(&imgSunflowerSelectorBackgroundRight, &imgSunflowerSelectorBackgroundLeft);

    loadimage(&imgSky, _T("resources/sky.png"));
    loadimage(&imgHills, _T("resources/hills.png"));
    loadimage(&imgPlatformLarge, _T("resources/platform_large.png"));
    loadimage(&imgPlatformSmall, _T("resources/platform_small.png"));

    loadimage(&img1PCursor, _T("resources/1P_cursor.png"));
    loadimage(&img2PCursor, _T("resources/2P_cursor.png"));

    atlasPeashooterIdleRight.loadFromFile(_T("resources/peashooter_idle_%d.png"), 9);
    flipAtlas(atlasPeashooterIdleRight, atlasPeashooterIdleLeft);
    atlasPeashooterRunRight.loadFromFile(_T("resources/peashooter_run_%d.png"), 5);
    flipAtlas(atlasPeashooterRunRight, atlasPeashooterRunLeft);
    atlasPeashooterAttackExRight.loadFromFile(_T("resources/peashooter_attack_ex_%d.png"), 3);
    flipAtlas(atlasPeashooterAttackExRight, atlasPeashooterAttackExLeft);
    atlasPeashooterDieRight.loadFromFile(_T("resources/peashooter_die_%d.png"), 4);
    flipAtlas(atlasPeashooterDieRight, atlasPeashooterDieLeft);

    atlasSunflowerIdleRight.loadFromFile(_T("resources/sunflower_idle_%d.png"), 8);
    flipAtlas(atlasSunflowerIdleRight, atlasSunflowerIdleLeft);
    atlasSunflowerRunRight.loadFromFile(_T("resources/sunflower_run_%d.png"), 5);
    flipAtlas(atlasSunflowerRunRight, atlasSunflowerRunLeft);
    atlasSunflowerAttackExRight.loadFromFile(_T("resources/sunflower_attack_ex_%d.png"), 9);
    flipAtlas(atlasSunflowerAttackExRight, atlasSunflowerAttackExLeft);
    atlasSunflowerDieRight.loadFromFile(_T("resources/sunflower_die_%d.png"), 2);
    flipAtlas(atlasSunflowerDieRight, atlasSunflowerDieLeft);

    loadimage(&imgPea, _T("resources/pea.png"));
    atlasPeaBreak.loadFromFile(_T("resources/pea_break_%d.png"), 3);

    atlasSun.loadFromFile(_T("resources/sun_%d.png"), 5);
    atlasSunExplode.loadFromFile(_T("resources/sun_explode_%d.png"), 5);
    atlasSunEx.loadFromFile(_T("resources/sun_ex_%d.png"), 5);
    atlasSunExExplode.loadFromFile(_T("resources/sun_ex_explode_%d.png"), 5);
    atlasSunText.loadFromFile(_T("resources/sun_text_%d.png"), 6);

    atlasRunEffect.loadFromFile(_T("resources/run_effect_%d.png"), 4);
    atlasJumpEffect.loadFromFile(_T("resources/jump_effect_%d.png"), 5);
    atlasLandEffect.loadFromFile(_T("resources/land_effect_%d.png"), 2);

    loadimage(&img1PWinner, _T("resources/1P_winner.png"));
    loadimage(&img2PWinner, _T("resources/2P_winner.png"));
    loadimage(&imgWinnerBar, _T("resources/winner_bar.png"));

    loadimage(&imgAvatarPeashooter, _T("resources/avatar_peashooter.png"));
    loadimage(&imgAvatarSunflower, _T("resources/avatar_sunflower.png"));

    //        加载音乐音效
    mciSendString(_T("open resources/bgm_game.mp3 alias bgm_game"), NULL, 0, NULL);
    mciSendString(_T("open resources/bgm_menu.mp3 alias bgm_menu"), NULL, 0, NULL);
    mciSendString(_T("open resources/pea_break_1.mp3 alias pea_break_1"), NULL, 0, NULL);
    mciSendString(_T("open resources/pea_break_2.mp3 alias pea_break_2"), NULL, 0, NULL);
    mciSendString(_T("open resources/pea_break_3.mp3 alias pea_break_3"), NULL, 0, NULL);
    mciSendString(_T("open resources/pea_shoot_1.mp3 alias pea_shoot_1"), NULL, 0, NULL);
    mciSendString(_T("open resources/pea_shoot_2.mp3 alias pea_shoot_2"), NULL, 0, NULL);
    mciSendString(_T("open resources/pea_shoot_ex.mp3 alias pea_shoot_ex"), NULL, 0, NULL);
    mciSendString(_T("open resources/sun_explode.mp3 alias sun_explode"), NULL, 0, NULL);
    mciSendString(_T("open resources/sun_explode_ex.mp3 alias sun_explode_ex"), NULL, 0, NULL);
    mciSendString(_T("open resources/sun_text.mp3 alias sun_text"), NULL, 0, NULL);
    mciSendString(_T("open resources/ui_confirm.wav alias ui_confirm"), NULL, 0, NULL);
    mciSendString(_T("open resources/ui_switch.wav alias ui_switch"), NULL, 0, NULL);
    mciSendString(_T("open resources/ui_win.wav alias ui_win"), NULL, 0, NULL);
}



int main()
{

    ExMessage msg;
    const int FPS = 60;

    //    加载资源
    loadGameResources();

    initgraph(1280, 720, EW_SHOWCONSOLE);

//    settextstyle(28, 0, _T("IPix"));
    settextstyle(28, 0, _T("宋体"));
    setbkmode(TRANSPARENT);

    BeginBatchDraw();

    /*场景实例化
     * */
    menuScene = new MenuScene();
    gameScene = new GameScene();
    selectorScene = new SelectorScene();

    /*默认场景
    * */
    sceneManager.setCurrentScene(menuScene);

    while (true)
    {
        DWORD frameStartTime = GetTickCount();

        while (peekmessage(&msg))
        {
            sceneManager.onInput(msg);
        }

        static DWORD lastTickTime = GetTickCount();
        DWORD currentTickTime = GetTickCount();
        DWORD deltaTick = currentTickTime - lastTickTime;

        sceneManager.onUpdate(deltaTick);
        lastTickTime = currentTickTime;

        cleardevice();

        sceneManager.onDraw(mainCamera);

        FlushBatchDraw();

        DWORD frameEndTime = GetTickCount();
        DWORD frameDeltaTime = frameEndTime - frameStartTime;

        if (frameDeltaTime < 1000 / FPS)Sleep(1000 / FPS - frameDeltaTime);


    }

    EndBatchDraw();
    return 0;
}
