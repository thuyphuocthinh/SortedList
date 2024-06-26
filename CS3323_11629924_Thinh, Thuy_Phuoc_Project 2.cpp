// Troy ID: 11629924
// Full name: Thinh, Thuy Phuoc
#include <bits/stdc++.h>

// define Employee class - list item type
class Employee
{
public:
    Employee() {}
    Employee(int employeeId, std::string firstName, std::string lastName, std::string phoneNumber, std::string emailAddress, double salary)
    {
        this->employeeId = employeeId;
        this->firstName = firstName;
        this->lastName = lastName;
        this->phoneNumber = phoneNumber;
        this->emailAddress = emailAddress;
        this->salary = salary;
    }

    int getEmployeeId() const
    {
        return employeeId;
    }

    void setFirstName(std::string firstName)
    {
        this->firstName = firstName;
    }

    std::string getFirstName() const
    {
        return firstName;
    }

    void setLastName(std::string lastName)
    {
        this->lastName = lastName;
    }

    std::string getLastName() const
    {
        return lastName;
    }

    void setPhoneNumber(std::string phoneNumber)
    {
        this->phoneNumber = phoneNumber;
    }

    std::string getPhoneNumber() const
    {
        return phoneNumber;
    }

    void setEmailAddress(std::string emailAddress)
    {
        this->emailAddress = emailAddress;
    }

    std::string getEmailAddress() const
    {
        return emailAddress;
    }

    void setSalary(double salary)
    {
        this->salary = salary;
    }

    double getSalary() const
    {
        return salary;
    }

    std::string getFullName()
    {
        return getFirstName() + " " + getLastName();
    }

private:
    int employeeId;
    std::string firstName;
    std::string lastName;
    std::string phoneNumber;
    std::string emailAddress;
    double salary;
};

// Node of the list
struct Node
{
    Employee *data;
    Node *next;
    Node(Employee *employee)
    {
        data = employee;
        next = NULL;
    }
    Node()
    {
        next = NULL;
    }
};

// define the ADT sorted list
class List
{
public:
    List()
    {
        head = NULL;
        currentPos = NULL;
        length = 0;
    }

    // Insert
    void Insert(Node *employee)
    {
        if (head == NULL)
        {
            head = employee;
            length++;
            return;
        }
        if (!IsFull())
        {
            if (employee->data->getEmployeeId() < head->data->getEmployeeId())
            {
                employee->next = head;
                head = employee;
            }
            else
            {
                Node *precNode = head;
                Node *currentNode = head->next;
                while (currentNode != NULL)
                {
                    if (currentNode->data->getEmployeeId() >= employee->data->getEmployeeId())
                    {
                        break;
                    }
                    precNode = currentNode;
                    currentNode = currentNode->next;
                }
                if (currentNode != NULL)
                {
                    precNode->next = employee;
                    employee->next = currentNode;
                }
                else
                {
                    precNode->next = employee;
                }
            }
            length++;
        }
    }

    // Delete
    void Delete(std::string fullName)
    {
        if (head == NULL)
        {
            std::cout << "List is empty" << "\n";
            return;
        }
        bool found = false;
        if (head->data->getFullName().compare(fullName) == 1)
        {
            Node *temp = head;
            head = head->next;
            found = true;
            delete temp;
        }
        else
        {

            Node *precNode = head;
            Node *currentNode = head->next;
            while (currentNode != NULL)
            {
                if (currentNode->data->getFullName().compare(fullName) == 1)
                {
                    precNode->next = currentNode->next;
                    delete currentNode;
                    found = true;
                    break;
                }
                precNode = currentNode;
                currentNode = currentNode->next;
            }
        }
        if (found)
        {
            length--;
            std::cout << "Deleted successfully" << "\n";
        }
        else
            std::cout << "Not found" << " " << fullName << "\n";
    }

    // ResetList
    void ResetList()
    {
        currentPos = NULL;
    }

    // MakeEmpty
    void MakeEmpty()
    {
        Node *temp = head;
        while (head != NULL)
        {
            head = head->next;
            delete temp;
            temp = head;
        }
        currentPos = NULL;
        length = 0;
    }

    // GetNextItem
    Node *GetNextItem()
    {
        if (currentPos == NULL)
        {
            currentPos = head;
        }
        else
        {
            currentPos = currentPos->next;
        }
        return currentPos;
    }
    // PrintList
    void PrintList(std::string output)
    {
        if (length == 0)
        {
            std::cout << "List is empty" << "\n";
            return;
        }
        std::ofstream outputFile(output);
        Node *currentNode = head;
        while (currentNode != NULL)
        {
            outputFile << currentNode->data->getEmployeeId() << " - " << currentNode->data->getFullName() << " - " << currentNode->data->getPhoneNumber() << " - " << currentNode->data->getEmailAddress() << " - " << currentNode->data->getSalary() << "\n";
            currentNode = currentNode->next;
        }
    }
    // IsFull
    bool IsFull()
    {
        try
        {
            Employee *employee = new Employee();
            delete employee;
            return false;
        }
        catch (std::bad_alloc e)
        {
            std::cout << e.what() << "\n";
            return true;
        }
    }
    // Destructor
    ~List()
    {
        Node *temp = head;
        while (head != NULL)
        {
            head = head->next;
            delete temp;
            temp = head;
        }
        delete currentPos;
    }

private:
    Node *head;
    Node *currentPos;
    int length;
};

// define App class that runs the app
class App
{
public:
    App() {}
    // this function to read file
    void input()
    {
        std::string input;
        std::cout << "Type input file name (no whitespace, including .txt): ";
        std::cin >> input;
        std::ifstream infile(input);
        if (infile.is_open())
        {
            int employeeId;
            std::string firstName;
            std::string lastName;
            std::string phoneNumber;
            std::string emailAddress;
            double salary;
            while (!infile.eof())
            {
                infile >> employeeId >> firstName >> lastName >> phoneNumber >> emailAddress >> salary;
                Employee *employee = new Employee(employeeId, firstName, lastName, phoneNumber, emailAddress, salary);
                Node *node = new Node(employee);
                list.Insert(node);
            }
            infile.clear();
            infile.close();
        }
    }
    // this function to write file
    void output()
    {
        std::string output;
        std::cout << "Type output file name (no whitespace, including .txt): ";
        std::cin >> output;
        list.PrintList(output);
        std::cout << "Done. Please, open the " << output << " file in the same folder to see the result" << "\n";
    }

private:
    List list;
};

int main()
{
    App app;
    app.input();
    app.output();
    return 0;
}