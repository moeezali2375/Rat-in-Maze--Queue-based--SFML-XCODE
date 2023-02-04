//=========================================================
//
//               #####   ##   ##  #####  ##   ##  #####
//              ##   ##  ##   ##  ##     ##   ##  ##
//              ##   ##  ##   ##  #####  ##   ##  #####
//               #####   ##   ##  ##     ##   ##  ##
//              ##        #####   #####   #####   #####
//
//=========================================================

#include <iostream>
using namespace std;
class queue
{
    int *i_array;
    int *j_array;
    int *value_array;
    int front;
    int last;
    int size;

public:
    queue(int size)
    {
        this->size = size;
        i_array = new int[size];
        j_array = new int[size];
        value_array = new int[size];
        front = -1;
        last = -1;
    }
    ~queue()
    {
        delete[] i_array;
        delete[] j_array;
        delete[] value_array;
    }
    void enqueue(int i, int j, int value)
    {
        if (front == -1 && last == -1)
        {
            front = 0;
            last = 0;
        }
        i_array[last] = i;
        j_array[last] = j;
        value_array[last] = value;
        last++;
    }
    void dequeue(int &i, int &j, int &value)
    {
        if (last == 0 || front == last)
        {
            cout << "EXCEPTION!" << endl;
            return;
        }
        else
        {
            i = i_array[front];
            j = j_array[front];
            value = value_array[front];
            front++;
        }
    }
    void display_queue()
    {
        for (int i = front; i < last; i++)
        {
            cout << i_array[i] << "," << j_array[i] << ": " << value_array[i] << endl;
        }
    }
};

// int main()
// {
//     queue a(10);
//     a.enqueue(0, 0, 0);
//     a.enqueue(0, 1, 1);
//     a.enqueue(1, 0, 1);
//     a.display_queue();
//     int i, j, val;
//     a.dequeue(i, j, val);
//     a.display_queue();
//     cout << "I: " << i << ",J: " << j << ": " << val;
// }