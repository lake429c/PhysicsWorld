#include "stdafx.h"
#include "CollectingBalls.h"


// コンストラクタ
CollectingBalls::CollectingBalls() {
	clearFlg = false;
	endFlg = false;
}

// デストラクタ
CollectingBalls::~CollectingBalls() {
}

void CollectingBalls::execute() {
	for (accumulatorSec += Scene::DeltaTime(); stepSec <= accumulatorSec; accumulatorSec -= stepSec)
	{
		// 2D 物理演算のワールドを更新
		world.update(stepSec);
	}

	// 地面より下に落ちた物体は削除
	bodies.remove_if([](const P2Body& b) { return (200 < b.getPos().y); });

	// 2D カメラの更新
	camera.update();
	{
		// 2D カメラから Transformer2D を作成
		const auto t = camera.createTransformer();

		// 左クリックしたら
		if (MouseL.down())
		{
			// クリックした場所に半径 10 cm のボールを作成
			P2Material mate;
			mate.density = 5;
			mate.friction = 0.8;
			mate.restitution = 0.9;
			bodies << world.createCircle(P2Dynamic, Cursor::PosF(), 10, mate);
		}

		// スコアをカウント
		score = 0.0;
		for (const auto& body : bodies)
		{
			if (goal.intersects(body.getPos())) {
				score += 20;
			}
		}

		// ゴール
		goal.draw(ColorF{ 1.0, 0, 0, 0.2 });

		// すべてのボディを描画
		for (const auto& body : bodies)
		{
			body.draw(HSV{ body.id() * 10.0 });
		}

		// 地面を描画
		ground.draw(Palette::Skyblue);
		slopeL.draw(Palette::Skyblue);
		slopeR.draw(Palette::Skyblue);


	}


	// 長方形の辺を X 軸方向に 30px ずつスライドさせた平行四辺形
	if (clearFlg || clearGauge.w + Scene::DeltaTime() * 50 >= clearGaugeFrame.w) {
		clearGauge.w = clearGaugeFrame.w;
		clearFlg = true;
	}
	else if (clearGauge.w > score) {
		clearGauge.w -= Scene::DeltaTime() * 50;
	}
	else if (clearGauge.w + Scene::DeltaTime() * 50 >= score) {
		clearGauge.w = score;
	}
	else {
		clearGauge.w += Scene::DeltaTime() * 50;
	}
	clearGaugeFrame.shearedX(clearGaugeGrad).drawFrame(0, 2, ColorF{ 1, 1, 1 });
	if (clearFlg) {
		clearGauge.shearedX(clearGaugeGrad).draw(Palette::Orange);
		font30(U"You did it!").draw(Arg::center(clearGauge.center()), ColorF{ 1,1,1 });
	}
	else {
		clearGauge.shearedX(clearGaugeGrad).draw(Palette::Skyblue);
	}

	if (clearFlg && SimpleGUI::Button(U"Go Menu", Vec2{ 500, 300 }))
	{
		endFlg = true;
	}

	// 2D カメラの操作を描画
	camera.draw(Palette::Orange);
}

bool CollectingBalls::getEndFlg()
{
	return endFlg;
}

