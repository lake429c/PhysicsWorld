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

	Point rects{ 400, 300 };
	Point rectSize{ 100, 50 };


	accumulator += Scene::DeltaTime();

	if (spawnTime * 4 < accumulator)
	{
		accumulator = 0;
	}

	// 蓄積時間が出現間隔を超えたら
	if (spawnTime * 0 <= accumulator && accumulator < spawnTime * 1)
	{
		topRect = Rect{
			rects,
			(int)(rectSize.x * (accumulator - spawnTime * 0) / spawnTime),
			rectSize.y
		};
		topRect.draw(ColorF{ 1, 1, 1, 1 });
		leftRect.draw(ColorF{ 1, 1, 1, spawnTime * 1 - accumulator / spawnTime });
	}
	if (spawnTime * 1 <= accumulator && accumulator < spawnTime * 2)
	{
		rightRect = Rect{
			rects.x + rectSize.x,
			rects.y,
			rectSize.y,
			(int)(rectSize.x * (accumulator - spawnTime * 1) / spawnTime)
		};
		rightRect.draw(ColorF{ 1, 1, 1, 1 });
		topRect.draw(ColorF{ 1, 1, 1, spawnTime * 2 - accumulator / spawnTime });
	}
	if (spawnTime * 2 <= accumulator && accumulator < spawnTime * 3)
	{
		bottomRect = Rect{
			(int)(rects.x + rectSize.y + rectSize.x - rectSize.x * (accumulator - spawnTime * 2) / spawnTime),
			rects.y + rectSize.x,
			(int)(rectSize.x * (accumulator - spawnTime * 2) / spawnTime),
			rectSize.y
		};
		bottomRect.draw(ColorF{ 1, 1, 1, 1 });
		rightRect.draw(ColorF{ 1, 1, 1, spawnTime * 3 - accumulator / spawnTime });
	}
	if (spawnTime * 3 <= accumulator && accumulator < spawnTime * 4)
	{
		leftRect = Rect{
			rects.x,
			(int)(rects.y + rectSize.y + rectSize.x - rectSize.x * (accumulator - spawnTime * 3) / spawnTime),
			rectSize.y,
			(int)(rectSize.x * (accumulator - spawnTime * 3) / spawnTime)
		};
		leftRect.draw(ColorF{ 1, 1, 1, 1 });
		bottomRect.draw(ColorF{ 1, 1, 1, spawnTime * 4 - accumulator / spawnTime });

	}
}

void Loading::DonatsCircle() {
}
