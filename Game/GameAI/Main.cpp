#include "header.h"

	//(dir -include *.cpp,*.h -recurse | select-string .).Count
	using namespace std;

	vector<Attackable*> Game::vTeamOne, Game::vTeamTwo;
	vector<Attacker*> Game::vAOne, Game::vATwo;
	Attackable *Game::cOne;
	Attackable *Game::cTwo;
	int Game::towerSelected = -1;
	int Game::pathSelected = 0;
	HWND hwnd;

	Point a, b, c;
	Point Game::path[3][3];

	bool firstTime = true;

	HBRUSH red = CreateSolidBrush(RGB(180, 0, 0 )  ) ;
	HBRUSH blue = CreateSolidBrush(RGB(0, 0, 180 )  ) ;
	HBRUSH black = CreateSolidBrush(RGB(140, 140, 140 )  ) ;

	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow) {
		static char szAppName[] = "Tower";
		MSG         msg;
		WNDCLASSEX  wndclass;

		wndclass.cbSize					= sizeof(wndclass);
		wndclass.style						= CS_HREDRAW | CS_VREDRAW;
		wndclass.lpfnWndProc			= WndProc;
		wndclass.cbClsExtra				= 0;
		wndclass.cbWndExtra			= 0;
		wndclass.hInstance				= hInstance;
		wndclass.hIcon						= LoadIcon(NULL, IDI_APPLICATION);
		wndclass.hIconSm					= LoadIcon(NULL, IDI_APPLICATION);
		wndclass.hCursor					= LoadCursor(NULL, IDC_ARROW);
		wndclass.hbrBackground		= (HBRUSH) GetStockObject(WHITE_BRUSH);
		wndclass.lpszClassName		= szAppName;
		wndclass.lpszMenuName		= NULL;

		RegisterClassEx(&wndclass);

		hwnd = CreateWindow(szAppName, szAppName,
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT, CW_USEDEFAULT,
				835, 555,
				NULL, NULL, hInstance, NULL);

		ShowWindow(hwnd, iCmdShow);
		UpdateWindow(hwnd);

		while ( GetMessage(&msg, NULL, 0, 0) ) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return msg.wParam;
	}
	
	DWORD WINAPI AI (LPVOID lp ) {
		int index = 0;
		std::vector<Attacker*>::iterator it;
		std::vector<Attacker*>::iterator end;
		RECT rect;

		while( 1 ) {
			for( index = 1; index < 3; index++ ) {
				it = Game::getAttackersBegin( index );
				end = Game::getAttackersEnd( index );
				for( ; it != end; ++it ) {
					(*it)->Update();
				}
			}

			if( Game::getCastle(2)->iHp <= 0 ) {
				break;
			}


			InvalidateRect( hwnd, NULL, true );
			UpdateWindow( hwnd );
			Sleep( TIME );
		}
		SetWindowText( hwnd, "Game over." );
		return 0;
	}

	void Setup( void ) {
	
		Castle cEnemy = Castle();
		cEnemy.pCurrPoint.x = 800,  cEnemy.pCurrPoint.y = 500;
		cEnemy.setTeam( 2 );

	
		Game::addCastle( new Castle( cEnemy ), 2 );
		/* Setting up the game field. 
		for(int i = 0; i < GAME_COL; i++ ) {
			for(int j = 0; j < GAME_ROW; j++ ) {
				field[i][j].id = -1;
				field[i][j].x = j * SQUARE_SIZE;
				field[i][j].y = i * SQUARE_SIZE;
			}
		}
		*/

		/* Setting up the 3 paths. Should be changed to parse from file. */
		a.x = 0, a.y = 0;
		b.x = 800, b.y = 0;
		c.x = 800, c.y = 500;

		Game::path[0][0] = a;
		Game::path[0][1] = b;
		Game::path[0][2] = c;

		b.x = 0, b.y = 500;

		Game::path[1][0] = a;
		Game::path[1][1] = b;
		Game::path[1][2] = c;

		b.x = 400, b.y = 240;

		Game::path[2][0] = a;
		Game::path[2][1] = b;
		Game::path[2][2] = c;

		/*Create a Thread to handle AI updates. */
		CreateThread( NULL, 0, AI, 0, 0, 0 );
	}

	LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
		PAINTSTRUCT		ps;
		HDC						hdc; 
		RECT					rect;
		int							index;
		vector<Attackable*>::iterator it;
		vector<Attackable*>::iterator end;
		static int x, y;

		switch ( iMsg ) {
			case WM_CREATE:
				Setup();
				return 0;

			case WM_PAINT:
				hdc = BeginPaint(hwnd, &ps);

				/* For Drawing the field.
				if( firstTime == true ) {
					firstTime = false;
					for(int i = 0; i < GAME_COL ; i++ ) {
						for(int j = 0; j < GAME_ROW; j++ ) {
					
							rect.left = i * 20 + 1;
							rect.top = j * 20 + 1;
							rect.bottom = rect.top + SQUARE_SIZE - 2;
							rect.right = rect.left + SQUARE_SIZE - 2;
							FillRect( hdc, &rect, CreateSolidBrush(RGB(0, 200, 0 )  ) );
						}
					}
				}
				//*/



				//* Drawing the lanes.
				rect.left = 0;
				rect.top = 0;
				rect.bottom = rect.top + SQUARE_SIZE;
				rect.right = 820;
				FillRect( hdc, &rect, CreateSolidBrush(RGB(140, 140, 140 )  ) );

				rect.left = 800;
				rect.top = 0;
				rect.bottom = 520;
				rect.right = 820;
				FillRect( hdc, &rect, CreateSolidBrush(RGB(140, 140, 140 )  ) );


				rect.left = 0;
				rect.top = 0;
				rect.bottom = 520;
				rect.right = 20;
				FillRect( hdc, &rect, CreateSolidBrush(RGB(140, 140, 140 )  ) );

				rect.left = 0;
				rect.top = 500;
				rect.bottom = 520;
				rect.right = 820;
				FillRect( hdc, &rect, CreateSolidBrush(RGB(140, 140, 140 )  ) );
				//*/
			
			
				for( index = 1; index < 3; index++ ) {
					it = Game::getEnemiesBegin( index );
					end = Game::getEnemiesEnd( index );
					for( ; it != end; ++it ) {
						rect.left = (*it)->pCurrPoint.x;
						rect.top = (*it)->pCurrPoint.y;
						rect.bottom = rect.top + SQUARE_SIZE;
						rect.right = rect.left + SQUARE_SIZE;

						FillRect( hdc, &rect, index == 1 ? red : blue );	
					}
				}			
				EndPaint(hwnd, &ps);
				return 0;

			case WM_CHAR:
				switch( wParam ) {
					case 'c': Game::SpawnCreep(); break;
					case '1' :
					case '2':
					case '3':
						Game::SelectTower( wParam - 48 ); 
						break;
					case 27:
						Game::SelectTower( -1 );
						break;
				}
				return 0;

			case WM_LBUTTONDOWN:
				if( Game::towerSelected != -1 )
					Game::BuildTower( 2, Game::towerSelected, LOWORD(lParam), HIWORD(lParam) );
				return 0;

			case WM_MOUSEMOVE:
				if( Game::towerSelected != -1  ) {
					hdc = GetDC(hwnd);
					rect.left = x; /* X */
					rect.top = y; /* Y */
					rect.bottom = rect.top + SQUARE_SIZE;
					rect.right = rect.left + SQUARE_SIZE;


					FillRect( hdc, &rect, black );	


					rect.left = x = LOWORD(lParam) - SQUARE_SIZE / 2; /* X */
					rect.top = y = HIWORD(lParam) - SQUARE_SIZE / 2; /* Y */
					rect.bottom = rect.top + SQUARE_SIZE;
					rect.right = rect.left + SQUARE_SIZE;
					FillRect( hdc, &rect, blue );	
					ReleaseDC(hwnd, hdc);
				}
				return 0;


			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
		}


		/*  Send any messages we don't handle to default window procedure  */
    
		return DefWindowProc(hwnd, iMsg, wParam, lParam);
	}

