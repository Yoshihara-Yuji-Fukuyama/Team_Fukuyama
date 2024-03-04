//--------------------------------------------
//グローバル変数領域
//--------------------------------------------

CImage* fieldimage = nullptr;

TexAnimData* playeranimdata = nullptr;
CImage* playerimage = nullptr;
CVector2D playerpos = CVector2D(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.75f);

TexAnimData* enemyanimdata = nullptr;
CImage* enemyimagea = nullptr;
CVector2D enemyposa = CVector2D(SCREEN_WIDTH * 0.75f, SCREEN_HEIGHT * 0.8f);
CImage* enemyimageb = nullptr;
CVector2D enemyposb = CVector2D(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.6f);
CImage* enemyimagec = nullptr;
CVector2D enemyposc = CVector2D(SCREEN_WIDTH * 0.85f, SCREEN_HEIGHT * 0.9f);

void updateplayer()
{
	if (HOLD(CInput::eLeft))
	{
		playerpos.x -= 8.0f;
		playerimage->ChangeAnimation(1);
		playerimage->SetFlipH(true);
	}
	else if (HOLD(CInput::eRight))
	{
		playerpos.x += 8.0f;
		playerimage->ChangeAnimation(1);
		playerimage->SetFlipH(false);
	}
	else
	{
		playerimage->ChangeAnimation(0);
	}

	playerimage->SetPos(playerpos);
	playerimage->UpdateAnimation();
}

void updateenemies()
{
	enemyimagea->SetPos(enemyposa);
	enemyimagea->UpdateAnimation();
	enemyimageb->SetPos(enemyposb);
	enemyimageb->UpdateAnimation();
	enemyimagec->SetPos(enemyposc);
	enemyimagec->UpdateAnimation();
}

void MainLoop(void) {
	//--------------------------------------------------------------
	//ゲーム中の動きはここに書く
	//ゲーム中はこの関数_を1秒間に60回呼び出している
	//--------------------------------------------------------------

	updateplayer();
	updateenemies();

	fieldimage->Draw();
	enemyimageb->Draw();
	playerimage->Draw();
	enemyimagea->Draw();
	enemyimagec->Draw();
}
void Init(void)
{

	CFPS::SetFPS(60);
	//フレーム制御初期化
	CFPS::Init();
	//ボタンの設定
	CInput::Init();
	CInput::SetButton(0, CInput::eButton1, 'Z');
	CInput::SetButton(0, CInput::eButton2, 'X');
	CInput::SetButton(0, CInput::eButton3, 'C');
	CInput::SetButton(0, CInput::eButton4, 'V');
	CInput::SetButton(0, CInput::eButton5, VK_SPACE);
	CInput::SetButton(0, CInput::eButton10, VK_RETURN);
	CInput::SetButton(0, CInput::eUp, VK_UP);
	CInput::SetButton(0, CInput::eDown, VK_DOWN);
	CInput::SetButton(0, CInput::eLeft, VK_LEFT);
	CInput::SetButton(0, CInput::eRight, VK_RIGHT);
	CInput::SetButton(0, CInput::eMouseL, VK_LBUTTON);
	CInput::SetButton(0, CInput::eMouseR, VK_RBUTTON);
	CInput::SetButton(0, CInput::eMouseC, VK_MBUTTON);
	//	CInput::SetMouseInside(true);
	//	CInput::ShowCursor(false);
	CInput::Update();
	CInput::Update();

	SetCurrentDirectory("data");
	CSound::GetInstance();

	//-----------------------------------------------------
	//初期化の命令を書く
	//ゲーム起動時に一度だけ呼ばれる
	//-----------------------------------------------------

	fieldimage = CImage::CreateImage("field.png");

	// アニメーション用意
	const int f = 6;
	playeranimdata = new TexAnimData[2]
	{
		// 待機アニメーション
		{
			new TexAnim[6]
			{
				{ 0, f}, { 1, f}, { 2, f},
				{ 3, f}, { 4, f}, { 5, f},
			},
			6
		},
		// 移動アニメーション
		{
			new TexAnim[6]
			{
				{ 6, f}, { 7, f}, { 8, f},
				{ 9, f}, {10, f}, {11, f},
			},
			6
		},
	};
	playerimage = CImage::CreateImage("player.png");
	playerimage->AttachAnimationData(playeranimdata, 384.0f, 384.0f);
	playerimage->ChangeAnimation(0);
	playerimage->SetSize(384.0f, 384.0f);
	playerimage->SetCenter(192.0f, 328.0f);
	playerimage->SetPos(playerpos);

	enemyanimdata = new TexAnimData[1]
	{
		{
			new TexAnim[4]
			{
				{ 0, f}, { 1, f}, { 2, f}, { 3, f},
			},
			4
		},
	};

	enemyimagea = CImage::CreateImage("slime_a.png");
	enemyimagea->AttachAnimationData(enemyanimdata, 256.0f, 256.0f);
	enemyimagea->ChangeAnimation(0);
	enemyimagea->SetSize(256.0f, 256.0f);
	enemyimagea->SetCenter(128.0f, 184.0f);
	enemyimagea->SetPos(enemyposa);
	enemyimagea->SetFlipH(true);

	enemyimageb = CImage::CreateImage("slime_b.png");
	enemyimageb->AttachAnimationData(enemyanimdata, 256.0f, 256.0f);
	enemyimageb->ChangeAnimation(0);
	enemyimageb->SetSize(256.0f, 256.0f);
	enemyimageb->SetCenter(128.0f, 184.0f);
	enemyimageb->SetPos(enemyposb);
	enemyimageb->SetFlipH(true);

	enemyimagec = CImage::CreateImage("slime_c.png");
	enemyimagec->AttachAnimationData(enemyanimdata, 256.0f, 256.0f);
	enemyimagec->ChangeAnimation(0);
	enemyimagec->SetSize(256.0f, 256.0f);
	enemyimagec->SetCenter(128.0f, 184.0f);
	enemyimagec->SetPos(enemyposc);
	enemyimagec->SetFlipH(true);
}


