#include<iostream>
#include<iomanip>
#include<stack>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
using namespace std;

//Danh sách các hàm hỗ trợ
void textcolor(int x);//hàm tô màu
void gotoxy(int x, int y);// Hàm dịch chuyển con trỏ đến tọa độ x, y.
void resizeConsole(int width, int height);
void DrawCaRo(int offsetX, int offsetY);
char kiemtra_hangdoc(char a[3][3], int vitridong, int vitricot);
char kiemtra_hangngang(char a[3][3], int vitridong, int vitricot);
char kiemtra_cheochinh(char a[3][3], int vitridong, int vitricot);
char kiemtra_cheophu(char a[3][3], int chisodong, int chisocot);


//Struct lưu trữ tọa độ dòng, tọa độ cột
struct ToaDo
{
	int toado_dong, toado_cot;
};

class Board
{
	char a[3][3];//chứa tọa độ các quân cờ đã đánh

public:
	Board();
	char geta(int i, int j);// Getter/
	void seta(int i, int j, char value); // Setter
	bool XuatQuanCo(int toado_dong, int toado_cot, char quanco, int chedo);//Kiểm tra chế độ chơi để tiến hành xuất cho phù hợp
	bool kiemtra_win(int vitridong, int vitricot);//Kiểm tra xem các đường đi qua quân cờ có thỏa mãn không để kết luận thắng
	bool kiemtra_hoa();//Kiểm tra xem ván cờ có hòa không
	void VeBanCo();//Vẽ bàn cờ

};

class Player : public Board
{
	char quanco;
public:

	Player(char _quanco);
	char getquanco();//lay quan co x hoac o
	void setquanco(char x); //dat quan co x hoac o
	virtual ToaDo LayToaDo() = 0; //NLấy tọa độ do người dùng nhập hoặc máy nhập

};

class HumanPlayer : public Player
{
public:
	HumanPlayer(char _quanco) :Player(_quanco) {};
	ToaDo LayToaDo();
};

class ComputerPlayer : public Player
{
public:
	ComputerPlayer(char _quanco) : Player(_quanco) {};

	ToaDo LayToaDo();
};

class Game
{
	Board b;
	Player* player1, * player2;
	char Continue; //dùng để nhận yêu cầu người dùng
public:
	Game() {};
	~Game() {};
	Game(Player*, Player*);
	char getContinue();
	void Start();
	void End();
};



int main()
{
	char ykien;
	do {
		Game game;
		game.Start();
		game.End();
		ykien = game.getContinue();
	} while (ykien == 'Y' || ykien == 'y');
	return 0;
}


//=========================================CLASS BOARD==========================================================//

Board::Board() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			a[i][j] = ' ';
		}
	}
}

// Getter/
char Board::geta(int i, int j) {
	if (i >= 0 && i < 3 && j >= 0 && j < 3) {
		return a[i][j];
	}
	return '\0';
}

