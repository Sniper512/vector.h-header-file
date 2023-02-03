#if !defined(VECTOR_H)
#define VECTOR_H
#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
using namespace std;

template <typename general>
class Vector
{
private:
    general data;
    Vector *next;
    Vector *head = nullptr;

public:
    Vector()
    {
    }

    Vector(unsigned int size)
    {
        for (int i = 0; i < size; i++)
        {
            push_back(0);
        }
    }

    ~Vector()
    {
        this->clear();
    }
    void clear()
    {
        Vector *temp;
        if (head == nullptr)
        {
            return;
        }
        while (this->size() > 0)
        {
            this->pop_back();
        }
    }

    int empty()
    {
        if (head == nullptr)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    int size()
    {
        unsigned int count = 0;
        Vector *temp = head;
        while (temp != nullptr)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }

    general &operator[](unsigned int index)
    {
        if (index >= size())
        {
            throw out_of_range("index out of range!");
        }
        Vector *temp = head;
        for (unsigned int i = 0; i < index; i++)
        {
            temp = temp->next;
        }
        return temp->data;
    }

    void push_back(general value)
    {
        Vector *node = (class Vector *)malloc(sizeof(class Vector));
        node->data = value;
        node->next = nullptr;
        if (head == nullptr)
        {
            head = node;
        }
        else
        {
            Vector *temp = head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = node;
        }
    }

    Vector(vector<general> vec)
    {
        for (general &i : vec)
        {
            push_back(i);
        }
    }

    void push_front(general value)
    {
        if (head == nullptr)
        {
            Vector *node = (class Vector *)malloc(sizeof(class Vector));
            node->data = value;
            node->next = nullptr;
            head = node;
        }
        else
        {
            Vector *node = (class Vector *)malloc(sizeof(class Vector));
            node->data = value;
            node->next = head;
            head = node;
        }
    }

    void pop_back()
    {
        Vector *temp = head;
        if (temp->next == nullptr)
        {
            head = head->next;
            free(temp);
            return;
        }
        while (temp->next->next != nullptr)
        {
            temp = temp->next;
        }
        free(temp->next->next);
        temp->next = nullptr;
    }

    general &at(unsigned int index)
    {
        Vector *temp = head;
        if (temp == nullptr)
        {
            throw out_of_range("index out of range!");
        }
        for (unsigned int i = 0; i < index; i++)
        {
            temp = temp->next;
        }
        if (temp == nullptr)
        {
            throw out_of_range("index out of range!");
        }
        return temp->data;
    }

    void pop_front()
    {
        head = head->next;
    }

    void insert(unsigned int index, general value)
    {

        Vector *temp = head;
        int counter = 0;
        bool check = false;
        while (temp != nullptr)
        {
            if (counter == index)
            {
                check = true;
                break;
            }
            else
            {
                temp = temp->next;
                counter++;
            }
        }
        if (check == true)
            temp->data = value;
        else
            cout << "Index out of range." << endl;
    }

    void remove(general value)
    {
        Vector *temp = head;
        Vector *prev = nullptr;
        bool check = false;
        if (head != nullptr && temp->data == value)
        {
            head = temp->next;
            delete (temp);
            return;
        }
        while (temp != nullptr && temp->data != value)
        {
            prev = temp;
            temp = temp->next;
        }
        if (temp == nullptr)
        {
            cout << "Value not Found.";
            return;
        }
        prev->next = temp->next;
        delete (temp);
    }
    void set_size(unsigned int size)
    {
        for (int i = 0; i < size; i++)
        {
            this->push_back(0);
        }
    }
    int search(general value)
    {
        Vector *temp = head;
        unsigned int counter = 0;
        while (temp != nullptr)
        {
            if (temp->data == value)
            {
                return counter;
            }
            else
            {
                temp = temp->next;
                counter++;
            }
        }
        return -1;
    }

    void printList()
    {
        Vector *node = head;
        while (node != nullptr)
        {
            cout << node->data << " ";
            node = node->next;
        }
    }

    Vector &operator=(Vector &vec)
    {
        if (this == &vec)
        {
            return *this;
        }
        Vector *temp = vec.head;
        while (temp != nullptr)
        {
            this->push_back(temp->data);
            temp = temp->next;
        }
        return *this;
    }
    void sort(unsigned int move)
    {
        for (int i = 0; i < this->size(); i++)
        {
            for (int j = i; j < this->size(); j++)
            {
                if (move == 0 && (this->at(i) > this->at(j)))
                {
                    general hold = this->at(i);
                    this->at(i) = this->at(j);
                    this->at(j) = hold;
                }
                else if (move == 1 && (this->at(i) < this->at(j)))
                {
                    general hold = this->at(i);
                    this->at(i) = this->at(j);
                    this->at(j) = hold;
                }
            }
        }
    }
    void resize(unsigned int new_size)
    {
        if (this->size() < new_size)
        {
            int increase = new_size - this->size();
            for (int i = 0; i < increase; i++)
            {
                push_back(0);
            }
        }
        else if (this->size() > new_size)
        {
            int decrease = this->size() - new_size;
            for (int i = 0; i < decrease; i++)
            {
                pop_back();
            }
        }
    }
    void rotate(int moves)
    {
        if (moves >= 0)
        {
            for (int i = 0; i < moves; i++)
            {
                general holder = this->at(size() - 1);
                for (int j = this->size() - 1; j > 0; j--)
                {
                    this->at(j) = this->at(j - 1);
                }
                this->at(0) = holder;
            }
        }
        else if (moves < 0)
        {
            for (int i = 0; i > moves; i--)
            {
                general holder = this->at(0);
                for (int j = 0; j < this->size() - 1; j++)
                {
                    this->at(j) = this->at(j + 1);
                }
                this->at(size() - 1) = holder;
            }
        }
    }
    general *find(general value)
    {
        Vector *temp = head;
        while (temp != nullptr)
        {
            if (temp->data == value)
            {
                return &temp->data;
            }
            else
            {
                temp = temp->next;
            }
        }
        return nullptr;
    }
    unsigned int count(general value)
    {
        Vector *temp = head;
        unsigned int count = 0;
        while (temp != nullptr)
        {
            if (temp->data == value)
            {
                count++;
            }
            temp = temp->next;
        }
        return count;
    }
    int binarysearch(general value)
    {
        sort(0);
        bool check = false;
        int start = this->at(0);
        int end = this->size() - 1;
        while (start <= end)
        {
            int mid = start + (end - start) / 2;

            if (this->at(mid) == value)
                return mid;

            if (this->at(mid) < value)
                start = mid + 1;

            else
                end = mid - 1;
        }

        return -1;
    }
    void copy(Vector<general> &vec)
    {
        this->clear();
        for (int i = 0; i < vec.size(); i++)
        {
            this->push_back(vec.at(i));
        }
    }
    int in(general value)
    {
        int check = 0;
        Vector *temp = head;
        while (temp != nullptr)
        {
            if (temp->data == value)
            {
                check = 1;
                break;
            }
            temp = temp->next;
        }
        return check;
    }

    void unique()
    {
        Vector<general> temp;
        for (int i = 0; i < this->size(); i++)
        {
            if (temp.in(this->at(i)) == 0)
            {
                temp.push_back(this->at(i));
            }
        }
        this->clear();
        this->copy(temp);
    }

    general *begin()
    {
        return &head->data;
    }
    general *end()
    {
        Vector *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        return &temp->data;
    }
    general front()
    {
        return head->data;
    }
    general back()
    {
        Vector *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        return temp->data;
    }

    void fill(general value)
    {
        Vector *temp = head;
        while (temp != nullptr)
        {
            temp->data = value;
            temp = temp->next;
        }
    }
};
#endif
