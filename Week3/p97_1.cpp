//1번
#include <iostream>

int main() {
    for(int i = 1; i <= 5; ++i)
    {
        for(int j = 1; j <= i; ++j)
        {
            std::cout << j << " ";
        }
        std::cout << "\n";
    }
}

//2번
#include <iostream>

int main() {
    for(int i = 1; i <= 5; ++i)
    {
        for(int j = 5; j >= i; --j)
        {
            std::cout << j << " ";
        }
        std::cout << "\n";
    }
}

//3번
#include <iostream>

int main() {
    for(int i = 1; i <= 6; ++i)
    {
        for(int j = 0; j <= 5-i; ++j)
        {
            std::cout << "  ";
        }

        for(int j = i-1; j >= 1; --j)
        {
            std::cout << j << " ";
        }
        std::cout << "\n";
    }
}

//4번
#include <iostream>

int main() {
    for(int i = 1; i <= 6; ++i)
    {
        for(int j = 0; j <= 5-i; ++j)
        {
            std::cout << "  ";
        }
        
        for(int j = i-1; j >= 2; --j)
        {
            std::cout << j << " ";
        }

        for(int j = 1; j <= i-1; ++j)
        {
            std::cout << j << " ";
        }
        std::cout << "\n"; 
    }
}