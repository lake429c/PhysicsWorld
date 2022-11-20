#pragma once
class Loading
{

private:

	// 出現間隔（秒）
	double spawnTime = 1.0;

	// 蓄積された時間（秒）
	double accumulator = 0.0;

	// 出現トランジション（spawnTime(s)かけて0.0->1.0, disappearTime(s)かけて1.0->0.0)
	Transition topTransition{ 1.0s , 3.0s };
	Transition rightTransition{ 1.0s , 3.0s };
	Transition bottomTransition{ 1.0s , 3.0s };
	Transition leftTransition{ 1.0s , 3.0s };

	// 四角
	Rect topRect;
	Rect rightRect;
	Rect bottomRect;
	Rect leftRect;


	void waveCircle();
	void cyclicalRectangle();
	void DonatsCircle();


public:
	Loading();
	~Loading();
	void execute();
};



