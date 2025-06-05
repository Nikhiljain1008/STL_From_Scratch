#include "../include/vector.hpp"
#include "../include/map.hpp"
#include "../include/set.hpp"
#include "../include/stack.hpp"
#include "../include/queue.hpp"
#include "../include/linkedlist.hpp"
#include <string>
#include <iostream>

using namespace std;

void testVector() {
    cout << "\n=== TESTING VECTOR ===\n";
    
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.print(); // [ 10 20 30 ]
    
    cout << "Size: " << v.size() << ", Capacity: " << v.capacity() << "\n";
    
    v.pop_back();
    v.print(); // [ 10 20 ]
    
    Vector<int> v2 = std::move(v);
    cout << "After move:\n";
    v2.print(); // [ 10 20 ]
    v.print();  // [ ] (empty after move)
    
    Vector<string> svec;
    svec.push_back("Hello");
    svec.push_back("World");
    svec.push_back("C++");
    svec.print(); // [ Hello World C++ ]
}

void testMap() {
    cout << "\n=== TESTING MAP ===\n";
    
    Map<string, int> m;
    m.insert("apple", 5);
    m.insert("banana", 3);
    m.insert("orange", 8);
    m.print();
    
    cout << "Size: " << m.size() << "\n";
    
    // Test operator[]
    m["grape"] = 12;
    m["apple"] = 7; // Update existing
    m.print();
    
    // Test find
    auto* val = m.find("banana");
    if (val) cout << "Found banana: " << *val << "\n";
    
    m.erase("orange");
    cout << "After erasing orange:\n";
    m.print();
    
    // Test with move semantics
    Map<int, string> m2;
    m2.insert(1, "One");
    m2.insert(2, "Two");
    m2.insert(3, "Three");
    
    Map<int, string> m3 = std::move(m2);
    cout << "After move:\n";
    m3.print();
    cout << "Original map size: " << m2.size() << "\n";
}

void testSet() {
    cout << "\n=== TESTING SET ===\n";
    
    Set<int> s;
    s.insert(15);
    s.insert(10);
    s.insert(20);
    s.insert(8);
    s.insert(12);
    s.insert(25);
    s.insert(10); // Duplicate, should not be inserted
    s.print();
    
    cout << "Size: " << s.size() << "\n";
    cout << "Contains 10: " << (s.contains(10) ? "Yes" : "No") << "\n";
    cout << "Contains 100: " << (s.contains(100) ? "Yes" : "No") << "\n";
    
    s.erase(10);
    cout << "After erasing 10:\n";
    s.print();
    
    Set<string> ss;
    ss.insert("zebra");
    ss.insert("apple");
    ss.insert("banana");
    ss.insert("cherry");
    ss.print(); // Should be sorted
}

void testStack() {
    cout << "\n=== TESTING STACK ===\n";
    
    Stack<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.print();
    
    cout << "Size: " << st.size() << "\n";
    cout << "Top: " << st.top() << "\n";
    
    st.pop();
    st.print();
    cout << "New top: " << st.top() << "\n";
    
    Stack<string> sst;
    sst.push("First");
    sst.push("Second");
    sst.push("Third");
    sst.print();
    
    // Test move semantics
    Stack<string> sst2 = std::move(sst);
    cout << "After move:\n";
    sst2.print();
    cout << "Original stack size: " << sst.size() << "\n";
}

void testQueue() {
    cout << "\n=== TESTING QUEUE ===\n";
    
    Queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.print();
    
    cout << "Size: " << q.size() << "\n";
    cout << "Front: " << q.front() << ", Back: " << q.back() << "\n";
    
    q.pop();
    q.print();
    cout << "New front: " << q.front() << "\n";
    
    Queue<string> sq;
    sq.push("Task1");
    sq.push("Task2");
    sq.push("Task3");
    sq.print();
    
    while (!sq.empty()) {
        cout << "Processing: " << sq.front() << "\n";
        sq.pop();
    }
    cout << "Queue is now empty: " << (sq.empty() ? "Yes" : "No") << "\n";
}