// Setter
void Board::seta(int i, int j, char value) {
	if (i >= 0 && i < 3 && j >= 0 && j < 3) {
		a[i][j] = value;
	}
}
void Board::VeBanCo()
{
	cout << (setw((13) / 2 + 2));
	for (int i = 0; i < 3; i++)
	{
		cout << i << setw((11 + 2) / 2 + 11 / 2 + 1);
	}
	cout << "\n";
	cout << " " << (char)218;
	//first
	for (int c = 0; c < 11; c++)
	{

		cout << (char)196;
	}
	for (int j = 0; j < 3 - 1; j++)
	{
		cout << (char)194;
		for (int c = 0; c < 11; c++)
		{
			cout << (char)196;
		}
	}
	cout << (char)191;
	cout << endl;
	int index = 0;

	//last
	for (int sd = 0; sd < 3; sd++)
	{
		for (int d = 0; d < 5; d++)
		{
			if (d == 2) cout << index;
			else cout << " ";
			cout << (char)179;
			for (int sc = 0; sc < 3; sc++)
			{
				for (int c = 0; c < 11; c++)
				{

					cout << " ";

				}

				cout << (char)179;
			}
			cout << endl;
			if (sd == 3 - 1 && d == 5 - 1)
			{
				cout << " " << (char)192;
				for (int sc = 0; sc < 3; sc++)
				{
					for (int c = 0; c < 11; c++)
					{
						cout << (char)196;
					}
					if (sc == 3 - 1)
					{
						cout << (char)217;
						break;
					}
					cout << (char)193;
				}
				break;
			}
			else
			{
				if (d == 5 - 1)
				{
					cout << " ";
					cout << (char)195;
					for (int sc = 0; sc < 3; sc++)
					{
						for (int c = 0; c < 11; c++)
						{
							cout << (char)196;
						}
						if (sc == 3 - 1)
						{
							cout << (char)180 << endl;
							break;
						}
						cout << (char)197;
					}
				}
			}
		}
		index++;
	}

}
bool Board::kiemtra_win(int vitridong, int vitricot)//kiêm tra xem có thắng chưa
{
	char wholeBoard[3][3];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			wholeBoard[i][j] = geta(i, j);
		}
	}
	if (kiemtra_hangngang(wholeBoard, vitridong, vitricot) != ' ' || kiemtra_hangdoc(wholeBoard, vitridong, vitricot) != ' ' || kiemtra_cheochinh(wholeBoard, vitridong, vitricot) != ' ' || kiemtra_cheophu(wholeBoard, vitridong, vitricot) != ' ')
	{
		return true;
	}
	return false;
}
bool Board::kiemtra_hoa()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (a[i][j] == ' ')
			{
				return false; // Nếu còn ô trống, không phải hòa
			}
		}
	}
	// Nếu tất cả các ô đã được đánh và không có người chơi nào thắng, đó là trạng thái hòa
	return true;
}

bool Board::XuatQuanCo(int toado_dong, int toado_cot, char quanco, int chedo)
{

	if (geta(toado_dong, toado_cot) == ' ')
	{
		seta(toado_dong, toado_cot, quanco);

		//Thực hiện nhảy đến tọa độ nhận được tiến hành đánh và thay đổi màu phù hợp cho quan cờ
		gotoxy(11 / 2 + 1 + 2 + toado_cot * (11 + 1), 5 / 2 + 1 + 2 + toado_dong * (5 + 1));
		quanco == 'O' ? textcolor(12) : textcolor(14); //O là màu đỏ - X là màu vàng
		cout << quanco;
		textcolor(7);

		//Thực hiện lấp những dòng chữ đã in ra để thực hiện in tiếp cho vòng lặp tiếp theo
		gotoxy(1, 3 + (5 + 1) * 3);
		for (int i = 3 + (5 + 1) * 3; i < 29; i++)
		{
			gotoxy(1, i); 
			cout << "                                                                                                   ";
		}

		return true;
	}
	else if (chedo != 2 && chedo != 3)
	{
		gotoxy(1, 5 + (5 + 1) * 3);

		cout << "Vi tri nay da duoc danh, xin hay danh vi tri khac, nhan space 2 lan de thuc hien lai";

		//Nhận tương tác phím 
		char c = _getch();
		if (c == 32)
		{
			gotoxy(1, 5 + (5 + 1) * 3);
			cout << "                                                                                                      ";
		}
		return false;
	}
	else
	{
		gotoxy(1, 5 + (5 + 1) * 3);

		cout << "Vi tri nay da duoc danh, xin hay danh vi tri khac, nhan space 2 lan de thuc hien lai";
		return false;
	}

}

//=========================================CLASS PLAYER==========================================================//
Player::Player(char _quanco) { quanco = _quanco; }
char Player::getquanco() { return quanco; }//lay quan co x hoac o
void Player::setquanco(char x) { quanco = x; }//dat quan co x hoa

