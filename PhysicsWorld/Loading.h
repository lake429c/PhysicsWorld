#pragma once
class Loading
{

private:

	// 出現間隔（秒）
	double spawnTime = 1.0;

	// 蓄積された時間（秒）
	double accumulator = 0.0;

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



