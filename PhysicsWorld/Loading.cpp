#include "stdafx.h"
#include "Loading.h"


Loading::Loading() {

}

Loading::~Loading() {

}

void Loading::execute() {

	const double t = Scene::Time();

	for (auto i : step(6))
	{
		// 円座標系における角度座標
		// 60° ごとに配置し、毎秒 30° の速さで回転する
		const double theta = (i * -60_deg + t * 180_deg);

		const Vec2 pos = OffsetCircular{ Scene::Center(), 100, theta };

		Circle{ 400 + 100 * i, ( - 50 + pos.y) > 340 ? 340 : -50 + pos.y, 20}.draw(ColorF{0.8});

	}
}
