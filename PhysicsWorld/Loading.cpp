#include "stdafx.h"
#include "Loading.h"


Loading::Loading() {

}

Loading::~Loading() {

}

void Loading::execute() {

	int selectCode = 2;

	switch (selectCode) {
	case 1:
		waveCircle();
		break;
	case 2:
		cyclicalRectangle();
		break;
	case 3:
		DonatsCircle();
		break;
	}

}


void Loading::waveCircle() {

	const double t = Scene::Time();

	for (auto i : step(6))
	{
		// 円座標系における角度座標
		// 60° ごとに配置し、毎秒 30° の速さで回転する
		const double theta = (i * -60_deg + t * 180_deg);

		const Vec2 pos = OffsetCircular{ Scene::Center(), 100, theta };

		Circle{ 400 + 100 * i, (-50 + pos.y) > 340 ? 340 : -50 + pos.y, 20 }.draw(ColorF{ 0.8 });

	}
}


void Loading::cyclicalRectangle() {

	Point rects{ 600, 300 };
	Point rectSize{ 50, 30 };

	// 蓄積時間の加算
	accumulator += Scene::DeltaTime();

	// 蓄積時間のリセット
	if (spawnTime * 4 < accumulator)
	{
		accumulator = 0;
	}

	// 蓄積時間によるフラグの循環
	bool topFlg = (spawnTime * 0 <= accumulator && accumulator < spawnTime * 1) ? true : false;
	bool rightFlg = (spawnTime * 1 <= accumulator && accumulator < spawnTime * 2) ? true : false;
	bool bottomFlg = (spawnTime * 2 <= accumulator && accumulator < spawnTime * 3) ? true : false;
	bool leftFlg = (spawnTime * 3 <= accumulator && accumulator < spawnTime * 4) ? true : false;

	// トランジションの更新
	topTransition.update(topFlg);
	rightTransition.update(rightFlg);
	bottomTransition.update(bottomFlg);
	leftTransition.update(leftFlg);

	// 長方形の大きさ設定
	topRect = Rect{
		rects.x + rectSize.y,
		rects.y,
		topFlg ? (int)ceil(rectSize.x * topTransition.value()) : rectSize.x,
		rectSize.y
	};
	rightRect = Rect{
		rects.x + rectSize.x,
		rects.y + rectSize.y,
		rectSize.y,
		rightFlg ? (int)ceil(rectSize.x * rightTransition.value()) : rectSize.x
	};
	bottomRect = Rect{
		bottomFlg ? (int)(rects.x + rectSize.x - ceil(rectSize.x * bottomTransition.value())) : rects.x,
		rects.y + rectSize.x,
		bottomFlg ? (int)ceil(rectSize.x * bottomTransition.value()) : rectSize.x,
		rectSize.y
	};
	leftRect = Rect{
		rects.x,
		leftFlg ? (int)(rects.y + rectSize.x - ceil(rectSize.x * leftTransition.value())) : rects.y,
		rectSize.y,
		leftFlg ? (int)ceil(rectSize.x * leftTransition.value()) : rectSize.x
	};

	// 長方形の描画
	topRect.draw(ColorF{ 1, 1, 1, topFlg ? 1.0 : topTransition.value() });
	rightRect.draw(ColorF{ 1, 1, 1, rightFlg ? 1.0 : rightTransition.value() });
	bottomRect.draw(ColorF{ 1, 1, 1, bottomFlg ? 1.0 : bottomTransition.value() });
	leftRect.draw(ColorF{ 1, 1, 1, leftFlg ? 1.0 : leftTransition.value() });

}

void Loading::DonatsCircle() {

	const double t = Scene::Time();

	for (auto i : step(6))
	{
		// 円座標系における角度座標
		// 60° ごとに配置し、毎秒 30° の速さで回転する
		const double theta = (i * -60_deg + t * 180_deg);

		const Vec2 pos = OffsetCircular{ Scene::Center(), 100, theta };

		Circle{ 400 + 100 * i, (-50 + pos.y) > 340 ? 340 : -50 + pos.y, 20 }.draw(ColorF{ 0.8 });

	}

}