//=========================================CLASS HumanPlayer==========================================================//
//Xuat thong bao va nhap toa do quan co
ToaDo HumanPlayer::LayToaDo()
{


	ToaDo kq;
	char tquanco = getquanco();

	gotoxy(1, 3 + (5 + 1) * 3);
	cout << "Luot di hien tai cua quan co: ";
	tquanco == 'O' ? textcolor(12) : textcolor(14); //O là màu đỏ - X là màu vàng
	cout << tquanco << endl;
	textcolor(7); //cho nó thành màu trắng lại


	do
	{
		cout << "Nhap vao toa do [dong][cot]: ";
		cin >> kq.toado_dong >> kq.toado_cot;

		if (kq.toado_cot < 0 || kq.toado_cot >= 3)
		{
			cout << "Toa do cot khong hop le, xin nhap lai" << endl;
		}
		if (kq.toado_dong < 0 || kq.toado_dong >= 3)
		{
			cout << "Toa do dong khong hop le, xin nhap lai" << endl;
		}

	} while (kq.toado_cot < 0 || kq.toado_cot >= 3 || kq.toado_dong < 0 || kq.toado_dong >= 3);
	for (int i = 3 + (5 + 1) * 3; i < 29; i++)
	{
		gotoxy(1, i);
		cout << "                                                                           ";
	}
	gotoxy(1, 3 + (5 + 1) * 3);
	return  kq;

}
//=========================================CLASS COMPUTERPLAYER==========================================================//
ToaDo ComputerPlayer::LayToaDo()
{
	//srand(time(NULL));
	ToaDo kq;
	char tquanco = getquanco();

	// In thông báo lượt đi của máy
	gotoxy(1, 3 + (5 + 1) * 3);
	cout << "Luot di hien tai cua quan co: ";
	tquanco == 'O' ? textcolor(12) : textcolor(14); //O là màu đỏ - X là màu vàng
	cout << tquanco << endl;
	textcolor(7); //cho nó thành màu trắng lại

	// Chọn một ô trống ngẫu nhiên trên bảng
	do
	{
		kq.toado_dong = rand() % 3;
		kq.toado_cot = rand() % 3;

	} while (geta(kq.toado_dong, kq.toado_cot) != ' ');

	// Xóa thông báo trước đó
	for (int i = 3 + (5 + 1) * 3; i < 20; i++)
	{
		gotoxy(1, i);
		cout << "                                                                           ";
	}
	gotoxy(1, 3 + (5 + 1) * 3);

	return kq;
}



