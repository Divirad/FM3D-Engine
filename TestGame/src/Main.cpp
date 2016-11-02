#include <Engine.h>
#include <chrono>
#include <iomanip>

using namespace Engine;

void Menu(HINSTANCE hInstance);
void NewButton(HINSTANCE hInstance);
void StarwarsScene(HINSTANCE hInstance);
void MatrixTester(HINSTANCE hInstance);

///////////////////////////////////////////////////////////////
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Menu(hInstance);
}
///////////////////////////////////////////////////////////////


void Menu(HINSTANCE hInstance)
{
	int but=1;

	Window::StartConsole();
	FileManager::Initialize("res/", "../FM3D-Engine/", "fm3d");
	ExternFileManager::Initialize();
	Window* win = Window::SetInstance(Window::Create(Platform::WINDOWS, hInstance));
	win->Start(600, 600, L"Voll das Krasse Fenster");
	CompCoords::Initialize(600, 600);
	RenderSystem* renderSystem = RenderSystem::Create(OpenGL3_3);
	if (!renderSystem->Initialize(win->GetWidth(), win->GetHeight(), true, ((Win32Window*)win)->GetHwnd(), false)) {
		std::cout << "Rendersystem Initializing Error!" << std::endl;
	}
	RenderTarget2D* target2D = renderSystem->CreateRenderTarget2D(Vector2i(win->GetWidth(), win->GetHeight()), true);
	Renderer2D* renderer2D = renderSystem->CreateRenderer2D(target2D);
	Matrix4f projectionMatrix = Matrix4f::Perspective(70.0f, (float)win->GetWidth() / (float)win->GetHeight(), 0.1f, 1000.0f);
	//->Initialize(projectionMatrix);
	///
	///Textures
	///
	Texture* trash = renderSystem->CreateTexture();
	Texture* doc = renderSystem->CreateTexture();

	Texture* left = renderSystem->CreateTexture();
	Texture* right = renderSystem->CreateTexture();
	Texture* middle = renderSystem->CreateTexture();
	
	Texture* home = renderSystem->CreateTexture();
	Texture* search = renderSystem->CreateTexture();
	Texture* profile = renderSystem->CreateTexture();

	ExternFileManager::ReadTextureFile("/doc.png", doc, Texture::NEAREST);
	ExternFileManager::ReadTextureFile("/trash.png", trash, Texture::NEAREST);

	ExternFileManager::ReadTextureFile("/0left.png", left, Texture::NEAREST);
	ExternFileManager::ReadTextureFile("/0right.png", right, Texture::NEAREST);
	ExternFileManager::ReadTextureFile("/0middle.png", middle, Texture::NEAREST);

	ExternFileManager::ReadTextureFile("/search.png", search, Texture::NEAREST);
	ExternFileManager::ReadTextureFile("/home.png", home, Texture::NEAREST);
	ExternFileManager::ReadTextureFile("/profile.png", profile, Texture::NEAREST);


	PictureQuad pq_trash(trash, Vector3f(-1.0f, -1.0f, 0));

	DragDropper dd_doc(doc, Vector3f(0.0f, 0.5f, 0));
	dd_doc.Anchor(DragDropper::TOP);
	
	Button bt_search(search, Vector3f(0.0f, 0.4f, 0));
	Button bt_home(home, Vector3f(0.0f, 0.0f, 0));
	Button bt_profile(profile, Vector3f(0.0f, -0.4f, 0));
	
	bt_search.AutoSize();
	bt_home.AutoSize();
	bt_profile.AutoSize();

	bt_search.Anchor(Button::CENTER_HORIZONTAL);
	bt_home.Anchor(Button::CENTER_HORIZONTAL);
	bt_profile.Anchor(Button::CENTER_HORIZONTAL);
	


	Button bt_left(left, Vector3f(-0.5f, -0.7f, 0));
	Button bt_right(right, Vector3f(0.5f, -0.7f, 0));
	Button bt_middle(middle, Vector3f(0.0f, -0.7f, 0));
	bt_middle.Anchor(Button::CENTER_VERTICAL);
	
	bt_middle.SetPosition0(Vector3f(bt_middle.GetPosition0().x,-0.7f,0));

	bt_left.AutoSize();
	bt_right.AutoSize();
	bt_middle.AutoSize();

	
	
	Color4f clearColor(1.0f, 0.5f, 0.2f, 1.0f);

	///
	///FONT instruction
	///
	Engine::Font* inst;
	ExternFileManager::ReadFontFile("fontilein.ttf", 50, Vector2f(0.001f, 0.001f), renderSystem->CreateTexture(), &inst);
	Text instruction;
	instruction.color = 0xffffffff;
	instruction.font = inst;
	instruction.txt = "Pull the doc into the trash\n";

	while (!win->ShouldClose()) {
		if (!win->HasMessage()) {

			renderSystem->BeginRendering(clearColor);
			///
			///Buffer Start
			///
			renderer2D->Begin();
			///
			///Button wird in den Buffer geschrieben
			///
			renderer2D->Submit(&pq_trash);
			renderer2D->Submit(&dd_doc);
			
			renderer2D->Submit(&bt_search);
			renderer2D->Submit(&bt_home);
			renderer2D->Submit(&bt_profile);
			
			renderer2D->Submit(&bt_left);
			renderer2D->Submit(&bt_right);
			renderer2D->Submit(&bt_middle);

			renderer2D->DrawString(instruction, Vector3f(-1.0f, 0.8f, 0.0f));

			///
			///END SUBMITTING
			///
			renderer2D->End();
			///
			///CHECK
			///
			dd_doc.InFieldAnimation();

			bt_search.InFieldAnimation();
			bt_home.InFieldAnimation();
			bt_profile.InFieldAnimation();

			bt_left.InFieldAnimation();
			bt_middle.InFieldAnimation();
			bt_right.InFieldAnimation();


			if (bt_search.Click(MOUSE_LEFT) == true){

			}



			if (pq_trash.Collision(dd_doc)) {
				instruction.txt = "Gooood job! Now Click it and pull it through the black hole!";
			}
			if (pq_trash.Click(MOUSE_LEFT) == true)
			{
				instruction.txt = instruction.txt + " FUUUCK ITS DARK HERE!";
			}
			if (dd_doc.Click(MOUSE_LEFT) == true)
			{
				if (pq_trash.Collision(dd_doc)){
					dd_doc.SetPosition0(Vector3f(-2.0f, -2.0f, 0.0f));
					instruction.txt = "Good job lil astronaut!";
					dd_doc.AutoSize();
				}
			}



			dd_doc.DragDrop(MOUSE_LEFT);
			

			renderer2D->Flush();
			renderSystem->EndRendering();
		}
	};
	renderSystem->Shutdown();


}

