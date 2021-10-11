#include <iostream> 
#include <stdlib.h>
using namespace std;
class Matrix { 
    public:
        Matrix(int row, int col); 
        int GetData();
        Matrix Transpose();
        int Display();
        Matrix Multiply(Matrix b); 
        Matrix Add(Matrix b); 
        Matrix Sub(Matrix b); 
        Matrix Multiply2(Matrix b); 
        int CompareRowCol(Matrix b);
    private:
        int rows, cols;
        int* Term; 
};

Matrix::Matrix(int row, int col) : rows(row), cols(col)
{
    Term = new int[rows * cols]; 
}

int Matrix::GetData() { 
    int input_value;
    cout<<"rows= "<<rows<<" cols= "<<cols<<endl; 
    for (int j = 0; j < rows * cols; j++)
    {
        cout << "term value = "; 
        cin >> input_value;
        cout << " " << endl; 
        Term[j] = input_value;
    }
    return 0; 
}

Matrix Matrix::Transpose() { 
    Matrix b(cols, rows);

    int n = rows * cols;
    for (int i = 0; i < cols; i++) 
    { 
      //To be implemented
      for (int j=0;j<rows;j++){
        b.Term[j + i*rows]=Term[i + j*cols];
      }
    }   
    cout << endl;
    return b;
}

Matrix Matrix::Multiply(Matrix b) {
    if (cols != b.rows) cout << "Incompatible matrices" << endl; 
    Matrix d(rows, b.cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < b.cols; j++) 
        {
            int sum = 0;
            for (int k = 0; k < cols; k++){
              sum += Term[k + i*cols]*b.Term[j+ k*b.cols]; 
            }
            d.Term[j + i*b.cols] = sum;
        }
    }
    return d;
}

Matrix Matrix::Add(Matrix b) {
    if (cols != b.cols) cout << "Incompatible matrices" << endl; 
    if (rows != b.rows) cout << "Incompatible matrices" << endl;
    Matrix d(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j=0; j < cols ; j++){
          d.Term[j + i*cols]=Term[j + i*cols]+b.Term[j + i*cols];
        }
    }
    return d; 
}

Matrix Matrix::Sub(Matrix b) {
    if (cols != b.cols) cout << "Incompatible matrices" << endl; 
    if (rows != b.rows) cout << "Incompatible matrices" << endl;

    Matrix d(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++) {
            d.Term[j + i*cols]=Term[j + i*cols]-b.Term[j + i*cols];
        } 
    }
    return d;
}

Matrix Matrix::Multiply2(Matrix b) {
    if (cols != b.rows) cout << "Incompatible matrices" << endl; 
    Matrix bXpose = b.Transpose();
    Matrix d(rows, b.cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < bXpose.rows; j++) 
        {
            int sum=0;
            for (int k=0; k<cols; k++){
              sum += Term[k + i*cols] * bXpose.Term[k + j*cols]; 
            }
            d.Term[j + i*bXpose.rows] = sum;
        }
    }
    return d;
}

int Matrix::CompareRowCol(Matrix b) {
    if (cols != b.rows) return 1;
    else return 0; 
}

int Matrix::Display() {

    int n;
    n=rows*cols;
    for (int i = 0; i < rows; i++) 
    { 
       for (int j=0; j<cols;j++){
        cout<< Term[j + cols*i]<<" ";
      }
      cout<<endl;
    }
    return 0;
}

int main()
{
    Matrix a(12,13);
    Matrix b(13,14);
    Matrix c(12,14);
    Matrix d(12,14);
    Matrix t(14,13);
    cout << "Enter first matrix: " << endl; 
    a.GetData();
    cout << "Enter second matrix: " << endl; 
    b.GetData();
    cout << "Display first matrix: " << endl; 
    a.Display();
    cout << "Display second matrix: " << endl;
    b.Display();
    t = b.Transpose();
    cout << "Transpose() of Matrix b" << endl; 
    t.Display();

    if (a.CompareRowCol(b)) 
    {
        cout << "Error! column of first matrix not equal to row of second." ;
        cout << "Enter rows and columns for first matrix: " ; 
    }
    c = a.Multiply(b); 
    cout << "Multiply of Matrix a,b" << endl; 
    c.Display(); // instead of   cout << c; 

    d.GetData(); 
    d = c.Sub(d);
    d.Display(); // instead of    cout << d;
    cout << "using transpose()" << endl; 
    t = b.Transpose(); 
    c = a.Multiply2(t); 
    c.Display(); // instead of   cout << c;
    
    c = a.Multiply2(b);
    c.Display();
    
    system("pause");
    return 0;
}