void Release()
{
	CLoadThread::ClearInstance();
	CSound::ClearInstance();
	CResourceManager::ClearInstance();
}

static void ResizeCallback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);

	//画面解像度変動
	CCamera::GetCamera()->SetSize((float)w, (float)h);
	//画面解像度固定
	//CCamera::GetCamera()->SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	CCamera::GetCamera()->Viewport(0, 0, w, h);
	CCamera::GetCurrent()->Perspective(DtoR(60.0), (float)w / (float)h, 1.0, 1000.0);

	glfwGetWindowPos(window, &GL::window_x, &GL::window_y);
	GL::UpdateWindowRect(GL::window_x, GL::window_y, w, h);
	CInput::UpdateClipCursor(true);

}
static void WheelCallback(GLFWwindow* _window, double _offsetx, double _offsety) {
	CInput::AddMouseWheel((int)_offsety);

}
static void PosCallback(GLFWwindow* _window, int x, int y) {
	GL::window_x = x;
	GL::window_y = y;
	GL::UpdateWindosRect(x, y, GL::window_width, GL::window_height);
	CInput::UpdateClipCursor(true);

}
static void FocusCallback(GLFWwindow* _window, int f) {
	CInput::UpdateClipCursor(f);
	GL::focus = f;
}

static void error_callback(int error, const char* description)
{
	printf("Error: %s\n", description);
}

//フルスクリーン?ウインドウモードの切り替え
//Alt+Enterで切り替える
void CheckFullScreen() {
	static int key_enter = 0;
	int key_enter_buf = key_enter;
	if (key_enter_buf ^ (key_enter = glfwGetKey(GL::window, GLFW_KEY_ENTER)) && key_enter && (glfwGetKey(GL::window, GLFW_KEY_LEFT_ALT) || glfwGetKey(GL::window, GLFW_KEY_RIGHT_ALT))) {
		GL::ChangeFullScreen(!GL::full_screen);
	}
}

int __main(int* argcp, char** argv) {
	// メモリリーク検出
	//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	//OpenGL4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) return -1;
	//	glutInit(argcp, argv);

	GL::window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Simple", nullptr, nullptr);
	glfwGetWindowSize(GL::window, &GL::window_width, &GL::window_height);
	glfwGetWindowPos(GL::window, &GL::window_x, &GL::window_y);

	glfwSetFramebufferSizeCallback(GL::window, ResizeCallback);
	glfwSetScrollCallback(GL::window, WheelCallback);
	glfwSetWindowFocusCallback(GL::window, FocusCallback);
	glfwSetWindowPosCallback(GL::window, PosCallback);
	if (!GL::window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(GL::window);
	glfwSwapInterval(1);
	ResizeCallback(GL::window, SCREEN_WIDTH, SCREEN_HEIGHT);

	GLenum err = glewInit();
	if (err == GLEW_OK) {
		printf("%s\n", glewGetString(GLEW_VERSION));
	}
	else {
		printf("%s\n", glewGetErrorString(err));
		getchar();
		return -1;
	}
	HDC glDc = wglGetCurrentDC();
	GL::hWnd = WindowFromDC(glDc);
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);//ブレンドの有効化
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//固定シェーダー用
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_ALPHA_TEST);

	Init();
	while (!glfwWindowShouldClose(GL::window)) {
		CheckFullScreen();


		CInput::Update();
		//各バッファーをクリア
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		MainLoop();


		glfwSwapBuffers(GL::window);


		CFPS::Wait();

		char title[32];
		sprintf_s(title, "Sample");
		glfwSetWindowTitle(GL::window, title);

		glfwPollEvents();
		if (glfwGetKey(GL::window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(GL::window, GL_TRUE);
		}

	}

	glfwTerminate();




	Release();
	return 0;
}

INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR argv, INT argc)
{
	return __main(&__argc, __argv);
}

int main(int argc, char** argv)
{
	return __main(&argc, argv);
}