void testLinkedList() {
    cout << "\n=== TESTING LINKEDLIST ===\n";
    
    LinkedList<int> ll;
    ll.push_back(1);
    ll.push_back(2);
    ll.push_back(3);
    ll.print();
    
    ll.push_front(0);
    ll.print();
    
    cout << "Size: " << ll.size() << "\n";
    cout << "Front: " << ll.front() << ", Back: " << ll.back() << "\n";
    
    // Test indexing
    cout << "Element at index 2: " << ll[2] << "\n";
    
    // Test insertion
    ll.insert(2, 99);
    ll.print();
    
    // Test deletion
    ll.erase(1);
    ll.print();
    
    ll.pop_front();
    ll.pop_back();
    ll.print();
    
    LinkedList<string> sll;
    sll.push_back("A");
    sll.push_back("B");
    sll.push_back("C");
    sll.push_front("Start");
    sll.print();
    
    // Test move semantics
    LinkedList<string> sll2 = std::move(sll);
    cout << "After move:\n";
    sll2.print();
    cout << "Original list size: " << sll.size() << "\n";
}

void performanceTest() {
    cout << "\n=== PERFORMANCE TEST ===\n";
    
    // Test with larger data sets
    Vector<int> big_vector;
    for (int i = 0; i < 1000; ++i) {
        big_vector.push_back(i);
    }
    cout << "Vector with 1000 elements - Size: " << big_vector.size() 
         << ", Capacity: " << big_vector.capacity() << "\n";
    
    Set<int> big_set;
    for (int i = 999; i >= 0; --i) { // Insert in reverse order to test balancing
        big_set.insert(i);
    }
    cout << "Set with 1000 elements - Size: " << big_set.size() << "\n";
    
    Map<int, string> big_map;
    for (int i = 0; i < 100; ++i) {
        big_map.insert(i, "Value" + to_string(i));
    }
    cout << "Map with 100 elements - Size: " << big_map.size() << "\n";
}

void testEdgeCases() {
    cout << "\n=== TESTING EDGE CASES ===\n";
    
    // Empty containers
    Vector<int> empty_vec;
    cout << "Empty vector size: " << empty_vec.size() << "\n";
    
    Stack<int> empty_stack;
    cout << "Empty stack size: " << empty_stack.size() << "\n";
    
    Queue<int> empty_queue;
    cout << "Empty queue: " << (empty_queue.empty() ? "Yes" : "No") << "\n";
    
    Set<int> empty_set;
    cout << "Empty set contains 1: " << (empty_set.contains(1) ? "Yes" : "No") << "\n";
    
    Map<int, int> empty_map;
    cout << "Empty map size: " << empty_map.size() << "\n";
    
    LinkedList<int> empty_list;
    cout << "Empty list size: " << empty_list.size() << "\n";
    
    // Test single element operations
    Vector<int> single_vec;
    single_vec.push_back(42);
    single_vec.pop_back();
    cout << "Single element vector after pop: size = " << single_vec.size() << "\n";
    
    Stack<int> single_stack;
    single_stack.push(42);
    cout << "Single stack top: " << single_stack.top() << "\n";
    single_stack.pop();
    cout << "Single stack after pop: empty = " << (single_stack.empty() ? "Yes" : "No") << "\n";
}

int main() {
    cout << "========================================\n";
    cout << "    CUSTOM CONTAINER LIBRARY TEST\n";
    cout << "========================================\n";
    
    try {
        testVector();
        testMap();
        testSet();
        testStack();
        testQueue();
        testLinkedList();
        performanceTest();
        testEdgeCases();
        
        cout << "\n========================================\n";
        cout << "    ALL TESTS COMPLETED SUCCESSFULLY!\n";
        cout << "========================================\n";
        
    } catch (const exception& e) {
        cout << "Error during testing: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
} 