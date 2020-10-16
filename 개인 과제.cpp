#include <bangtal>
#include <ctime>
#include <iostream>

using namespace bangtal;
using namespace std;



int main() {
	clock_t start;
	srand((unsigned int)time(NULL)); // 랜덤 초기화 호출
	auto sound1 = Sound::create("sound/backgroundsound.mp3");
	auto aliensound1 = Sound::create("sound/aliensound1.mp3");
	auto aliensound2 = Sound::create("sound/aliensound2.mp3");
	auto aliensound3 = Sound::create("sound/aliensound3.mp3");
	auto aliensound4 = Sound::create("sound/aliensound4.mp3");
	auto shotsound1 = Sound::create("sound/shotsound1.mp3");
	auto shotsound2 = Sound::create("sound/shotsound1.mp3");
	sound1->play(true);

	auto sceneX = 550, sceneY = 30;
	ScenePtr firstpage;
	firstpage = Scene::create("AlienAttack", "image1/firstpage.png");
	ScenePtr lastpage;
	lastpage = Scene::create("EndGame", "image1/lastpage.png");
	const auto sceneNum = 6;
	ScenePtr scene[sceneNum];
	ObjectPtr startButton[sceneNum];
	ObjectPtr endButton[sceneNum];

	for (int i = 0; i < sceneNum; i++) {
		string stageName = "STAGE " + to_string(i + 1);
		string fileName = "image1/background" + to_string(i + 1) + ".jpg";
		scene[i] = Scene::create(stageName, fileName);
		startButton[i] = Object::create("image1/start.png", scene[i], sceneX, sceneY);
		startButton[i]->setScale(0.1f);
	}

	const int startPageNum = 3;
	ScenePtr startPage[startPageNum];
	ObjectPtr passButton[startPageNum];
	const int tutorialNum = 6;
	ScenePtr tutorial[tutorialNum];
	ObjectPtr nextButton[tutorialNum];

	for (int i = 0; i < startPageNum; i++) {
		string stageName = "Alien Attack ";
		string fileName = "image1/page" + to_string(i + 1) + ".png";
		startPage[i] = Scene::create(stageName, fileName);
		passButton[i] = Object::create("image1/next.png", startPage[i], sceneX, sceneY);
		passButton[i]->setScale(0.1f);
		passButton[i]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction action)-> bool {
			int j;
			for (j = 0; j < startPageNum; j++) {
				if (passButton[j] == object)
					break;
			}
			if (j == 2) tutorial[0]->enter();
			else {
				startPage[j + 1]->enter();
				passButton[j + 1]->show();
			}
			return true;
			});
	}


	for (int i = 0; i < tutorialNum; i++) {
		string stageName = "Tutorial " + to_string(i + 1);
		string fileName = "image1/tutorial" + to_string(i + 1) + ".png";
		tutorial[i] = Scene::create(stageName, fileName);
		nextButton[i] = Object::create("image1/next.png", tutorial[i], sceneX, sceneY);
		nextButton[i]->setScale(0.1f);
		nextButton[i]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction action)-> bool {
			int j;
			for (j = 0; j < tutorialNum; j++) {
				if (nextButton[j] == object)
					break;
			}
			scene[j]->enter();
			startButton[j]->show();
			return true;
			});
	}

	//stage1
	const auto alien1Num = 100;
	auto pointCheck1 = 0;

	int alien1X[alien1Num];
	int alien1Y[alien1Num];
	ObjectPtr alien1[alien1Num];


	// 외계인 y축 랜덤좌표 생성
	for (int i = 0; i < alien1Num; i++) {
		alien1X[i] = -100;
		int n = rand() % 550;
		alien1Y[i] = n;
	}

	// 외계인 생성& 클릭시 포인트 추가
	for (int i = 0; i < alien1Num; i++) {
		//float n = rand() % 20 / 100;
		alien1[i] = Object::create("image1/alien1.png", scene[0], alien1X[i], alien1Y[i], false);
		alien1[i]->setScale(0.12f);
		alien1[i]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction action)-> bool {
			int j;
			for (j = 0; j < alien1Num; j++) {
				if (alien1[j] == object)
					break;
			}
			aliensound1->play();
			alien1[j]->hide();
			++pointCheck1;
			if (pointCheck1 == 5) {
				showMessage("Stage 1 통과!");
				tutorial[1]->enter();
			}
			return true;
			});
	}

	TimerPtr alien1Timer[alien1Num];
	int count1[alien1Num];

	for (int i = 0; i < alien1Num; i++) {
		count1[i] = 0;
		alien1Timer[i] = Timer::create(0.2f);
	}

	// 외계인 이동
	for (int a = 0; a < alien1Num; a++) {
		alien1Timer[a]->setOnTimerCallback([&](TimerPtr t)->bool {
			int j;
			for (j = 0; j < alien1Num; j++) {
				if (alien1Timer[j] == t)
					break;
			}
			auto n = rand() % 30;
			alien1X[j] += n;
			alien1[j]->locate(scene[0], alien1X[j], alien1Y[j]);
			count1[j]++;
			if (count1[j] < 500) {
				t->set(0.03f);
				t->start();
			}
			for (int i = 0; i < alien1Num; i++) {
				int j = 0;
				if (count1[j] == 25 * i) {
					alien1[i]->show();
					alien1Timer[i]->start();
				}
				j++;
			}
			return true;
			});
	}

	startButton[0]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction)-> bool {
		alien1[0]->show();
		alien1Timer[0]->start();
		startButton[0]->hide();
		start = clock();
		return true;
		});





	//stage 2

	const auto alien2Num = 100;
	auto pointCheck2 = 0;

	int alien2X[alien2Num];
	int alien2Y[alien2Num];
	ObjectPtr alien2[alien2Num];


	// 우주선 y축 랜덤좌표 생성
	for (int i = 0; i < alien2Num; i++) {
		alien2X[i] = 1400;
		int n = rand() % 500;
		alien2Y[i] = n;
	}

	// 우주선 생성& 클릭시 포인트 추가
	for (int i = 0; i < alien2Num; i++) {
		alien2[i] = Object::create("image1/alien2.png", scene[1], alien2X[i], alien2Y[i], false);
		alien2[i]->setScale(0.12f);
		alien2[i]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction action)-> bool {
			int j;
			for (j = 0; j < alien2Num; j++) {
				if (alien2[j] == object)
					break;
			}
			int a = rand() % 2;
			if (a == 0) 	shotsound1->play();
			if (a == 1) 	shotsound2->play();
			alien2[j]->hide();
			++pointCheck2;
			if (pointCheck2 == 10) {
				showMessage("Stage 2 통과!");
				tutorial[2]->enter();
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
			auto n = rand() % 40;
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
			if (count2[9] < 500) {
				t->set(0.03f);
				t->start();
				//	if ((count2[9] == 140) && (pointCheck2 <= 7)) {
				//		showMessage("미션 실패! 클릭 시 스테이지가 다시 시작됩니다!");
				//		restartButton[1]->show();
				//	}
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

	const auto alien3_1Num = 100;
	auto pointCheck3 = 0;

	int alien3_1X[alien3_1Num];
	int alien3_1Y[alien3_1Num];
	ObjectPtr alien3_1[alien3_1Num];

	const auto alien3_2Num = 100;
	int alien3_2X[alien3_2Num];
	int alien3_2Y[alien3_2Num];
	ObjectPtr alien3_2[alien3_2Num];

	// alien3_1 y축 랜덤좌표 생성
	for (int i = 0; i < alien3_1Num; i++) {
		alien3_1X[i] = 1200;
		int n = rand() % 600;
		alien3_1Y[i] = n;
	}

	// alien3_2 x축 랜덤좌표 생성
	for (int i = 0; i < alien3_2Num; i++) {
		alien3_2Y[i] = 850;
		int n = rand() % 1100;
		alien3_2X[i] = n;
	}

	// alien3_1 생성& 클릭시 포인트 추가
	for (int i = 0; i < alien3_1Num; i++) {
		alien3_1[i] = Object::create("image1/alien3_1.png", scene[2], alien3_1X[i], alien3_1Y[i], false);
		alien3_1[i]->setScale(0.13f);
		alien3_1[i]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction action)-> bool {
			int j;
			for (j = 0; j < alien3_1Num; j++) {
				if (alien3_1[j] == object)
					break;
			}
			aliensound3->play();
			alien3_1[j]->hide();
			++pointCheck3;
			if (pointCheck3 == 15) {
				showMessage("Stage 3 통과!");
				tutorial[3]->enter();
			}
			return true;
			});
	}

	// alien3_2 생성& 클릭시 포인트 추가
	for (int i = 0; i < alien3_2Num; i++) {
		//float n = rand() % 20 / 100;
		alien3_2[i] = Object::create("image1/alien3_2.png", scene[2], alien3_2X[i], alien3_2Y[i], false);
		alien3_2[i]->setScale(0.08f);
		alien3_2[i]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction action)-> bool {
			int j;
			for (j = 0; j < alien3_2Num; j++) {
				if (alien3_2[j] == object)
					break;
			}
			aliensound4->play();
			alien3_2[j]->hide();
			++pointCheck3;
			if (pointCheck3 == 10) {
				showMessage("Stage 3 통과!");
				tutorial[3]->enter();
			}
			return true;
			});
	}

	TimerPtr alien3_1Timer[alien3_1Num];
	int count3_1[alien3_1Num];
	for (int i = 0; i < alien3_1Num; i++) {
		count3_1[i] = 0;
		alien3_1Timer[i] = Timer::create(0.5f);
	}

	TimerPtr alien3_2Timer[alien3_2Num];
	int count3_2[alien3_2Num];
	for (int i = 0; i < alien3_2Num; i++) {
		count3_2[i] = 0;
		alien3_2Timer[i] = Timer::create(0.5f);
	}

	for (int a = 0; a < alien3_1Num; a++) {
		alien3_1Timer[a]->setOnTimerCallback([&](TimerPtr t)->bool {
			int j;
			for (j = 0; j < alien3_1Num; j++) {
				if (alien3_1Timer[j] == t)
					break;
			}
			auto n = rand() % 40;
			alien3_1X[j] -= n;
			alien3_1[j]->locate(scene[2], alien3_1X[j], alien3_1Y[j]);
			count3_1[j]++;
			if (count3_1[j] < 500) {
				t->set(0.03f);
				t->start();
			}
			for (int i = 0; i < alien3_1Num; i++) {
				int j = 0;
				if (count3_1[j] == 30 * i) {
					alien3_1[i]->show();
					alien3_1Timer[i]->start();
				}
				j++;
			}
			return true;
			});
	}

	for (int a = 0; a < alien3_2Num; a++) {
		alien3_2Timer[a]->setOnTimerCallback([&](TimerPtr t)->bool {
			int j;
			for (j = 0; j < alien3_2Num; j++) {
				if (alien3_2Timer[j] == t)
					break;
			}
			auto n = rand() % 35;
			alien3_2Y[j] -= n;
			alien3_2[j]->locate(scene[2], alien3_2X[j], alien3_2Y[j]);
			count3_2[j]++;
			if (count3_2[j] < 500) {
				t->set(0.03f);
				t->start();
			}
			for (int i = 0; i < alien3_2Num; i++) {
				int j = 0;
				if (count3_2[j] == 30 * i) {
					alien3_2[i]->show();
					alien3_2Timer[i]->start();
				}
				j++;
			}
			return true;
			});
	}

	startButton[2]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction)-> bool {
		alien3_1[0]->show();
		alien3_1Timer[0]->start();
		alien3_2[0]->show();
		alien3_2Timer[0]->start();
		startButton[2]->hide();
		return true;
		});




	//stage 4

	const auto alien4Num = 100;
	auto pointCheck4 = 0;

	int alien4X[alien4Num];
	int alien4Y[alien4Num];
	ObjectPtr alien4[alien4Num];


	// 외계인 x, y축 랜덤좌표 생성
	for (int i = 0; i < alien4Num; i++) {
		int m = rand() % 1100;
		alien4X[i] = m;
		int n = rand() % 500;
		alien4Y[i] = n;
	}

	// 외계인 생성& 클릭시 포인트 추가
	for (int i = 0; i < alien4Num; i++) {
		alien4[i] = Object::create("image1/alien4.png", scene[3], alien4X[i], alien4Y[i], false);
		alien4[i]->setScale(0.15f);
		alien4[i]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction action)-> bool {
			int j;
			for (j = 0; j < alien4Num; j++) {
				if (alien4[j] == object)
					break;
			}
			int a = rand() % 2;
			if (a == 0) 	aliensound2->play();
			if (a == 1) 	aliensound2->play();
			alien4[j]->hide();
			++pointCheck4;
			if (pointCheck4 == 10) {
				showMessage("Stage 4 통과!");
				tutorial[4]->enter();
			}
			return true;
			});
	}

	TimerPtr alien4Timer[alien4Num];
	int count4[alien4Num];
	for (int i = 0; i < alien4Num; i++) {
		count4[i] = 0;
		alien4Timer[i] = Timer::create(0.3f);
	}

	for (int a = 0; a < alien4Num; a++) {
		alien4Timer[a]->setOnTimerCallback([&](TimerPtr t)->bool {
			int j;
			for (j = 0; j < alien4Num; j++) {
				if (alien4Timer[j] == t)
					break;
			}
			alien4[j]->hide();
			if (count4[j] < 500) {
				t->set(0.3f);
				t->start();
			}
			count4[j]++;
			for (int i = 0; i < alien4Num; i++) {
				int j = 0;
				if (count4[j] == 4 * i) {
					alien4[i]->show();
					alien4Timer[i]->start();
				}
			}
			return true;
			});
	}


	startButton[3]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction)-> bool {
		alien4[0]->show();
		alien4Timer[0]->start();
		startButton[3]->hide();
		return true;
		});




	//stage 5      외계인 보스 1

	auto pointCheck5 = 0;
	auto alien5X = 600;
	auto alien5Y = 300;
	auto alien5 = Object::create("image1/alien5.png", scene[4], alien5X, alien5Y, false);
	alien5->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction action)-> bool {
		int a = rand() % 2;
		if (a == 0) 	shotsound1->play();
		if (a == 1) 	shotsound2->play();

		++pointCheck5;
		if (pointCheck5 == 10) {
			showMessage("Stage 4 통과!");
			tutorial[5]->enter();
		}
		return true;
		});

	alien5->setScale(0.25f);
	TimerPtr alien5Timer;
	alien5Timer = Timer::create(0.5f);
	auto count5 = 0;

	//외계인이 가운데에서 랜덤방향으로 막 움직임 >> 뚜드려패야 스테이지 클리어

	alien5Timer->setOnTimerCallback([&](TimerPtr t)->bool {	
		auto m = rand() % 4;
		auto n = rand() % 40 * 8;
		if (alien5X < 0) alien5X += n;
		else if (alien5X > 1000) alien5X -= n;
		else if (alien5Y < 0) alien5Y += n;
		else if (alien5Y > 600) alien5Y -= n;
		else {
			switch (m) {
			case 0: alien5X -= n; break;
			case 1: alien5X += n; break;
			case 2: alien5Y -= n; break;
			case 3: alien5Y += n; break;
			}
		}

		alien5->locate(scene[4], alien5X, alien5Y);
		count5++;
		if (count5 < 1000) {
			t->set(0.2f);
			t->start();
		}
		return true;
		});


	startButton[4]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction)-> bool {
		alien5->show();
		alien5Timer->start();
		startButton[4]->hide();
		return true;
		});





	//stage 6  보스 스테이지 2

	auto pointCheck6_1 = 0;
	auto pointCheck6_2 = 0;
	auto alien6_1X = 600;
	auto alien6_1Y = 300;
	auto alien6_1 = Object::create("image1/alien6_1.png", scene[5], alien6_1X, alien6_1Y, false);
	alien6_1->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction action)-> bool {
		int a = rand() % 2;
		if (a == 0) 	shotsound1->play();
		if (a == 1) 	shotsound2->play();

		++pointCheck6_1;
		if (pointCheck6_1 == 10) {
			showMessage("외계인 10대 타격 성공!");
		}
		if ((pointCheck6_1 == 10) && (pointCheck6_2 == 10)) {
			float endTime = (float)(clock() - start) / CLOCKS_PER_SEC;
			if (endTime <= 60) {
				showMessage("1분 이내 성공! 당신은 LEGEND HERO 입니다!");
			}
			else if (endTime > 60 && endTime <= 120 ) {
				showMessage("2분 이내 성공! 당신은 SUPER HERO 입니다!");
			}
			else if (endTime > 120 && endTime <= 180 ) {
				showMessage("3분 이내 성공! 당신은 HERO 입니다!");
			}
			else {
				showMessage("지구 방어 성공! 당신은 Warrior 입니다!");
			}
			lastpage->enter();
		}
		return true;
		});

	alien6_1->setScale(0.20f);
	TimerPtr alien6_1Timer;
	alien6_1Timer = Timer::create(0.5f);
	auto count6_1 = 0;

	//외계인이 가운데에서 랜덤방향으로 움직이면서 크기도 계속 바뀜 >> 뚜드려패야 스테이지 클리어

	alien6_1Timer->setOnTimerCallback([&](TimerPtr t)->bool {
		auto m = rand() % 4;
		auto n = rand() % 40 * 8;
		if (alien6_1X < 0) alien6_1X += n;
		else if (alien6_1X > 1000) alien6_1X -= n;
		else if (alien6_1Y < 0) alien6_1Y += n;
		else if (alien6_1Y > 600) alien6_1Y -= n;
		else {
			switch (m) {
			case 0: alien6_1X -= n; break;
			case 1: alien6_1X += n; break;
			case 2: alien6_1Y -= n; break;
			case 3: alien6_1Y += n; break;
			}
		}


		alien6_1->locate(scene[5], alien6_1X, alien6_1Y);
		count6_1++;
		if (count6_1 < 1000) {
			t->set(0.2f);
			t->start();
		}
		return true;
		});


	const auto alien6_2Num = 100;
	int alien6_2X[alien6_2Num];
	int alien6_2Y[alien6_2Num];
	ObjectPtr alien6_2[alien6_2Num];

	// alien6_2 x축 랜덤좌표 생성
	for (int i = 0; i < alien6_2Num; i++) {
		alien6_2Y[i] = -100;
		int n = rand() % 1100;
		alien6_2X[i] = n;
	}


	// alien6_2 생성& 클릭시 포인트 추가
	for (int i = 0; i < alien6_2Num; i++) {
		alien6_2[i] = Object::create("image1/alien6_2.png", scene[5], alien6_2X[i], alien6_2Y[i], false);
		alien6_2[i]->setScale(0.15f);
		alien6_2[i]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction action)-> bool {
			int j;
			for (j = 0; j < alien6_2Num; j++) {
				if (alien6_2[j] == object)
					break;
			}
			shotsound2->play();
			alien6_2[j]->hide();
			++pointCheck6_2;
			if (pointCheck6_2 == 10) {
				showMessage("우주선 10대 격추 성공!");
			}
			if ((pointCheck6_1 == 10) && (pointCheck6_2 == 10)) {
				float endTime = (float)(clock() - start) / CLOCKS_PER_SEC;
				if (endTime <= 60) {
					showMessage("1분 이내 지구 방어 성공!");
				}
				else if (endTime <= 120 && endTime > 60) {
					showMessage("2분 이내 지구방어 성공!");
				}
				lastpage->enter();
			}

			return true;
			});


	}
	TimerPtr alien6_2Timer[alien6_2Num];
	int count6_2[alien6_2Num];
	for (int i = 0; i < alien6_2Num; i++) {
		count6_2[i] = 0;
		alien6_2Timer[i] = Timer::create(0.5f);
	}

	for (int a = 0; a < alien6_2Num; a++) {
		alien6_2Timer[a]->setOnTimerCallback([&](TimerPtr t)->bool {
			int j;
			for (j = 0; j < alien6_2Num; j++) {
				if (alien6_2Timer[j] == t)
					break;
			}
			auto n = rand() % 30;
			alien6_2Y[j] += n;
			alien6_2[j]->locate(scene[5], alien6_2X[j], alien6_2Y[j]);
			count6_2[j]++;
			if (count6_2[j] < 1000) {
				t->set(0.03f);
				t->start();
			}
			for (int i = 0; i < alien6_2Num; i++) {
				int j = 0;
				if (count6_2[j] == 30 * i) {
					alien6_2[i]->show();
					alien6_2Timer[i]->start();
				}
				j++;
			}
			return true;
			});
	}

	startButton[5]->setOnMouseCallback([&](ObjectPtr object, int, int, MouseAction)-> bool {
		alien6_1->show();
		alien6_2[0]->show();
		alien6_1Timer->start();
		alien6_2Timer[0]->start();
		startButton[5]->hide();
		return true;
		});

	startGame(startPage[0]);

	return 0;
}