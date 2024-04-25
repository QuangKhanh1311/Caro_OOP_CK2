#include<iostream>
#include<fstream>
#define MAX 20
using namespace std;
void xuatbanco(int n, char a[MAX][MAX])
{
      for(int i = 0; i < n; i ++)
    {
        for(int j = 0; j < n;  j ++)
        {
            cout << a[i][j];
            if(j == n-1) cout << endl;
        }
    }
}

void kiemtra(char kq, ifstream &FileIn)
{
    if(kq != '.')
	{
		if(kq == 'x')
		{
			cout <<"Ti wins";
		}
		else
		{
			cout <<"Teo wins";
        }
        FileIn.close();
        exit(0);

    }

    
}

char kiemtra_hangngang(int  n, char a[MAX][MAX],int vitridong,int vitricot)
{
    int dem = 1;
    //chạy từ bên trái sang
    for(int i = vitricot -1; i >= 0; i --)
    {
        if(a[vitridong][i] == a[vitridong][vitricot])
        {
            dem ++;
            if(dem == 5) return a[vitridong][vitricot];
        }
        else break;
    }

    for(int i = vitricot+1; i < n; i ++)
    {
         if(a[vitridong][i] == a[vitridong][vitricot])
        {
            dem ++;
            if(dem == 5) return a[vitridong][vitricot];
        }
        else break;
    }
    return '.';
}

char kiemtra_hangdoc(int n,  char a[MAX][MAX], int vitridong, int vitricot)
{
   int dem = 1; 
	for(int i = vitridong - 1; i >= 0; --i)
	{
		if(a[i][vitricot] == a[vitridong][vitricot])
		{
			dem++;

			if(dem == 5)
			{
				return a[vitridong][vitricot];
			}
		}
		else 
		{
			break;
		}
	}

	for(int i = vitridong + 1; i < n; ++i)
	{
		if(a[i][vitricot] == a[vitridong][vitricot])
		{
			dem++;

			if(dem == 5)
			{
				return a[vitridong][vitricot];
			}
		}
		else 
		{
			break;
		}
	}
	return '.'; 
}

char kiemtra_cheochinh(int n, char a[MAX][MAX], int vitridong, int vitricot)
{
	int dem = 1; // Tính luôn quân vừa đánh xuống

	// Kiểm tra chéo chính trên: Các phần tử dòng - cột luôn giảm 1 đơn vị và giảm đến khi nào 1 trong 2 thằng xuất hiện 0
	int i = vitridong - 1;
	int j = vitricot - 1;
	while(true)
	{
		if(i < 0 || j < 0)
		{
			break; // vị trí xét không hợp lệ
		}

		// Nếu còn chạy xuống đây được thì có nghĩa vị trí i, j hợp lệ
		if(a[i][j] == a[vitridong][vitricot])
		{
			dem++;

			if(dem == 5)
			{
				return a[vitridong][vitricot];
			}
		}
		else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
		{
			break;
		}

		// Xét qua lần lặp mới
		i--;
		j--;
	}

	//	Kiểm tra chéo chính dưới: Các phần tử dòng - cột đều tăng lên 1 đơn vị và tăng đến khi nào 1 trong 2 thằng bằng n - 1 thì dừng lại
	i = vitridong + 1;
	j = vitricot + 1;
	while(true)
	{
		if(i == n || j == n)
		{
			break; // vị trí xét không hợp lệ
		}

		// Nếu còn chạy xuống đây được thì có nghĩa vị trí i, j hợp lệ
		if(a[i][j] == a[vitridong][vitricot])
		{
			dem++;

			if(dem == 5)
			{
				return a[vitridong][vitricot];
			}
		}
		else // chỉ cần phát hiện không còn tính liên tục => dừng quá trình lặp lại
		{
			break;
		}

		// Xét qua lần lặp mới
		i++;
		j++;
	}
	return '.'; // chưa thắng
}

char kiemtra_cheophu(int n, char a[MAX][MAX], int chisodong, int chisocot)
{
    int dem= 1;
    int i = chisodong -1,j = chisocot + 1;
    while(true)
    {
        if(i < 0||j >=n) break;
        if(a[i][j] == a[chisodong][chisocot])
        {
            dem ++;
            if(dem == 5) return a[chisodong][chisocot];
        }
        else break;
        i --; j ++;
    }
    i = chisodong + 1; j = chisocot - 1;
    while(true)
    {
        if(i >= n||j < 0) break;
        if(a[i][j] == a[chisodong][chisocot])
        {
            dem ++;
            if(dem == 5) return a[chisodong][chisocot];
        }
        else break;
        i++;j--;
    }
    return '.';
}

int main()
{
    char a[MAX][MAX];
    ifstream FileIn;
    FileIn.open("input9.txt",ios_base::in);
    int n; FileIn >> n;
    for(int i = 0; i < n; i ++)
    {
        for(int j = 0; j < n ; j ++)
        {
            FileIn >> a[i][j];
           kiemtra(kiemtra_hangngang(n,a,i,j),FileIn);
           kiemtra(kiemtra_hangdoc(n,a,i,j),FileIn);
           kiemtra(kiemtra_cheochinh(n,a,i,j),FileIn);
           kiemtra(kiemtra_cheophu(n,a,i,j),FileIn);
        }
    }
 
    return 0; 
}