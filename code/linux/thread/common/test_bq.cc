#include "ring_queue.hpp"

ring_queue<string> rq(1);

void* product(void* arg)
{
    string val = static_cast<const char*>(arg);
    rq.push(val);
    return nullptr;
}

void* consume(void* arg)
{
    cout << rq.pop() << endl;
    return nullptr;
}

int  main()
{
    pthread_t p1, p2, p3, p4, p5, p6;
    pthread_t c1, c2, c3, c4, c5, c6;

    pthread_create(&p1, nullptr, product, (void*)"product1");
    pthread_create(&p2, nullptr, product, (void*)"product2");
    pthread_create(&p3, nullptr, product, (void*)"product3");
    pthread_create(&p4, nullptr, product, (void*)"product4");
    pthread_create(&p5, nullptr, product, (void*)"product5");
    pthread_create(&p6, nullptr, product, (void*)"product6");

    pthread_create(&c1, nullptr, consume, nullptr);
    pthread_create(&c2, nullptr, consume, nullptr);
    pthread_create(&c3, nullptr, consume, nullptr);
    pthread_create(&c4, nullptr, consume, nullptr);
    pthread_create(&c5, nullptr, consume, nullptr);
    pthread_create(&c6, nullptr, consume, nullptr);

    pthread_join(p1, nullptr);
    pthread_join(p2, nullptr);
    pthread_join(p3, nullptr);
    pthread_join(p4, nullptr);
    pthread_join(p5, nullptr);
    pthread_join(p6, nullptr);

    pthread_join(c1, nullptr);
    pthread_join(c2, nullptr);
    pthread_join(c3, nullptr);
    pthread_join(c4, nullptr);
    pthread_join(c5, nullptr);
    pthread_join(c6, nullptr);
    return 0;
}
