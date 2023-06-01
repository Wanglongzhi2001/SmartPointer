#include "shared_ptr.h"
#include <cassert>
#include <string>
#include <iostream>

void test_pointer_constructor()
{
    mysharedsptr::shared_ptr<int> sp1(new int(10));
    assert(*sp1 == 10);
}

void test_copy_assignment()
{
    mysharedsptr::shared_ptr<int> sp1(new int(10));
    mysharedsptr::shared_ptr<int> sp2;
    sp2 = sp1;

    assert(*sp1 == 10);
    assert(*sp2 == *sp1);
    assert(sp1.use_count() == 2);
    assert(sp2.use_count() == 2);
}

void test_copy_construction()
{
    mysharedsptr::shared_ptr<int> sp1(new int(10));
    mysharedsptr::shared_ptr<int> sp2(sp1);

    assert(*sp1 == 10);
    assert(*sp2 == *sp1);
    assert(sp1.use_count() == 2);
    assert(sp2.use_count() == 2);
}

void test_get()
{
    mysharedsptr::shared_ptr<int> sp1(new int(10));
    assert(&(*sp1) == sp1.get());
}


void test_swap()
{
    mysharedsptr::shared_ptr<int> sp1(new int(10));
    mysharedsptr::shared_ptr<int> sp2(new int(20));

    mysharedsptr::swap(sp1, sp2);
    assert(*sp1 == 20);
    assert(*sp2 == 10);
}

void test_make_shared()
{
    mysharedsptr::shared_ptr<int> sp = mysharedsptr::make_shared<int>(10);
    assert(*sp == 10);
}

int main()
{
    test_pointer_constructor();
    test_copy_assignment();
    test_copy_construction();
    test_get();
    test_swap();
    test_make_shared();
    return 0;
}