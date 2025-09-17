#include <iostream>
#include <atomic>
#include <utility>

template <typename T>
class SharedPtr; // forward declaration
template <typename T>
class WeakPtr;   // forward declaration

template <typename T>
class ControlBlock {
public:
    std::atomic<size_t> shared_count;
    std::atomic<size_t> weak_count;
    T* ptr;

    explicit ControlBlock(T* p) : shared_count(1), weak_count(1), ptr(p) {}
};

// ------------------- SharedPtr -------------------
template <typename T>
class SharedPtr {
    ControlBlock<T>* ctrl;

    void release() {
        if (!ctrl) return;

        // decrement shared_count
        if (ctrl->shared_count.fetch_sub(1, std::memory_order_acq_rel) == 1) {
            delete ctrl->ptr;  // delete object

            // decrement weak_count because shared_ptr held implicit +1
            if (ctrl->weak_count.fetch_sub(1, std::memory_order_acq_rel) == 1) {
                delete ctrl;   // delete control block if no weak_ptr
            }
        }
        ctrl = nullptr;
    }

public:
    void release();
    explicit SharedPtr(T* p = nullptr) {
        ctrl = p ? new ControlBlock<T>(p) : nullptr;
    }

    // Copy constructor
    SharedPtr(const SharedPtr& other) {
        ctrl = other.ctrl;
        if (ctrl)
            ctrl->shared_count.fetch_add(1, std::memory_order_relaxed);
    }

    // Move constructor
    SharedPtr(SharedPtr&& other) noexcept {
        ctrl = other.ctrl;
        other.ctrl = nullptr;
    }

    // Construct from WeakPtr
    explicit SharedPtr(const WeakPtr<T>& wp) {
        ctrl = wp.ctrl;
        if (ctrl) {
            size_t count = ctrl->shared_count.load(std::memory_order_relaxed);
            while (count != 0) {
                if (ctrl->shared_count.compare_exchange_weak(
                        count, count + 1, std::memory_order_acq_rel)) {
                    return; // successfully promoted
                }
                // count updated automatically by compare_exchange_weak
            }
            // object expired
            ctrl = nullptr;
        }
    }

    // Copy assignment
    SharedPtr& operator=(const SharedPtr& other) {
        if (this != &other) {
            release();
            ctrl = other.ctrl;
            if (ctrl)
                ctrl->shared_count.fetch_add(1, std::memory_order_relaxed);
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

    ~SharedPtr() { release(); }

    T* get() const { return ctrl ? ctrl->ptr : nullptr; }
    T& operator*() const { return *ctrl->ptr; }
    T* operator->() const { return ctrl->ptr; }
    size_t use_count() const { return ctrl ? ctrl->shared_count.load() : 0; }
    explicit operator bool() const { return get() != nullptr; }

    friend class WeakPtr<T>;
};

// ------------------- WeakPtr -------------------
template <typename T>
class WeakPtr {
    ControlBlock<T>* ctrl;

    void release() {
        if (!ctrl) return;
        if (ctrl->weak_count.fetch_sub(1, std::memory_order_acq_rel) == 1 &&
            ctrl->shared_count.load(std::memory_order_relaxed) == 0) {
            delete ctrl; // delete control block if no shared_ptr
        }
        ctrl = nullptr;
    }

public:
    WeakPtr() : ctrl(nullptr) {}

    // Construct from SharedPtr
    WeakPtr(const SharedPtr<T>& sp) {
        ctrl = sp.ctrl;
        if (ctrl)
            ctrl->weak_count.fetch_add(1, std::memory_order_relaxed);
    }

    // Copy constructor
    WeakPtr(const WeakPtr& other) {
        ctrl = other.ctrl;
        if (ctrl)
            ctrl->weak_count.fetch_add(1, std::memory_order_relaxed);
    }

    // Move constructor
    WeakPtr(WeakPtr&& other) noexcept {
        ctrl = other.ctrl;
        other.ctrl = nullptr;
    }

    // Copy assignment
    WeakPtr& operator=(const WeakPtr& other) {
        if (this != &other) {
            release();
            ctrl = other.ctrl;
            if (ctrl)
                ctrl->weak_count.fetch_add(1, std::memory_order_relaxed);
        }
        return *this;
    }

    // Move assignment
    WeakPtr& operator=(WeakPtr&& other) noexcept {
        if (this != &other) {
            release();
            ctrl = other.ctrl;
            other.ctrl = nullptr;
        }
        return *this;
    }

    ~WeakPtr() { release(); }

    size_t use_count() const { return ctrl ? ctrl->shared_count.load() : 0; }
    bool expired() const { return use_count() == 0; }

    SharedPtr<T> lock() const { return SharedPtr<T>(*this); }
};

// ------------------- Example -------------------
struct Foo {
    Foo() { std::cout << "Foo constructed\n"; }
    ~Foo() { std::cout << "Foo destroyed\n"; }
    void hello() { std::cout << "Hello from Foo\n"; }
};

int main() {
    SharedPtr<Foo> sp1(new Foo());
    std::cout << "use_count = " << sp1.use_count() << "\n";

    WeakPtr<Foo> wp1 = sp1; // create weak_ptr
    {
        SharedPtr<Foo> sp2 = sp1;
        SharedPtr<Foo> sp3;
        sp3 = sp2;

        std::cout << "use_count = " << sp1.use_count() << "\n";
        sp2->hello();
    }

    std::cout << "use_count after scope = " << sp1.use_count() << "\n";

    if (auto sp_from_wp = wp1.lock()) {
        std::cout << "Locked weak_ptr, use_count = " << sp_from_wp.use_count() << "\n";
        sp_from_wp->hello();
    }

    sp1.release();
    std::cout << "sp1 released\n";

    if (wp1.expired()) {
        std::cout << "Weak pointer expired\n";
    }
}
