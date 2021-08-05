#include <DxLib.h>
#include <cmath>
#include <list>
#include <memory>
#include <random>
#include "HomingShot.h"
#include "Geometry.h"
#include "Main.h"


#define BULLETMAX 256

struct SHOT
{
	Position2 bPos;
	Vector2 velocity;
	bool flag = false;
};

int frame = 0;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SetWindowText(L"1916002_荒木響稀");
	ChangeWindowMode(true);
	if (DxLib_Init() == -1)
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	char keyState[256] = {};
	
	char lastKeyState[256] = {};
	
	frame++;
	//背景用
	int bgH[4];
	LoadDivGraph(L"image/bganim.png", 4, 4, 1, 256, 192, bgH);

	int skyH = LoadGraph(L"image/sky.png");
	int sky2H = LoadGraph(L"image/sky2.png");
	//移動画像
	int runImage[8];
	
	//プレイヤーの位置
	Position2 pPos = { 100,300 };
	//敵の位置
	Position2 ePos = { 0,20 };
	//移動量
	float move = 5.0f;
	//球の位置
	SHOT bullet[BULLETMAX];

	HomingShot homingShot[16] = {};
	for (int i = 0; i < BULLETMAX; i++)
	{
		bullet[i].bPos = ePos;
		bullet[i].velocity;
		bullet[i].flag = false;
	}
	int animCnt = 0;
	int freameForAngle = 0;
	bool eFlag = true;
	int skyy = 0;
	int skyy2 = 0;
	int bgidx = 0;
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		ClsDrawScreen();

		GetHitKeyStateAll(keyState);
		//背景
		DrawExtendGraph(0, 0, 640, 480, bgH[bgidx / 8], false);
		bgidx = (bgidx + 1) % 32;

		//SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		skyy = (skyy + 1) % 480;
		skyy2 = (skyy2 + 2) % 480;
		DrawExtendGraph(0, skyy, 640, skyy + 480, skyH, true);
		DrawExtendGraph(0, skyy - 480, 640, skyy, skyH, true);
		DrawExtendGraph(0, skyy2, 640, skyy2 + 480, sky2H, true);
		DrawExtendGraph(0, skyy2 - 480, 640, skyy2, sky2H, true);
		animCnt++;
		//移動のアニメーション
		int tmpAnim = (animCnt / 10) % 8;
		//アクションのアニメーション
		int actionAnim = (animCnt / 10) % 2;

		int blockImage = LoadGraph(L"Image/ground.png");
		//int arrowImage = LoadGraph(L"Image/arrow2.png");

		constexpr size_t block_size = 32;
		const auto count = 720 / block_size;
		float theta = (float)(freameForAngle) * (DX_PI_F) / 180.0f;
		int x = 0;
		int y = 240;

		Position2 lastPos(x, y);
		Position2 p0(x, y);

		Vector2 lastDelta90Vectors[2] = { {0.0f,0.0f},{0.0f,0.0f} };
		auto last90DeltaVec = { 0.0f,0.0f };
		for (int i = 2; i < count; ++i)
		{
			theta += 0.1f;
			auto p1 = p0;

			auto deltaVec = Vector2(block_size, 2000.0f *
				sinf(0.02f * (float)freameForAngle + block_size * i)
				* DX_PI_F / 180.0f);

			deltaVec = deltaVec.Normalized() * block_size;

			p1 = p0 + deltaVec;
			auto delta90Vec = deltaVec.Rotated90();

			auto middleVecR = delta90Vec;
			auto middleVecL = delta90Vec;
			if (!(lastDelta90Vectors[0] == Vector2(0.0f, 0.0f)))
			{
				middleVecR = (delta90Vec + lastDelta90Vectors[0]).Normalized() * block_size;
				middleVecL = lastDelta90Vectors[0];
			}


			if (!(lastDelta90Vectors[1] == Vector2(0.0f, 0.0f)))
			{
				middleVecL = (lastDelta90Vectors[0] + lastDelta90Vectors[1]).Normalized() * block_size;
			}

			lastDelta90Vectors[1] = lastDelta90Vectors[0];
			lastDelta90Vectors[0] = deltaVec.Rotated90();

			//DrawLineAA(p0.x, p0.y, p1.x, p1.y, 0xffffff, 5.0f);
			auto rightPos = p1 + delta90Vec;
			auto leftPos = p0 + middleVecR;
		}
		freameForAngle = (freameForAngle + 1) % 720;
	
		//ホーミング弾
		int enemyImage[2];
		float enemyMove = 1.0f;
		//if (LoadDivGraph(L"image/Flight.png", 8, 8, 1, 150, 150, &enemyImage[0]) == -1);
		if (LoadDivGraph(L"image/enemy.png", 2, 2, 1, 32, 32, &enemyImage[0]) == -1);
		int pImage[10];
		float pMove = 4.0f;
		if (LoadDivGraph(L"image/player.png", 10, 5, 2, 16, 24, &pImage[0]) == -1);

		int arrowImage;
		arrowImage = LoadGraph(L"Image/arrow_short.png");
		for (auto& shot : homingShot)
		{
			shot.trail.Sethandle(arrowImage);
		}

		if (eFlag)
		{
			ePos.x += enemyMove;
		}
		else
		{
			ePos.x -= enemyMove;
		}

		if (ePos.x > 600)
		{
			ePos.x = 600;
			eFlag = false;
		}
		if (ePos.x < 0)
		{
			ePos.x = 0;
			eFlag = true;
		}

		if (CheckHitKey(KEY_INPUT_RIGHT)) {
			pPos.x = min(640, pPos.x + 4);
		}
		if (CheckHitKey(KEY_INPUT_LEFT)) {
			pPos.x = max(0,pPos.x-4);
		}
		if (CheckHitKey(KEY_INPUT_UP)) {
			pPos.y = max(0,pPos.y-4);
		}
		if (CheckHitKey(KEY_INPUT_DOWN)) {
			pPos.y = min(480,pPos.y+4);
		}

		//弾発射
		float pShotSpeed = 5.0f;
		int cnt = 0;
		constexpr float diffAngle = DX_PI_F / 6.0f;
		auto v = (ePos - pPos).Normalized();
		auto angle = atan2f(v.y, v.x);

		if (keyState[KEY_INPUT_W] && !lastKeyState[KEY_INPUT_W])
		{
			for (auto& hs : homingShot)
			{
				if (!hs.isFlag)
				{
					bool isRight = rand() % 2;
					hs.isFlag = true;
					//angle += (cnt - 1);
					hs.pos = pPos;
					hs.vel = isRight ? Vector2(pShotSpeed, 0.0f) : Vector2(-pShotSpeed, 0.0f);  //Vector2(cnt == 0 ? 3.0f : -3.0f, 3.0f);
					hs.trail.Clear();
					//hs.vel *= rspeed(mt);

					if (++cnt > 1)
					{
						break;
					}
				}
			
				//弾の更新および表示
		
				if (!hs.isFlag) {
					continue;
				}
				hs.pos += hs.vel;

			}
		}

		for (auto& hShot : homingShot)
		{
			if (!hShot.isFlag)continue;
			if (frame %= 5)
			{
				hShot.trail.Update();
			}

			hShot.pos += hShot.vel;

			hShot.trail.Draw();

			hShot.vel = (hShot.vel + (ePos - hShot.pos).Normalized());
			
			hShot.vel = hShot.vel.Normalized() * pShotSpeed;

			//敵に当たった
			if ((ePos - hShot.pos).SQMagnitude() < 900.0f)
			{
				hShot.isFlag = false;
			}
		}
		//移動のアニメーション
		int tmpEnemyAnim = (animCnt / 10) % 2;
		//アクションのアニメーション
		int playerAnim = (animCnt / 4 % 2) * 5 + 3;
		//敵の描画
		DrawRotaGraph(ePos.x, ePos.y, 2.0f, 0.0f, enemyImage[tmpEnemyAnim], true);

		//自機の描画
		DrawRotaGraph(pPos.x, pPos.y, 1.5f, 0.0f, pImage[playerAnim], true);


		ScreenFlip();
		std::copy(std::begin(keyState),std::end(keyState),std::begin(lastKeyState));
	}
}
