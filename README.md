# C++ Order Matching Engine v1.0

Hello! I built this project to dive deep into the world of high-performance computing and finance. It's a simulation of the core engine that powers every modern stock exchange, built from scratch in C++. My goal was to tackle a complex, real-world problem while mastering fundamental data structures and professional software engineering practices.

---

### 🚀 Live Demo

Here’s a quick look at the engine in action: placing buy and sell orders, seeing an instant trade execution, and then displaying the updated, real-time order book.

*(**Pro Tip:** Use a free tool like `asciinema` or `termtoscreen` to record your terminal session, then convert it to a GIF and upload it here. It's incredibly impressive to recruiters.)*



---

### ✅ Core Features

* **Real-Time Matching Engine:** The engine instantly matches `BUY` and `SELL` limit orders based on **price-time priority**. It correctly handles both full and partial fills.
* **Robust Order Management:** You can place new orders or cancel existing ones. The system is designed to maintain perfect data integrity, even during complex trade scenarios.
* **Accurate Order Book Display:** A clean, formatted, and real-time view of the order book, showing all active bids and asks sorted for clarity.
* **Intelligent Input Handling:** The command-line interface is built to be robust, gracefully handling invalid commands and logically incorrect orders (like those with a negative price or quantity).

---

### 🧠 Architectural Decisions & The "Why"

Building a trading engine is a game of efficiency. Every design choice was made with performance and correctness in mind.

#### **1. The Order Book: Finding the Best Price Instantly**
* **The Challenge:** In a sea of thousands of orders, how do you find the highest bid and the lowest ask in O(1) time? A simple list or vector would be far too slow.
* **The Solution:** I used two **`std::priority_queue`** heaps.
    * A **Max-Heap** for buy orders (bids), keeping the highest price at the top.
    * A **Min-Heap** for sell orders (asks), keeping the lowest price at the top.
    * This structure guarantees that the best possible trade is always ready to be matched in constant time.

#### **2. Order Tracking: The Need for Speed**
* **The Challenge:** When a user wants to cancel an order, how do you find it instantly without searching the entire heap?
* **The Solution:** I implemented a master **`std::unordered_map`** that acts as a central record keeper, mapping a unique `long long` Order ID to its corresponding `Order` object. This provides O(1) average time complexity for lookups.

#### **3. Cancellation: The "Lazy Deletion" Strategy**
* **The Challenge:** You can't efficiently remove an item from the middle of a heap.
* **The Solution:** I implemented the **"lazy deletion"** pattern. When an order is cancelled, it's simply flagged as `isCancelled = true` in the `unordered_map`. The engine then has a "garbage collection" routine that discards these "ghost" orders only when they naturally reach the top of a heap, avoiding any costly reorganizations.

---

### 🛠️ Getting Started

#### Prerequisites
You'll need a C++ compiler (g++ is recommended).

#### Compilation & Execution
1.  Clone this repository to your local machine.
2.  Navigate to the project directory.
3.  Compile the source files:
    ```bash
    g++ main.cpp OrderBook.cpp -o main
    ```
4.  Run the engine:
    ```bash
    ./main
    ```

---

### 💡 Future Ideas
This project has a solid foundation that could be extended with even more advanced features, such as:
* Implementing "Market Orders" and other common order types.
* Logging all executed trades to a persistent file for auditing.
* Exposing the order book data via a simple web API.
