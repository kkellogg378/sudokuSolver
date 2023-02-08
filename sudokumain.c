#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>
#pragma comment(lib,"User32.lib")

#define ID_EDIT 1
#define ID_BUTTON 2
#define maxtextlength1 2	//needs to be a constant int, so its defined here
#define maxtextlength2 1000

const char g_szClassName[] = "myWindowClass";			//define windows class?

int sudoku(int grid[9][9], int *p);
int isValid (int grid[9][9], int i, int j);
int t2i(const char *s);



// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND static hwndButton,hwndStatic;
	//HWND static e00,e01,e02,e03,e04,e05,e06,e07,e08;
	//HWND static e10,e11,e12,e13,e14,e15,e16,e17,e18;
	HWND static e[9][9];
    switch(msg)
    {
		case WM_CREATE: //activates when window is created
		{
			for (int i = 0; i < 9; i++) {			//initializing the 9x9
				for (int j = 0; j < 9; j++)
					e[i][j] = CreateWindow(TEXT("edit"), NULL,	WS_CHILD | WS_VISIBLE | WS_BORDER, (20 + 18 * i), (20 + 22 * j), 12, 20, hwnd, (HMENU) ID_EDIT, NULL, NULL);
			}
			
			hwndButton = CreateWindow(TEXT("button"), TEXT("Solve!"), WS_VISIBLE |  WS_CHILD, 180, 190, 50, 30, hwnd, (HMENU) ID_BUTTON, NULL, NULL);
			hwndStatic = CreateWindow(TEXT("static"), NULL, WS_BORDER | WS_CHILD | WS_VISIBLE | SS_LEFT, 250, 20, 125, 180, hwnd, (HMENU) 1, NULL, NULL);
		}
		break;
		
		case WM_COMMAND:		//when an item is interacted with
		{
			if (HIWORD(wParam) == BN_CLICKED) {			//when button is clicked
				
				
				int grid[9][9];
				
				TCHAR input_num[maxtextlength1] = TEXT("");
				for (int i = 0; i < 9; i++) {
					for (int j = 0; j < 9; j++) {
						GetWindowText(e[i][j], input_num, maxtextlength1);
						grid[j][i] = t2i(input_num);		//returns 0 if no integer found
					}
				}
				
				int nosolution = 0;
				sudoku(grid, &nosolution);
				
				if (nosolution == 1) {
					char szFileName[MAX_PATH];
					HINSTANCE hInstance = GetModuleHandle(NULL);

					GetModuleFileName(hInstance, szFileName, MAX_PATH);
					MessageBox(hwnd, "     No solution!     ", "Status:", MB_OK | MB_ICONINFORMATION);
				}
				else {
					TCHAR answer1[maxtextlength2];
					_stprintf( answer1, TEXT("%d %d %d   %d %d %d   %d %d %d\n%d %d %d   %d %d %d   %d %d %d\n%d %d %d   %d %d %d   %d %d %d\n\n%d %d %d   %d %d %d   %d %d %d\n%d %d %d   %d %d %d   %d %d %d\n%d %d %d   %d %d %d   %d %d %d\n\n%d %d %d   %d %d %d   %d %d %d\n%d %d %d   %d %d %d   %d %d %d\n%d %d %d   %d %d %d   %d %d %d\n\n"), 
						grid[0][0], grid[0][1], grid[0][2], grid[0][3], grid[0][4], grid[0][5], grid[0][6], grid[0][7], grid[0][8],
						grid[1][0], grid[1][1], grid[1][2], grid[1][3], grid[1][4], grid[1][5], grid[1][6], grid[1][7], grid[1][8],
						grid[2][0], grid[2][1], grid[2][2], grid[2][3], grid[2][4], grid[2][5], grid[2][6], grid[2][7], grid[2][8],
						grid[3][0], grid[3][1], grid[3][2], grid[3][3], grid[3][4], grid[3][5], grid[3][6], grid[3][7], grid[3][8],
						grid[4][0], grid[4][1], grid[4][2], grid[4][3], grid[4][4], grid[4][5], grid[4][6], grid[4][7], grid[4][8],
						grid[5][0], grid[5][1], grid[5][2], grid[5][3], grid[5][4], grid[5][5], grid[5][6], grid[5][7], grid[5][8],
						grid[6][0], grid[6][1], grid[6][2], grid[6][3], grid[6][4], grid[6][5], grid[6][6], grid[6][7], grid[6][8],
						grid[7][0], grid[7][1], grid[7][2], grid[7][3], grid[7][4], grid[7][5], grid[7][6], grid[7][7], grid[7][8],
						grid[8][0], grid[8][1], grid[8][2], grid[8][3], grid[8][4], grid[8][5], grid[8][6], grid[8][7], grid[8][8]);
					SetWindowText(hwndStatic, answer1);
					
					
					MessageBox(hwnd, "     Success!     ", "Status:", MB_OK | MB_ICONINFORMATION);
					
				}
				//TCHAR textvalue[maxtextlength1] = TEXT("");			//creates 'textvalue'
				//GetWindowText(e[0][0], textvalue, maxtextlength1);	//saves value of hwndEdit to 'textvalue'
				
				
				
				//TCHAR test[maxtextlength2] = TEXT("Turtle");			//predefined string
				//SetWindowText(hwndStatic, test);					//assigns string to the static text box
			}
		}
		break;
		
        //case WM_LBUTTONDOWN:				//activates when the window is clicked on
        //{
            //char szFileName[MAX_PATH];
            //HINSTANCE hInstance = GetModuleHandle(NULL);

            //GetModuleFileName(hInstance, szFileName, MAX_PATH);
            //MessageBox(hwnd, "     Success!     ", "Status:", MB_OK | MB_ICONINFORMATION);
        //}
        //break;
		
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
	BOOL bRet;
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    //Step 1: Registering the Window Class					//windows class stores information about a type of window
    wc.cbSize        = sizeof(WNDCLASSEX);					//size of structure
    wc.style         = 0;									//class style, usually set to 0
    wc.lpfnWndProc   = WndProc;								//pointer to window procedure for the window class
    wc.cbClsExtra    = 0;									//amount of extra data allocated for this class in memory, usually set to 0
    wc.cbWndExtra    = 0;									//amount of extra data allocated per window of this type, usually set to 0
    wc.hInstance     = hInstance;							//handle to application instance
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);		//large icon shown when user presses Alt+Tab (usually 32x32)
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);			//cursor that will be displayed over the window
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);			//background brush to set the color of the window
    wc.lpszMenuName  = NULL;								//name of menu resource to use for the windows in the class 
    wc.lpszClassName = g_szClassName;						//name to identify the class with
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);		//small icon to show in taskbar and top left of window (usually 16x16)

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,											//extended windows style
        g_szClassName,												//class name to tell the system what kind of window to create
        "kkellogg378's Sudoku Solver v1.0.0",									// define window title
        WS_OVERLAPPEDWINDOW,										// Windows Style parameter
        CW_USEDEFAULT, CW_USEDEFAULT, 425, 300,						// define window location/resolution
        NULL, NULL, hInstance, NULL);								//Parent Window handle, menu handle, application instance handle, pointer to window creation data

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);										//
    UpdateWindow(hwnd);												//

    // Step 3: The Message Loop
    /*while(GetMessage(&Msg, NULL, 0, 0) > 0)			//old message loop
	{
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }*/
	
	while( (bRet = GetMessage( &Msg, NULL, 0, 0 )) != 0)
    { 
        if (bRet == -1)
        {
            // handle the error and possibly exit
        }
        else
        {
            TranslateMessage(&Msg); 
            DispatchMessage(&Msg); 
        }
    } 
	
    return Msg.wParam;
}