//=========================================CLASS Game==========================================================//
Game::Game(Player* player1, Player* player2) {
	this->player1 = player1;
	this->player2 = player2;
}
char Game::getContinue()
{
	return Continue;
}
void Game::Start()
{
	int chedo;
	char quanco_ditruoc, quanco_disau;

	//thực hiện xuất tiêu đề và bàng lựa chọn
	while (true)
	{
		textcolor(13);
		gotoxy(21, 4);
		cout << "DO AN GAME CARO - NHOM abc";
		textcolor(14);
		DrawCaRo(5, 25);
		gotoxy(10, 10);
		textcolor(7);
		cout << "HAY NHAP CAC LUA CHON";
		gotoxy(10, 11);
		cout << "1. Che Do Danh 2 Nguoi";
		gotoxy(10, 12);
		cout << "2. Che Do Danh Voi May";
		gotoxy(10, 13);
		cout << "3. Che Do May Danh Voi May";
		gotoxy(10, 14);
		cout << "Hay nhap lua chon cua ban : [1],[2],[3]: ";
		cin >> chedo;
		gotoxy(10, 16);
		cout << "                                                                      ";
		gotoxy(10, 15);
		cout << "Quan co muon di truoc la X hay O ?: "; cin >> quanco_ditruoc;

		if (chedo >= 1 && chedo <= 3 && (quanco_ditruoc == 'X' || quanco_ditruoc == 'O' || quanco_ditruoc == 'x' || quanco_ditruoc == 'o'))
		{
			system("cls");
			gotoxy(0, 0);
			break;
		}
		else
		{
			gotoxy(10, 16);
			textcolor(12);
			cout << "Xin kiem tra lai, du lieu ban nhap sai";
			gotoxy(10, 14);
			cout << "                                                                      ";
			gotoxy(10, 15);
			cout << "                                                                      ";
		}
	}

	if (quanco_ditruoc == 'x' || quanco_ditruoc == 'X')
	{
		quanco_ditruoc = 'X';
		quanco_disau = 'O';
	}
	else
	{
		quanco_ditruoc = 'O';
		quanco_disau = 'X';
	}

	//Thực hiện kiểm tra chế độ nhập vào để cấp kí tự đánh trước cho player
	if (chedo == 1)
	{
		player1 = new HumanPlayer(quanco_ditruoc);
		player2 = new HumanPlayer(quanco_disau);
	}
	if (chedo == 2)
	{
		player1 = new HumanPlayer(quanco_ditruoc);
		player2 = new ComputerPlayer(quanco_disau);
	}
	if (chedo == 3)
	{
		player1 = new ComputerPlayer(quanco_ditruoc);
		player2 = new ComputerPlayer(quanco_disau);
	}
	//thực hiện đánh cờ và xử lý
	b.VeBanCo();
	while (true)
	{
		srand(time(nullptr));
		if (chedo == 3) Sleep(1500);
		ToaDo td1, td2;
		do
		{
			td1 = player1->LayToaDo();
			if (b.XuatQuanCo(td1.toado_dong, td1.toado_cot, quanco_ditruoc, chedo) == true) break;
		} while (b.XuatQuanCo(td1.toado_dong, td1.toado_cot, quanco_ditruoc, chedo) == false);

		//Thực hiện xử lý thắng thua cho cả quân cờ đi trước
		if (b.kiemtra_win(td1.toado_dong, td1.toado_cot) == true)
		{
			gotoxy(1, 3 + (5 + 1) * 3);
			for (int i = 1; i <= 15; i++)
			{
				Sleep(200);
				textcolor(i);
				cout << " " << b.geta(td1.toado_dong, td1.toado_cot) << " chien thang";
				gotoxy(1, 3 + (5 + 1) * 3);
				cout << "                  ";
			}
			textcolor(7);
			break;
		}

		//kiểm tra có hòa không
		if (b.kiemtra_hoa() == true)
		{
			gotoxy(1, 3 + (5 + 1) * 3);
			for (int i = 1; i <= 15; i++)
			{
				Sleep(200);
				textcolor(i);
				cout << "Van co da hoa, khong co ai win ca :((((";
				gotoxy(1, 3 + (5 + 1) * 3);
				cout << "                  ";
			}
			break;
		}

		//Thực hiện xử lý thắng thua cho cả quân cờ đi sau
		if (chedo == 3) Sleep(1500);
		do
		{
			td2 = player2->LayToaDo();
			if (b.XuatQuanCo(td2.toado_dong, td2.toado_cot, quanco_disau, chedo) == true) break;
		} while (b.XuatQuanCo(td2.toado_dong, td2.toado_cot, quanco_disau, chedo) == false);
		if (b.kiemtra_win(td2.toado_dong, td2.toado_cot) == true)
		{
			gotoxy(1, 3 + (5 + 1) * 3);
			for (int i = 1; i <= 15; i++)
			{
				Sleep(200);
				textcolor(i);
				cout << " " << b.geta(td2.toado_dong, td2.toado_cot) << " chien thang";
				gotoxy(1, 3 + (5 + 1) * 3);
				cout << "                  ";
			}
			textcolor(7);
			break;
		}

		//kiểm tra có hòa không
		if (b.kiemtra_hoa() == true)
		{
			gotoxy(1, 3 + (5 + 1) * 3);
			for (int i = 1; i <= 15; i++)
			{
				Sleep(200);
				textcolor(i);
				cout << "Van co da hoa, khong co ai win ca :((((";
				gotoxy(1, 3 + (5 + 1) * 3);
				cout << "                  ";
			}
			break;
		}

	}

}
void Game::End()
{
	gotoxy(1, 4 + (5 + 1) * 3);
	cout << "Ban co muon choi lai khong? (Y/N): ";
	cin >> Continue;
	if (Continue == 'Y' || Continue == 'y') {
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				b.seta(i, j, ' ');
			}
		}
		system("cls");
	}
}

//=========================================CÁC HÀM KHÁC==========================================================//

void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

// Hàm dịch chuyển con trỏ đến tọa độ x, y.
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x - 1,y - 1 };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
void resizeConsole(int width, int height)
{


	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

//Hàm thực hiện vẽ INTRO
void DrawCaRo(int offsetX, int offsetY)
{
	int C[20] = { 32, 219, 220, 223, 222, 221 };
	int Caro[20][20] = {
		{ 0, 2, 2, 0, 0, 0, 2, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0 },
		{ 1, 0, 0, 1, 0, 4, 0, 5, 0, 1, 0, 1, 0, 1, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 1, 2, 1, 0, 1, 2, 5, 0, 1, 0, 0, 1 },
		{ 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1 },
		{ 0, 3, 3, 0, 0, 3, 0, 3, 0, 3, 0, 3, 0, 0, 3, 3, 0 }
	};
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 20; j++) {
			if (Caro[i][j]) {
				gotoxy(j + offsetY, i + offsetX);
				cout << char(C[Caro[i][j]]);
			}
		}
	}
}


