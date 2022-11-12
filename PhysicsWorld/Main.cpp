# include <Siv3D.hpp>

void Main()
{
	// ウィンドウを 1280x720 にリサイズ
	Window::Resize(1280, 720);

	// 2D 物理演算のシミュレーションステップ（秒）
	constexpr double stepSec = (1.0 / 200.0);

	// 2D 物理演算のシミュレーション蓄積時間（秒）
	double accumulatorSec = 0.0;

	// 重力加速度 (cm/s^2)
	constexpr double gravity = 980;

	// 2D 物理演算のワールド
	P2World world{ gravity };

	// [_] 地面 (幅 1200 cm の床）
	const P2Body ground = world.createLine(P2Static, Vec2{ 0, 0 }, Line{ -600, 0, 600, 0 });

	// ^ 坂（幅 100の正三角形）
	const P2Body slopeL = world.createTriangle(P2Static, Vec2{ 0, 0 }, Triangle{ -550, 0, -500, -50 * sqrt(3), -450, 0});
	const P2Body slopeR = world.createTriangle(P2Static, Vec2{ 0, 0 }, Triangle{ 450, 0, 500, -50 * sqrt(3), 550, 0 });

	// 物体
	Array<P2Body> bodies;

	// 2D カメラ
	Camera2D camera{ Vec2{ 0, -300 } };

	// クリア判定ゲージ
	Point clearGaugePos{ 50, 50 };
	Point clearGaugeSize{ 200, 100 };
	double clearGaugeGrad = 30;
	Rect clearGaugeFrame{ clearGaugePos, clearGaugeSize };
	Rect clearGauge{ clearGaugePos, 0, 100 };

	// クリア範囲
	Rect goal{ -300, -50, 600, 50 };

	// スコア
	double score = 0.0;

	// クリアフラグ
	bool clearFlg = false;

	// フォントの設定
	Font font30{ 30 };

	while (System::Update())
	{

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
			font30(U"You did it!").draw(Arg::center(clearGauge.center()), ColorF{1,1,1});
		}else{
			clearGauge.shearedX(clearGaugeGrad).draw(Palette::Skyblue);
		}

		
		// 2D カメラの操作を描画
		camera.draw(Palette::Orange);
	}
}
