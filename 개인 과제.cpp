#include <bangtal>
#include <ctime>
#include <iostream>

using namespace bangtal;
using namespace std;

int main() {
	//for (int i = 0; i < 9; i++) {
	//	string filename = "images/part" + to_string(i + 1) + ".png";
	//}
	//	game_board[i] = Object::create(filename, scene, 300 + (i % 3) * 150, 470 - (i / 3) * 150);
	auto sound1 = Sound::create("sound/backgroundsound.mp3");
	auto sound2 = Sound::create("sound/aliensound1.mp3");
	sound1->play(true);

	srand((unsigned int)time(NULL)); // 랜덤 초기화 호출
	auto sceneX = 550, sceneY = 30;
	auto scene1 = Scene::create("STAGE 1", "image1/background1.png");
	auto scene2 = Scene::create("STAGE 2", "image1/background2.png");
	auto scene3 = Scene::create("STAGE 3", "image1/background3.png");
	auto startButton1 = Object::create("image1/start.png", scene1, sceneX, sceneY);
	auto startButton2 = Object::create("image1/start.png", scene2, sceneX, sceneY, false);
	auto startButton3 = Object::create("image1/start.png", scene3, sceneX, sceneY, false);
	startButton1->setScale(0.1f);
	startButton2->setScale(0.1f);
	startButton3->setScale(0.1f);

	const auto alienNum = 5;
	auto pointCheck1 = 0;

	int alienX[alienNum];
	int alienY[alienNum];
	ObjectPtr alien[alienNum];


	// 외계인 y축 랜덤좌표 생성
	for (int i = 0; i < alienNum; i++) {
		alienX[i] = 0;
		int n = rand() % 400;
		alienY[i] = n;
	}

	// 외계인 생성& 클릭시 포인트 추가
	for (int i = 0; i < alienNum; i++) {
		//float n = rand() % 20 / 100;
		alien[i] = Object::create("image1/alien1.png", scene1, alienX[i], alienY[i], false);
		alien[i]->setScale(0.08f);	
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
				scene2->enter();
				startButton2->show();
			}
			return true;
			});
	}

	TimerPtr alienTimer[alienNum];
	int count[alienNum];
	for (int i = 0; i < alienNum; i++) {
		count[i] = 0;
		alienTimer[i] = Timer::create(0.5f);
	}

	for(int a = 0; a < alienNum; a++){
		alienTimer[a]->setOnTimerCallback([&](TimerPtr t)->bool {
			int j;
			for (j = 0; j < alienNum; j++) {
				if (alienTimer[j] == t)
					break;
			}
			float n = rand() % 20 * 10;
			alienX[j] += n;
			alien[j]->locate(scene1, alienX[j], alienY[j]);
			count[j]++;
			if (count[j] < 100) {
				t->set(0.4f);
				t->start();
			}
			for (int i = 0; i < alienNum; i++) {
				int j = 0;
				if (count[j] == 3 * i) {
					alien[i]->show();
					alienTimer[i]->start();
				}
				j++;
			}
			return true;
			});
	}

	startButton1->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction)-> bool {
		alien[0]->show();
		alienTimer[0]->start();
		startButton1->hide();
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
		alien2X[i] = 0;
		int n = rand() % 400;
		alien2Y[i] = n;
	}

	// 외계인 생성& 클릭시 포인트 추가
	for (int i = 0; i < alien2Num; i++) {
		//float n = rand() % 20 / 100;
		alien2[i] = Object::create("image1/alien2.png", scene2, alien2X[i], alien2Y[i], false);
		alien2[i]->setScale(0.1f);
		alien2[i]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction action)-> bool {
			int j;
			for (j = 0; j < alien2Num; j++) {
				if (alien2[j] == object)
					break;
			}
			sound2->play();
			alien2[j]->hide();
			++pointCheck2;
			if (pointCheck2 == 7) {
				showMessage("Stage 2 통과!");
				scene3->enter();
				startButton3->show();
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
			float n = rand() % 20 * 10;
			alien2X[j] += n;
			alien2[j]->locate(scene2, alien2X[j], alien2Y[j]);
			count2[j]++;
			if (count2[j] < 100) {
				t->set(0.3f);
				t->start();
			}
			for (int i = 0; i < alien2Num; i++) {
				int j = 0;
				if (count2[j] == 3 * i) {
					alien2[i]->show();
					alien2Timer[i]->start();
				}
				j++;
			}
			return true;
			});
	}

	startButton2->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction)-> bool {
		alien2[0]->show();
		alien2Timer[0]->start();
		startButton2->hide();
		return true;
		});

	startGame(scene1);

	return 0;
}