int sudoku(int grid[9][9], int *p)
{
	int isLocked[9][9];									//Function to generate a reference matrix that has a value of 0 if the slot is unlocked and a value of 1 if it is
	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++) {
			if (grid[i][j] == 0)
				isLocked[i][j] = 0;
			else
				isLocked[i][j] = 1;
		}
	}
	
	int i = 0, j = 0, no_solution = 0;
	while (i < 9) {
		if (j == 9) {									//check to make sure we stay in possible spots
			j = 0;
			i = i + 1;
		}
		while (isLocked[i][j] == 1) {					//moves the current location to an unlocked slot
			j = j + 1;
			if (j == 9) {
				j = 0;
				i = i + 1;
			}
			if (i == 9) {
				//no_solution = 1;
				break;
			}
		}
		if (i == 9) {
			//no_solution = 1;
			break;
		}
		grid[i][j] = grid[i][j] + 1;					//increases value of the current slot by 1
		if (grid[i][j] > 9) {							//if no possible value
			grid[i][j] = 0;								//resets value to 0
			j = j - 1;									//moves back a slot
			if (j < 0) {								//moves up a row if needed
				j = 8;
				i = i - 1;
				if (i < 0)								//determines there is no solution if the first unlocked slot has no possible value
					no_solution = 1;
			}
			if (no_solution == 1)//addednew
				break;
			while (isLocked[i][j] == 1) {				//moves the current location to the previous unlocked slot
				j = j - 1;
				if (j < 0) {							//repeat of previous statements if the selected slot is a locked one
					j = 8;
					i = i - 1;
					if (i < 0) {
						no_solution = 1;
						break;
					}
				}
			}
			if (no_solution == 1)						//checks if its been determined that there is no solution
				break;
			else
				continue;								//resets to beginning of loop
		}
		
		int valid = isValid(grid, i, j);
		
		if (no_solution == 1)//addednew
			break;
		else if (valid == 1) {						//if the new value for the location is a possible one, checks that value to see if it is valid
			j = j + 1;									//moves location to next slot if the number is valid
			if (j == 9) {
				j = 0;
				i = i + 1;
			}
			if (i == 9) {
				//no_solution = 1;
				break;
			}
			continue;
		}
		else
			continue;									//does not move the location because the number is not valid
	}
	
	if (no_solution != 0) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {//attempt to reset the grid if there is no solution
				grid[i][j] = 0;
			}
		}
	}
	
	*p = no_solution;
	
	return 0;
}