//nơi thực hiện các hàm kiểm tra ngang, dọc, chéo chính,chéo phụ
char kiemtra_hangngang(char a[3][3], int vitridong, int vitricot)
{
	int dem = 1;
	//chạy từ bên trái sang
	for (int i = vitricot - 1; i >= 0; i--)
	{
		if (a[vitridong][i] == a[vitridong][vitricot])
		{
			dem++;
			if (dem == 3) return a[vitridong][vitricot];
		}
		else break;
	}

	for (int i = vitricot + 1; i < 3; i++)
	{
		if (a[vitridong][i] == a[vitridong][vitricot])
		{
			dem++;
			if (dem == 3) return a[vitridong][vitricot];
		}
		else break;
	}
	return ' ';
}
char kiemtra_hangdoc(char a[3][3], int vitridong, int vitricot)
{
	int dem = 1;
	for (int i = vitridong - 1; i >= 0; --i)
	{
		if (a[i][vitricot] == a[vitridong][vitricot])
		{
			dem++;

			if (dem == 3)
			{
				return a[vitridong][vitricot];
			}
		}
		else
		{
			break;
		}
	}

	for (int i = vitridong + 1; i < 3; ++i)
	{
		if (a[i][vitricot] == a[vitridong][vitricot])
		{
			dem++;

			if (dem == 3)
			{
				return a[vitridong][vitricot];
			}
		}
		else
		{
			break;
		}
	}
	return ' ';
}
char kiemtra_cheochinh(char a[3][3], int vitridong, int vitricot)
{
	int dem = 1; // tính luôn quân vừa đánh xuống

	// kiểm tra chéo chính trên: các phần tử dòng - cột luôn giảm 1 đơn vị và giảm đến khi nào 1 trong 2 thằng xuất hiện 0
	int i = vitridong - 1;
	int j = vitricot - 1;
	while (true)
	{
		if (i < 0 || j < 0)
		{
			break; // vị trí xét không hợp lệ
		}

		// nếu còn chạy xuống đây được thì có nghĩa vị trí i, j hợp lệ
		if (a[i][j] == a[vitridong][vitricot])
		{
			dem++;

			if (dem == 3)
			{
				return a[vitridong][vitricot];
			}
		}
		else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
		{
			break;
		}

		// xét qua lần lặp mới
		i--;
		j--;
	}

	//	kiểm tra chéo chính dưới: các phần tử dòng - cột đều tăng lên 1 đơn vị và tăng đến khi nào 1 trong 2 thằng bằng n - 1 thì dừng lại
	i = vitridong + 1;
	j = vitricot + 1;
	while (true)
	{
		if (i == 3 || j == 3)
		{
			break; // vị trí xét không hợp lệ
		}

		// nếu còn chạy xuống đây được thì có nghĩa vị trí i, j hợp lệ
		if (a[i][j] == a[vitridong][vitricot])
		{
			dem++;

			if (dem == 3)
			{
				return a[vitridong][vitricot];
			}
		}
		else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
		{
			break;
		}

		// xét qua lần lặp mới
		i++;
		j++;
	}
	return ' '; // chưa thắng
}
char kiemtra_cheophu(char a[3][3], int chisodong, int chisocot)
{
	int dem = 1;
	int i = chisodong - 1, j = chisocot + 1;
	while (true)
	{
		if (i < 0 || j >= 3) break;
		if (a[i][j] == a[chisodong][chisocot])
		{
			dem++;
			if (dem == 3) return a[chisodong][chisocot];
		}
		else break;
		i--; j++;
	}
	i = chisodong + 1; j = chisocot - 1;
	while (true)
	{
		if (i >= 3 || j < 0) break;
		if (a[i][j] == a[chisodong][chisocot])
		{
			dem++;
			if (dem == 3) return a[chisodong][chisocot];
		}
		else break;
		i++; j--;
	}
	return ' ';
}

