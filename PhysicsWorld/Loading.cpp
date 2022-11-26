#include "stdafx.h"
#include "Loading.h"


Loading::Loading() {

}

Loading::~Loading() {

}

void Loading::execute() {

	int selectCode = 3;

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

	// 中心を示す点
	Circle{ Scene::Center(), 5 }.draw(ColorF{1.0, 0, 0});
}


void Loading::waveCircle() {

	// 経過時間
	const double t = Scene::Time();

	// 円の個数
	const int numCircle = 6;

	// 円の大きさ
	const double radiusCircle = 20;

	// 円の間隔
	const double intervalCircle = radiusCircle * 5;

	// ウェーブの速さ（s/1周）
	const double velocityWave = 2.0;

	for (auto i : step(numCircle))
	{

		// 極座標系で半径intervalCircleの円周上に等間隔に座標を配置
		const double theta = (
				i * 360.0 / numCircle * Math::Pi_v<long double> / 180 + 
				t * -360.0 / velocityWave * Math::Pi_v<long double> / 180
			);
		const Vec2 pos = OffsetCircular{ Scene::Center(), intervalCircle, theta };

		// 円を描画
		Circle{
			Scene::Center().x - (numCircle - 1) / 2.0 * intervalCircle + i * intervalCircle,
			pos.y < Scene::Center().y ? pos.y : Scene::Center().y,
			radiusCircle
		}
		.draw(ColorF{ 0.5 + 0.5 * (pos.y < Scene::Center().y) });

	}
}


void Loading::cyclicalRectangle() {

	// 出現間隔（秒）
	double spawnTime = 1.0;

	// 四角
	Rect topRect;
	Rect rightRect;
	Rect bottomRect;
	Rect leftRect;

	// 長方形ひとつの大きさ
	Point rectSize{ 50, 30 };

	// 循環長方形の左上位置
	Point rects{ Scene::Center().x - (rectSize.x + rectSize.y) / 2, Scene::Center().y - (rectSize.x + rectSize.y) / 2 };

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
	topRect.draw(HSV{ 90 * 0, 0.7, 1.0, topFlg ? 1.0 : topTransition.value() });
	rightRect.draw(HSV{ 90 * 1, 0.7, 1.0, rightFlg ? 1.0 : rightTransition.value() });
	bottomRect.draw(HSV{ 90 * 2, 0.7, 1.0, bottomFlg ? 1.0 : bottomTransition.value() });
	leftRect.draw(HSV{ 90 * 3, 0.7, 1.0, leftFlg ? 1.0 : leftTransition.value() });

}

void Loading::DonatsCircle() {

	// 円の中心位置
	const Point posCircle = { Scene::Center() };

	// 円の半径
	const double radiusCircle = 50;

	// 円枠の基準位置の周期
	const double phaseBase = Periodic::Sine0_1(3.0s);

	// 円外枠の周期
	const double phaseOuter = Periodic::Sine0_1(5.0s);

	// 円内枠の周期
	const double phaseInner = Periodic::Sine0_1(13.0s);

	// 円の描画
	Circle{ posCircle, (phaseBase + 0.5) * radiusCircle }
		.drawFrame(
			radiusCircle * phaseInner,
			radiusCircle * phaseOuter,
			ColorF{ (phaseBase + phaseInner) / 2, (phaseBase + phaseOuter) / 2, (phaseOuter + phaseInner) / 2 }
	);

}