int isValid (int grid[9][9], int i, int j) {		//returns 1 if valid and 0 if not (Most likely fully functional)
	
	int row = 0, column = 0, box = 0;
	if (j > 8 || i > 8 || j < 0 || i < 0)
		return 0;
	else {
		if (i == 0){
			if (grid[i][j] == grid[1][j] || grid[i][j] == grid[2][j] || grid[i][j] == grid[3][j] || grid[i][j] == grid[4][j] || grid[i][j] == grid[5][j] || grid[i][j] == grid[6][j] || grid[i][j] == grid[7][j] || grid[i][j] == grid[8][j])
				column = column + 1;
			else;
		}
		else if (i == 1) {
			if (grid[i][j] == grid[0][j] || grid[i][j] == grid[2][j] || grid[i][j] == grid[3][j] || grid[i][j] == grid[4][j] || grid[i][j] == grid[5][j] || grid[i][j] == grid[6][j] || grid[i][j] == grid[7][j] || grid[i][j] == grid[8][j])
				column = column + 1;
			else;
		}
		else if (i == 2) {
			if (grid[i][j] == grid[0][j] || grid[i][j] == grid[1][j] || grid[i][j] == grid[3][j] || grid[i][j] == grid[4][j] || grid[i][j] == grid[5][j] || grid[i][j] == grid[6][j] || grid[i][j] == grid[7][j] || grid[i][j] == grid[8][j])
				column = column + 1;
			else;
		}
		else if (i == 3) {
			if (grid[i][j] == grid[0][j] || grid[i][j] == grid[1][j] || grid[i][j] == grid[2][j] || grid[i][j] == grid[4][j] || grid[i][j] == grid[5][j] || grid[i][j] == grid[6][j] || grid[i][j] == grid[7][j] || grid[i][j] == grid[8][j])
				column = column + 1;
			else;
		}
		else if (i == 4) {
			if (grid[i][j] == grid[0][j] || grid[i][j] == grid[1][j] || grid[i][j] == grid[2][j] || grid[i][j] == grid[3][j] || grid[i][j] == grid[5][j] || grid[i][j] == grid[6][j] || grid[i][j] == grid[7][j] || grid[i][j] == grid[8][j])
				column = column + 1;
			else;
		}
		else if (i == 5) {
			if (grid[i][j] == grid[0][j] || grid[i][j] == grid[1][j] || grid[i][j] == grid[2][j] || grid[i][j] == grid[3][j] || grid[i][j] == grid[4][j] || grid[i][j] == grid[6][j] || grid[i][j] == grid[7][j] || grid[i][j] == grid[8][j])
				column = column + 1;
			else;
		}
		else if (i == 6) {
			if (grid[i][j] == grid[0][j] || grid[i][j] == grid[1][j] || grid[i][j] == grid[2][j] || grid[i][j] == grid[3][j] || grid[i][j] == grid[4][j] || grid[i][j] == grid[5][j] || grid[i][j] == grid[7][j] || grid[i][j] == grid[8][j])
				column = column + 1;
			else;
		}
		else if (i == 7) {
			if (grid[i][j] == grid[0][j] || grid[i][j] == grid[1][j] || grid[i][j] == grid[2][j] || grid[i][j] == grid[3][j] || grid[i][j] == grid[4][j] || grid[i][j] == grid[5][j] || grid[i][j] == grid[6][j] || grid[i][j] == grid[8][j])
				column = column + 1;
			else;
		}
		else if (i == 8) {
			if (grid[i][j] == grid[0][j] || grid[i][j] == grid[1][j] || grid[i][j] == grid[2][j] || grid[i][j] == grid[3][j] || grid[i][j] == grid[4][j] || grid[i][j] == grid[5][j] || grid[i][j] == grid[6][j] || grid[i][j] == grid[7][j])
				column = column + 1;
			else;
		}
		else;
		
		if (j == 0) {
			if (grid[i][j] == grid[i][1] || grid[i][j] == grid[i][2] || grid[i][j] == grid[i][3] || grid[i][j] == grid[i][4] || grid[i][j] == grid[i][5] || grid[i][j] == grid[i][6] || grid[i][j] == grid[i][7] || grid[i][j] == grid[i][8])
				row = row + 1;
			else;
		}
		else if (j == 1) {
			if (grid[i][j] == grid[i][0] || grid[i][j] == grid[i][2] || grid[i][j] == grid[i][3] || grid[i][j] == grid[i][4] || grid[i][j] == grid[i][5] || grid[i][j] == grid[i][6] || grid[i][j] == grid[i][7] || grid[i][j] == grid[i][8])
				row = row + 1;
			else;
		}
		else if (j == 2) {
			if (grid[i][j] == grid[i][0] || grid[i][j] == grid[i][1] || grid[i][j] == grid[i][3] || grid[i][j] == grid[i][4] || grid[i][j] == grid[i][5] || grid[i][j] == grid[i][6] || grid[i][j] == grid[i][7] || grid[i][j] == grid[i][8])
				row = row + 1;
			else;
		}
		else if (j == 3) {
			if (grid[i][j] == grid[i][0] || grid[i][j] == grid[i][1] || grid[i][j] == grid[i][2] || grid[i][j] == grid[i][4] || grid[i][j] == grid[i][5] || grid[i][j] == grid[i][6] || grid[i][j] == grid[i][7] || grid[i][j] == grid[i][8])
				row = row + 1;
			else;
		}
		else if (j == 4) {
			if (grid[i][j] == grid[i][0] || grid[i][j] == grid[i][1] || grid[i][j] == grid[i][2] || grid[i][j] == grid[i][3] || grid[i][j] == grid[i][5] || grid[i][j] == grid[i][6] || grid[i][j] == grid[i][7] || grid[i][j] == grid[i][8])
				row = row + 1;
			else;
		}
		else if (j == 5) {
			if (grid[i][j] == grid[i][0] || grid[i][j] == grid[i][1] || grid[i][j] == grid[i][2] || grid[i][j] == grid[i][3] || grid[i][j] == grid[i][4] || grid[i][j] == grid[i][6] || grid[i][j] == grid[i][7] || grid[i][j] == grid[i][8])
				row = row + 1;
			else;
		}
		else if (j == 6) {
			if (grid[i][j] == grid[i][0] || grid[i][j] == grid[i][1] || grid[i][j] == grid[i][2] || grid[i][j] == grid[i][3] || grid[i][j] == grid[i][4] || grid[i][j] == grid[i][5] || grid[i][j] == grid[i][7] || grid[i][j] == grid[i][8])
				row = row + 1;
			else;
		}
		else if (j == 7) {
			if (grid[i][j] == grid[i][0] || grid[i][j] == grid[i][1] || grid[i][j] == grid[i][2] || grid[i][j] == grid[i][3] || grid[i][j] == grid[i][4] || grid[i][j] == grid[i][5] || grid[i][j] == grid[i][6] || grid[i][j] == grid[i][8])
				row = row + 1;
			else;
		}
		else if (j == 8) {
			if (grid[i][j] == grid[i][0] || grid[i][j] == grid[i][1] || grid[i][j] == grid[i][2] || grid[i][j] == grid[i][3] || grid[i][j] == grid[i][4] || grid[i][j] == grid[i][5] || grid[i][j] == grid[i][6] || grid[i][j] == grid[i][7])
				row = row + 1;
			else;
		}
		else;
		
		int addi = 0, addj = 0;
		
		if (i <= 2) {			// Program used to determine how to tweak checking function
			addi = 0;
			if (j <= 2)			// BOX 1
				addj = 0;
			else if (j <= 5)	// BOX 2
				addj = 3;
			else if (j <= 8)	// BOX 3
				addj = 6;
			else;
		}
		else if (i <= 5) {
			addi = 3;
			if (j <= 2)			// BOX 4
				addj = 0;
			else if (j <= 5)	// BOX 5
				addj = 3;
			else if (j <= 8)	// BOX 6
				addj = 6;
			else;
		}
		else if (i <= 8) {
			addi = 6;
			if (j <= 2)			// BOX 7
				addj = 0;
			else if (j <= 5)	// BOX 8
				addj = 3;
			else if (j <= 8)	// BOX 9
				addj = 6;
			else;
		}
		else;
		
		if (i == (addi + 0) && j == (addj + 0)) {
			if (grid[i][j] == grid[(addi + 0)][(addj + 1)] || grid[i][j] == grid[(addi + 0)][(addj + 2)] || grid[i][j] == grid[(addi + 1)][(addj + 0)] || grid[i][j] == grid[(addi + 1)][(addj + 1)] || grid[i][j] == grid[(addi + 1)][(addj + 2)] || grid[i][j] == grid[(addi + 2)][(addj + 0)] || grid[i][j] == grid[(addi + 2)][(addj + 1)] || grid[i][j] == grid[(addi + 2)][(addj + 2)]) 
				box = box + 1;
			else;
		}
		else if (i == (addi + 0) && j == (addj + 1)) {
			if (grid[i][j] == grid[(addi + 0)][(addj + 0)] || grid[i][j] == grid[(addi + 0)][(addj + 2)] || grid[i][j] == grid[(addi + 1)][(addj + 0)] || grid[i][j] == grid[(addi + 1)][(addj + 1)] || grid[i][j] == grid[(addi + 1)][(addj + 2)] || grid[i][j] == grid[(addi + 2)][(addj + 0)] || grid[i][j] == grid[(addi + 2)][(addj + 1)] || grid[i][j] == grid[(addi + 2)][(addj + 2)]) 
				box = box + 1;
			else;
		}
		else if (i == (addi + 0) && j == (addj + 2)) {
			if (grid[i][j] == grid[(addi + 0)][(addj + 0)] || grid[i][j] == grid[(addi + 0)][(addj + 1)] || grid[i][j] == grid[(addi + 1)][(addj + 0)] || grid[i][j] == grid[(addi + 1)][(addj + 1)] || grid[i][j] == grid[(addi + 1)][(addj + 2)] || grid[i][j] == grid[(addi + 2)][(addj + 0)] || grid[i][j] == grid[(addi + 2)][(addj + 1)] || grid[i][j] == grid[(addi + 2)][(addj + 2)]) 
				box = box + 1;
			else;
		}
		else if (i == (addi + 1) && j == (addj + 0)) {
			if (grid[i][j] == grid[(addi + 0)][(addj + 0)] || grid[i][j] == grid[(addi + 0)][(addj + 1)] || grid[i][j] == grid[(addi + 0)][(addj + 2)] || grid[i][j] == grid[(addi + 1)][(addj + 1)] || grid[i][j] == grid[(addi + 1)][(addj + 2)] || grid[i][j] == grid[(addi + 2)][(addj + 0)] || grid[i][j] == grid[(addi + 2)][(addj + 1)] || grid[i][j] == grid[(addi + 2)][(addj + 2)]) 
				box = box + 1;
			else;
		}
		else if (i == (addi + 1) && j == (addj + 1)) {
			if (grid[i][j] == grid[(addi + 0)][(addj + 0)] || grid[i][j] == grid[(addi + 0)][(addj + 1)] || grid[i][j] == grid[(addi + 0)][(addj + 2)] || grid[i][j] == grid[(addi + 1)][(addj + 0)] || grid[i][j] == grid[(addi + 1)][(addj + 2)] || grid[i][j] == grid[(addi + 2)][(addj + 0)] || grid[i][j] == grid[(addi + 2)][(addj + 1)] || grid[i][j] == grid[(addi + 2)][(addj + 2)]) 
				box = box + 1;
			else;
		}
		else if (i == (addi + 1) && j == (addj + 2)) {
			if (grid[i][j] == grid[(addi + 0)][(addj + 0)] || grid[i][j] == grid[(addi + 0)][(addj + 1)] || grid[i][j] == grid[(addi + 0)][(addj + 2)] || grid[i][j] == grid[(addi + 1)][(addj + 0)] || grid[i][j] == grid[(addi + 1)][(addj + 1)] || grid[i][j] == grid[(addi + 2)][(addj + 0)] || grid[i][j] == grid[(addi + 2)][(addj + 1)] || grid[i][j] == grid[(addi + 2)][(addj + 2)]) 
				box = box + 1;
			else;
		}
		else if (i == (addi + 2) && j == (addj + 0)) {
			if (grid[i][j] == grid[(addi + 0)][(addj + 0)] || grid[i][j] == grid[(addi + 0)][(addj + 1)] || grid[i][j] == grid[(addi + 0)][(addj + 2)] || grid[i][j] == grid[(addi + 1)][(addj + 0)] || grid[i][j] == grid[(addi + 1)][(addj + 1)] || grid[i][j] == grid[(addi + 1)][(addj + 2)] || grid[i][j] == grid[(addi + 2)][(addj + 1)] || grid[i][j] == grid[(addi + 2)][(addj + 2)]) 
				box = box + 1;
			else;
		}
		else if (i == (addi + 2) && j == (addj + 1)) {
			if (grid[i][j] == grid[(addi + 0)][(addj + 0)] || grid[i][j] == grid[(addi + 0)][(addj + 1)] || grid[i][j] == grid[(addi + 0)][(addj + 2)] || grid[i][j] == grid[(addi + 1)][(addj + 0)] || grid[i][j] == grid[(addi + 1)][(addj + 1)] || grid[i][j] == grid[(addi + 1)][(addj + 2)] || grid[i][j] == grid[(addi + 2)][(addj + 0)] || grid[i][j] == grid[(addi + 2)][(addj + 2)]) 
				box = box + 1;
			else;
		}
		else if (i == (addi + 2) && j == (addj + 2)) {
			if (grid[i][j] == grid[(addi + 0)][(addj + 0)] || grid[i][j] == grid[(addi + 0)][(addj + 1)] || grid[i][j] == grid[(addi + 0)][(addj + 2)] || grid[i][j] == grid[(addi + 1)][(addj + 0)] || grid[i][j] == grid[(addi + 1)][(addj + 1)] || grid[i][j] == grid[(addi + 1)][(addj + 2)] || grid[i][j] == grid[(addi + 2)][(addj + 0)] || grid[i][j] == grid[(addi + 2)][(addj + 1)]) 
				box = box + 1;
			else;
		}
		else;
		
		if (row == 0 && column == 0 && box == 0)
			return 1;
		else
			return 0;
	}
}

int t2i(const char *s) {
	int num=0;
	while(*s) {
		num = ((*s) - '0') + num * 10;
		s++;
	}
	return num;
}
