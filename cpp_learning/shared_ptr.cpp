#include <iostream>
#include <atomic>
#include <utility>

template <typename T>
class SharedPtr {
    struct ControlBlock {
        std::atomic<size_t> ref_count;
        T* ptr;

        ControlBlock(T* p) : ref_count(1), ptr(p) {}
    };

    ControlBlock* ctrl;

public:
    // Constructor
    explicit SharedPtr(T* p = nullptr) {
        if (p) ctrl = new ControlBlock(p);
        else ctrl = nullptr;
    }

    // Copy constructor
    SharedPtr(const SharedPtr& other) {
        ctrl = other.ctrl;
        if (ctrl) {
            ctrl->ref_count.fetch_add(1, std::memory_order_relaxed);
        }
    }

    // Move constructor
    SharedPtr(SharedPtr&& other) noexcept {
        ctrl = other.ctrl;
        other.ctrl = nullptr;
    }

    // Copy assignment
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            ctrl = other.ctrl;
            if (ctrl) {
                ctrl->ref_count.fetch_add(1, std::memory_order_relaxed);
            }
        }
        return *this;
    }

    // Move assignment
    SharedPtr& operator=(SharedPtr&& other) noexcept {
        if (this != &other) {
            release();
            ctrl = other.ctrl;
            other.ctrl = nullptr;
        }
        return *this;
    }

    // Destructor
    ~SharedPtr() {
        release();
    }

    // Helper to release ownership
    void release() {
        if (ctrl) {
            if (ctrl->ref_count.fetch_sub(1, std::memory_order_acq_rel) == 1) {
                delete ctrl->ptr;   // delete managed object
                delete ctrl;        // delete control block
            }
            ctrl = nullptr;
        }
    }

    // Accessors
    T* get() const { return ctrl ? ctrl->ptr : nullptr; }
    T& operator*() const { return *ctrl->ptr; }
    T* operator->() const { return ctrl->ptr; }

    size_t use_count() const {
        return ctrl ? ctrl->ref_count.load(std::memory_order_relaxed) : 0;
    }

    explicit operator bool() const { return get() != nullptr; }
};

#include <thread>
#include <vector>

struct Foo {
    Foo()  { std::cout << "Foo constructed\n"; }
    ~Foo() { std::cout << "Foo destroyed\n"; }
    void hello() { std::cout << "Hello from Foo\n"; }
};

int main() {
    SharedPtr<Foo> sp1(new Foo());       // construct
    std::cout << "use_count = " << sp1.use_count() << "\n";

    {
        SharedPtr<Foo> sp2 = sp1;        // copy → increases count
        std::cout << "use_count = " << sp1.use_count() << "\n";

        SharedPtr<Foo> sp3;              
        sp3 = sp2;                       // assignment → increases count
        std::cout << "use_count = " << sp1.use_count() << "\n";

        sp2->hello();                    // use like normal pointer
        (*sp3).hello();
    } // sp2 and sp3 destroyed → count decrements automatically

    std::cout << "use_count after scope = " << sp1.use_count() << "\n";

    sp1.release(); // manually drop last reference
    std::cout << "sp1 released\n";
}

// int main() {
//     SharedPtr<Foo> sp1(new Foo());

//     std::cout << "use_count = " << sp1.use_count() << "\n";

//     {
//         SharedPtr<Foo> sp2 = sp1;  // copy
//         std::cout << "use_count = " << sp1.use_count() << "\n";

//         // Launch multiple threads that copy sp1
//         std::vector<std::thread> threads;
//         for (int i = 0; i < 5; ++i) {
//             threads.emplace_back([sp1]() mutable {
//                 SharedPtr<Foo> local = sp1;
//                 local->hello();
//             });
//         }

//         for (auto& t : threads) t.join();

//         std::cout << "use_count after threads = " << sp1.use_count() << "\n";
//     }

//     std::cout << "use_count after sp2 destroyed = " << sp1.use_count() << "\n";
// } // last sp1 destroyed → Foo destroyed
