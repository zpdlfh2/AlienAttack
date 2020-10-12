#include <bangtal>
#include <ctime>
#include <iostream>

using namespace bangtal;
using namespace std;

int main() {
	srand((unsigned int)time(NULL)); // 랜덤 초기화 호출
	auto sound1 = Sound::create("sound/backgroundsound.mp3");
	auto sound2 = Sound::create("sound/aliensound1.mp3");
	auto sound3 = Sound::create("sound/aliensound2.mp3");
	auto shotsound1 = Sound::create("sound/shotsound1.mp3");
	sound1->play(true);
	auto sceneX = 550, sceneY = 30;

	const auto sceneNum = 5;
	ScenePtr scene[sceneNum];
	ObjectPtr startButton[sceneNum];

	for (int i = 0; i < sceneNum; i++) {
		string stageName = "STAGE " + to_string(i + 1);
		string fileName = "image1/background" + to_string(i + 1) + ".png";
		scene[i] = Scene::create(stageName, fileName);
		startButton[i] = Object::create("image1/start.png", scene[i], sceneX, sceneY);
		startButton[i]->setScale(0.1f);
	}


//stage1

	const auto alienNum = 5;
	auto pointCheck1 = 0;

	int alienX[alienNum];
	int alienY[alienNum];
	ObjectPtr alien[alienNum];


	// 외계인 y축 랜덤좌표 생성
	for (int i = 0; i < alienNum; i++) {
		alienX[i] = -100;
		int n = rand() % 550;
		alienY[i] = n;
	}

	// 외계인 생성& 클릭시 포인트 추가
	for (int i = 0; i < alienNum; i++) {
		//float n = rand() % 20 / 100;
		alien[i] = Object::create("image1/alien1.png", scene[0], alienX[i], alienY[i], false);
		alien[i]->setScale(0.12f);	
		alien[i]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction action)-> bool {
			int j;
			for (j = 0; j < alienNum; j++) {
				if (alien[j] == object)
					break;
			}
			sound2->play();
			alien[j]->hide();
			++pointCheck1;
			if (pointCheck1 == 4) {
				showMessage("Stage 1 통과!");
				scene[1]->enter();
				startButton[1]->show();
			}
			return true;
			});
	}

	TimerPtr alienTimer[alienNum];
	int count[alienNum];
	for (int i = 0; i < alienNum; i++) {
		count[i] = 0;
		alienTimer[i] = Timer::create(0.2f);
	}

	for(int a = 0; a < alienNum; a++){
		alienTimer[a]->setOnTimerCallback([&](TimerPtr t)->bool {
			int j;
			for (j = 0; j < alienNum; j++) {
				if (alienTimer[j] == t)
					break;
			}
			float n = rand() % 30 ;
			alienX[j] += n;
			alien[j]->locate(scene[0], alienX[j], alienY[j]);
			count[j]++;
			if (count[j] < 500) {
				t->set(0.03f);
				t->start();
			}
			for (int i = 0; i < alienNum; i++) {
				int j = 0;
				if (count[j] == 25 * i) {
					alien[i]->show();
					alienTimer[i]->start();
				}
				j++;
			}
			return true;
			});
	}

	startButton[0]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction)-> bool {
		alien[0]->show();
		alienTimer[0]->start();
		startButton[0]->hide();
		return true;
		});



	//stage 2

	const auto alien2Num = 10;
	auto pointCheck2 = 0;

	int alien2X[alien2Num];
	int alien2Y[alien2Num];
	ObjectPtr alien2[alien2Num];


	// 외계인 y축 랜덤좌표 생성
	for (int i = 0; i < alien2Num; i++) {
		alien2X[i] = 1400;
		int n = rand() % 500;
		alien2Y[i] = n;
	}

	// 외계인 생성& 클릭시 포인트 추가
	for (int i = 0; i < alien2Num; i++) {
		//float n = rand() % 20 / 100;
		alien2[i] = Object::create("image1/alien2.png", scene[1], alien2X[i], alien2Y[i], false);
		alien2[i]->setScale(0.1f);
		alien2[i]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction action)-> bool {
			int j;
			for (j = 0; j < alien2Num; j++) {
				if (alien2[j] == object)
					break;
			}
			sound3->play();
			alien2[j]->hide();
			++pointCheck2;
			if (pointCheck2 == 7) {
				showMessage("Stage 2 통과!");
				scene[2]->enter();
				startButton[2]->show();
			}
			return true;
			});
	}

	TimerPtr alien2Timer[alien2Num];
	int count2[alien2Num];
	for (int i = 0; i < alien2Num; i++) {
		count2[i] = 0;
		alien2Timer[i] = Timer::create(0.5f);
	}

	for (int a = 0; a < alien2Num; a++) {
		alien2Timer[a]->setOnTimerCallback([&](TimerPtr t)->bool {
			int j;
			for (j = 0; j < alien2Num; j++) {
				if (alien2Timer[j] == t)
					break;
			}
			float n = rand() % 25;
			alien2X[j] -= n;
			alien2[j]->locate(scene[1], alien2X[j], alien2Y[j]);
			count2[j]++;
			if (count2[j] < 500) {
				t->set(0.02f);
				t->start();
			}
			for (int i = 0; i < alien2Num; i++) {
				int j = 0;
				if (count2[j] == 20 * i) {
					alien2[i]->show();
					alien2Timer[i]->start();
				}
				j++;
			}
			return true;
			});
	}

	startButton[1]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction)-> bool {
		alien2[0]->show();
		alien2Timer[0]->start();
		startButton[1]->hide();
		return true;
		});


	//stage 3

	const auto alien3Num = 10;
	auto pointCheck3 = 0;

	int alien3X[alien3Num];
	int alien3Y[alien3Num];
	ObjectPtr alien3[alien3Num];

	const auto alien4Num = 10;
	int alien4X[alien4Num];
	int alien4Y[alien4Num];
	ObjectPtr alien4[alien4Num];

	// alien3 y축 랜덤좌표 생성
	for (int i = 0; i < alien3Num; i++) {
		alien3X[i] = 1200;
		int n = rand() % 600;
		alien3Y[i] = n;
	}

	// alien4 x축 랜덤좌표 생성
	for (int i = 0; i < alien4Num; i++) {
		alien4Y[i] = 850;
		int n = rand() % 1100;
		alien4X[i] = n;
	}

	// alien3 생성& 클릭시 포인트 추가
	for (int i = 0; i < alien3Num; i++) {
		//float n = rand() % 20 / 100;
		alien3[i] = Object::create("image1/alien3.png", scene[2], alien3X[i], alien3Y[i], false);
		alien3[i]->setScale(0.18f);
		alien3[i]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction action)-> bool {
			int j;
			for (j = 0; j < alien3Num; j++) {
				if (alien3[j] == object)
					break;
			}
			sound2->play();
			alien3[j]->hide();
			++pointCheck3;
			if (pointCheck3 == 10) {
				showMessage("Stage 3 통과!");
				scene[3]->enter();
				startButton[3]->show();
			}
			return true;
			});
	}

	// alien4 생성& 클릭시 포인트 추가
	for (int i = 0; i < alien4Num; i++) {
		//float n = rand() % 20 / 100;
		alien4[i] = Object::create("image1/alien4.png", scene[2], alien4X[i], alien4Y[i], false);
		alien4[i]->setScale(0.1f);
		alien4[i]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction action)-> bool {
			int j;
			for (j = 0; j < alien4Num; j++) {
				if (alien4[j] == object)
					break;
			}
			sound2->play();
			alien4[j]->hide();
			++pointCheck3;
			if (pointCheck3 == 10) {
				showMessage("Stage 3 통과!");
				scene[3]->enter();
				startButton[3]->show();
			}
			return true;
			});
	}

	TimerPtr alien3Timer[alien3Num];
	int count3[alien3Num];
	for (int i = 0; i < alien3Num; i++) {
		count3[i] = 0;
		alien3Timer[i] = Timer::create(0.5f);
	}

	TimerPtr alien4Timer[alien4Num];
	int count4[alien4Num];
	for (int i = 0; i < alien4Num; i++) {
		count4[i] = 0;
		alien4Timer[i] = Timer::create(0.5f);
	}

	for (int a = 0; a < alien3Num; a++) {
		alien3Timer[a]->setOnTimerCallback([&](TimerPtr t)->bool {
			int j;
			for (j = 0; j < alien3Num; j++) {
				if (alien3Timer[j] == t)
					break;
			}
			float n = rand() % 20;
			alien3X[j] -= n;
			alien3[j]->locate(scene[2], alien3X[j], alien3Y[j]);
			count3[j]++;
			if (count3[j] < 500) {
				t->set(0.03f);
				t->start();
			}
			for (int i = 0; i < alien3Num; i++) {
				int j = 0;
				if (count3[j] == 30 * i) {
					alien3[i]->show();
					alien3Timer[i]->start();
				}
				j++;
			}
			return true;
			});
	}
	
	for (int a = 0; a < alien4Num; a++) {
		alien4Timer[a]->setOnTimerCallback([&](TimerPtr t)->bool {
			int j;
			for (j = 0; j < alien4Num; j++) {
				if (alien4Timer[j] == t)
					break;
			}
			float n = rand() % 20;
			alien4Y[j] -= n;
			alien4[j]->locate(scene[2], alien4X[j], alien4Y[j]);
			count4[j]++;
			if (count4[j] < 500) {
				t->set(0.03f);
				t->start();
			}
			for (int i = 0; i < alien4Num; i++) {
				int j = 0;
				if (count4[j] == 30 * i) {
					alien4[i]->show();
					alien4Timer[i]->start();
				}
				j++;
			}
			return true;
			});
	}

	startButton[2]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction)-> bool {
		alien3[0]->show();
		alien3Timer[0]->start();
		alien4[0]->show();
		alien4Timer[0]->start();
		startButton[2]->hide();
		return true;
		});





	//stage 4

	auto pointCheck4 = 0;
	auto alien5X = 400;
	auto alien5Y = 300;
	auto alien5 = Object::create("image1/alien5.png", scene[3], alien5X, alien5Y, false);
	alien5->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction action)-> bool {
		shotsound1->play();
		++pointCheck4;
		if (pointCheck4 == 10) {
			showMessage("Stage 4 통과!");
			scene[4]->enter();
			startButton[4]->show();
		}
		return true;
		});

	alien5->setScale(0.15f);
	TimerPtr alien5Timer;
	alien5Timer = Timer::create(0.5f);
	auto count5 = 0;

