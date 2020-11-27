#include <atomic>
#include <thread>
#include <assert.h>
#include <iostream>

std::atomic<bool> x, y;
std::atomic<int> z;
int a =0;
int b =0;
int c =0;
int d =0;
int e =0;
int f =0;
int g =0;
int h =0;
void write_x_then_y()
{   
     a =1;
     b =1;
     c =1;
     d =1;
     e =1;
     f =1;
     g =1;
     h =1;
	// x.store(true, std::memory_order_relaxed); // 1
	y.store(true, std::memory_order_relaxed); // 2
}

void read_y_then_x()
{
	while(!y.load(std::memory_order_relaxed));
    {
        std::cout << "a :" <<a<<std::endl;
        std::cout << "b :" <<b<<std::endl;
        std::cout << "c :" <<c<<std::endl;
        std::cout << "d :" <<d<<std::endl;
        std::cout << "e :" <<e<<std::endl;
        std::cout << "f :" <<f<<std::endl;
        std::cout << "g :" <<g<<std::endl;
    } // 3
	// if(x.load(std::memory_order_relaxed)) // 4
	// 	++z;
}

int main()
{
	x = false;
	y = false;
	z = 0;
    std::move()
	std::thread a(write_x_then_y);
	std::thread b(read_y_then_x);
	a.join();
	b.join();
	// assert(z.load()!= 0); // 5
}