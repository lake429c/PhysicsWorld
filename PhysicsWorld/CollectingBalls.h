#pragma once
class CollectingBalls
{

private:

	// 2D 物理演算のシミュレーションステップ（秒）
	const double stepSec = (1.0 / 200.0);

	// 2D 物理演算のシミュレーション蓄積時間（秒）
	double accumulatorSec = 0.0;

	// 重力加速度 (cm/s^2)
	const double gravity = 980;

	// 2D 物理演算のワールド
	P2World world{ gravity };

	// [_] 地面 (幅 1200 cm の床）
	const P2Body ground = world.createLine(P2Static, Vec2{ 0, 0 }, Line{ -600, 0, 600, 0 });

	// ^ 坂（幅 100の正三角形）
	const P2Body slopeL = world.createTriangle(P2Static, Vec2{ 0, 0 }, Triangle{ -550, 0, -500, -50 * sqrt(3), -450, 0 });
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
	bool clearFlg;

	// 終了フラグ
	bool endFlg;

	// フォントの設定
	Font font30{ 30 };

public:
	CollectingBalls();
	~CollectingBalls();
	void execute();
	bool getEndFlg();
};

