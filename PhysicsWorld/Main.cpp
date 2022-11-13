# include <Siv3D.hpp>
#include "CollectingBalls.h"
#include "Loading.h"

void Main()
{
	// ウィンドウを 1280x720 にリサイズ
	Window::Resize(1280, 720);

	CollectingBalls *cb = nullptr;

	// ロード画面の表示時間(s)
	double loadTime = 0.0;

	// メニュー画面フラグ
	bool menuFlg = true;

	// ロード画面フラグ
	bool loadFlg = false;

	// ゲーム画面フラグ
	bool gameFlg = false;

	// ロード画面クラスポインタ
	Loading *ld = nullptr;

	while (System::Update())
	{
		if (menuFlg && SimpleGUI::Button(U"Collecting Balls", Vec2{ 500, 300 }))
		{
			loadTime = 3.0;
			ld = new Loading();
			menuFlg = false;
			loadFlg = true;
		}

		if (loadFlg) {
			if (ld != nullptr && loadTime > 0) {
				(*ld).execute();
				loadTime -= Scene::DeltaTime();
			}
			else {
				ld = nullptr;
				cb = new CollectingBalls();
				loadFlg = false;
				gameFlg = true;
			}
		}

		if (gameFlg) {
			if (cb != nullptr && !(*cb).getEndFlg()) {
				(*cb).execute();
			}
			else {
				cb = nullptr;
				gameFlg = false;
				menuFlg = true;
			}
		}
	}
}