//외계인이 가운데에서 랜덤방향으로 막 움직임 >> 뚜드려패야 스테이지 클리어

	alien5Timer->setOnTimerCallback([&](TimerPtr t)->bool {
		int j;
		//for (j = 0; j < alien5Num; j++) {
		//	if (alien5Timer[j] == t)
		//		break;
		//}
		int m = rand() % 4;
		float n = rand() % 40 * 8;
		if (alien5X < 200) {
			switch (m) {
			case 1: alien5X += n; break;
			case 2: alien5Y -= n; break;
			case 3: alien5Y += n; break;
			}
		}
		else if (alien5X > 900) {
			switch (m) {
			case 0: alien5X -= n; break;
			case 2: alien5Y -= n; break;
			case 3: alien5Y += n; break;
			}
		}		
		else if (alien5Y < 200) {
			switch (m) {
			case 0: alien5X -= n; break;
			case 1: alien5X += n; break;
			case 3: alien5Y += n; break;
			}
		}		
		else if (alien5Y > 450){
			switch (m) {
			case 0: alien5X -= n; break;
			case 1: alien5X += n; break;
			case 2: alien5Y -= n; break;
			}
		}
		else {
			switch (m) {
			case 0: alien5X -= n; break;
			case 1: alien5X += n; break;
			case 2: alien5Y -= n; break;
			case 3: alien5Y += n; break;
			}
		}


		alien5->locate(scene[3], alien5X, alien5Y);
		count5++;
		if (count5 < 1000) {
			t->set(0.2f);
			t->start();
		}
		return true;
		});


startButton[3]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction)-> bool {
	alien5->show();
	alien5Timer->start();
	startButton[3]->hide();
	return true;
	});

	startGame(scene[0]);

	return 0;
}