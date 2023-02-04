
//-1 for hurdles
// 0 for start
//-3 for destination
//-2 for rasta

//===========================================================
//
//              #####    #####     ###    #####    ####
//              ##  ##  ##   ##   ## ##   ##  ##   ##  ##
//              #####   ##   ##  ##   ##  #####    ##  ##
//              ##  ##  ##   ##  #######  ##  ##   ##  ##
//              #####    #####   ##   ##  ##   ##  ####
//
//===========================================================

#include <iostream>
#include "queue.cpp"
using namespace std;
class board
{
public:
    int **array;
    int rows;
    int columns;

public:
    // TODO Functions
    board();
    ~board();
    board(int r, int c);
    void load_data();
    void set(int destination);
    void display_board();
    bool set_values(queue &a, int &i, int &j);
    void set_path(int i, int j);
};

board::board()
{
    array = NULL;
    rows = 0;
    columns = 0;
}

board::~board()
{
    if (array != NULL)
    {
        for (int i = 0; i < rows; i++)
            delete[] array[i];
        delete[] array;
        rows = 0;
        columns = 0;
    }
}

board::board(int r, int c)
{
    rows = r;
    columns = c;
    array = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        array[i] = new int[columns];
        for (int j = 0; j < columns; j++)
        {
            array[i][j] = -2;
        }
    }
}

void board::load_data()
{
    srand(time(NULL));
    int total_hurdles = rows * columns / 4;
    while (total_hurdles != 0)
    {
        int random_rows = 0 + rand() % rows;
        int random_columns = 0 + rand() % columns;
        if (array[random_rows][random_columns] == -1)
            ;
        else
        {
            array[random_rows][random_columns] = -1;
            total_hurdles--;
        }
    }
}

void board::set(int destination)
{
    if (destination == 1)
        array[0][0] = -3;
    else if (destination == 3)
        array[rows - 1][0] = -3;
    else if (destination == 2)
        array[0][columns - 1] = -3;
    else if (destination == 4)
        array[rows - 1][columns - 1] = -3;
}

void board::display_board()
{
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->rows; j++)
        {
            cout << this->array[i][j] << "  ";
        }
        cout << endl;
    }
}

bool board::set_values(queue &a, int &q, int &w)
{
    // DRUL
    int i, j, value;
    a.dequeue(i, j, value);
    cout << "Dequeuing: " << i << "," << j << ": " << value << endl;
    // PUSH_DOWN
    if (i >= 0 && i < this->rows - 1 && (this->array[i + 1][j] == -2 || this->array[i + 1][j] == -3))
    {
        cout << "Enqueuing: " << i + 1 << "," << j << ": " << value + 1 << endl;
        a.enqueue(i + 1, j, value + 1);
        if (this->array[i + 1][j] == -3)
        {
            this->array[i + 1][j] = value + 1;
            q = i + 1;
            w = j;
            return true;
        }
        this->array[i + 1][j] = value + 1;
    }

    // PUSH_RIGHT
    if (j >= 0 && j < this->rows - 1 && (this->array[i][j + 1] == -2 || this->array[i][j + 1] == -3))
    {
        cout << "Enqueuing: " << i << "," << j + 1 << ": " << value + 1 << endl;
        a.enqueue(i, j + 1, value + 1);
        if (this->array[i][j + 1] == -3)
        {
            this->array[i][j + 1] = value + 1;
            q = i;
            w = j + 1;
            return true;
        }
        this->array[i][j + 1] = value + 1;
    }

    // PUSH_UP
    if (i > 0 && i <= this->rows - 1 && (this->array[i - 1][j] == -2 || this->array[i - 1][j] == -3))
    {
        cout << "Enqueuing: " << i - 1 << "," << j << ": " << value + 1 << endl;
        a.enqueue(i - 1, j, value + 1);
        if (this->array[i - 1][j] == -3)
        {
            this->array[i - 1][j] = value + 1;
            q = i - 1;
            w = j;
            return true;
        }
        this->array[i - 1][j] = value + 1;
    }

    // PUSH_LEFT
    if (j > 0 && j <= this->rows - 1 && (this->array[i][j - 1] == -2 || this->array[i][j - 1] == -3))
    {
        cout << "Enqueuing: " << i << "," << j - 1 << ": " << value + 1 << endl;
        if (this->array[i][j - 1] == -3)
        {
            this->array[i][j - 1] = value + 1;
            q = i;
            w = j - 1;
            return true;
        }
        a.enqueue(i, j - 1, value + 1);
        this->array[i][j - 1] = value + 1;
    }
    return false;
}

void board::set_path(int i, int j)
{
    int q = i;
    int w = j;
    int times = array[q][w] + 1;
    for (int I = 0; I < times && array[i][j] != 0; I++)
    {
        if (j > 0 && j < rows && array[i][j - 1] == array[i][j] - 1)
        {
            array[i][j] = -5;
            j--;
            continue;
        }
        if (i < rows - 1 && i >= 0 && array[i + 1][j] == array[i][j] - 1)
        {
            array[i][j] = -5;
            i++;
            continue;
        }
        if (j < rows - 1 && j >= 0 && array[i][j + 1] == array[i][j] - 1)
        {
            array[i][j] = -5;
            j++;
            continue;
        }
        if (i > 0 && i < rows && array[i - 1][j] == array[i][j] - 1)
        {
            array[i][j] = -5;
            i--;
            continue;
        }
    }
    for (int I = 0; I < rows; I++)
    {
        for (int J = 0; J < rows; J++)
        {
            if (array[I][J] == -1 || array[I][J] == -5)
                ;
            else
                array[I][J] = -2;
        }
    }
}

// int main()
// {
//     board a(10, 10);
//     a.load_data();
//     a.array[5][5] = -3;
//     a.array[0][0] = 0;
//     queue b(100);
//     b.enqueue(0, 0, 0);
//     char close;
//     // cin >> close;
//     a.display_board();
//     int i, j;
//     while (close != 'x')
//     {
//         // cin >> close;
//         if (a.set_values(b, i, j))
//         {
//             cout << "OH YEAH" << endl;
//             cout << "i: " << i << ",j: " << j << endl;
//             a.set_path(i, j);
//             break;
//         }
//         a.display_board();
//     }
//     a.display_board();
// }