/////
/////2D Test Project
/////
//void NewButton(HINSTANCE hInstance)
//{
//	///
//	///Start der Konsole
//	///
//	Window::StartConsole();
//	///
//	///Initialisierung des Filemanagers
//	///
//	FileManager::Initialize("res/", "../FM3D-Engine/", "fm3d");
//	///
//	///Initialisierung des Externen Filemanagers
//	///
//	ExternFileManager::Initialize();
//	///
//	///Window wird erstellt und gestartet
//	///
//	Window* win = Window::SetInstance(Window::Create(Platform::WINDOWS, hInstance));
//	win->Start(1280, 720, L"Voll das Krasse Fenster");
//	///
//	///Compute Coordinates wird Initialisiert
//	///
//	CompCoords::Initialize(1280, 720);
//	
//	///
//	///Rendersystem wird mit OpenGL 3.3 erstellt
//	///
//	RenderSystem* renderSystem = RenderSystem::Create(OpenGL3_3);
//	///
//	///Check if rendersystem is konkretkrass 
//	///
//	if (!renderSystem->Initialize(win->GetWidth(), win->GetHeight(), true, ((Win32Window*)win)->GetHwnd(), false)) {
//		std::cout << "Rendersystem Initializing Error!" << std::endl;
//	}
//	///
//	///2D Rendersystem wird erstellt
//	///
//	Renderer2D* renderer = renderSystem->CreateRenderer2D();
//	///
//	///Definierung der Projektionsmatrix
//	///
//	Matrix4f projectionMatrix = Matrix4f::Identity();
//	///
//	///Initialisierung der Projektionsmatrix
//	///
//	renderer->Initialize(projectionMatrix);
//		///
//		///Leere Textur wird erstellt
//		///
//		Texture* Test_Tex = renderSystem->CreateTexture(NULL);
//		Texture* VollDieTextur = renderSystem->CreateTexture(NULL);
//		///
//		///Textur wird eingelesen
//		///
//		ExternFileManager::ReadTextureFile("NewFM3DLogoMini.png", Test_Tex, Texture::NEAREST);
//		ExternFileManager::ReadTextureFile("knupke392x378.png", VollDieTextur, Texture::NEAREST);
//		///
//		///BasicItem2D wird erstellt 
//		///
//		DragDropper MyFirstButton(Test_Tex, Vector3f(0.0f, 0.0f, 0.0f)); 
//		DragDropper VollDatZweiteKnoppke(VollDieTextur, Vector3f(-0.5f, -0.5f, 0.1f));
//		Engine::Font* f;
//		ExternFileManager::ReadFontFile("fontilein.ttf", 50, Vector2f(0.001f, 0.001f), renderSystem->CreateTexture(""), &f);
//		///
//		///Hauptschleife
//		///
//		while (!win->ShouldClose()) {
//			if (!win->HasMessage()) {
//
//				renderSystem->BeginRendering(new float[4]{ 0.2f, 0.5f, 0.5f, 1.0f });
//				///
//				///Buffer Start
//				///
//				renderer->Begin();
//				///
//				///Button wird in den Buffer geschrieben
//				///
//				renderer->Submit(&VollDatZweiteKnoppke);
//				renderer->DrawString({ "supper tooohhler Text :)", f, 0xffffffff }, Vector3f(-0.5f, -0.2f, -1.0f));
//
//				renderer->Submit(&MyFirstButton);
//				///
//				///END SUBMITTING
//				///
//				renderer->End();
//				///
//				///TEST AREA
//				///
//				//MyFirstButton.InFieldAnimation();
//				//MyFirstButton.InFieldAnimation();
//				//MyFirstButton.ClickAnimation(MOUSE_LEFT);
//				MyFirstButton.InFieldAnimation();
//
//				MyFirstButton.DragDrop(MOUSE_LEFT);
//				MyFirstButton.ClickAnimation(MOUSE_LEFT);
//				if (MyFirstButton.Click(MOUSE_LEFT)==true){
//
//				}
//				/*VollDatZweiteKnoppke.DragDrop(MOUSE_RIGHT);
//				MyFirstButton.Click(MOUSE_LEFT);*/
//				renderer->Flush();
//				renderSystem->EndRendering();
//			}
//		};
//		///Renderer wird beendet
//		renderSystem->Shutdown();
//}
//
//void StarwarsScene(HINSTANCE hInstance) {
//	Window::StartConsole();
//	FileManager::Initialize("res/", "../FM3D-Engine/", "fm3d");
//	ExternFileManager::Initialize();
//
//	Window* win = Window::SetInstance(Window::Create(Platform::WINDOWS, hInstance));
//	win->Start(1280, 720, L"JOOONGE");
//	
//
//	RenderSystem* renderSystem = RenderSystem::Create(OpenGL3_3);
//
//	if (!renderSystem->Initialize(win->GetWidth(), win->GetHeight(), true, ((Win32Window*)win)->GetHwnd(), false)) {
//		std::cout << "Rendersystem Initializing Error!" << std::endl;
//	}
//	Matrix4f projectionMatrix = Matrix4f::Perspective(70.0f, (float)win->GetWidth() / (float)win->GetHeight(), 0.1f, 1000.0f);
//
//	////////////////////////////projectionMatrix.Transpose();
//	Renderer3D* renderer = renderSystem->CreateRenderer3D(projectionMatrix, win->GetWidth(), win->GetHeight());
//
//	Texture* emptyTex = renderSystem->CreateTexture(NULL);
//	float pixels[] = {
//		1.0f, 1.0f, 1.0f, 1.0f,
//		1.0f, 1.0f, 1.0f, 1.0f,
//		1.0f, 1.0f, 1.0f, 1.0f,
//		1.0f, 1.0f, 1.0f, 1.0f
//	};
//	emptyTex->Initialize(2, 2, Texture::NEAREST, Texture::CLAMP, pixels, 32);
//
//	//Texture* trooperTex = renderSystem->CreateTexture(NULL);
//	//ExternFileManager::ReadTextureFile("Stormtrooper_d.tga", trooperTex, Texture::NEAREST);
//	//Texture* blasterTex = renderSystem->CreateTexture(NULL);
//	//ExternFileManager::ReadTextureFile("E11_Blaster_d.tga", blasterTex, Texture::NEAREST);
//
//	//Model* trooperMesh;
//	//ExternFileManager::ReadModelFile("Stormtrooper.dae", renderSystem, &trooperMesh, false, false);
//
//	//Array<const Material*>& materials = trooperMesh->GetMaterials();
//	//Material mat1 = { 0xffffffff, blasterTex };
//	//Material mat2 = { 0xffffffff, blasterTex };
//	//Material mat3 = { 0xffffffff, trooperTex };
//
//	//materials[0] = &mat1;
//	//materials[1] = &mat2;
//	//materials[2] = &mat3;
//
//	//Entity trooper1(Vector3f(-2.0f, -2.0f, -5.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f), trooperMesh);
//	//Entity trooper2(Vector3f(2.0f, -2.0f, -5.0f), Vector3f(0.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f), trooperMesh);
//	
//	Texture* bobaTexBody = renderSystem->CreateTexture(NULL);
//	ExternFileManager::ReadTextureFile("Fett_body_D.tga", bobaTexBody, Texture::NEAREST);
//	Texture* bobaTexJet = renderSystem->CreateTexture(NULL);
//	ExternFileManager::ReadTextureFile("Fett_jetpak_D.tga", bobaTexJet, Texture::NEAREST);
//	Texture* bobaTexHelmet = renderSystem->CreateTexture(NULL);
//	ExternFileManager::ReadTextureFile("Fett_helmet_D.tga", bobaTexHelmet, Texture::NEAREST);
//	Texture* bobaTexDisplay = renderSystem->CreateTexture(NULL);
//	ExternFileManager::ReadTextureFile("Fett_display_D.tga", bobaTexDisplay, Texture::NEAREST);
//
//	Model* bobaMesh;
//	ExternFileManager::ReadModelFile("bobaFett.dae", renderSystem, &bobaMesh, false, true);
//
//	Array<const Material*>& materialsBoba = bobaMesh->GetMaterials();
//	Material mat1Boba = { 0xffffffff, bobaTexJet };
//	Material mat2Boba = { 0xffffffff, bobaTexDisplay };
//	Material mat3Boba = { 0xffffffff, bobaTexHelmet };
//	Material mat4Boba = { 0xffffffff, bobaTexJet };
//	Material mat5Boba = { 0xffffffff, bobaTexBody };
//
//	materialsBoba[0] = &mat1Boba;
//	materialsBoba[1] = &mat2Boba;
//	materialsBoba[2] = &mat3Boba;
//	materialsBoba[3] = &mat4Boba;
//	materialsBoba[4] = &mat5Boba;
//
//	Entity boba(Vector3f(0.0f, 0.0f, -5.0f), Vector3f(180.0f, 0.0f, 0.0f), Vector3f(1.0f, 1.0f, 1.0f), bobaMesh);
//	boba.GetAnimations().push_back({ 0u, 0.0 });
//
//	float color[4] = { 0.2f, 0.5f, 0.5f, 1.0f };
//
//	Camera camera(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 0.0f));
//
//	while (!win->ShouldClose()) {
//		if (!win->HasMessage()) {
//
//			renderSystem->BeginRendering(color);
//
//			//renderer->Submit(&trooper1);
//			//renderer->Submit(&trooper2);
//			renderer->Submit(&boba);
//			renderer->Flush(camera.GetViewMatrix(),camera.GetPosition());
//
//			renderSystem->EndRendering();
//			boba.GetAnimations()[0].time += 1.0 / 60.0;
//
//			if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_LEFT)) {
//				camera.GetRotation().y += 1.0f;
//			}
//			if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_RIGHT)) {
//				camera.GetRotation().y -= 1.0f;
//			}
//			if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_UP)) {
//				camera.GetRotation().x += 1.0f;
//			}
//			if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_DOWN)) {
//				camera.GetRotation().x -= 1.0f;
//			}
//
//			
//
//			Vector3f look = Math::GetLookingDirection2D(camera.GetRotation());
//			//std::cout << std::endl << look;
//			Vector3f orthLook = Matrix4f::Rotate(90.0f, Vector3f(0.0f, 1.0f, 0.0f)) * look;
//
//			bool forward = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_W);
//			bool backward = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_S);
//			bool left = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_A);
//			bool right = Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_D);
//
//			float speedFW = 0.1f;
//			float speedSW = 0.1f;
//
//			if(forward && !backward) {
//				camera.GetPosition() += speedFW * look;
//			} else if(!forward && backward) {
//				camera.GetPosition() += -speedFW * look;
//			}
//			if(left && !right) {
//				camera.GetPosition() += speedSW * orthLook;
//			} else if(!left && right) {
//				camera.GetPosition() += -speedSW * orthLook;
//			}
//			if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(KEY_SPACE)) {
//				camera.GetPosition().y += 0.1f;
//			}
//			if (Inputsystem::GetInstance()->CheckIfKeyIsPressed(0x10)) {
//				camera.GetPosition().y -= 0.1f;
//			}
//
//			
//		}
//	};
//
//	renderSystem->Shutdown();
//}
//
//void MatrixTester(HINSTANCE hInstance){
//	Window::StartConsole();
//
//
//
//	FileManager::Initialize("res/", "../FM3D-Engine/", "fm3d");
//	ExternFileManager::Initialize();
//
//	Window* win = Window::SetInstance(Window::Create(Platform::WINDOWS, hInstance));
//
//	win->Start(1280, 720, L"JOOONGE");
//
//	CompCoords::Initialize(1280, 720);
//	Vector2f v1(660, 360); 
//	std::cout << v1 << std::endl;
//	std::cout << CompCoords::PixelToScreenSpace(v1) << std::endl;
//	std::cout << "####################################" << std::endl;
//	std::cout << "----------------------------------" << std::endl <<
//		Vector2f(Window::GetInstance()->GetWidth() / 2.0f, Window::GetInstance()->GetHeight() / 2.0f) << std::endl
//		<< CompCoords::PixelToScreenSpace(Vector2f(Window::GetInstance()->GetWidth() / 2.0f, 0.0f)) << std::endl
//		<< "----------------------------------" << std::endl;
//	while(1){
//		
//	}
//}
//
